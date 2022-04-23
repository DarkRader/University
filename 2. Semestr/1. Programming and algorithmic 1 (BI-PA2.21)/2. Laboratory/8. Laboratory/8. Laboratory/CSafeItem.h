/**
 * @author Jan Matoušek
 * @copybrief Whoever copies the file, should at least understand it
 */

#pragma once

#include "CNamedItem.h"

/**
 * An item that never explodes
 */
class CSafeItem : public CNamedItem {

public:

    /**
     * Constructs the item
     * @param name The item name
     */
    CSafeItem(const std::string & name);

    CItem * clone() const;

    /**
     * Virtual destructor
     * @note Needed for proper destruction handling in descendants
     */
    virtual ~CSafeItem() = default;

    /**
     * Determines whether the item can explode under given conditions
     * @param environment Environment conditions against which the item is tested
     * @return true if the item can explode under given conditions
     */
    virtual bool canExplode(const CEnvironment & environment) const;

protected:

    /**
     * Outputs dynamically bound item to output stream
     * @note This function should be overridden by each descendant to provide its own output representation
     * @param os The output stream
     */
    virtual void print(std::ostream & os) const;
};
