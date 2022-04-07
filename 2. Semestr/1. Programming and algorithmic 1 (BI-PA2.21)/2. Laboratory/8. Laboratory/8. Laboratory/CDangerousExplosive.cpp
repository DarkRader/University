#include "CDangerousExplosive.h"

CDangerousExplosive::CDangerousExplosive(const std::string & name) : CSafeItem(name) {}

bool CDangerousExplosive::canExplode(const CEnvironment &environment) const {
    return environment.hasOxygen;
}

void CDangerousExplosive::print(std::ostream &os) const {
    CSafeItem::print(os);
    os << " [!]";
}
