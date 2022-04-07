#pragma once

#include <vector>
#include <memory>
#include "CItem.h"

class CWarehouse : public CItem
{
    public:
        CWarehouse (const std::string & name);
    
        bool canExplode (const CEnvironment & environment) const override;
        void addItem (CItem * item);
    
    protected:
        void print (std::ostream & os) const override;
    private:
        std::vector<std::unique_ptr<CItem>> m_items;
};
