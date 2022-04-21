#pragma once

#include <vector>
#include "CNamedItem.h"
#include "CItemPtr.h"

class CWarehouse : public CNamedItem {
public:
    CWarehouse(const std::string & name);

    CItem * clone() const override;

    bool canExplode(const CEnvironment &environment) const override;
    void addItem(CItem *item);

protected:
    void print(std::ostream &os) const override;

private:
    std::vector<CItemPtr> m_items;
};
