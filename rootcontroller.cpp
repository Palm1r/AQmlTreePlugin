#include "rootcontroller.h"

RootController::RootController(QObject *parent)
    : QObject{parent}
    , m_treeModel(new TreeModel(this))
{
    m_treeModel->addTreeItem(nullptr, "Child");
    auto child = m_treeModel->addTreeItem(nullptr, "Child");
    m_treeModel->addTreeItem(child, "GrandChild");
    m_treeModel->addTreeItem(child, "GrandChild");
    m_treeModel->addTreeItem(child, "GrandChild");
    auto grandChild = m_treeModel->addTreeItem(child, "GrandChild");
    m_treeModel->addTreeItem(grandChild, "GrandGrandChild");

    emit treeModelChanged();
}

TreeModel *RootController::treeModel() const
{
    return m_treeModel;
}

void RootController::addItem(const QVariant &data)
{
    m_treeModel->addTreeItem(m_treeModel->rootItem(), data);

    emit treeModelChanged();
}
