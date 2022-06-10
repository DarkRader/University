/**
 * @author Artem Kuznetsov  <kuznear1@fit.cvut.cz>
 * @date 08.05.2021
 */
#include "CInteger.h"

CDataSize * CInteger::clone() const
{
    return new CInteger(*this);
}

CInteger::CInteger(long long int variable) { m_varInt[0] = variable; }

CInteger::CInteger(long long int variable, const std::string & type, const std::string & size)
{
    m_type = type;
    m_size = size;
    m_varInt.push_back(variable);
}

long long int CInteger::getVariable(void) const { return m_varInt[0]; }

void CInteger::negativeNum(void) 
{
    m_varInt[0] = m_varInt[0] * (-1);
}

char CInteger::getSign(void)
{
    if(m_varInt[0] >= 0)
        return '+';
    else
        return '-';
}

CDataSize & CInteger::operator + (const CDataSize & number)
{
        m_varInt[0] = m_varInt[0] + number.getVarInt();
    return *this;
}

CDataSize & CInteger::operator - (const CDataSize & number)
{
        m_varInt[0] = m_varInt[0] - number.getVarInt();
    return *this;
}

CDataSize & CInteger::operator / (const CDataSize & number)
{
        m_varInt[0] = m_varInt[0] / number.getVarInt();
    return *this;
}

CDataSize & CInteger::operator * (const CDataSize & number)
{
        m_varInt[0] = m_varInt[0] * number.getVarInt();
    return *this;
}

void CInteger::print(std::ostream & history) const
{
    std::cout << "Result: " << m_varInt[0] << std::endl;
}
