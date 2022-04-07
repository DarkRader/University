#pragma once

#include "CNamedItem.h"

class CDangerousExplosive : public CNamedItem {
public:
    CDangerousExplosive(const std::string & name);

    bool canExplode(const CEnvironment & environment) const override;
    
    CItem * clone() const override;

protected:
    void print(std::ostream & os) const override;
};
