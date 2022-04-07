#include "CItem.h"

std::ostream & operator << (std::ostream & os, const CItem & item) {
    // dispatch item
    item.print(os);
    return os;    
}
