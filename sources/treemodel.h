
#ifndef TREEMODEL_H
#define TREEMODEL_H

#include "treeitem.h"

#include <QAbstractItemModel>

#include <QtQml/qqml.h>

class TreeModel : public QAbstractItemModel
{
    Q_OBJECT
    QML_ELEMENT
public:
    explicit TreeModel(QObject *parent = nullptr);
    ~TreeModel() override = default;

    int rowCount(const QModelIndex &index) const override;
    int columnCount(const QModelIndex &) const override;
    QModelIndex index(const int row, const int column, const QModelIndex &parent) const override;
    QModelIndex parent(const QModelIndex &childIndex) const override;
    QVariant data(const QModelIndex &index, const int role = 0) const override;

    Q_INVOKABLE TreeItem::ItemPtr addTreeItem(TreeItem::ItemPtr parent, QVariant data);
    Q_INVOKABLE TreeItem::ItemPtr addTreeItem(const QModelIndex &parentIndex, const QVariant &data);
    Q_INVOKABLE void removeItemByIndex(TreeItem::ItemPtr parent, int index);
    Q_INVOKABLE void removeItemByIndex(const QModelIndex &index);
    Q_INVOKABLE TreeItem::ItemPtr rootItem() const;
    Q_INVOKABLE QModelIndex rootIndex();

private:
    TreeItem::ItemPtr m_rootItem;
};

#endif // TREEMODEL_H
