/**
 * @author Artem Kuznetsov  <kuznear1@fit.cvut.cz>
 * @date 08.05.2021
 */
#pragma once
#include "CDataSize.h"

/**
 *@brief child class of CDataSize designed to perform operations with a very big integers
 */
class CIntegerBig : public CDataSize
{
public:
    /**
     * Virtual copy
     * @return Pointer to allocated copy of the object
     */
    CDataSize * clone() const override;
    /**
     *@param variable represented a vector of strings, each instance of which will transform into a long long int and push into m_varInt
     *@param type represented type of incoming number
     *@param size epresented size of incoming number
     */
    CIntegerBig(const std::vector<std::string> & variable, const std::string & type, const std::string & size);
    /**
     *@param variable represented the number that will be pushed to the first instance of m_varInt
     *@param type represented type of incoming number
     *@param size epresented size of incoming number
     */
    CIntegerBig(const long long int variable, const std::string & type, const std::string & size);
    /**
     *@param variable represented string presentation of the number, which will be translated
     *@param type represented type of incoming number
     *@param size epresented size of incoming number
     */
    CIntegerBig(std::string & variable, const std::string & type, const std::string & size);
    /**
     *@param num represented the long long int vector that will be copied to the m_varInt object
     *@param type represented type of incoming number
     *@param size epresented size of incoming number
     */
    CIntegerBig(std::vector<long long int> num, const std::string & type, const std::string & size);
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
     *@note implementation of the addition of very large numbers
     *@return the operator returns itself
     */
    CDataSize & operator + (const CDataSize & number) override;
    /**
     *operator -  for subtract numbers
     *@param number represented the number which will be deducted
     *@note implementation of subtraction of very large numbers
     *@return the operator returns itself
     */
    CDataSize & operator - (const CDataSize & number) override;
    /**
     *operator *  for multiplying numbers
     *@param number represented the number which will be multiplied by
     *@note implementation of multiplication of very large numbers
     *@return the operator returns itself
     */
    CDataSize & operator * (const CDataSize & number) override;
    /**
     *operator / for dividing numbers
     *@param number represented the number which will divide
     *@note implementation of division of very large numbers
     *@return the operator returns itself
     */
    CDataSize & operator / (const CDataSize & number) override;
    /**
     *print the method for printing the result
     *@note printing out the entire vector long long int in variable m_varInt
     */
    void print(void) const override;
    
private:
    /**
     *transFromStr the method, which transforms numbers from string to vector <long long int> in variable m_varInt
     *@param str represented string to be translated
     *@param operation the operator from which the translation takes place
     */
    void transFromStr(std::string & str, const char operation);
    /**
     *incDivision the method that checks the transition
     *@param x represented the number over which we make changes
     */
    void  incDivision(std::string &  x);
    /**
     *reduceDivision the method that produces a gradual separation of the divisor and the divisible
     *@param minuend represented the number that is divided
     *@param subtrahend represented the number that divides
     */
    void  reduceDivision(std::string &  minuend, const std::string &  subtrahend);
    /**
     *controlSize the method for checking the size of the divisible and divisor
     *@param x represented the number that is divided
     *@param y represented the number that divides
     *@return true if the divisor is smaller and false if the other way around
     */
    bool controlSize(std::string x, std::string y);
    /**
     *delExtraZero the method that removes extra zeros from the beginning of a line
     *@param str represented a string from which extra zeros are removed
     *@param operation represented the operator from which the translation takes place
     */
    void  delExtraZero(std::string & str, const char operation);
    /**
     *whatSymbol the method that finds out which number is positive or negative
     *@param num represented a very large number whose sign you need to find out
     *@return if the number is negative, it returns '-', and if positive, '+'
     */
    char whatSymbol(std::vector<long long int> & num);
    /**
     *transformToString the method that translates incoming variable  from a long long int vector to a string
     *@param vecNum represented the variable that will need to be translated
     *@return the received string after translation
     */
    std::string transformToString(std::vector<long long int> & vecNum);
    /**
     *findRemainder the  method that finds the remainder after division
     *@param res represented the result obtained after division
     *@param num represented the number divided by
     *@param num2 represented the number that was divided
     */
    void findRemainder(std::string res, std::string num, std::string num2);
    /**
     *multAlg the method that deals with multiplying two numbers
     *@param num represented the first number that is multiplied
     *@param num2 epresented second number that is multiplied
     *@return the result obtained after multiplication is presented in the form of a string
     */
    std::string multAlg(std::string num, std::string num2);
    /**
     *sizeNum the method designed to find the size of a number
     *@param num represented the number whose size you need to find out
     *@return number size
     *@note the size of a number means how many digits are in the number
     */
    int sizeNum(long long int num) const;
    /**
     *addRem the method that adds a remainder method from an expression on which an operation was performed
     *@param number represented instance of the class on which the operation was performed
     */
    void addRem(const CDataSize & number);
    
};
