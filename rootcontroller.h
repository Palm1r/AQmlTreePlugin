#ifndef ROOTCONTROLLER_H
#define ROOTCONTROLLER_H

#include "tree_model.h"
#include <QObject>

class RootController : public QObject
{
    Q_OBJECT
    Q_PROPERTY(TreeModel *treeModel READ treeModel NOTIFY treeModelChanged)

public:
    explicit RootController(QObject *parent = nullptr);

    TreeModel *treeModel() const;
    // TO DO add new item for any parent
    Q_INVOKABLE void addItem(const QVariant &data);

signals:
    void treeModelChanged();

private:
    TreeModel *m_treeModel;
};

#endif // ROOTCONTROLLER_H
