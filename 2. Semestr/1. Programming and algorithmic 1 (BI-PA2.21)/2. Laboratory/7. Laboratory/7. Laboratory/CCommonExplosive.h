#pragma once

#include "CItem.h"

class CCommonExplosive : public CItem
{
    public:
        CCommonExplosive(const std::string & name, int criticalTemp);
        bool canExplode (const CEnvironment & environment) const override;
    protected:
        void print (std::ostream & os) const override;
    private:
        int m_criticalTemp; ///< Critical temperature in Celsius
};
