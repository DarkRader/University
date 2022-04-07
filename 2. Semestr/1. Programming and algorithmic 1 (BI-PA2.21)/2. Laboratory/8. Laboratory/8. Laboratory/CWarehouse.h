#pragma once

#include <vector>
#include <memory>
#include "CSafeItem.h"

class CWarehouse : public CSafeItem {
public:
    CWarehouse(const std::string & name);

    bool canExplode(const CEnvironment &environment) const override;
    void addItem(CSafeItem *item);

protected:
    void print(std::ostream &os) const override;

private:
    std::vector<std::unique_ptr<CSafeItem>> m_items;
};
