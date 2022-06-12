/**
 * @author Artem Kuznetsov  <kuznear1@fit.cvut.cz>
 * @date 04.06.2021
 */
#pragma once
#include <vector>
#include <string>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <ios>

class CDataSize
{
public:
    CDataSize(void);
    virtual ~CDataSize() = default;
    virtual CDataSize * clone() const = 0;
    
    std::string getSize(void) const;
    std::string getType(void) const;
    
    long long int getVarInt(void) const;
    long long int getVarFloat(void) const;
    long long int getRemains(void) const;
    
    std::vector<long long int> getVecInt(void) const;
    std::vector<long long int> getVecFloat(void) const;
    std::vector<long long int> getVecRem(void) const;
    
    void pushNum(long long int num);
    void writeRem(std::vector<long long int> rem);
    
    virtual void negativeNum(void) = 0;
    
    virtual char getSign(void) = 0;
    
    virtual CDataSize & operator + (const CDataSize & number) = 0;
    
    virtual CDataSize & operator - (const CDataSize & number) = 0;
    
    virtual CDataSize & operator * (const CDataSize & number) = 0;
    
    virtual CDataSize & operator / (const CDataSize & number) = 0;
    
    virtual void print(void) const = 0;
    
protected:
    std::string m_size;
    std::string m_type;
    std::vector<long long int> m_varInt;
    std::vector<long long int> m_floatPart;
    std::vector<long long int> m_remains;
    
};
