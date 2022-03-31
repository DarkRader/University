#pragma once
#include <string>
#include <ostream>
#include "CEnvironment.h"

class CItem {
    public:
        CItem(const std::string &);
        virtual ~CItem () = default;
        virtual bool canExplode (const CEnvironment &) const;
        friend std::ostream & operator << (std::ostream &, const CItem &);
    protected:
        virtual void print(std:: ostream &) const;
        std::string m_name;
};
