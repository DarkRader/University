/**
 * @author Artem Kuznetsov  <kuznear1@fit.cvut.cz>
 * @date 08.05.2021
 */
#pragma once
#include "CDataSize.h"
#include "CIntegerBig.h"

/**
 *@brief child class of CDataSize designed to perform operations with a very big float numbers
 */
class CFloatBig : public CDataSize
{
public:
    /**
     * Virtual copy
     * @return Pointer to allocated copy of the object
     */
    CDataSize * clone() const override;
    /**
     *@param variable represented a vector of strings, each instance of which will transform into a long long int and push into m_varInt
     *@param floatPart represented a vector of strings, each instance of which will transform into a long long int and push into m_floatPart
     *@param type represented type of incoming number
     *@param size epresented size of incoming number
     */
    CFloatBig(const std::vector<std::string> & variable, const std::vector<std::string> & floatPart, const std::string & type,
              const std::string & size);
    /**
     *@param varInt represented the number that will be pushed to the first instance of m_varInt
     *@param floatPart represented the number after the decimal point that will be pushed to the first instance of m_floatPart
     *@param type represented type of incoming number
     *@param size epresented size of incoming number
     */
    CFloatBig(long long int varInt, long long int floatPart, const std::string & type, const std::string & size);
    /**
     *@param num represented the long long int vector that will be copied to the m_varInt object
     *@param floatPart represented the long long int vector that will be copied to the m_floatPart object
     *@param type represented type of incoming number
     *@param size epresented size of incoming number
     */
    CFloatBig(std::vector<long long int> num, std::vector<long long int> floatPart,  const std::string & type, const std::string & size);
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
     *@note implementation of the addition of very large numbers with a value after the decimal point
     *@return the operator returns itself
     */
    CDataSize & operator + (const CDataSize & number) override;
    /**
     *operator -  for subtract numbers
     *@param number represented the number which will be deducted
     *@note implementation of subtraction of very large numbers with a value after the decimal point
     *@return the operator returns itself
     */
    CDataSize & operator - (const CDataSize & number) override;
    /**
     *operator *  for multiplying numbers
     *@param number represented the number which will be multiplied by
     *@note implementation of multiplication of very large numbers with a value after the decimal point
     *@return the operator returns itself
     */
    CDataSize & operator * (const CDataSize & number) override;
    /**
     *operator / for dividing numbers
     *@param number represented the number which will divide
     *@note implementation of division of very large numbers with a value after the decimal point
     *@return the operator returns itself
     */
    CDataSize & operator / (const CDataSize & number) override;
    /**
     *print the method for printing the result
     *@note printing out the entire vector long long int in variable m_varInt and vector long long int in variable m_floatPart, because the number after the decimal point
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
     *whatSymbol the method that finds out which number is positive or negative
     *@param num represented a very large number whose sign you need to find out
     *@return if the number is negative, it returns '-', and if positive, '+'
     */
    char whatSymbol(std::vector<long long int> & num);
    /**
     *transformToString the method that translates incoming variable  from a long long int vector to a string
     *@param vecNum represented the variable that will need to be translated
     *@param typ represented the type that is being translated
     *@return the received string after translation
     */
    std::string transformToString(std::vector<long long int> & vecNum, const std::string & typ);
    /**
     *transFromStr the method, which transforms numbers from string to vector <long long int> in variable m_varInt
     *@param str represented string to be translated
     *@param sizeflNum represented the size of the number 
     */
    void transFromStr(std::string & str, size_t & sizeflNum);
    /**
     *multAlg the method that deals with multiplying two numbers
     *@param num represented the first number that is multiplied
     *@param num2 epresented second number that is multiplied
     *@return the result obtained after multiplication is presented in the form of a string
     */
    std::string multAlg(std::string num, std::string num2);
    /**
     *delExtraZero the method that removes extra zeros from the beginning of a line
     *@param str represented a string from which extra zeros are removed
     *@param size represented the size to be deleted
     */
    void delExtraZero(std::string & str, size_t size);
    /**
     *addNull adds zeros for numbers after the decimal point to perform correct operations with them
     *@param flNum represented the first number after the decimal point in the form of a string
     *@param flNum2 represented second number after the decimal point in the form of a string
     */
    size_t addNull(std::string & flNum, std::string & flNum2);
    /**
     *addRem the method that adds a remainder method from an expression on which an operation was performed
     *@param number represented instance of the class on which the operation was performed
     */
    void addRem(const CDataSize & number);
    /**
     *ifExistFlPartPlus the method for adding two numbers after the decimal point
     *@param flNum represented the number after the decimal point that will add up
     */
    void ifExistFlPartPlus(std::vector<long long int> & flNum);
    /**
     *ifExistFlPartMinus the method for subtracting two numbers after the decimal point
     *@param flNum represented the number after the decimal point that will be subtracted
     */
    void ifExistFlPartMinus(std::vector<long long int> & flNum);
    /**
     *transFromStrFlPart the method, which transforms numbers after the decimal point from string to vector <long long int> in variable m_floatPart
     *@param str represented string to be translated
     *@param sizeflNum represented the size of the number after the decimal point
     */
    void transFromStrFlPart(std::string & str, size_t & sizeflNum);
    
};
