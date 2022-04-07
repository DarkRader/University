#include "CItem.h"

CItem::CItem (const std::string & name) : m_name(name) {}

bool CItem::canExplode (const CEnvironment & environment) const
{
    return false;
}

std::ostream & operator << (std::ostream & os, const CItem & item)
{
    // dispatch item
    item.print(os);
    return os;
}

void CItem::print (std::ostream & os) const
{
    os << m_name;
}
