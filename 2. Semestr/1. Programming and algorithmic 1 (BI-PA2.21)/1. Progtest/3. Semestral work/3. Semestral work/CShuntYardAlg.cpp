/**
 * @author Artem Kuznetsov  <kuznear1@fit.cvut.cz>
 * @date 31.05.2021
 */
#include "CShuntYardAlg.h"

std::string CShuntYardAlg::getOp(size_t i) const { return stackOp[i]; }

size_t CShuntYardAlg::sizeStackOp(void) const { return stackOp.size(); }

void CShuntYardAlg::addOp(const std::string & op)
{
    stackOp.push_back(op);
}

void CShuntYardAlg::changeNum(size_t i)
{
    stackNum[i]->negativeNum();
}

void CShuntYardAlg::changeOp(const std::string & op, size_t i)
{
    stackOp[i] = op;
}

void CShuntYardAlg::addSmallNum(const std::string & num, const std::string & floatPart, const std::string & type, const std::string & size)
{
    std::shared_ptr<CDataSize> tmp;
    if(type == "float")
    {
        long long int numInt = atoll(num.c_str());
        long long int numFloat = atoll(floatPart.c_str());
        tmp = std :: make_shared<CFloat>(numInt, numFloat, "float", "small");
    } else
    {
        long long int numInt = atoll(num.c_str());
        tmp = std :: make_shared<CInteger>(numInt, "int", "small");
    }
    stackNum.push_back(tmp);
}

void CShuntYardAlg::addSmallVar(const long long int num, const long long floatPart, const std::string & type, const std::string & size)
{
    std::shared_ptr<CDataSize> tmp;
    if(type == "float") {
        tmp = std :: make_shared<CFloat>(num, floatPart, "float", "small");
    } else {
        tmp = std :: make_shared<CInteger>(num, "int", "small");
    }
    stackNum.push_back(tmp);
}

void CShuntYardAlg::addBigNum(const std::vector<std::string> & num, const std::vector<std::string> & numFloat, const std::string & type, const std::string & size)
{
    std::shared_ptr<CDataSize> tmp;
    
    if(type == "float")
    {
        tmp = std :: make_shared<CFloatBig>(num, numFloat, "float", "big");
    } else
    {
        tmp = std :: make_shared<CIntegerBig>(num, "int", "big");
    }
    stackNum.push_back(tmp);
}

void CShuntYardAlg::addBigVar(std::vector<long long int> num, std::vector<long long int> floatPart, const std::string & type, const std::string & size)
{
    std::shared_ptr<CDataSize> tmp;
    if(type == "float") {
        tmp = std :: make_shared<CFloatBig>(num, floatPart, "float", "small");
    } else {
        tmp = std :: make_shared<CIntegerBig>(num, "int", "small");
    }
    stackNum.push_back(tmp);
}

std::shared_ptr<CDataSize> CShuntYardAlg::getRes(int res) const
{
    if(res == 1) {
        std::cout << "Result: ";
        stackNum[0]->print();
    } else{
        std::cout << "Variable is equal: ";
        stackNum[0]->print();
    }
    
    return stackNum[0];
}

