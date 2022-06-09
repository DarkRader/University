/**
 * @author Artem Kuznetsov  <kuznear1@fit.cvut.cz>
 * @date 08.05.2021
 */
#include "CFloatBig.h"

CDataSize * CFloatBig::clone() const
{
    return new CFloatBig(*this);
}

CFloatBig::CFloatBig(const std::vector<std::string> & variable, const std::vector<std::string> & floatPart,
                     const std::string & type, const std::string & size)
{
    m_type = type;
    m_size = size;
    for(size_t i = 0; i < variable.size(); i++)
    {
        long long int numInt = atoll(variable[i].c_str());
        m_varInt.push_back(numInt);
    }
    
    for(size_t i = 0; i < floatPart.size(); i++)
    {
        long long int numFloat = atoll(floatPart[i].c_str());
        m_floatPart.push_back(numFloat);
    }
 
}

void CFloatBig::writeVariable(CVariable & var)
{
    
}

void CFloatBig::negativeNum(void)
{
    m_varInt[m_varInt.size() - 1] = m_varInt[m_varInt.size() - 1] * (-1);
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
    std::vector<long long int> num = number.getVecInt();
    std::vector<long long int> flNum = number.getVecFloat();
    
    char symbol = '+';
    
    if(m_varInt[m_varInt.size() - 1] > 0 && num[num.size() - 1] > 0){
        symbol = '+';
    } else if(m_varInt[m_varInt.size() - 1] < 0 && num[num.size() - 1] < 0) {
        symbol = '-';
        m_varInt[m_varInt.size() - 1] = m_varInt[m_varInt.size() - 1] * (-1);
        num[num.size() - 1] = num[num.size() - 1] * (-1);
    }
    
        size_t i = 0, j = 0;
        int lostNull = 0;
        while(i < m_varInt.size() && j < num.size())
        {
            if(m_varInt[i] + num[j] > 1000000000000000000)
            {
                if(m_varInt.size() != i + 1) {
                    m_varInt[i + 1] = m_varInt[i + 1] + 1;
                    m_varInt[i] = (m_varInt[i] + num[j]) - 1000000000000000000;
                    if(lostNull == 1) {
                        m_varInt[i] = m_varInt[i] * 10;
                        lostNull = 0;
                    }
                    if(m_varInt[i] < 100000000000000000)
                        lostNull = 1;
                } else {
                    m_varInt[i + 1] = m_varInt[i + 1] + 1;
                    m_varInt[i] = (m_varInt[i] + num[j]) - 1000000000000000000;
                    if(lostNull == 1) {
                        m_varInt[i] = m_varInt[i] * 10;
                        lostNull = 0;
                    }
                    if(m_varInt[i] < 100000000000000000)
                        lostNull = 1;
                    m_varInt.push_back(1);
                }
            } else {
                m_varInt[i] = (m_varInt[i] + num[j]);
                if(lostNull == 1) {
                    m_varInt[i] = m_varInt[i] * 10;
                    lostNull = 0;
                }
            }
            i++;
            j++;
        }
    if(num.size() > m_varInt.size())
    {
        size_t t = num.size() - m_varInt.size();
        for(size_t i = t; i < num.size(); i++)
            m_varInt.push_back(num[i]);
    }
    
    if(m_floatPart.size() > 1 || flNum.size() > 1)
    {
        
        if(m_floatPart.size() < flNum.size() || (m_floatPart.size() == flNum.size() &&
                                                 m_floatPart[m_floatPart.size() - 1] < flNum[flNum.size() - 1]))
        {
            std::vector<long long int> tmp = flNum;
            flNum = m_floatPart;
            m_floatPart = tmp;
        }
        
        int flag = 0;
        for(size_t i = 0; i < m_floatPart.size(); i++)
        {
            if(sizeNum(m_floatPart[i]) != sizeNum(flNum[i]))
            {
                int size = sizeNum(m_floatPart[i]) - sizeNum(flNum[i]);
                long long int degree = findDegree(size);
                flNum[i] = flNum[i] * degree;
                long long int control = (m_floatPart[i] + flNum[i]);
                if(sizeNum(control) > sizeNum(m_floatPart[i]))
                    flag = 1;
            }
            if(m_floatPart[i] + flNum[i] > 1000000000000000000 || flag == 1)
            {
//                if(m_floatPart.size() != i + 1) {
                    if(i == 0) {
                        m_varInt[0]++;
                    } else {
                        m_floatPart[i - 1]++;
                    }
                    if(flag == 1) {
                        int size = sizeNum(m_floatPart[i]);
                        long long degree = findDegree(size);
                        m_floatPart[i] = (m_floatPart[i] + flNum[i]) - degree;
                    } else
                        m_floatPart[i] = (m_floatPart[i] + flNum[i]) - 1000000000000000000;
//                }
            } else {
                m_floatPart[i] = (m_floatPart[i] + flNum[i]);
            }
        }
    }
    
    if(symbol == '-')
        m_varInt[m_varInt.size() - 1] = m_varInt[m_varInt.size() - 1] * (-1);
    
    return *this;
}

CDataSize & CFloatBig::operator - (const CDataSize & number)
{

    
    return *this;
}

CDataSize & CFloatBig::operator * (const CDataSize & number)
{


    return *this;
}

CDataSize & CFloatBig::operator / (const CDataSize & number)
{

    
    return *this;
}

void CFloatBig::print(void) const
{
    std::cout << "Result: ";
    for(size_t i = m_varInt.size(); i > 0; i--)
        std::cout << m_varInt[i - 1];
    std::cout << ",";
    for(size_t i = 0; i < m_floatPart.size(); i++)
        std::cout << m_floatPart[i];
    std::cout << std::endl;
}

int CFloatBig::sizeNum(long long int num)
{
    int size = 1;
    for(size_t i = num; i >= 10; size++)
    {
        i = i / 10;
    }
    
    return size;
}

long long int CFloatBig::findDegree(size_t size)
{
    long long int degree = 1;
    for(size_t i = 0; i < size; i++)
        degree = degree * 10;
    return degree;
}
