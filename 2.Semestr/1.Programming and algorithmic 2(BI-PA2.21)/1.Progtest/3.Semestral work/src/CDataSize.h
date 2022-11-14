/**
 * @author Artem Kuznetsov  <kuznear1@fit.cvut.cz>
 * @date 04.06.2021
 */
#pragma once
#include <vector>
#include <string>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <ios>

/**
 *@brief parent abstract class designed to perform operations between numbers
 */
class CDataSize
{
public:
    CDataSize(void);
    /**
     * Virtual destructor
     * @note Needed for proper destruction handling in descendants
     */
    virtual ~CDataSize() = default;
    /**
     * Virtual copy
     * @return Pointer to allocated copy of the object
     */
    virtual CDataSize * clone() const = 0;
    /**
     *@return the size that the class is marked with
     */
    std::string getSize(void) const;
    /**
     *@return the type that the class is marked with
     */
    std::string getType(void) const;
    /**
     *@return the value of a number if it is a small number
     */
    long long int getVarInt(void) const;
    /**
     *@return the value of a float part number if it is a small number
     *@note the value of the number after the decimal point
     */
    long long int getVarFloat(void) const;
    /**
     *@return the remainder of the number if it is a small number
     */
    long long int getRemains(void) const;
    /**
     *@return a vector of numbers if it is a large number
     */
    std::vector<long long int> getVecInt(void) const;
    /**
     *@return a vector of numbers if it is a large number
     *@note the value of the numbers after the decimal point
     */
    std::vector<long long int> getVecFloat(void) const;
    /**
     *@return the vector of the remainder numbers if it is a larger number
     */
    std::vector<long long int> getVecRem(void) const;
    /**
     *pushNum a method that makes push incoming numbers into a vector
     *@param num represented incoming numbers
     */
    void pushNum(long long int num);
    /**
     *writeRem a method that writes an incoming vector to the remainder
     *@param rem represented incoming vector
     */
    void writeRem(std::vector<long long int> rem);
    /**
     *negativeNum a method for changing a positive number to a negative one and back
     */
    virtual void negativeNum(void) = 0;
    /**
     *getSign the method for getting the sign of a number
     *@return if the number is negative, it returns '-', and if positive, '+'
     */
    virtual char getSign(void) = 0;
    /**
     *operator + for  adding numbers
     *@param number represented the number with which the addition will occur
     *@return the operator returns itself
     */
    virtual CDataSize & operator + (const CDataSize & number) = 0;
    /**
     *operator -  for subtract numbers
     *@param number represented the number which will be deducted
     *@return the operator returns itself
     */
    virtual CDataSize & operator - (const CDataSize & number) = 0;
    /**
     *operator *  for multiplying numbers
     *@param number represented the number which will be multiplied by
     *@return the operator returns itself
     */
    virtual CDataSize & operator * (const CDataSize & number) = 0;
    /**
     *operator / for dividing numbers
     *@param number represented the number which will divide
     *@return the operator returns itself
     */
    virtual CDataSize & operator / (const CDataSize & number) = 0;
    /**
     *print the method for printing the result
     */
    virtual void print(void) const = 0;
    
protected:
    //represented number size: big or small
    std::string m_size;
    //represented number type: int or float
    std::string m_type;
    //represented the contents of the numbers, if a small number,
    //then one instance of the vector, if large, then more
    std::vector<long long int> m_varInt;
    //represented the contents of the numbers after the decimal point,
    //if a small number, then one instance of the vector, if large, then more
    std::vector<long long int> m_floatPart;
    //the contents of the remainder of the numbers,if a small number,
    //then one instance of the vector, if large, then more
    std::vector<long long int> m_remains;
    
};
