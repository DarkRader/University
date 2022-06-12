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

/**
 *@brief the class is an algorithm that computes numbers taking into account the priority of signs and the location of brackets
 */
class CShuntYardAlg
{
public:
    
    CShuntYardAlg   ( void ) {}
   ~CShuntYardAlg   ( void ) {}
    /**
     *shuntYardAlg  the main method in the class that does all the necessary checks
     *@return true if the operation was successful and false if something went wrong
     */
    bool shuntYardAlg(void);
    /**
     *addOp the method, which adds an incoming operator to the stack of operators
     *@param op represented an incoming operator
     */
    void addOp(const std::string & op);
    /**
     *@return the length of the stack of operators
     */
    size_t sizeStackOp(void) const;
    /**
     *addSmallNum the method whose purpose is to add all incoming parameters to an instance of one of the classes:
     * Integer CFloat, when using make_shared from the instance of the parent class
     * @param num  represented the number in the form of a string that will be translated
     * @param floatPart represented the float part number  in the form of a string that will be translated
     * @param type represented type of number
     * @param size represented size of number
     * @note float part number means the number that follows the comma I divide the float decimal number into two parts by the part that goes before the comma and after
     */
    void addSmallNum(const std::string & num, const std::string & floatPart, const std::string & type, const std::string & size);
    /**
     *addSmallNum the method whose purpose is to add all incoming parameters to an instance of one of the classes:
     * Integer CFloat, when using make_shared from the instance of the parent class, but to add a variable
     * @param num  represented the number of integer part
     * @param floatPart represented the float part number of float part
     * @param type represented type of number
     * @param size represented size of number
     * @note float part number means the number that follows the comma I divide the float decimal number into two parts by the part that goes before the comma and after
     */
    void addSmallVar(const long long int num, const long long floatPart, const std::string & type, const std::string & size);
    /**
     *addBigNum the method whose purpose is to add all incoming parameters to an instance of one of the classes:
     * IntegerBig CFloatBig, when using make_shared from the instance of the parent class
     * @param num  represented a large number divided into a vector of strings with a maximum length of 18
     * @param numFloat represented the float part number a large number divided into a vector of strings with a maximum length of 18
     * @param type represented type of number
     * @param size represented size of number
     * @note float part number means the number that follows the comma I divide the float decimal number into two parts by the part that goes before the comma and after
     */
    void addBigNum(const std::vector<std::string> & num, const std::vector<std::string> & numFloat, const std::string & type, const std::string & size);
    /**
     *addBigNum the method whose purpose is to add all incoming parameters to an instance of one of the classes:
     * IntegerBig CFloatBig, when using make_shared from the instance of the parent class, but to add a variable
     * @param num  represented a large number divided into a vector of long long int
     * @param floatPart represented the float part number a large number divided into a vector of long long int
     * @param type represented type of number
     * @param size represented size of number
     * @note float part number means the number that follows the comma I divide the float decimal number into two parts by the part that goes before the comma and after
     */
    void addBigVar(std::vector<long long int> num, std::vector<long long int> floatPart, const std::string & type, const std::string & size);
    /**
     *changeNum the method for converting a number from positive to negative and back
     *@param i represented position a number in stack
     */
    void changeNum(size_t i);
    /**
     *changeOp the method for replacing one operator with another, if such an opportunity is needed at the time of parsing
     *@param op represented incoming operator to be replaced by
     *@param i represented position an operator in stack
     */
    void changeOp(const std::string & op, size_t i);
    /**
     *@param i represented position in operator in stack
     *@return the operator that is set to the position of the incoming parameter
     */
    std::string getOp(size_t i) const;
    /**
     *@param res represented  a number-flag to determine which condition to do
     *@return the very first instation of stackNum, after performing operations, there is the result of all operations
     */
    std::shared_ptr<CDataSize> getRes(int res) const;
    
private:
    //the vector of strings where all operators and brackets are stored
    std::vector<std::string> stackOp;
    //vector of unique pointers to instances of the abstract CDataSize class
    std::vector<std::shared_ptr<CDataSize>> stackNum;
    /**
     *op the method for performing a specific operation depending on the operator
     *@param op represented the operation to be performed
     *@param leftNum the number on the left side that will participate in the operation
     *@param rightNum the number on the right side that will participate in the operation
     *@return true if the operation is perfect without problems and false if there is a problem
     */
    bool op(std::string & op, std::shared_ptr<CDataSize> & leftNum, std::shared_ptr<CDataSize> & rightNum);
    /**
     *prior the method that identifies the priority of the operation
     *@param op represented the operator whose priority you need to find out
     *@return operator priority
     */
    int prior(const std::string & op);
    /**
     *prepForOperation before performing the operation, a method that determines on which side what number should be
     * and whether the transformation of numbers into another size or type is necessary
     * @param i represented position a number in stack
     * @param j represented position an operator in stack
     * @return true if there are no mistakes or false if there are
     */
    bool prepForOperation(size_t i, size_t j);
    /**
     *transformIfNeed the method that deals with the transformation of numbers into a different size or type, if necessary
     *@param i represented position a number in stack
     *@param j represented position an operator in stack
     */
    void transformIfNeed(size_t i, size_t j);
    /**
     *whatBigger the method that determines which side of the number is greater without taking into account the minus sign
     *@param lhs represented  a large number that is currently on the right side
     *@param rhs represented a large number that is currently on the left side
     *@return the designation of the side from which the number is bigger
     */
    std::string whatBigger(const std::vector<long long int> & lhs, const std::vector<long long int> & rhs);
};
