/**
 * @author Artem Kuznetsov  <kuznear1@fit.cvut.cz>
 * @date 08.05.2021
 */
#pragma once
#include "CDataSize.h"
#include <iostream>

class CInteger : public CDataSize
{
public:
    
    CDataSize * clone() const override;
    
    void print(void) const override;
    
    CInteger(long long int variable);
    
    CInteger(long long int variable, const std::string & type, const std::string & size);
    
    long long int getVariable(void) const;
    
    void writeVariable(CVariable & var) override;
    
    void negativeNum(void) override;
    
    char getSign(void) override;
    
    CDataSize & operator + (const CDataSize & number) override;
    
    CDataSize & operator - (const CDataSize & number) override;
    
    CDataSize & operator * (const CDataSize & number) override;
    
    CDataSize & operator / (const CDataSize & number) override;
    
    
protected:
    
};
