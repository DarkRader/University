/**
 * @author Artem Kuznetsov  <kuznear1@fit.cvut.cz>
 * @date 26.05.2021
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
#include "CShuntYardAlg.h"

class CParsData
{
public:
    
    CParsData   ( void ) {}
   ~CParsData   ( void ) {}
    
    std::string getRes(void) const;
    
    bool parsingDate(const std::string & operation);
    
private:
    std::string m_res;
    std::map <std::string, std::shared_ptr<CDataSize>> m_var;
    
    bool fillStack(const std::vector<std::string> & token, CShuntYardAlg & a);
    
    bool fillSymbol(std::string & operation, CShuntYardAlg & a);
    
    bool controlSynErr(const std::vector<std::string> & control);
    
    void clWhiteSpace(std::string & newOperation);
    
    bool symbol(const char & symbol);
    
    bool transformNum(std::string repNum, size_t i, CShuntYardAlg & a);
    
    bool findVariable(const std::string & var);
    
    void fillVec(std::vector<std::string> & splitNum, const std::string & oper);
    
    bool errorInSymbol(std::string & operation, size_t i, int & bracket, CShuntYardAlg & a);
    
    bool writeRes(std::string & variable, std::vector<std::string> & seqNum, CShuntYardAlg & a);
    
    bool writeSymbol(std::string & operation, CShuntYardAlg & a, int & count, int & bracket);
};

