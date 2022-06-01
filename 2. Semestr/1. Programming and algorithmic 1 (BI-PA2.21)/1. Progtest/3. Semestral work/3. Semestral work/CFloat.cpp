/**
 * @author Artem Kuznetsov  <kuznear1@fit.cvut.cz>
 * @date 08.05.2021
 */
#include "CFloat.h"

CType * CFloat::clone() const
{
    return new CFloat(*this);
}

CFloat::CFloat(long double variable) { m_varFloat = variable; }

long long int CFloat::getVariable(void) const { return m_varInt; }

std::string CFloat::getNewVariable(void) const { return m_newVariable; }

CType & CFloat::operator + (const CType & number)
{
    long double newVariable = m_varFloat + number.getVarFloat();
    
    m_newVariable = std::to_string(newVariable);
    
    return *this;
}

CType & CFloat::operator - (const CType & number)
{
    long double newVariable = m_varFloat - number.getVarFloat();
    
    m_newVariable = std::to_string(newVariable);
    
    return *this;
}

CType & CFloat::operator * (const CType & number)
{
    long double newVariable = m_varFloat * number.getVarFloat();
    
    m_newVariable = std::to_string(newVariable);

    return *this;
}

void CFloat::print(std::ostream & os) const
{
    
}
