#include "CWarehouse.h"

CWarehouse::CWarehouse(const std::string &name)
: CNamedItem(name) {}

bool CWarehouse::canExplode(const CEnvironment &environment) const {
    for(const auto & item : m_items) {
        if(item->canExplode(environment)) return true;
    }
    return false;
}

void CWarehouse::print(std::ostream &os) const {
    os << getName() << " [" << m_items.size() << "]";
}

void CWarehouse::addItem(CItem *item) {
    if(!item) return;
    m_items.emplace_back(CItemPtr(item));
}

CItem *CWarehouse::clone() const {
    return new CWarehouse(*this);
}

