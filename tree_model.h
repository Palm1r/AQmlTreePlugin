#pragma once

#include <QAbstractItemModel>
#include <memory>

#include "tree_item.h"

class TreeModel : public QAbstractItemModel {
  Q_OBJECT
 public:
  enum Role { NameRole = Qt::UserRole + 1, DataRole };

  explicit TreeModel(QObject *parent = nullptr);

  int rowCount(const QModelIndex &index) const override;
  int columnCount(const QModelIndex &) const override;
  QModelIndex index(const int row, const int column,
                    const QModelIndex &parent) const override;
  QModelIndex parent(const QModelIndex &childIndex) const override;
  QVariant data(const QModelIndex &index, const int role) const override;
  Qt::ItemFlags flags(const QModelIndex &index) const override;

  QHash<int, QByteArray> roleNames() const override;

  void addTreeItem(TreeItem *parent, TreeItem *child);

  std::shared_ptr<TreeItem> rootItem() const;

  Q_INVOKABLE QModelIndex rootIndex();

 private:
  std::shared_ptr<TreeItem> _rootItem;
};
