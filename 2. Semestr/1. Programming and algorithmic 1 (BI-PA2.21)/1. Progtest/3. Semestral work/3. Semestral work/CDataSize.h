/**
 * @author Artem Kuznetsov  <kuznear1@fit.cvut.cz>
 * @date 04.06.2021
 */
#pragma once
#include <vector>
#include <string>

class CDataSize
{
public:
    
    virtual ~CDataSize() = default;
    virtual CDataSize * clone() const = 0;
    
    long long int getVarInt(void) const;
    
    std::vector<long long int> getVecInt(void) const;
    
    long double getVarFloat(void) const;
    
    virtual void negativeNum(void) = 0;
    
    virtual char getSign(void) = 0;
    
    virtual CDataSize & operator + (const CDataSize & number) = 0;
    
    virtual CDataSize & operator - (const CDataSize & number) = 0;
    
    virtual CDataSize & operator * (const CDataSize & number) = 0;
    
    virtual CDataSize & operator / (const CDataSize & number) = 0;
    
    CDataSize(void);
    
    std::string getSize(void) const;
    std::string getType(void) const;
    void writeSize(const std::string & size);
    void writeType(const std::string & type);
    void writeFloat(long double);
    void pushNum(long long int num);
    
protected:
    std::string m_size;
    std::string m_type;
    std::vector<long long int> m_varInt;
    
    void print(void);

    long double m_varFloat;
    
    virtual void print(std::ostream & os) const = 0;
    
};
