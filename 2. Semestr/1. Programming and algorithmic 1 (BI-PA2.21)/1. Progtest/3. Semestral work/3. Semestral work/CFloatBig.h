/**
 * @author Artem Kuznetsov  <kuznear1@fit.cvut.cz>
 * @date 08.05.2021
 */
#pragma once
#include "CDataSize.h"
#include "CIntegerBig.h"

class CFloatBig : public CDataSize
{
public:
    
    CDataSize * clone() const override;
    
    CFloatBig(const std::vector<std::string> & variable, const std::vector<std::string> & floatPart, const std::string & type,
              const std::string & size);
    CFloatBig(long long int varInt, long long int floatPart, const std::string & type, const std::string & size);
    CFloatBig(std::vector<long long int> num, std::vector<long long int> floatPart,  const std::string & type, const std::string & size);
    
    void negativeNum(void) override;
    char getSign(void) override;
    
    CDataSize & operator + (const CDataSize & number) override;
    
    CDataSize & operator - (const CDataSize & number) override;
    
    CDataSize & operator * (const CDataSize & number) override;
    
    CDataSize & operator / (const CDataSize & number) override;
    
    void print(void) const override;
    
protected:
    int sizeNum(long long int num) const;
    long long int findDegree(size_t size);
    char whatSymbol(std::vector<long long int> & num);
    std::string transformToString(std::vector<long long int> & vecNum, std::string & num, const std::string & typ);
    void transFromStr(std::string & str, size_t & sizeflNum);
    std::string multAlg(std::string num, std::string num2);
    void delExtraZero(std::string & str, size_t size);
    size_t addNull(std::string & flNum, std::string & flNum2);
    void addRem(const CDataSize & number);
    void ifExistFlPartPlus(std::vector<long long int> & flNum);
    void ifExistFlPartMinus(std::vector<long long int> & flNum);
    void transFromStrFlPart(std::string & str, size_t & sizeflNum);
    
};
