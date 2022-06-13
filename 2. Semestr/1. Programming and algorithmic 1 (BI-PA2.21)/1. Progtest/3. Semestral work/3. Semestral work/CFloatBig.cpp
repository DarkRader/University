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

    m_remains.push_back(0);
}

CFloatBig::CFloatBig(long long int varInt, long long int floatPart, const std::string & type, const std::string & size)
{
    m_varInt.push_back(varInt);
    m_floatPart.push_back(floatPart);
    m_remains.push_back(0);
}

CFloatBig::CFloatBig(std::vector<long long int> num, std::vector<long long int> floatPart,  const std::string & type, const std::string & size)
{
    m_type = type;
    m_size = size;

    m_varInt = num;
    m_floatPart = floatPart;
    m_remains.push_back(0);}

void CFloatBig::negativeNum(void)
{
    m_varInt[m_varInt.size() - 1] = m_varInt[m_varInt.size() - 1] * (-1);
}

char CFloatBig::getSign(void)
{
    if(m_varInt[m_varInt.size() - 1] >= 0)
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

    if(m_floatPart.size() > 1 || flNum.size() > 1)
        ifExistFlPartPlus(flNum);

    if(symbol == '-')
        m_varInt[m_varInt.size() - 1] = m_varInt[m_varInt.size() - 1] * (-1);

    addRem(number);

    return *this;
}

void CFloatBig::ifExistFlPartPlus(std::vector<long long int> & flNum)
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
        } else {
            m_floatPart[i] = (m_floatPart[i] + flNum[i]);
        }
    }
}

CDataSize & CFloatBig::operator - (const CDataSize & number)
{
    std::vector<long long int> num = number.getVecInt();
    std::vector<long long int> flNum = number.getVecFloat();

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

    if(m_varInt[m_varInt.size() - 1] == 0 && m_varInt.size() != 1)
        m_varInt.erase(m_varInt.begin() + m_varInt.size() - 1);

    if(m_floatPart.size() > 1 || flNum.size() > 1)
        ifExistFlPartMinus(flNum);

    if(symbol == '-')
        m_varInt[m_varInt.size() - 1] = m_varInt[m_varInt.size() - 1] * (-1);

    addRem(number);

    return *this;
}

void CFloatBig::ifExistFlPartMinus(std::vector<long long int> & flNum)
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
        if(i > flNum.size() - 1)
            break;
        if(sizeNum(m_floatPart[i]) != sizeNum(flNum[i]))
        {
            int size = sizeNum(m_floatPart[i]) - sizeNum(flNum[i]);
            long long int degree = findDegree(size);
            flNum[i] = flNum[i] * degree;
            if(m_floatPart[i] - flNum[i] < 0)
                flag = 1;
        }

        if(m_floatPart[i] - flNum[i] < 0 || flag == 1)
        {
            if(i == 0) {
                m_varInt[0]--;
            } else {
                m_floatPart[i - 1]--;
            }
            if(flag == 1) {
                int size = sizeNum(m_floatPart[i]);
                long long degree = findDegree(size);
                m_floatPart[i] = degree + (m_floatPart[i] - flNum[i]);
            } else
                m_floatPart[i] = 1000000000000000000 + m_floatPart[i] - flNum[i];
        } else {
            m_floatPart[i] = m_floatPart[i] - flNum[i];
        }
    }
}

CDataSize & CFloatBig::operator * (const CDataSize & number)
{
    std::vector<long long int> secondNum = number.getVecInt();
    std::vector<long long int> secNumFloat = number.getVecFloat();
    char symbol = whatSymbol(secondNum);

    std::string num = transformToString(m_varInt, "int");
    std::string num2 = transformToString(secondNum, "int");
    std::string numFloat = transformToString(m_floatPart, "float");
    std::string numFloat2 = transformToString(secNumFloat, "float");
    size_t sizeFlPart = addNull(numFloat, numFloat2);
    num = num + numFloat;
    num2 = num2 + numFloat2;

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
    delExtraZero(res, sizeFlPart);
    transFromStr(res, sizeFlPart);

    if(symbol == '-')
        m_varInt[m_varInt.size() - 1] = m_varInt[m_varInt.size() - 1] * (-1);

    addRem(number);

    return *this;
}

CDataSize & CFloatBig::operator / (const CDataSize & number)
{
    throw 2;
    return *this;
}

int CFloatBig::sizeNum(long long int num) const
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

char CFloatBig::whatSymbol(std::vector<long long int> & num)
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

std::string CFloatBig::transformToString(std::vector<long long int> & vecNum, const std::string & typ)
{
    std::string num = "";
    if(typ == "int") {
        for(size_t i = vecNum.size(); i > 0; i--)
            num = num + std::to_string(vecNum[i - 1]);
    } else {
        for(size_t i = 0; i < vecNum.size(); i++)
            num = num + std::to_string(vecNum[i]);
    }

    return num;
}

