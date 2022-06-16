/**
 * @author Artem Kuznetsov  <kuznear1@fit.cvut.cz>
 * @date 08.05.2021
 */
#pragma once

#include "CDataSize.h"
#include "CFloatBig.h"
#include <iostream>

/**
 *@brief child class of CDataSize designed to perform operations with small float numbers
 */
class CFloat : public CDataSize
{
public:
    /**
     * Virtual copy
     * @return Pointer to allocated copy of the object
     */
    CDataSize * clone() const override;
    /**
     *@param varIntPart represented the value of the number to be pusht into the m_varInt variable
     *@param varFloatPart represented the value of the number after the decimal point to be pusht into the m_floatPart variable
     *@param type represented type of incoming number
     *@param size epresented size of incoming number
     */
    CFloat(long long int varIntPart, long long int varFloatPart, const std::string & type, const std::string & size);
    /**
     *@param varInt represented the value of the number to be pusht into the m_varInt variable
     *@param type represented type of incoming number
     *@param size epresented size of incoming number
     */
    CFloat(long long int varInt, const std::string & type, const std::string & size);
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
     *@note also need to add the part of the number after the decimal point
     *@return the operator returns itself
     */
    CDataSize & operator + (const CDataSize & number) override;
    /**
     *operator -  for subtract numbers
     *@param number represented the number which will be deducted
     *@note subtract the part of the number after the decimal point
     *@return the operator returns itself
     */
    CDataSize & operator - (const CDataSize & number) override;
    /**
     *operator *  for multiplying numbers
     *@param number represented the number which will be multiplied by
     *@note multiply the part of the number after the decimal point
     *@return the operator returns itself
     */
    CDataSize & operator * (const CDataSize & number) override;
    /**
     *operator / for dividing numbers
     *@param number represented the number which will divide
     *@note calling this operator here implies an error, since the program is not designed to divide by float number
     *@return the operator returns itself
     */
    CDataSize & operator / (const CDataSize & number) override;
    /**
     *print the method for printing the result
     *@note since small numbers are printed, the very first instance of m_varInt is taken and it is written out, similarly with m_floatPartb because it is float number
     */
    void print(void) const override;
    
private:
    /**
     *sizeNum the method designed to find the size of a number
     *@param num represented the number whose size you need to find out
     *@return number size
     *@note the size of a number means how many digits are in the number
     */
    int sizeNum(long long int num) const;
    /**
     *findDegree the method designed to find the power of 10 by which the number will need to be multiplied
     *@param size represented the size by the power of which you will need to multiply 10
     *@return returns some of the powers of 10
     */
    long long int findDegree(size_t size);
    /**
     *plusFlPart the method that adds two numbers representing numbers after the decimal point
     *@param number represented the number with which our m_floatPart object will be added
     */
    void plusFlPart(long long int number);
    /**
     *minusFlPart the method that will subtract two numbers representing numbers after the decimal point
     *@param number represented the number with which our m_floatPart object will be subtract
     */
    void minusFlPart(long long int number);
};
