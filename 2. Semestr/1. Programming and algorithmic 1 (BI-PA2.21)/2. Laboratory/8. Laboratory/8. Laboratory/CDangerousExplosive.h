#pragma once

#include "CNamedItem.h"

class CDangerousExplosive : public CNamedItem {
public:
    CDangerousExplosive(const std::string & name);

    CItem * clone() const override;

    bool canExplode(const CEnvironment & environment) const override;

protected:
    void print(std::ostream & os) const override;
};
