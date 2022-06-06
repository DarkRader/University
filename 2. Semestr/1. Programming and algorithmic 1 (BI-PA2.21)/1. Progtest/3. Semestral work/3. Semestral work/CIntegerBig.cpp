/**
 * @author Artem Kuznetsov  <kuznear1@fit.cvut.cz>
 * @date 08.05.2021
 */
#include "CIntegerBig.h"

CDataSize * CIntegerBig::clone() const
{
    return new CIntegerBig(*this);
}

CIntegerBig::CIntegerBig(const std::vector<std::string> & variable, const std::string & type, const std::string & size)
{
    m_type = type;
    m_size = size;
    
    for(size_t i = 0; i < variable.size(); i++)
    {
        long long int numInt = atoll(variable[i].c_str());
        m_varInt.push_back(numInt);
    }
}

void CIntegerBig::negativeNum(void)
{
   
}

char CIntegerBig::getSign(void)
{
    if(m_varInt[0] >= 0)
        return '+';
    else
        return '-';
}

CDataSize & CIntegerBig::operator + (const CDataSize & number)
{

    
    
    return *this;
}

CDataSize & CIntegerBig::operator - (const CDataSize & number)
{

    
    return *this;
}

CDataSize & CIntegerBig::operator / (const CDataSize & number)
{

    
    return *this;
}

CDataSize & CIntegerBig::operator * (const CDataSize & number)
{


    return *this;
}

void CIntegerBig::print(std::ostream & os) const
{
    
}
