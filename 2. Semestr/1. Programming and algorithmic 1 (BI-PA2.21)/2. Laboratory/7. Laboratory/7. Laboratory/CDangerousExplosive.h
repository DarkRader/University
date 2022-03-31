#pragma once
#include <string>
#include <ostream>
#include "CEnvironment.h"
#include "CItem.h"

class CDangerousExplosive : public CItem //standart is private, so we need to write public
{
    public:
        CDangerousExplosive(const std::string &);
        virtual bool canExplode (const CEnvironment &) const;
    private:
        void print (std::ostream &) const override;
};
