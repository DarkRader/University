/**
 * @author Artem Kuznetsov  <kuznear1@fit.cvut.cz>
 * @date 08.05.2021
 */
#pragma once
#include "CDataSize.h"
#include <iostream>
#include <fstream>

/**
 *@brief child class of CDataSize designed to perform operations with small integers
 */
class CInteger : public CDataSize
{
public:
    /**
     * Virtual copy
     * @return Pointer to allocated copy of the object
     */
    CDataSize * clone() const override;
    /**
     *@param variable represented the value of the number to be pusht into the m_varInt variable
     *@param type represented type of incoming number
     *@param size epresented size of incoming number
     */
    CInteger(long long int variable, const std::string & type, const std::string & size);
    /**
     *negativeNum a method for changing a positive number to a negative one and back
     */
    void negativeNum(void) override;
    /**
     *getSign the method for getting the sign of a number
     *@return if the number is negative, it returns '-', and if positive, '+'
     */
    char getSign(void) override;
    /**
     *operator + for  adding numbers
     *@param number represented the number with which the addition will occur
     *@note the two very first instances of m_varInt add up to each other
     *@return the operator returns itself
     */
    CDataSize & operator + (const CDataSize & number) override;
    /**
     *operator -  for subtract numbers
     *@param number represented the number which will be deducted
     *@note the very first instances of m_varInt are subtracted
     *@return the operator returns itself
     */
    CDataSize & operator - (const CDataSize & number) override;
    /**
     *operator *  for multiplying numbers
     *@param number represented the number which will be multiplied by
     *@note the very first instances of m_varInt are multiplied
     *@return the operator returns itself
     */
    CDataSize & operator * (const CDataSize & number) override;
    /**
     *operator / for dividing numbers
     *@param number represented the number which will divide
     *@note the very first instances of m_varInt are divided
     *@return the operator returns itself
     */
    CDataSize & operator / (const CDataSize & number) override;
    /**
     *print the method for printing the result
     *@note since small numbers are printed, the very first instance of m_varInt is taken and it is written out
     */
    void print(void) const override;
    
};
