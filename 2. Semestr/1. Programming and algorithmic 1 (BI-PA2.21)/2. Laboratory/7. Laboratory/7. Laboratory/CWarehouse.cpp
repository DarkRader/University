#include "CWarehouse.h"

CWarehouse::CWarehouse(const std::string & name)
: CItem(name)
{}

bool CWarehouse::canExplode (const CEnvironment & env) const
{
    bool can_explode = false;
    for(const auto & item : m_items)
        can_explode |= item->canExplode(env);
    return can_explode;
}

void CWarehouse::addItem (CItem * item)
{
    if (item)
        m_items.emplace_back(item);
    // m_items.push_back(item) // don't work
}

void CWarehouse::print (std::ostream & os) const
{
    CItem::print(os);
    os << " [!]";
}
