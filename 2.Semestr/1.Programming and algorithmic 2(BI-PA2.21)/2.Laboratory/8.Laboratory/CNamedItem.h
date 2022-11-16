/**
 * @author Jan Matoušek
 * @copybrief Whoever copies the file, should at least understand it
 */

#pragma once

#include <string>
#include "CItem.h"

/**
 * An item that never explodes
 */
class CNamedItem : public CItem {

public:

    /**
     * Constructs the item
     * @param name The item name
     */
    CNamedItem(const std::string & name);

protected:

    /**
     * Retrieves item name
     * @return The item name, read only.
     */
    const std::string & getName() const;

private:

    std::string m_name; ///< Item name
};

