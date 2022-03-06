#include "rootcontroller.h"

RootController::RootController(QObject *parent)
    : QObject{parent}
    , m_treeModel(new TreeModel(this))
{}

TreeModel *RootController::treeModel() const
{
    return m_treeModel;
}

void RootController::addItem(const QVariant &data)
{
    m_treeModel->addTreeItem(m_treeModel->rootItem(), data);

    emit treeModelChanged();
}
