#pragma once

#include "CNamedItem.h"

class CCommonExplosive : public CNamedItem {
public:
    CCommonExplosive(const std::string & name, int criticalTemp);
    bool canExplode(const CEnvironment &environment) const override;
    virtual CItem * clone() const override;
protected:
    void print(std::ostream &os) const override;
private:
    int m_criticalTemp; ///< Critical temperature in Celsius
};
