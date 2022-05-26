/**
 * @author Artem Kuznetsov  <kuznear1@fit.cvut.cz>
 * @date 08.05.2021
 */
#pragma once
#include "CTypeBig.h"

class CIntegerBig : public CTypeBig
{
public:
    
    CTypeBig * clone() const override;
    
    CTypeBig & operator + (const CTypeBig & number) const override;
    
    CTypeBig & operator - (const CTypeBig & number) const override;
    
    CTypeBig & operator * (const CTypeBig & number) const override;
    
    CTypeBig & operator / (const CTypeBig & number) const override;
    
    
protected:
    
    
};
