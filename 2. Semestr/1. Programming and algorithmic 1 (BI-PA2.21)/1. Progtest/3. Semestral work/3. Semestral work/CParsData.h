/**
 * @author Artem Kuznetsov  <kuznear1@fit.cvut.cz>
 * @date 26.05.2021
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
    
    void fillStack(const std::vector<std::string> & token, CShuntYardAlg & a);
    
    void fillSymbol(std::string & operation, CShuntYardAlg & a);
    
    bool controlSynErr(const std::vector<std::string> & control);
    
    void clWhiteSpace(std::string & newOperation);
    
    bool symbol(const char & symbol);
    
    void negNum(const std::string & operation);
    
    void replaceComma(std::string repNum, CShuntYardAlg & a);
    
};

