/**
 * @author Artem Kuznetsov  <kuznear1@fit.cvut.cz>
 * @date 08.05.2021
 */
#pragma once
#include <ostream>
#include <vector>

class CTypeBig
{
public:
    
    virtual ~CTypeBig() = default;
    
    virtual CTypeBig * clone() const = 0;
    
    virtual CTypeBig & operator + (const CTypeBig & number) const = 0;
    
    virtual CTypeBig & operator - (const CTypeBig & number) const = 0;
    
    virtual CTypeBig & operator * (const CTypeBig & number) const = 0;
    
    virtual CTypeBig & operator / (const CTypeBig & number) const = 0;
    
    friend std::ostream & operator << (std::ostream & os, const CTypeBig & item);
    
    
protected:
    
    virtual void print(std::ostream & os) const = 0;
    
    std::vector<std::string> m_intBig; //maybe do something for work with bytes
    std::vector<std::string> m_doubleBig; //maybe do something for work with bytes
    
    
};
