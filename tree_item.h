#pragma once

#include <QObject>
#include <QVariant>

class TreeItem {
 public:
  explicit TreeItem(const QVariant &data, TreeItem *parent = nullptr);

  ~TreeItem();

  void appendChild(TreeItem *item);
  void removeChild(TreeItem *item);

  TreeItem *child(int row);
  int childCount() const;
  QVariant data() const;
  int row() const;
  TreeItem *parentItem();
  void setParentItem(TreeItem *parentItem);

 private:
  QList<TreeItem *> _childItems;
  QVariant _itemData;
  TreeItem *_parentItem;
};