bool CShuntYardAlg::shuntYardAlg(void)
{
    size_t i = 0, j = 0;
    if(stackOp[j] == "=")
    {
        stackNum.erase(stackNum.begin() + i);
        stackOp.erase(stackOp.begin() + j);
    }
    
    if(stackOp[j] == "(" && stackOp[j + 1] == ")") {
        stackOp.erase(stackOp.begin());
        stackOp.erase(stackOp.begin());
    }
    
    while(stackOp[j] == "(")
    {
        j++;
    }
    
    while(stackOp.size() != 0)
    {
        if(stackOp.size() > 1) {
            if(stackOp[j] == ")" && stackOp[j - 1] == "(") {
                stackOp.erase(stackOp.begin() + j);
                stackOp.erase(stackOp.begin() + j - 1);
                j--;
                if(stackOp.size() - 1 < j) {
                    if(j != 0)
                        j--;
                }
                continue;
            }
        }
        
        if(stackOp.size() == j + 1)
        {
            if(stackOp.size() > 1 && ((stackOp[j] == "*" && stackOp[j - 1] == "/") || (stackOp[j] == "/" && stackOp[j - 1] == "*") ||
                                       (stackOp[j] == "*" && stackOp[j - 1] == "*") || (stackOp[j] == "/" && stackOp[j - 1] == "/")))
            {
                i--;
                j--;
            }
            if(i == stackNum.size() - 1 && stackNum.size() > 1)
                i--;
            if(prepForOperation(i, j) == true) {
                if(i != 0)
                    i--;
                if(j != 0)
                    j--;
            } else
                return false;
        } else if(stackOp[j + 1] != ")" && stackOp[j + 1] != "(" && stackOp[j] != "(" && stackOp[j] != "- fl" &&
           prior(stackOp[j + 1]) >= prior(stackOp[j]))
        {
            i++;
            j++;
        } else if(stackOp[j + 1] == "(")
        {
            i++;
            j = j + 2;
            while(stackOp[j] == "(")
            {
                j++;
            }
        } else if(stackOp[j] == "- fl")
        {
            stackNum[i]->negativeNum();
            stackOp.erase(stackOp.begin() + j);
            if(stackOp[j] == ")" && stackOp[j - 1] == "(")
            {
                stackOp.erase(stackOp.begin() + j);
                stackOp.erase(stackOp.begin() + j - 1);
                j = j - 2;
                if(stackNum.size() - 1 != i) {
                    i++;
                    j++;
                }  else {
                    i--;
                }
                if(stackOp[j] == ")") {
                    i = i - 2;
                    j--;
                }
            }
            
        } else if(stackOp[j + 1] != ")" && stackOp[j + 1] != "(" && stackOp[j] != "(" && stackOp[j] != "- fl"
                  && prior(stackOp[j + 1]) < prior(stackOp[j]))
        {
            if(stackOp.size() > 1 && ((stackOp[j] == "*" && stackOp[j - 1] == "/") || (stackOp[j] == "/" && stackOp[j - 1] == "*") ||
                                      (stackOp[j] == "*" && stackOp[j - 1] == "*") || (stackOp[j] == "/" && stackOp[j - 1] == "/")))
            {
                i--;
                j--;
            }
            if(i == stackNum.size() - 1 && stackNum.size() > 1)
                i--;
            if(prepForOperation(i, j) == true) {
                if(stackOp.size() == j + 1) {
                    i--;
                    j--;
                } 
            } else
                return false;
        }else if(stackOp[j + 1] == ")")
        {
            if(stackOp.size() > 1 && ((stackOp[j] == "*" && stackOp[j - 1] == "/") || (stackOp[j] == "/" && stackOp[j - 1] == "*") ||
                                      (stackOp[j] == "*" && stackOp[j - 1] == "*") || (stackOp[j] == "/" && stackOp[j - 1] == "/")))
            {
                i--;
                j--;
                if(prepForOperation(i, j) != true)
                    return false;
            }
            while(stackOp[j] != "(")
            {
                if(i == stackNum.size() - 1 && stackNum.size() > 1)
                    i--;
                if(prepForOperation(i, j) == true) {
                    if(i != 0)
                        i--;
                    if(j != 0)
                        j--;
                } else
                    return false;
            }
            stackOp.erase(stackOp.begin() + j);
            stackOp.erase(stackOp.begin() + j);
            if(j != 0)
                j--;
            if(stackNum.size() > 1 && stackNum[i + 1]->getSign() == '-' && stackOp[j] == "-")
            {
                stackNum[i + 1]->negativeNum();
                stackOp[j] = "+";
            }
        }
        
    }
    
    return true;
}

bool CShuntYardAlg::prepForOperation(size_t i, size_t j)
{
    if(stackOp.size() != 1 && stackOp[j - 1] == "-")
    {
        stackNum[i]->negativeNum();
        stackOp[j - 1] = "+";
    }
    
    transformIfNeed(i, j);
    
    if(stackNum[i] ->getSize() == "big" && (stackOp[j] == "-" || stackOp[j] == "+") &&
                                           ((stackNum[i]->getSign() == '-' && stackNum[i + 1]->getSign() == '+') ||
                                            (stackNum[i]->getSign() == '+' && stackNum[i + 1]->getSign() == '-')))
        {
            if(stackOp[j] == "+")
                stackOp[j] = "-";
            
            if(whatBigger(stackNum[i]->getVecInt(), stackNum[i + 1]->getVecInt()) == "rhs")
            {
                if(op(stackOp[j], stackNum[i + 1], stackNum[i]) == true) {
                stackNum.erase(stackNum.begin() + i);
                stackOp.erase(stackOp.begin() + j);
                } else
                    return false;
            } else {
                if(op(stackOp[j], stackNum[i], stackNum[i + 1]) == true) {
                stackNum.erase(stackNum.begin() + i + 1);
                stackOp.erase(stackOp.begin() + j);
                } else
                    return false;
            }

            return true;
        }
    
    if(stackNum[i] ->getSize() == "big" && stackOp[j] == "-" && whatBigger(stackNum[i]->getVecInt(), stackNum[i + 1]->getVecInt()) == "rhs" &&
       (stackNum[i]->getSign() == '+' && stackNum[i + 1]->getSign() == '+'))
    {

        if(op(stackOp[j], stackNum[i + 1], stackNum[i]) == true) {
            stackNum[i + 1]->negativeNum();
            stackNum.erase(stackNum.begin() + i);
            stackOp.erase(stackOp.begin() + j);
            return true;
        } else
            return false;
    }
    
    if(op(stackOp[j], stackNum[i], stackNum[i + 1]) == true) {
        stackNum.erase(stackNum.begin() + i + 1);
        stackOp.erase(stackOp.begin() + j);
    } else
        return false;
    
    return true;
}

