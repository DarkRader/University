/**
 * @author Artem Kuznetsov  <kuznear1@fit.cvut.cz>
 * @date 08.05.2021
 */
#include "CInteger.h"

CDataSize * CInteger::clone() const
{
    return new CInteger(*this);
}

CInteger::CInteger(long long int variable, const std::string & type, const std::string & size)
{
    m_type = type;
    m_size = size;
    m_varInt.push_back(variable);
    m_remains.push_back(0);
}

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
    m_remains[0] += number.getRemains();
    return *this;
}

CDataSize & CInteger::operator - (const CDataSize & number)
{
    m_varInt[0] = m_varInt[0] - number.getVarInt();
    m_remains[0] += number.getRemains();
    return *this;
}

CDataSize & CInteger::operator / (const CDataSize & number)
{
    if(number.getVarInt() == 0)
        throw 1;
    m_remains[0] = m_varInt[0] % number.getVarInt();
    m_varInt[0] = m_varInt[0] / number.getVarInt();
    return *this;
}

CDataSize & CInteger::operator * (const CDataSize & number)
{
    m_varInt[0] = m_varInt[0] * number.getVarInt();
    m_remains[0] += number.getRemains();
    if(m_remains[0] < 0)
        m_remains[0] = m_remains[0] * (-1);
    return *this;
}

void CInteger::print(void) const
{
    std::cout << m_varInt[0];
    
    if(m_remains[0] != 0) {
        std::cout << " (rem. " << m_remains[0] << ")" << std::endl;
    } else {
        std::cout << std::endl;
    }
}
