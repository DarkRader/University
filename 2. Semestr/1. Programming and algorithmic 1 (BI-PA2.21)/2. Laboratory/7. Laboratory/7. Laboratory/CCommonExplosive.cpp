#include "CCommonExplosive.h"

CCommonExplosive::CCommonExplosive(const std::string & name, int critical_temp)
: CItem(name),
  m_critical_temp(critical_temp)
{}

bool CCommonExplosive::::canExplode (const CEnvironment & env) const
{
    return enc.tempCelsuis > m_critical_temp;
}

void CCommonExplosive::::print (std::ostream & os) const
{
    CItem::print(os);
    os << " [critical_temp: " << m_critical_temp << "]";
}
