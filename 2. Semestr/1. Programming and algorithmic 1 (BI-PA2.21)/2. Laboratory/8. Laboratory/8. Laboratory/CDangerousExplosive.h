#pragma once

#include "CSafeItem.h"

class CDangerousExplosive : public CSafeItem {
public:
    CDangerousExplosive(const std::string & name);

    bool canExplode(const CEnvironment & environment) const override;

protected:
    void print(std::ostream & os) const override;
};
