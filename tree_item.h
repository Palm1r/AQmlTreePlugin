#pragma once

#include "QVariant"
#include <memory>
#include <vector>

class TreeItem : public std::enable_shared_from_this<TreeItem>
{
public:
    using ItemWeekPtr = std::weak_ptr<TreeItem>;
    using ItemPtr = std::shared_ptr<TreeItem>;

    explicit TreeItem(ItemWeekPtr parent = ItemWeekPtr(), const QVariant &data = QVariant());
    ~TreeItem();

    int index() const;
    int childCount() const;

    ItemPtr parent();
    ItemPtr child(int index);

    int childIndexByItem(const std::shared_ptr<const TreeItem> &item) const;

    ItemPtr appendChild(const QVariant &data);
    void removeChild(int childIndex);

    QVariant data() const;

private:
    ItemWeekPtr m_parent;
    QVariant m_data;
    std::vector<ItemPtr> m_childItems;
};
