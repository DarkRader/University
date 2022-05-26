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
    
    CType & operator + (const CType & number) const override;
    
    CType & operator - (const CType & number) const override;
    
    CType & operator * (const CType & number) const override;
    
    CType & operator / (const CType & number) const override;
    
    
protected:
    
    
};
