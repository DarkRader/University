#include "CDangerousExplosive.h"

CDangerousExplosive::CDangerousExplosive(const std::string & name)
: CItem(name)
{}

bool CDangerousExplosive::canExplode (const CEnvironment & env) const
{
    return env.hasOxygen;
}

void CDangerousExplosive::print (std::ostream & os) const
{
    CItem::print(os);
    os << " [!]";
}


