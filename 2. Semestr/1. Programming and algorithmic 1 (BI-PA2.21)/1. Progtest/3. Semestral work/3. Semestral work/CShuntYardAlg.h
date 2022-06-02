/**
 * @author Artem Kuznetsov  <kuznear1@fit.cvut.cz>
 * @date 31.05.2021
 */
#pragma once
#include "CType.h"
#include "CTypeBig.h"
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

class CShuntYardAlg
{
public:
    
    CShuntYardAlg   ( void ) {}
   ~CShuntYardAlg   ( void ) {}
    
    std::string shuntYardAlg();
    
    void addOp(const std::string & op);
    
    void addNum(const std::string & num);
    
    void changeNum(const std::string & num, size_t i);
    
    void changeOp(const std::string & op, size_t i);
    
    std::string getNum(size_t i) const;
    
    std::string getOp(size_t i) const;
    
protected:
    std::vector<std::string> stakNum;
    std::vector<std::string> stakOp;
    
    void op(std::string & op, CInteger & leftNum, CInteger & rightNum);
    
    void op(std::string & op, CFloat & leftNum, CFloat & rightNum);
    
    int prior(const std::string & op);
    
    void typDateAndLenght(size_t i, size_t j);
    
};
