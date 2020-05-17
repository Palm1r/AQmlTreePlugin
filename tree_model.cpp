#include "tree_model.h"

#include <QDebug>

constexpr int COLUMNS = 1;

TreeModel::TreeModel(QObject *parent) : QAbstractItemModel(parent) {
  QVariantList rootData;
  rootData << roleNames()[NameRole] << roleNames()[DataRole];
  _rootItem = std::make_shared<TreeItem>(rootData);
}

int TreeModel::rowCount(const QModelIndex &parent) const {
  if (!parent.isValid()) return _rootItem->childCount();
  TreeItem *p = static_cast<TreeItem *>(parent.internalPointer());
  return p->childCount();
}
int TreeModel::columnCount(const QModelIndex & /*parent*/) const {
  return COLUMNS;
}

QModelIndex TreeModel::index(const int row, const int column,
                             const QModelIndex &parent) const {
  if (!hasIndex(row, column, parent)) return QModelIndex();

  TreeItem *item = _rootItem.get();
  if (parent.isValid())
    item = static_cast<TreeItem *>(parent.internalPointer());

  auto child = item->child(row);
  if (child) return createIndex(row, column, child);

  return QModelIndex();
}
QModelIndex TreeModel::parent(const QModelIndex &index) const {
  if (!index.isValid()) return QModelIndex();

  TreeItem *childItem = static_cast<TreeItem *>(index.internalPointer());
  TreeItem *parentItem = childItem->parentItem();

  if (parentItem == _rootItem.get()) return QModelIndex();

  return createIndex(parentItem->row(), 0, parentItem);
}

QVariant TreeModel::data(const QModelIndex &index, const int role) const {
  if (!index.isValid() || role != Qt::DisplayRole) {
    return QVariant();
  }
  TreeItem *item = static_cast<TreeItem *>(index.internalPointer());
  return item->data(role);
}

Qt::ItemFlags TreeModel::flags(const QModelIndex &index) const {
  if (!index.isValid()) return nullptr;

  return QAbstractItemModel::flags(index);
}

QHash<int, QByteArray> TreeModel::roleNames() const {
  QHash<int, QByteArray> roles = QAbstractItemModel::roleNames();
  roles[NameRole] = "itemName";
  roles[DataRole] = "itemData";
  return roles;
}

void TreeModel::addTreeItem(TreeItem *parent, TreeItem *child) {
  emit QAbstractItemModel::layoutAboutToBeChanged();

  if (child->parentItem()) {
    beginRemoveRows(QModelIndex(), child->parentItem()->childCount() - 1,
                    child->parentItem()->childCount());
    child->parentItem()->removeChild(child);
    endRemoveRows();
  }

  beginInsertRows(QModelIndex(), parent->childCount() - 1,
                  parent->childCount() - 1);
  child->setParentItem(parent);
  parent->appendChild(child);
  endInsertRows();

  emit QAbstractItemModel::layoutChanged();
}

std::shared_ptr<TreeItem> TreeModel::rootItem() const { return _rootItem; }
