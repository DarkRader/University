/**
 * @author Jan Matoušek
 * @copybrief Whoever copies the file, should at least understand it
 */

#pragma once

#include <ostream>
#include "CEnvironment.h"

/**
 * An item that never explodes
 */
class CItem {

public:

    /**
     * Virtual destructor
     * @note Needed for proper destruction handling in descendants
     */
    virtual ~CItem() = default;

    /**
     * Virtual copy
     * @return Pointer to allocated copy of the object
     */
    virtual CItem * clone() const = 0;

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

protected:

    /**
     * Outputs dynamically bound item to output stream
     * @note This function should be overridden by each descendant to provide its own output representation
     * @param os The output stream
     */
    virtual void print(std::ostream & os) const = 0;
};
