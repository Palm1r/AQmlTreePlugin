#include "tree_item.h"

#include <QDebug>

TreeItem::TreeItem(ItemWeekPtr parent, const QVariant &data)
    : m_parent(parent)
    , m_data(data)
{
    m_childItems.reserve(4);
}

TreeItem::~TreeItem() {}

TreeItem::ItemPtr TreeItem::parent()
{
    return m_parent.lock();
}

int TreeItem::childCount() const
{
    return m_childItems.size();
}

TreeItem::ItemPtr TreeItem::child(int index)
{
    return m_childItems.at(index);
}

int TreeItem::childIndexByItem(const std::shared_ptr<const TreeItem> &item) const
{
    auto it = std::find(m_childItems.begin(), m_childItems.end(), item);
    if (it != m_childItems.end())
        return std::distance(m_childItems.begin(), it);
    return -1;
}

int TreeItem::index() const
{
    if (m_parent.expired())
        return 0;

    return m_parent.lock()->childIndexByItem(TreeItem::shared_from_this());
}

TreeItem::ItemPtr TreeItem::appendChild(const QVariant &data)
{
    return m_childItems.emplace_back(std::make_shared<TreeItem>(TreeItem::shared_from_this(), data));
}

void TreeItem::removeChild(int childIndex)
{
    auto child = m_childItems.begin() + childIndex;
    m_childItems.erase(child);
}

QVariant TreeItem::data() const
{
    return m_data;
}
