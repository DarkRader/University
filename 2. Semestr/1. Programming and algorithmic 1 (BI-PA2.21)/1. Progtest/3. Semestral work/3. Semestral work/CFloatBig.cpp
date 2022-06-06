/**
 * @author Artem Kuznetsov  <kuznear1@fit.cvut.cz>
 * @date 08.05.2021
 */
#include "CFloatBig.h"

CDataSize * CFloatBig::clone() const
{
    return new CFloatBig(*this);
}

CFloatBig::CFloatBig(const std::vector<std::string> & variable, const std::string & type, const std::string & size)
{
    m_type = type;
    m_size = size;
    
    for(size_t i = 0; variable.size(); i++)
    {
        if(variable[i] == "")
        {
            m_varInt.push_back(NULL);
        }
        long long int numInt = atoi(variable[i].c_str());
        m_varInt.push_back(numInt);
    }
}

void CFloatBig::negativeNum(void)
{
   
}

char CFloatBig::getSign(void)
{
    if(m_varFloat >= 0)
        return '+';
    else
        return '-';
}

CDataSize & CFloatBig::operator + (const CDataSize & number)
{

    
    
    return *this;
}

CDataSize & CFloatBig::operator - (const CDataSize & number)
{

    
    return *this;
}

CDataSize & CFloatBig::operator / (const CDataSize & number)
{

    
    return *this;
}

CDataSize & CFloatBig::operator * (const CDataSize & number)
{


    return *this;
}

void CFloatBig::print(std::ostream & os) const
{
    
}
