/**
 * @author Artem Kuznetsov  <kuznear1@fit.cvut.cz>
 * @date 08.05.2021
 */
#pragma once
#include "CDataSize.h"

class CIntegerBig : public CDataSize
{
public:
    
    CDataSize * clone() const override;
    
    CIntegerBig(const std::vector<std::string> & variable, const std::string & type, const std::string & size);
    CIntegerBig(const long long int variable, const std::string & type, const std::string & size);
    CIntegerBig(std::string & variable, const std::string & type, const std::string & size);
    CIntegerBig(std::vector<long long int> num, const std::string & type, const std::string & size);
    
    void negativeNum(void) override;
    char getSign(void) override;
    
    CDataSize & operator + (const CDataSize & number) override;
    
    CDataSize & operator - (const CDataSize & number) override;
    
    CDataSize & operator * (const CDataSize & number) override;
    
    CDataSize & operator / (const CDataSize & number) override;
    
    void print(void) const override;
    
    
protected:
    void transFromStr(std::string & str, const char operation);
    void  incDivision(std::string &  x);
    void  reduceDivision(std::string &  minuend, const std::string &  subtrahend);
    bool controlSize(std::string x, std::string y);
    void  delExtraZero(std::string & str, const char operation);
    char whatSymbol(std::vector<long long int> & num);
    std::string transformToString(std::vector<long long int> & vecNum, std::string & num);
    void controlAnswer(std::string res, std::string num, std::string num2);
    std::string multAlg(std::string num, std::string num2);
    int sizeNum(long long int num) const;
    void addRem(const CDataSize & number);
    
};
