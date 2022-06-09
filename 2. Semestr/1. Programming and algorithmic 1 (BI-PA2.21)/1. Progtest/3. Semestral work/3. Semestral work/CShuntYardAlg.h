/**
 * @author Artem Kuznetsov  <kuznear1@fit.cvut.cz>
 * @date 31.05.2021
 */
#pragma once
#include <string>
#include <map>
#include <regex>
#include <fstream>
#include <algorithm>
#include <iterator>
#include <iostream>
#include <sstream>
#include "CInteger.h"
#include "CFloat.h"
#include "CIntegerBig.h"
#include "CFloatBig.h"
#include "CVariable.h"


class CShuntYardAlg
{
public:
    
    CShuntYardAlg   ( void ) {}
   ~CShuntYardAlg   ( void ) {}
    
    std::shared_ptr<CDataSize> shuntYardAlg(const std::string & variable, std::map <std::string, std::shared_ptr<CDataSize>> & var);
    
    void addOp(const std::string & op);
    
    void addSmallNum(const std::string & num, const std::string & type, const std::string & size, size_t i);
    
    void addBigNum(const std::vector<std::string> & num, const std::vector<std::string> & numFloat, const std::string & type, const std::string & size);
    
    void changeNum(size_t i);
    
    void changeOp(const std::string & op, size_t i);
    
    void addVariable(std::shared_ptr<CDataSize> & var);
    
    std::string getNum(size_t i) const;
    
    std::string getOp(size_t i) const;
    
    std::string getType(void) const;
    
    std::string getSize(void) const;
    
    std::vector<long long int> getInt(void) const;
    
    long double getFloat(void) const;
    
protected:
    std::vector<std::string> stackOp;
    std::vector<std::shared_ptr<CDataSize>> stackNum;
    
    void op(std::string & op, std::shared_ptr<CDataSize> & leftNum, std::shared_ptr<CDataSize> & rightNum);
    
    void op(std::string & op, CFloat & leftNum, CFloat & rightNum);
    
    int prior(const std::string & op);
    
    void typDateAndLenght(size_t i, size_t j, std::map <std::string, std::shared_ptr<CDataSize>> & var);
    
    std::string whatBigger(const std::vector<long long int> & lhs, const std::vector<long long int> & rhs);
};
