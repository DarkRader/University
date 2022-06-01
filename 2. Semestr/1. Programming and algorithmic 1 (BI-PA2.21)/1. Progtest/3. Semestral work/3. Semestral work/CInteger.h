/**
 * @author Artem Kuznetsov  <kuznear1@fit.cvut.cz>
 * @date 08.05.2021
 */
#pragma once
#include "CType.h"

class CInteger : public CType
{
public:
    
    CType * clone() const override;
    
    CInteger(long long int variable);
    
    long long int getVariable(void) const;
    
    std::string getNewVariable(void) const;
    
    CType & operator + (const CType & number) override;
    
    CType & operator - (const CType & number) override;
    
    CType & operator * (const CType & number) override;
    
    CType & operator / (const CType & number);
    
    
protected:
    virtual void print(std::ostream & os) const override;
    
};
