#pragma once

#include "CItem.h"
#include <memory>

class CItemPtr : public std::unique_ptr<CItem> {
public:
    using std::unique_ptr<CItem>::unique_ptr;

    CItemPtr(const CItemPtr& other) : std::unique_ptr<CItem>(other->clone()) {}
    CItemPtr & operator = (CItemPtr other) {
        swap(other);
        return *this;
    }
};
