#pragma once

#include "CSafeItem.h"

class CCommonExplosive : public CSafeItem {
public:
    CCommonExplosive(const std::string & name, int criticalTemp);
    bool canExplode(const CEnvironment &environment) const override;
protected:
    void print(std::ostream &os) const override;
private:
    int m_criticalTemp; ///< Critical temperature in Celsius
};
