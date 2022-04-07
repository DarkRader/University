#pragma once

#include <ostream>
#include "CEnvironment.h"

class CItem {
public:
    virtual ~CItem() = default;
    
    /**
     * Determines whether the item can explode under given conditions
     * @param environment Environment conditions against which the item is tested
     * @return true if the item can explode under given conditions
     */
    virtual bool canExplode(const CEnvironment & environment) const = 0;
    
    /**
     * Outputs item to output stream
     * @param os The output stream
     * @param item The item which should be written out to the stream
     * @return The output stream os
     */
    friend std::ostream & operator << (std::ostream & os, const CItem & item);
    
    virtual CItem * clone() const = 0;
    
protected:

    /**
     * Outputs dynamically bound item to output stream
     * @note This function should be overridden by each descendant to provide its own output representation
     * @param os The output stream
     */
    virtual void print(std::ostream & os) const = 0; // pure virtual method
};
