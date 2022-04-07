#pragma once

#include "CItem.h"

class CDangerousExplosive : public CItem //standart is private, so we need to write public
{
    public:
        CDangerousExplosive(const std::string & name);
    
        bool canExplode (const CEnvironment & environment) const override;
    
    protected:
        void print (std::ostream & os) const override;
};
