#pragma once

#include "CNamedItem.h"

class CCommonExplosive : public CNamedItem {
public:
    CCommonExplosive(const std::string & name, int criticalTemp);
    CItem * clone() const override;
    bool canExplode(const CEnvironment &environment) const override;
protected:
    void print(std::ostream &os) const override;
private:
    int m_criticalTemp; ///< Critical temperature in Celsius
};
