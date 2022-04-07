#include "CWarehouse.h"

CWarehouse::CWarehouse(const std::string &name)
: CNamedItem(name) {}

CWarehouse::CWarehouse(const CWarehouse & other) : CNamedItem(other) {
    for(const auto & item : other.m_items) {
        m_items.emplace_back(item->clone());
    }
}

CWarehouse & CWarehouse::operator=(const CWarehouse & other) {
    if(this == &other) return *this;
//    CWarehouse otherCopy(other);
//    swap(otherCopy);
    this->CWarehouse::~CWarehouse();
    new (this) CWarehouse (other);
    return *this;
}

CWarehouse::~CWarehouse() {
    for(const auto & item : m_items) {
        delete item;
    }
}

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
    m_items.emplace_back(std::shared_ptr<CItem>(item));
}

CItem * CWarehouse::clone() const {
    return new CWarehouse(*this);
}
