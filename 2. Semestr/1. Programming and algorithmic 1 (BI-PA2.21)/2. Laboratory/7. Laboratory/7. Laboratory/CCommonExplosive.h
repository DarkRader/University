#pragma once
#include <string>
#include <ostream>
#include "CEnvironment.h"
#include "CItem.h"

class CCommonExplosive
{
    public:
        CCommonExplosive(const std::string &, int);
        bool canExplode (const CEnvironment &) const;
    private:
        void print (std::ostream &) const override;
};
