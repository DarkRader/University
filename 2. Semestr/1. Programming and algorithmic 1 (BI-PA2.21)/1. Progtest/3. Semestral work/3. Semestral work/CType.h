/**
 * @author Artem Kuznetsov  <kuznear1@fit.cvut.cz>
 * @date 08.05.2021
 */
#pragma once

#include <ostream>
#include <vector>

class CType
{
public:
    
    virtual ~CType() = default;
    
    virtual CType * clone() const = 0;
    
    virtual CType & operator + (const CType & number) const = 0;
    
    virtual CType & operator - (const CType & number) const = 0;
    
    virtual CType & operator * (const CType & number) const = 0;
    
    virtual CType & operator / (const CType & number) const = 0;
    
    friend std::ostream & operator << (std::ostream & os, const CType & item);
    
    
protected:
    
    virtual void print(std::ostream & os) const = 0;
    
private:
    
    std::vector<long long int> m_int;
    std::vector<long double> m_double;
    
    
};
