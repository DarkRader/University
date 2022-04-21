#include "CSafeItem.h"

CSafeItem::CSafeItem(const std::string & name) : CNamedItem(name) {}

bool CSafeItem::canExplode(const CEnvironment &environment) const {
    return false;
}

void CSafeItem::print(std::ostream &os) const {
    os << getName();
}

CItem *CSafeItem::clone() const {
    return new CSafeItem(*this);
}
