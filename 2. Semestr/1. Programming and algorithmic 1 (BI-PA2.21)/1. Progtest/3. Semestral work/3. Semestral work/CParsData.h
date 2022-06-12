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

/**
 *@brief a class for parsing data and passing parsed data to other classes
 */
class CParsData
{
public:
    
    CParsData   ( void ) {}
   ~CParsData   ( void ) {}
    /**
     *parsingDate the main method that parses data and calls all other methods
     *@param operation represented the data that the user entered and that we need to parse
     *@return true, if parsing was successful and false if there is an error or this is a special case
     */
    bool parsingDate(const std::string & operation);
    
private:
    //a map that uses a string to store the name of the variable and a class to store all the necessary data about the variable
    std::map <std::string, std::shared_ptr<CDataSize>> m_var;
    /**
     *fillStack the method for filling the stack with numbers for further calculations
     *@param token represented numbers and variables shared in the parsing process, which are added to the string vector
     *@param a instance of the class to which data will be added
     *@return true, if parsing was successful and false if there is an error
     */
    bool fillStack(const std::vector<std::string> & token, CShuntYardAlg & a);
    /**
     *fillSymbol the method for filling the stack with operation for further calculations
     *@param operation represented the data that the user entered, but without whitespaces
     *@param a instance of the class to which data will be added
     *@return true, if parsing was successful and false if there is an error
     */
    bool fillSymbol(std::string & operation, CShuntYardAlg & a);
    /**
     *controlSynErr the method that reacts if there is a sign in the data that is parsed, which should not be
     *@param control represented user-entered data divided into tokens
     *@return false, if found a sign that shouldn't be there, and true if nothing superfluous is found
     */
    bool controlSynErr(const std::vector<std::string> & control);
    /**
     *clWhiteSpace the method that gets rid of all the whitespaces in the expression that the user entered
     *@param newOperation represented user-entered data
     */
    void clWhiteSpace(std::string & newOperation);
    /**
     *symbol the method determines whether the sign is an operator or something else
     *@param symbol represented the sign that will be checked
     *@return true if it's operator or false if it's not
     */
    bool symbol(const char & symbol);
    /**
     *transformNum the method, which transforms numbers from string to vector <long long int>
     *and enters the data into the instance of "a" class CShuntYardAlg
     *@param repNum represented a vector of strings that is filled with numbers with a maximum length of 18
     *@param a instance of the class to which data will be added
     *@return true if there are no errors and false if there are errors in the number
     */
    bool transformNum(std::string repNum, size_t i, CShuntYardAlg & a);
    /**
     *findVariable the method that checks whether the number corresponds to the type of variable or not
     *@param var represented  the number that is checked for compliance with the variable
     *@return true if the number is a variable or false if it is not
     */
    bool findVariable(const std::string & var);
    /**
     *fillVec the method that splits a large number on a string with a maximum length of 18 and adds it to a string vector
     *@param splitNum represented a vector that will be filled with numbers with a maximum length of 18 in string format
     *@param oper represents a number in string format that will be divisible by
     */
    void fillVec(std::vector<std::string> & splitNum, const std::string & oper);
    /**
     *errorInSymbol the method that checks for errors that are associated with operators
     *@param operation represented the data that the user entered, but without whitespaces
     *@param bracket represented flag for detecting the absence-presence of brackets
     *@param a instance of the class to which data will be added
     *@return false if  an error is found and true if it's not
     */
    bool errorInSymbol(std::string & operation, size_t i, int & bracket, CShuntYardAlg & a);
    /**
     *writeRes the method that goes inside the CShuntYardAlg class and performs operations,
     *as well as writes out the result and writes the result to a variable if a variable is assigned
     *@param variable represented the sign that comes first
     *@param seqNum numbers represented as a vector of strings
     *@param a instance of the class to which data will be added
     *@return true if the operations were successful, without errors, and false if an error or an unacceptable operation was found in the operation
     */
    bool writeRes(std::string & variable, std::vector<std::string> & seqNum, CShuntYardAlg & a);
    /**
     *writeSymbol the method that checks operators and changes numbers if this is a special case
     *@param operation represented the data that the user entered, but without whitespaces
     *@param a nstance of the class to which data will be added
     *@param count represented flag, to check that the expression does not start with an impermissible operator
     *@param bracket represented flag for detecting the absence-presence of brackets
     *@return false if  an error is found and true if it's not
     */
    bool writeSymbol(std::string & operation, CShuntYardAlg & a, int & count, int & bracket);
};

