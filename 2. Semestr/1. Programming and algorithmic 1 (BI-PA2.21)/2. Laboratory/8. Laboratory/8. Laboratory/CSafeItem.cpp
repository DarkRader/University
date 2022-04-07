#include "CSafeItem.h"

CSafeItem::CSafeItem(const std::string & name) : m_name(name) {}

bool CSafeItem::canExplode(const CEnvironment &environment) const {
    return false;
}

std::ostream &operator<<(std::ostream &os, const CSafeItem &item) {
    // dispatch item
    item.print(os);
    return os;
}

void CSafeItem::print(std::ostream &os) const {
    os << m_name;
}
