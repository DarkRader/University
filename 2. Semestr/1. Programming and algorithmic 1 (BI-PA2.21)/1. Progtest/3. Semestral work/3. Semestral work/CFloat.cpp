/**
 * @author Artem Kuznetsov  <kuznear1@fit.cvut.cz>
 * @date 08.05.2021
 */
#include "CFloat.h"

CDataSize * CFloat::clone() const
{
    return new CFloat(*this);
}

//CFloat::CFloat(long double variable) : CType(variable){  }

long long int CFloat::getVariable(void) const { return m_varInt[0]; }

CFloat::CFloat(long double variable, const std::string & type, const std::string & size)
{
    m_varFloat = variable;
    m_type = type;
    m_size = size;
}

CFloat::CFloat(long double varFloat, long long int varInt, const std::string & type, const std::string & size)
{
    m_varFloat = varFloat;
    m_varInt.push_back(varInt);
    m_type = type;
    m_size = size;
}

void CFloat::writeVariable(CVariable & var)
{
    
}

void CFloat::negativeNum(void)
{
    m_varFloat = m_varFloat * (-1);
}

char CFloat::getSign(void)
{
    if(m_varFloat >= 0)
        return '+';
    else
        return '-';
}

CDataSize & CFloat::operator + (const CDataSize & number)
{
    m_varFloat = m_varFloat + number.getVarFloat();
    return *this;
}

CDataSize & CFloat::operator - (const CDataSize & number)
{
    m_varFloat = m_varFloat - number.getVarFloat();
    return *this;
}

CDataSize & CFloat::operator * (const CDataSize & number)
{
    m_varFloat = m_varFloat * number.getVarFloat();
    return *this;
}

CDataSize & CFloat::operator / (const CDataSize & number)
{
    std::cout << "Logic error" << std::endl;
    return *this;
}

void CFloat::print(void) const
{
    //std::cout << m_varFloat << std::endl;
    std::cout << "Result: ";
    std::cout << std::fixed << std::setprecision(5) << m_varFloat << std::endl;
}
