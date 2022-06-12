/**
 * @author Artem Kuznetsov  <kuznear1@fit.cvut.cz>
 * @date 08.05.2021
 */
#pragma once
#include "CDataSize.h"
#include <iostream>
#include <fstream>

class CInteger : public CDataSize
{
public:
    
    CDataSize * clone() const override;
    
    CInteger(long long int variable);
    
    CInteger(long long int variable, const std::string & type, const std::string & size);
    
    void negativeNum(void) override;
    char getSign(void) override;
    
    CDataSize & operator + (const CDataSize & number) override;
    
    CDataSize & operator - (const CDataSize & number) override;
    
    CDataSize & operator * (const CDataSize & number) override;
    
    CDataSize & operator / (const CDataSize & number) override;
    
    void print(void) const override;
    
    
protected:
    
};
