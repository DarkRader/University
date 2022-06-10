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
    m_varInt.push_back(variable);
}

CIntegerBig::CIntegerBig(std::string & variable, const std::string & type, const std::string & size)
{
    m_type = type;
    m_size = size;
    
    transFromStr(variable, '-');
}

CIntegerBig::CIntegerBig(std::vector<long long int> num, const std::string & type, const std::string & size)
{
    m_type = type;
    m_size = size;
    
    m_varInt = num;
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
        while(i < m_varInt.size() && j < num.size())
        {
            if(m_varInt[i] + num[j] > 1000000000000000000)
            {
                if(m_varInt.size() != i + 1) {
                    m_varInt[i + 1] = m_varInt[i + 1] + 1;
                    m_varInt[i] = (m_varInt[i] + num[j]) - 1000000000000000000;
                } else {
                    m_varInt[i + 1] = m_varInt[i + 1] + 1;
                    m_varInt[i] = (m_varInt[i] + num[j]) - 1000000000000000000;
                    m_varInt.push_back(1);
                }
            } else {
                m_varInt[i] = (m_varInt[i] + num[j]);
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
    
    if(m_varInt[m_varInt.size() - 1] == 0)
        m_varInt.erase(m_varInt.begin() + m_varInt.size() - 1);
    
    if(symbol == '-')
        m_varInt[m_varInt.size() - 1] = m_varInt[m_varInt.size() - 1] * (-1);
    
    return *this;
}

CDataSize & CIntegerBig::operator * (const CDataSize & number)
{
    std::vector<long long int> secondNum = number.getVecInt();
    char symbol = whatSymbol(secondNum);
    
    std::string num = transformToString(m_varInt, num);
    std::string num2 = transformToString(secondNum, num2);;
    
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
    
    std::string res = multAlg(num, num2);
    
    delExtraZero(res);
    transFromStr(res, '*');

    if(symbol == '-')
        m_varInt[m_varInt.size() - 1] = m_varInt[m_varInt.size() - 1] * (-1);

    return *this;
}

CDataSize & CIntegerBig::operator / (const CDataSize & number)
{
    std::vector<long long int> secondNum = number.getVecInt();
    char symbol = whatSymbol(secondNum);
    
    if(m_varInt.size() < secondNum.size() ||
       (m_varInt.size() == secondNum.size() && m_varInt[m_varInt.size() - 1] < secondNum[secondNum.size() - 1]))
    {
        for(size_t i = 0; i < m_varInt.size(); i++)
            m_remains.push_back(m_varInt[i]);
        if(symbol == '-')
            m_remains[m_remains.size() - 1] = m_remains[m_remains.size() - 1] * (-1);
        return *this;
    }
    
    std::string num = "";
    num = transformToString(m_varInt, num);
    
    std::string num2 = "";
    num2 = transformToString(secondNum, num2);;
    
    if(num == "0")
    {
        for(size_t i = m_varInt.size(); i > 0; i--)
        {
            if(m_varInt.size() > 1)
                m_varInt.erase(m_varInt.begin() + i - 1);
        }
        m_varInt[0] = 0;
        return *this;
    } else if(num2 == "0")
    {
        std::cout << "You can't divide number on zero!" << std::endl;
        return *this;
    }
    
    std::string res = "0";
    std::string minuend = num;
    std::string subtrahend = num2;
    
    while(subtrahend.size() < minuend.size())
    {
        subtrahend += '0';
    }
     
    for( ; ; )
    {
        while(!controlSize(minuend, subtrahend))
        {
            reduceDivision(minuend, subtrahend);
            incDivision(res);
        }
        if(subtrahend.size() <= num2.size())
        {
            break;
        }
        
        subtrahend.erase(subtrahend.size() - 1);
        res += '0';
        delExtraZero(res);
    }
    
    //controlAnswer(res, num, num2);
    
    transFromStr(res, '/');
    
    if(symbol == '-')
        m_varInt[m_varInt.size() - 1] = m_varInt[m_varInt.size() - 1] * (-1);
    
    return *this;
}

void CIntegerBig::incDivision(std::string &  x)
{
    for(size_t i = x.size() - 1 ; ; i--)
        {
            if(x[i] < '9')
            {
                x[i]++;
                return;
            }
            else
            {
                x[i] = '0';
                if(i == 0)
                {
                    x.insert(0, "1");
                    return;
                }
            }
        }
}

void  CIntegerBig::reduceDivision(std::string & minuend, const std::string & subtrahend)
{
    for(size_t pos = 0; pos < subtrahend.size(); pos++)
        {
            size_t minuend_pos = minuend.size() - 1 - pos;
            size_t subtrahend_pos = subtrahend.size() - 1 - pos;
     
            char &minuend_dig_ref = minuend[minuend_pos];
            const char &subtrahend_dig_ref = subtrahend[subtrahend_pos];
     
            if(minuend_dig_ref >= subtrahend_dig_ref)
            {
                minuend_dig_ref -= subtrahend_dig_ref - '0';
            }
            else
            {
                (minuend_dig_ref -= subtrahend_dig_ref - '0') += 10;
                for(int i = 1 ; ; i++)
                {
                    if(minuend[minuend_pos - i] == '0')
                    {
                        minuend[minuend_pos - i] = '9';
                    }
                    else
                    {
                        minuend[minuend_pos - i]--;
                        break;
                    }
                }
            }
            delExtraZero(minuend);
        }
    delExtraZero(minuend);
}

bool CIntegerBig::controlSize(std::string  x, std::string  y)
{
    delExtraZero(x);
    delExtraZero(y);

    if(x.size() == y.size())
        return x < y;
    else
        return x.size() < y.size();
    
    return true;
}

void  CIntegerBig::delExtraZero(std::string & str)
{
    while(str.size() > 1 && str[0] == '0')
        {
            str.erase(0, 1);
        }
}

char CIntegerBig::whatSymbol(std::vector<long long int> & num)
{
    if(m_varInt[m_varInt.size() - 1] < 0 && num[num.size() - 1] < 0)
    {
        m_varInt[m_varInt.size() - 1] = m_varInt[m_varInt.size() - 1] * (-1);
        num[num.size() - 1] = num[num.size() - 1] * (-1);
        return '+';
    } else if(m_varInt[m_varInt.size() - 1] > 0 && num[num.size() - 1] < 0) {
        num[num.size() - 1] = num[num.size() - 1] * (-1);
        return '-';
    } else if(m_varInt[m_varInt.size() - 1] < 0 && num[num.size() - 1] > 0) {
        m_varInt[m_varInt.size() - 1] = m_varInt[m_varInt.size() - 1] * (-1);
        return '-';
    }
    
    return '+';
}

std::string CIntegerBig::transformToString(std::vector<long long int> & vecNum, std::string & num)
{
    num = "";
    for(size_t i = vecNum.size(); i > 0; i--)
        num = num + std::to_string(vecNum[i - 1]);
    return num;
}

void CIntegerBig::transFromStr(std::string & str, const char operation)
{
    size_t size = str.size();
    std::string splitStr = "";
    size_t vecSize = 0;
    int lostNull = 0;
    while(size > 17)
    {
        size = size - 18;
        for(size_t i = size; i < size + 18; i++)
        {
            if(operation == '*')
                str[i] += '0';
            splitStr = splitStr + str[i];
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
            if(operation == '*')
                str[i] += '0';
            splitStr = splitStr + str[i];
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
    for(size_t i = m_varInt.size(); i > vecSize; i--)
        m_varInt.erase(m_varInt.begin() + i - 1);
}

void CIntegerBig::controlAnswer(std::string res, std::string num, std::string num2)
{
    std::string control = multAlg(res, num2);
    //transFromStr(control, '*');
    for (int i = 0; i < control.size(); i++) {
        control[i] += '0';
       }
    delExtraZero(control);
    
    if(num == control)
        return;
    else {
        CIntegerBig lhs(num, "int", "big");
        CIntegerBig rhs(control, "int", "big");
        
        lhs - rhs;
        
        for(size_t i = 0; i < lhs.getVecInt().size(); i++)
            m_remains.push_back(lhs.getVecInt()[i]);
    }
}

std::string CIntegerBig::multAlg(std::string num, std::string num2)
{
    std::string res(num.size() + num2.size(), 0);
    for(size_t i = num.size(); i > 0; i--) {
        for(size_t j = num2.size(); j > 0; j--) {
            int tmpNum = (num[i - 1] - '0') * (num2[j - 1] - '0') + res[i - 1 + j - 1 + 1];
            res[i - 1 + j - 1 + 1] = (tmpNum % 10);
            res[i - 1 + j - 1] += (tmpNum / 10);
        }
    }
    
    return res;
}

int CIntegerBig::sizeNum(long long int num) const
{
    int size = 1;
    for(size_t i = num; i >= 10; size++)
    {
        i = i / 10;
    }
    
    return size;
}

void CIntegerBig::print(std::ostream & history) const
{
    std::cout << "Result: ";
    for(size_t i = m_varInt.size(); i > 0; i--) {
        if(i != m_varInt.size() && sizeNum(m_varInt[i - 1]) < 18)
        {
            int lostNull = 18 - sizeNum(m_varInt[i - 1]);
            for(size_t i = 0; i < lostNull; i++)
                std::cout << '0';
        }
        std::cout << m_varInt[i - 1];
    }
    std::cout << std::endl;
}
