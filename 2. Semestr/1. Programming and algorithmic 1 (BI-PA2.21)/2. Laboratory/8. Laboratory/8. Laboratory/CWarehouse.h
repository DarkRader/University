#pragma once

#include <vector>
#include <memory>
#include "CNamedItem.h"

class CWarehouse : public CNamedItem {
public:
    CWarehouse(const std::string & name);
    CWarehouse(const CWarehouse & other);
    CWarehouse & operator = (const CWarehouse & other);
    ~CWarehouse();

    bool canExplode(const CEnvironment &environment) const override;
    void addItem(CItem *item);
    
    CItem * clone() const override;

protected:
    void print(std::ostream &os) const override;

private:
    std::vector<CItem *> m_items;
};
