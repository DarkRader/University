/**
 * @author Artem Kuznetsov  <kuznear1@fit.cvut.cz>
 * @date 08.05.2021
 */
#pragma once

#include "CDataSize.h"
#include <iostream>


class CFloat : public CDataSize
{
public:
    
    CDataSize * clone() const override;
    CFloat(void) {}
    CFloat(long double variable);
    
    CFloat(long double variable, const std::string & type, const std::string & size);
    
    CFloat(long double varFloat, long long int varInt, const std::string & type, const std::string & size);
    
    long long int getVariable(void) const;

    void negativeNum(void) override;
    
    char getSign(void) override;
    
    CDataSize & operator + (const CDataSize & number) override;
    
    CDataSize & operator - (const CDataSize & number) override;
    
    CDataSize & operator * (const CDataSize & number) override;
    
    CDataSize & operator / (const CDataSize & number) override;
    
    
    
protected:
    long double m_Float;
    virtual void print(std::ostream & os) const override;
    
    
};
