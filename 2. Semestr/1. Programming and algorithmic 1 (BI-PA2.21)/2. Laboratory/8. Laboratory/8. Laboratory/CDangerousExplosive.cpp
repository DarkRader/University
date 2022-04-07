#include "CDangerousExplosive.h"

CDangerousExplosive::CDangerousExplosive(const std::string & name) : CNamedItem(name) {}

bool CDangerousExplosive::canExplode(const CEnvironment &environment) const {
    return environment.hasOxygen;
}

void CDangerousExplosive::print(std::ostream &os) const {
    os << getName() << " [!]";
}

CItem * CDangerousExplosive::clone() const {
    return new CDangerousExplosive(*this);
}
