#include "tree_item.h"

TreeItem::TreeItem(const QVariant &data, TreeItem *parent)
    : _itemData(data), _parentItem(parent) {}

TreeItem::~TreeItem() { qDeleteAll(_childItems); }

void TreeItem::appendChild(TreeItem *item) { _childItems.append(item); }

void TreeItem::removeChild(TreeItem *item) { _childItems.removeAll(item); }

TreeItem *TreeItem::child(int row) { return _childItems.value(row); }

int TreeItem::childCount() const { return _childItems.count(); }

QVariant TreeItem::data() const { return _itemData; }

int TreeItem::row() const {
  if (_parentItem)
    return _parentItem->_childItems.indexOf(const_cast<TreeItem *>(this));

  return 0;
}

TreeItem *TreeItem::parentItem() { return _parentItem; }

void TreeItem::setParentItem(TreeItem *parentItem) { _parentItem = parentItem; }
