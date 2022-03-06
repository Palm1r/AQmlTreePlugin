#pragma once

#include <memory>
#include <QAbstractItemModel>

#include "tree_item.h"
#include <QtQml/qqml.h>

class TreeModel : public QAbstractItemModel
{
    Q_OBJECT
    QML_ELEMENT
public:
    explicit TreeModel(QObject *parent = nullptr);
    ~TreeModel();

    int rowCount(const QModelIndex &index) const override;
    int columnCount(const QModelIndex &) const override;
    QModelIndex index(const int row, const int column, const QModelIndex &parent) const override;
    QModelIndex parent(const QModelIndex &childIndex) const override;
    QVariant data(const QModelIndex &index, const int role = 0) const override;

    Q_INVOKABLE TreeItem::ItemPtr addTreeItem(TreeItem::ItemPtr parent, QVariant data);
    Q_INVOKABLE void removeItemByIndex(TreeItem::ItemPtr parent, int index);

    Q_INVOKABLE TreeItem::ItemPtr rootItem() const;

    Q_INVOKABLE QModelIndex rootIndex();

private:
    TreeItem::ItemPtr _rootItem;
};
