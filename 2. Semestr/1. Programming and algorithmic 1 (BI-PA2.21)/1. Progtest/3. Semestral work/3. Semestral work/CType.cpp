/**
 * @author Artem Kuznetsov  <kuznear1@fit.cvut.cz>
 * @date 08.05.2021
 */
#include "CType.h"


std::ostream &operator<<(std::ostream &os, const CType &item) {
    item.print(os);
    return os;
}
