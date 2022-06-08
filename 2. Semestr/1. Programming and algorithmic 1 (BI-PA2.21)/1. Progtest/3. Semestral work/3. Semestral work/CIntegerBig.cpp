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

CIntegerBig::CIntegerBig(const long long int variable, const std::string & type, const std::string & size)
{
    m_type = type;
    m_size = size;
    m_varInt.push_back(0);
}

void CIntegerBig::writeVariable(CVariable & var)
{
    
}

void CIntegerBig::negativeNum(void)
{
    m_varInt[m_varInt.size() - 1] = m_varInt[m_varInt.size() - 1] * (-1);
}

char CIntegerBig::getSign(void)
{
    if(m_varInt[m_varInt.size() - 1] >= 0)
        return '+';
    else
        return '-';
}

CDataSize & CIntegerBig::operator + (const CDataSize & number)
{
    std::vector<long long int> num = number.getVecInt();
    
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
    
    if(symbol == '-')
        m_varInt[m_varInt.size() - 1] = m_varInt[m_varInt.size() - 1] * (-1);
    
    return *this;
}

CDataSize & CIntegerBig::operator - (const CDataSize & number)
{
    std::vector<long long int> num = number.getVecInt();
    
    char symbol = '+';
        
        if((m_varInt[m_varInt.size() - 1] <= 0 && num[num.size() - 1] >= 0) ||
           (m_varInt[m_varInt.size() - 1] >= 0 && num[num.size() - 1] <= 0))
        {
            if(m_varInt[m_varInt.size() - 1] >= 0)
            {
                symbol = '+';
                num[num.size() - 1] = num[num.size() - 1] * (-1);
            } else {
                symbol = '-';
                m_varInt[m_varInt.size() - 1] = m_varInt[m_varInt.size() - 1] * (-1);
            }
        }
        
        size_t i = 0, j = 0;
        while(i < m_varInt.size() && j < num.size())
        {
                if(m_varInt[i] - num[i] < 0)
                {
                    if(m_varInt.size() != i + 1)
                    {
                        m_varInt[i + 1] = m_varInt[i + 1] - 1;
                        m_varInt[i] = 1000000000000000000 + m_varInt[i] - num[i];
                    } else {
                        m_varInt[i] = m_varInt[i] - num[i];
                        m_varInt[i] = m_varInt[i] * (-1);
                    }
                } else {
                    m_varInt[i] = m_varInt[i] - num[i];
                }
            i++;
            j++;
        }
    
    if(symbol == '-')
        m_varInt[m_varInt.size() - 1] = m_varInt[m_varInt.size() - 1] * (-1);
    
    return *this;
}

CDataSize & CIntegerBig::operator * (const CDataSize & number)
{
    char symbol = '+';
    std::vector<long long int> secondNum = number.getVecInt();
    
    if(m_varInt[m_varInt.size() - 1] < 0 && secondNum[secondNum.size() - 1] < 0)
    {
        m_varInt[m_varInt.size() - 1] = m_varInt[m_varInt.size() - 1] * (-1);
        secondNum[secondNum.size() - 1] = secondNum[secondNum.size() - 1] * (-1);
    } else if(m_varInt[m_varInt.size() - 1] > 0 && secondNum[secondNum.size() - 1] < 0) {
        secondNum[secondNum.size() - 1] = secondNum[secondNum.size() - 1] * (-1);
        symbol = '-';
    } else if(m_varInt[m_varInt.size() - 1] < 0 && secondNum[secondNum.size() - 1] > 0) {
        m_varInt[m_varInt.size() - 1] = m_varInt[m_varInt.size() - 1] * (-1);
        symbol = '-';
    }
    
    
    std::string num = "";
    for(size_t i = m_varInt.size(); i > 0; i--)
    {
        num = num + std::to_string(m_varInt[i - 1]);
    }
    std::string num2 = "";
    for(size_t i = secondNum.size(); i > 0; i--)
    {
        num2 = num2 + std::to_string(secondNum[i - 1]);
    }
    
    if(num.size() < num2.size())
    {
        std::string tmp = num;
        num = num2;
        num2 = tmp;
    }
    
    if(num == "0" || num2 == "0")
    {
        for(size_t i = m_varInt.size(); i > 0; i--)
        {
            if(m_varInt.size() > 1)
                m_varInt.erase(m_varInt.begin() + i - 1);
        }
        m_varInt[0] = 0;
        return *this;
    }

    std::string result(num.size() + num2.size(), 0);
    for(size_t i = num.size(); i > 0; i--) {
        for(size_t j = num2.size(); j > 0; j--) {
            int tmpNum = (num[i - 1] - '0') * (num2[j - 1] - '0') + result[i - 1 + j - 1 + 1];
            result[i - 1 + j - 1 + 1] = (tmpNum % 10);
            result[i - 1 + j - 1] += (tmpNum / 10);
        }
    }
    if(result[0] + '0' == '0')
        result.erase(result.begin());
    
    size_t size = result.size();
    std::string splitStr = "";
    size_t vecSize = 0;
    int lostNull = 0;
    while(size > 17)
    {
        size = size - 18;
        for(size_t i = size; i < size + 18; i++)
        {
            result[i] += '0';
            splitStr = splitStr + result[i];
        }
        long long int newInt = atoll(splitStr.c_str());
        if(lostNull == 1) {
            newInt = newInt * 10;
            lostNull = 0;
        }
        if(vecSize != m_varInt.size()) {
            m_varInt[vecSize] = newInt;
            vecSize++;
            if(splitStr[0] == '0')
                lostNull = 1;
        } else {
            m_varInt.push_back(newInt);
            vecSize++;
            if(splitStr[0] == '0')
                lostNull = 1;
        }
        splitStr = "";
    }
    if(size != 0)
    {
        for(size_t i = 0; i < size; i++)
        {
            result[i] += '0';
            splitStr = splitStr + result[i];
        }
        long long int newInt = atoll(splitStr.c_str());
        if(lostNull == 1) {
            newInt = newInt * 10;
        }
        if(vecSize != m_varInt.size()) {
            m_varInt[vecSize] = newInt;
            vecSize++;
        } else {
            m_varInt.push_back(newInt);
            vecSize++;
        }
    }

    if(symbol == '-')
        m_varInt[m_varInt.size() - 1] = m_varInt[m_varInt.size() - 1] * (-1);

    return *this;
}

CDataSize & CIntegerBig::operator / (const CDataSize & number)
{

    
    return *this;
}

void CIntegerBig::print(void) const
{
    std::cout << "Result: ";
    for(size_t i = m_varInt.size(); i > 0; i--)
        std::cout << m_varInt[i - 1];
    std::cout << std::endl;
}