void CFloatBig::transFromStr(std::string & str, size_t & sizeflNum)
{
    size_t nextMinusSize = sizeflNum;

    transFromStrFlPart(str, sizeflNum);

    size_t size = str.size() - nextMinusSize;
    std::string splitStr = "";
    size_t vecSize = 0;
    while(size > 17)
    {
        size = size - 18;
        for(size_t i = size; i < size + 18; i++)
        {
            str[i] += '0';
            splitStr = splitStr + str[i];
        }
        long long int newInt = atoll(splitStr.c_str());
        if(vecSize != m_varInt.size()) {
            m_varInt[vecSize] = newInt;
            vecSize++;
        } else {
            m_varInt.push_back(newInt);
            vecSize++;
        }
        splitStr = "";
    }
    if(size != 0)
    {
        for(size_t i = 0; i < size; i++)
        {
            str[i] += '0';
            splitStr = splitStr + str[i];
        }
        long long int newInt = atoll(splitStr.c_str());
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

void CFloatBig::transFromStrFlPart(std::string & str, size_t & sizeflNum)
{
    std::string splitFlPart = "";
    size_t vecFlPart = 0;

    if(sizeflNum > 0)
    {
        while(sizeflNum > 17)
        {
            size_t tmpSize = str.size() - sizeflNum + 18;
            for(size_t i = (str.size() - sizeflNum); i < tmpSize; i++) {
                str[i] += '0';
                splitFlPart += str[i];
            }
            sizeflNum -= 18;
            long long int newFlPart = atoll(splitFlPart.c_str());
            if(vecFlPart != m_floatPart.size()) {
                m_floatPart[vecFlPart] = newFlPart;
                vecFlPart++;
            } else {
                m_floatPart.push_back(newFlPart);
                vecFlPart++;
            }
            splitFlPart = "";
        }
        if(sizeflNum != 0)
        {
            for(size_t i = (str.size() - sizeflNum); i < str.size(); i++)
            {
                str[i] += '0';
                splitFlPart = splitFlPart + str[i];
            }
            long long int newFlPart = atoll(splitFlPart.c_str());
            if(vecFlPart != m_floatPart.size()) {
                m_floatPart[vecFlPart] = newFlPart;
                vecFlPart++;
            } else {
                m_floatPart.push_back(newFlPart);
                vecFlPart++;
            }
        }
        for(size_t i = m_floatPart.size(); i > vecFlPart; i--)
            m_floatPart.erase(m_floatPart.begin() + i - 1);
    }
}

std::string CFloatBig::multAlg(std::string num, std::string num2)
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

void CFloatBig::delExtraZero(std::string & str, size_t size)
{
    while(str.size() > 1 && str[0] + '0' == '0')
    {
        str.erase(0, 1);
    }

    while(str.size() > 1 && str[str.size() - 1] + '0' == '0')
    {
        if(size > 0) {
            str.erase(str.begin() + str.size() - 1);
            size--;
        } else
            break;
    }

    for(size_t i = str.size(); size > 0; size--, i--)
        str.erase(str.begin() + i - 1);

//    for (int i = 0; i < str.size(); i++) {
//        str[i] += '0';
//       }
}

size_t CFloatBig::addNull(std::string & flNum, std::string & flNum2)
{
    if(flNum.size() == flNum2.size()) {
        return flNum.size();
    } else if(flNum.size() > flNum2.size()) {
        size_t addSize = flNum.size() - flNum2.size();
        for(size_t i = 0; i < addSize; i++)
            flNum2 = flNum2 + '0';
        return flNum.size();
    } else if(flNum.size() < flNum2.size()) {
        size_t addSize = flNum2.size() - flNum.size();
        for(size_t i = 0; i < addSize; i++)
            flNum = flNum + '0';
        return flNum2.size();
    }

    return flNum.size();
}

void CFloatBig::addRem(const CDataSize & number)
{
    CIntegerBig lhs(m_remains, "int", "big");
    CIntegerBig rhs(number.getVecRem(), "int", "big");

    lhs + rhs;

    m_remains = lhs.getVecInt();
}

void CFloatBig::print(void) const
{
    for(size_t i = m_varInt.size(); i > 0; i--) {
        if(i != m_varInt.size() && sizeNum(m_varInt[i - 1]) < 18)
        {
          size_t lostNull = 18 - sizeNum(m_varInt[i - 1]);
            for(size_t i = 0; i < lostNull; i++)
                std::cout << '0';
        }
        std::cout << m_varInt[i - 1];
    }
    std::cout << ",";
    for(size_t i = 0; i < m_floatPart.size(); i++) {
        if(i != m_floatPart.size() - 1 && sizeNum(m_floatPart[i]) < 18)
        {
            size_t lostNull = 18 - sizeNum(m_floatPart[i]);
            for(size_t i = 0; i < lostNull; i++)
                std::cout << '0';
        }
        std::cout << m_floatPart[i];
    }

    if((m_remains.size() > 1 && m_remains[m_remains.size() - 1] != 0) || m_remains[0] != 0) {
        std::cout << " (rem. ";
        for(size_t i = m_remains.size(); i > 0; i--) {
            if(i != m_remains.size() && sizeNum(m_remains[i - 1]) < 18)
            {
                size_t lostNull = 18 - sizeNum(m_remains[i - 1]);
                for(size_t i = 0; i < lostNull; i++)
                    std::cout << '0';
            }
            std::cout << m_remains[i - 1];
        }
        std::cout << ")";
    }

    std::cout << std::endl;
}
