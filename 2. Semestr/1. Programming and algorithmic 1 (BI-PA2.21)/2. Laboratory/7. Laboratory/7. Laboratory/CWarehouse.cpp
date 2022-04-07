#include "CWarehouse.h"

CWarehouse::CWarehouse(const std::string & name)
: CItem(name)
{}

bool CWarehouse::canExplode (const CEnvironment & environment) const
{
    for(const auto & item : m_items) {
        if(item->canExplode(environment)) return true;
    }
    return false;
}

void CWarehouse::print (std::ostream & os) const
{
    CItem::print(os);
    os << " [" << m_items.size() << "]";
}

void CWarehouse::addItem (CItem * item)
{
    if (!item) return;
        m_items.emplace_back(std::unique_ptr<CItem>(item));
    // m_items.push_back(item) // don't work
}
