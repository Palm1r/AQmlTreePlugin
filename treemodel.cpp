
#include "treemodel.h"

TreeModel::TreeModel(QObject *parent)
    : QAbstractItemModel(parent)
    , m_rootItem(std::make_shared<TreeItem>())
{}

int TreeModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid()) {
        TreeItem *p = static_cast<TreeItem *>(parent.internalPointer());
        return p->childCount();
    }
    return m_rootItem->childCount();
}

int TreeModel::columnCount(const QModelIndex & /*parent*/) const
{
    return 1;
}

QModelIndex TreeModel::index(const int row, const int column, const QModelIndex &parent) const
{
    if (!hasIndex(row, column, parent))
        return QModelIndex();

    TreeItem *item = m_rootItem.get();
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

    if (parentItem == m_rootItem.get())
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
    if (!parent)
        parent = m_rootItem;
    int indexToInsert = parent->childCount();
    beginInsertRows(parent->parent() ? createIndex(parent->index(), 0, parent.get()) : QModelIndex(),
                    indexToInsert,
                    indexToInsert);
    auto newItem = parent->appendChild(data);
    endInsertRows();

    return newItem;
}

TreeItem::ItemPtr TreeModel::addTreeItem(const QModelIndex &parentIndex, const QVariant &data)
{
    TreeItem::ItemPtr parent;
    if (!parentIndex.isValid()) {
        parent = m_rootItem;
    } else {
        parent = static_cast<TreeItem *>(parentIndex.internalPointer())->shared_from_this();
    }
    int indexToInsert = parent->childCount();
    beginInsertRows(parentIndex, indexToInsert, indexToInsert);
    auto newItem = parent->appendChild(data);
    endInsertRows();

    return newItem;
}

void TreeModel::removeItemByIndex(TreeItem::ItemPtr parent, int index)
{
    if (parent->child(index)) {
        beginRemoveRows(parent->parent() ? createIndex(parent->index(), 0, parent.get())
                                         : QModelIndex(),
                        index,
                        index);
        parent->removeChild(index);
        endRemoveRows();
    }
}

void TreeModel::removeItemByIndex(const QModelIndex &index)
{
    qDebug() << "index" << index << "count" << rowCount(index);
    if (!index.isValid()) {
        return;
    }

    TreeItem::ItemPtr item = static_cast<TreeItem *>(index.internalPointer())->shared_from_this();
    TreeItem::ItemPtr parent = item->parent();

    if (!parent) {
        return;
    }

    int rowIndex = index.row();

    beginRemoveRows(parent->parent() ? createIndex(parent->index(), 0, parent.get()) : QModelIndex(),
                    rowIndex,
                    rowIndex);
    parent->removeChild(rowIndex);
    endRemoveRows();
}

TreeItem::ItemPtr TreeModel::rootItem() const
{
    return m_rootItem;
}

QModelIndex TreeModel::rootIndex()
{
    return QModelIndex();
}