void CShuntYardAlg::transformIfNeed(size_t i, size_t j)
{
    if(stackNum[i]->getType() == "float" && stackNum[i + 1]->getType() == "int")
    {
        stackNum[i + 1] = std :: make_shared<CFloat>(stackNum[i + 1]->getVarInt(), "float", "small");
    } else if (stackNum[i]->getType() == "int" && stackNum[i + 1]->getType() == "float")
    {
        stackNum[i] = std :: make_shared<CFloat>(stackNum[i]->getVarInt(), "float", "small");
    }
    
    if(stackNum[i]->getSize() == "small" && stackNum[i + 1]->getSize() == "big")
    {
        if(stackNum[i + 1]->getType() == "int")
            stackNum[i] = std::make_shared<CIntegerBig>(stackNum[i]->getVarInt(), "int", "big");
        else
            stackNum[i] = std::make_shared<CFloatBig>(stackNum[i]->getVarInt(), stackNum[i]->getVarFloat(), "float", "big");
    } else if(stackNum[i]->getSize() == "big" && stackNum[i + 1]->getSize() == "small") {
        if(stackNum[i]->getType() == "int")
            stackNum[i + 1] = std::make_shared<CIntegerBig>(stackNum[i + 1]->getVarInt(), "int", "big");
        else
            stackNum[i + 1] = std::make_shared<CFloatBig>(stackNum[i + 1]->getVarInt(), stackNum[i + 1]->getVarFloat(), "float", "big");
    }
}

int CShuntYardAlg::prior(const std::string & op)
{
    if(op == "+" || op == "-")
        return 1;
    else if(op == "/"|| op == "*")
        return 3;
    
    return -10;
}

bool CShuntYardAlg::op(std::string & op, std::shared_ptr<CDataSize> & leftNum, std::shared_ptr<CDataSize> & rightNum)
{
    if(op == "+") {
        *leftNum + *rightNum;
         return true;
    }
    else if(op == "-") {
        *leftNum - *rightNum;
        return true;
    }
    else if(op == "*") {
        if(leftNum->getSize() == "small" && leftNum->getVarInt() > 100000000 && rightNum->getVarInt() > 100000000) {
            if(leftNum->getType() == "float" || rightNum->getType() == "float") {
                leftNum = std::make_shared<CFloatBig>(leftNum->getVarInt(), leftNum->getVarFloat(), "float", "big");
                rightNum = std::make_shared<CFloatBig>(rightNum->getVarInt(), rightNum->getVarFloat(), "float", "big");
            } else {
                leftNum = std::make_shared<CIntegerBig>(leftNum->getVarInt(), "int", "big");
                rightNum = std::make_shared<CIntegerBig>(rightNum->getVarInt(), "int", "big");
            }
        }
        *leftNum * *rightNum;
        return true;
    }
    else if(op == "/")
    {
        try{
        *leftNum / *rightNum;
        }
        catch(int & x)
        {
            if(x == 1)
                std::cout << "You can't divide by zero!" << std::endl;
            else
                std::cout << "You can't divide by decimal float!" << std::endl;
            return false;
        }
        return true;
    }
    
    return true;
}

std::string CShuntYardAlg::whatBigger(const std::vector<long long int> & lhs, const std::vector<long long int> & rhs)
{
    
    if(lhs.size() < rhs.size()) {
        return "rhs";
    } else if(lhs.size() == rhs.size()) {
        long long int lhsNum = lhs[lhs.size() - 1];
        if(lhsNum < 0)
            lhsNum = lhsNum * (-1);
        long long int rhsNum = rhs[rhs.size() - 1];
        if(rhsNum < 0)
            rhsNum = rhsNum * (-1);
        if(lhsNum < rhsNum)
            return "rhs";
        else
            return "lhs";
    }
    
    return "lhs";
}
