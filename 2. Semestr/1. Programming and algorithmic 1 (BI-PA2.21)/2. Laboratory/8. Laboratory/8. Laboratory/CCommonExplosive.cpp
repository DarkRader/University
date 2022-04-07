#include "CCommonExplosive.h"

CCommonExplosive::CCommonExplosive(const std::string &name, int criticalTemp)
        : CSafeItem(name), m_criticalTemp(criticalTemp) {}

bool CCommonExplosive::canExplode(const CEnvironment &environment) const {
    return environment.tempCelsius > m_criticalTemp;
}

void CCommonExplosive::print(std::ostream &os) const {
    CSafeItem::print(os);
    os << " [critical temp: " << m_criticalTemp << "]";
}
