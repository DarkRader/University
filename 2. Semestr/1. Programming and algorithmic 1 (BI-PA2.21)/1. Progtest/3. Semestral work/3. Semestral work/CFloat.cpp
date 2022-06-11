/**
 * @author Artem Kuznetsov  <kuznear1@fit.cvut.cz>
 * @date 08.05.2021
 */
#include "CFloat.h"

CDataSize * CFloat::clone() const
{
    return new CFloat(*this);
}

CFloat::CFloat(long double varIntPart, long double varFloatPart, const std::string & type, const std::string & size)
{
    m_varInt.push_back(varIntPart);
    m_floatPart.push_back(varFloatPart);
    m_type = type;
    m_size = size;
    m_remains.push_back(0);
}

CFloat::CFloat(long long int varInt, const std::string & type, const std::string & size)
{
    m_varInt.push_back(varInt);
    m_floatPart.push_back(0);
    m_type = type;
    m_size = size;
    m_remains.push_back(0);
}

void CFloat::negativeNum(void)
{
    m_varInt[0] = m_varInt[0] * (-1);
}

char CFloat::getSign(void)
{
    if(m_varInt[0] >= 0)
        return '+';
    else
        return '-';
}

CDataSize & CFloat::operator + (const CDataSize & number)
{
    char operation = '+';
    
    if((m_varInt[0] > 0 && number.getVarInt() > 0) || (m_varInt[0] < 0 && number.getVarInt() < 0))
        operation = '+';
    else
        operation = '-';
    
    m_varInt[0] += number.getVarInt();
    
    if(operation == '+')
        plusFlPart(number.getVarFloat());
    else
        minusFlPart(number.getVarFloat());
    
    m_remains[0] += number.getRemains();
    
    return *this;
}

CDataSize & CFloat::operator - (const CDataSize & number)
{
    m_varInt[0] -= number.getVarInt();
    
    minusFlPart(number.getVarFloat());
    
    m_remains[0] += number.getRemains();
    
    return *this;
}

CDataSize & CFloat::operator * (const CDataSize & number)
{
    CFloatBig lhs(m_varInt[0], m_floatPart[0], "float", "big");
    CFloatBig rhs(number.getVarInt(), number.getVarFloat(), "float", "big");
    
    lhs * rhs;
    
    m_varInt[0] = lhs.getVarInt();
    m_floatPart[0] = lhs.getVarFloat();
    m_remains[0] += number.getRemains();
    
    return *this;
}

CDataSize & CFloat::operator / (const CDataSize & number)
{
    throw 2;
    return *this;
}

void CFloat::plusFlPart(long long int number)
{
    long long int lhsFloat;
    long long int rhsFloat;
    
    if(m_floatPart[0] > number) {
        lhsFloat = m_floatPart[0];
        rhsFloat = number;
    } else {
        lhsFloat = number;
        rhsFloat = m_floatPart[0];
    }
    
    if(lhsFloat == 0) {
        m_floatPart[0] = rhsFloat;
        return ;
    } else if(rhsFloat == 0){
        m_floatPart[0] = lhsFloat;
        return ;
    }
    
    long long int control = lhsFloat + rhsFloat;
    if(sizeNum(lhsFloat) != sizeNum(rhsFloat))
    {
        int size = sizeNum(lhsFloat) - sizeNum(rhsFloat);
        long long int degree = findDegree(size);
        rhsFloat = rhsFloat * degree;
        control = lhsFloat + rhsFloat;
        if(sizeNum(control) > sizeNum(lhsFloat))
        {
            if(m_varInt[0] > 0) {
                m_varInt[0]++;
            } else {
                m_varInt[0]--;
            }
            int size = sizeNum(lhsFloat);
            long long degree = findDegree(size);
            m_floatPart[0] = (lhsFloat + rhsFloat) - degree;
        } else {
            m_floatPart[0] = lhsFloat + rhsFloat;
        }
    } else if(sizeNum(control) > sizeNum(lhsFloat)) {
        if(m_varInt[0] > 0) {
            m_varInt[0]++;
        }
        else {
            m_varInt[0]--;
        }
        m_floatPart[0] = (lhsFloat + rhsFloat) - 1000000000000000000;
    } else {
        m_floatPart[0] = lhsFloat + rhsFloat;
    }
}

void CFloat::minusFlPart(long long int number)
{
    long long int lhsFloat = m_floatPart[0];
    long long int rhsFloat = number;
    
    if(lhsFloat == 0) {
        m_floatPart[0] = rhsFloat;
        return ;
    } else if(rhsFloat == 0){
        m_floatPart[0] = lhsFloat;
        return ;
    }
    
    if(sizeNum(lhsFloat) != sizeNum(rhsFloat))
    {
        long long int degree;
        if(lhsFloat > rhsFloat)
        {
            int size = sizeNum(lhsFloat) - sizeNum(rhsFloat);
            degree = findDegree(size);
            rhsFloat = rhsFloat * degree;
        } else {
            int size = sizeNum(rhsFloat) - sizeNum(lhsFloat);
            degree = findDegree(size);
            lhsFloat = lhsFloat * degree;
        }
        if(lhsFloat - rhsFloat < 0)
        {
            if(m_varInt[0] > 0)
                m_varInt[0]--;
            else
                m_varInt[0]++;
            int size = sizeNum(lhsFloat);
            long long degree = findDegree(size);
            m_floatPart[0] = degree + (lhsFloat - rhsFloat);
        }
    } else if(lhsFloat - rhsFloat < 0) {
        if(m_varInt[0] > 0)
            m_varInt[0]--;
        else
            m_varInt[0]++;
        m_floatPart[0] = 1000000000000000000 + (lhsFloat - rhsFloat);
    } else {
        m_floatPart[0] = lhsFloat - rhsFloat;
    }
}

int CFloat::sizeNum(long long int num) const
{
    int size = 1;
    for(size_t i = num; i >= 10; size++)
    {
        i = i / 10;
    }
    
    return size;
}

long long int CFloat::findDegree(size_t size)
{
    long long int degree = 1;
    for(size_t i = 0; i < size; i++)
        degree = degree * 10;
    return degree;
}

void CFloat::print(void) const
{
    std::cout << "Result: ";
    std::cout << m_varInt[0] << "," << m_floatPart[0];
    
    if(m_remains[0] != 0) {
        std::cout << " (rem. " << m_remains[0] << ")" << std::endl;
    } else {
        std::cout << std::endl;
    }
}
