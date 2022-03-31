#include "CItem.h"

CItem::CItem(const std::string & name)
: m_name(name)
{}

bool CItem::canExplode (const CEnvironment & env) const
{
    return false;
}

void CItem::print (std::ostream & os) const
{
    os << m_name;
}

std::ostream & operator << (std::ostream & os, const CItem & item)
{
    item.print(os);
    return os;
}
