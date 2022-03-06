#include "tree_model.h"

TreeModel::TreeModel(QObject *parent)
    : QAbstractItemModel(parent)
    , _rootItem(std::make_shared<TreeItem>())
{
    addTreeItem(_rootItem, "Child");
    auto child = addTreeItem(_rootItem, "Child");
    addTreeItem(child, "GrandChild");
    addTreeItem(child, "GrandChild");
    addTreeItem(child, "GrandChild");
    auto grandChild = addTreeItem(child, "GrandChild");
    addTreeItem(grandChild, "GrandGrandChild");
}

TreeModel::~TreeModel() {}

int TreeModel::rowCount(const QModelIndex &parent) const
{
    if (!parent.isValid())
        return _rootItem->childCount();
    TreeItem *p = static_cast<TreeItem *>(parent.internalPointer());
    return p->childCount();
}

int TreeModel::columnCount(const QModelIndex & /*parent*/) const
{
    return 1;
}

QModelIndex TreeModel::index(const int row, const int column, const QModelIndex &parent) const
{
    if (!hasIndex(row, column, parent))
        return QModelIndex();

    TreeItem *item = _rootItem.get();
    if (parent.isValid())
        item = static_cast<TreeItem *>(parent.internalPointer());

    auto child = item->child(row);
    if (child)
        return createIndex(row, column, child.get());

    return QModelIndex();
}
QModelIndex TreeModel::parent(const QModelIndex &index) const
{
    if (!index.isValid())
        return QModelIndex();

    TreeItem *childItem = static_cast<TreeItem *>(index.internalPointer());
    TreeItem *parentItem = childItem->parent().get();

    if (parentItem == _rootItem.get())
        return QModelIndex();

    return createIndex(parentItem->index(), 0, parentItem);
}

QVariant TreeModel::data(const QModelIndex &index, const int role) const
{
    if (!index.isValid() || role != Qt::DisplayRole) {
        return QVariant();
    }
    TreeItem *item = static_cast<TreeItem *>(index.internalPointer());
    return item->data();
}

TreeItem::ItemPtr TreeModel::addTreeItem(TreeItem::ItemPtr parent, QVariant data)
{
    beginInsertRows(QModelIndex(),
                    parent->childCount() > 0 ? parent->childCount() - 1 : 0,
                    parent->childCount() > 0 ? parent->childCount() - 1 : 0);
    auto newItem = parent->appendChild(data);
    endInsertRows();

    return newItem;
}

void TreeModel::removeItemByIndex(TreeItem::ItemPtr parent, int index)
{
    if (parent->child(index)) {
        beginRemoveRows(QModelIndex(), parent->childCount() - 1, parent->childCount());
        parent->removeChild(index);
        endRemoveRows();
    }
}

TreeItem::ItemPtr TreeModel::rootItem() const
{
    return _rootItem;
}

QModelIndex TreeModel::rootIndex()
{
    return QModelIndex();
}
