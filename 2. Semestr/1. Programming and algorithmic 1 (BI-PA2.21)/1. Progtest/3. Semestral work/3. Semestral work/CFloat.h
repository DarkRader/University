/**
 * @author Artem Kuznetsov  <kuznear1@fit.cvut.cz>
 * @date 08.05.2021
 */
#pragma once

#include "CDataSize.h"
#include "CFloatBig.h"
#include <iostream>


class CFloat : public CDataSize
{
public:
    
    CDataSize * clone() const override;
    CFloat(void) {}
    
    void print(void) const override;
    
    CFloat(long double varIntPart, long double varFloatPart, const std::string & type, const std::string & size);
    
    CFloat(long long int varInt, const std::string & type, const std::string & size);

    void negativeNum(void) override;
    
    char getSign(void) override;
    
    CDataSize & operator + (const CDataSize & number) override;
    
    CDataSize & operator - (const CDataSize & number) override;
    
    CDataSize & operator * (const CDataSize & number) override;
    
    CDataSize & operator / (const CDataSize & number) override;
    
protected:
    int sizeNum(long long int num) const;
    long long int findDegree(size_t size);
    void plusFlPart(long long int number);
    void minusFlPart(long long int number);
};
