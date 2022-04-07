#include "CNamedItem.h"

CNamedItem::CNamedItem(const std::string & name) : m_name(name) {}

const std::string & CNamedItem::getName() const {
    return m_name;
}
