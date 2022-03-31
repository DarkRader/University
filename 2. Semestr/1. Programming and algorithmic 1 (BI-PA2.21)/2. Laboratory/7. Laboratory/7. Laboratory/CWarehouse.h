#pragma once
#include "CItem.h"
#include <vector>
#include <memory>

class CWarehouse : public CItem
{
    public:
        CWarehouse (const std:: string &);
        bool canExplode (const CEnvironment &) const override;
        void addItem (CItem *);
    private:
        void print (std::ostream &) const override;
        std::vector<std::unique_ptr<CItem>> m_items;
};
