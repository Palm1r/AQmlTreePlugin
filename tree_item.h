#pragma once

#include <QObject>
#include <QVariant>

class TreeItem {
 public:
  explicit TreeItem(const QList<QVariant> &data, TreeItem *parent = nullptr);

  ~TreeItem();

  void appendChild(TreeItem *item);
  void removeChild(TreeItem *item);

  TreeItem *child(int row);
  int childCount() const;
  int columnCount() const;
  QVariant data(int column) const;
  void setData(int column, QVariant value);
  int row() const;
  TreeItem *parentItem();
  void setParentItem(TreeItem *parentItem);

 signals:

 private:
  QList<TreeItem *> _childItems;
  QList<QVariant> _itemData;
  TreeItem *_parentItem;
};
