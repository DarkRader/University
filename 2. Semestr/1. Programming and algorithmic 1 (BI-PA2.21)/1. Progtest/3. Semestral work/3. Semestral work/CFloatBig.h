/**
 * @author Artem Kuznetsov  <kuznear1@fit.cvut.cz>
 * @date 08.05.2021
 */
#pragma once
#include "CDataSize.h"

class CFloatBig : public CDataSize
{
public:
    
    CDataSize * clone() const override;
    
    void negativeNum(void) override;
    
    char getSign(void) override;
    
    CFloatBig(const std::vector<std::string> & variable, const std::string & type, const std::string & size);
    
    CDataSize & operator + (const CDataSize & number) override;
    
    CDataSize & operator - (const CDataSize & number) override;
    
    CDataSize & operator * (const CDataSize & number) override;
    
    CDataSize & operator / (const CDataSize & number) override;

    
    
protected:
    virtual void print(std::ostream & os) const override;
    
};
