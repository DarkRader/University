#include "CCommonExplosive.h"

CCommonExplosive::CCommonExplosive(const std::string &name, int criticalTemp)
        : CNamedItem(name), m_criticalTemp(criticalTemp) {}

bool CCommonExplosive::canExplode(const CEnvironment &environment) const {
    return environment.tempCelsius > m_criticalTemp;
}

void CCommonExplosive::print(std::ostream &os) const {
    os << getName() << " [critical temp: " << m_criticalTemp << "]";
}

CItem *CCommonExplosive::clone() const {
    return new CCommonExplosive(*this);
}
