/**
 * @author Artem Kuznetsov  <kuznear1@fit.cvut.cz>
 * @date 08.05.2021
 */
#include "CInteger.h"

CType * CInteger::clone() const
{
    return new CInteger(*this);
}

CInteger::CInteger(long long int variable) { m_variable = variable; }

long long int CInteger::getVariable(void) const { return m_variable; }

std::string CInteger::getNewVariable(void) const { return m_newVariable; }

CType & CInteger::operator + (const CType & number)
{
    long long int newVariable = m_variable + number.getVariable();
    
    m_newVariable = std::to_string(newVariable);
    
    return *this;
}

CType & CInteger::operator - (const CType & number)
{
    long long int newVariable = m_variable - number.getVariable();
    
    m_newVariable = std::to_string(newVariable);
    
    return *this;
}

CType & CInteger::operator / (const CType & number)
{
    long long int newVariable = m_variable / number.getVariable();
    
    m_newVariable = std::to_string(newVariable);
    
    return *this;
}

CType & CInteger::operator * (const CType & number)
{
    long long int newVariable = m_variable * number.getVariable();
    
    m_newVariable = std::to_string(newVariable);

    return *this;
}

void CInteger::print(std::ostream & os) const
{
    
}
