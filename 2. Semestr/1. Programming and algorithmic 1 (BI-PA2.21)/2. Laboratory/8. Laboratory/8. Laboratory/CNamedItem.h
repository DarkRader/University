#pragma once

#include <string>
#include "CItem.h"

class CNamedItem : public CItem {
public:
    CNamedItem(const std::string & name);
protected:
    const std::string & getName() const;
private:
    std::string m_name;
};

