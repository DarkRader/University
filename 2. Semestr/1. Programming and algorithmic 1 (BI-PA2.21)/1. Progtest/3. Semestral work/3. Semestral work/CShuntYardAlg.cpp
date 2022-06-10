/**
 * @author Artem Kuznetsov  <kuznear1@fit.cvut.cz>
 * @date 31.05.2021
 */
#include "CShuntYardAlg.h"

std::string CShuntYardAlg::getNum(size_t i) const
{
    std::string num = std::to_string(stackNum[i]->getVarInt());
    return num;
}

std::string CShuntYardAlg::getOp(size_t i) const { return stackOp[i]; }

size_t CShuntYardAlg::sizeStackOp(void) const { return stackOp.size(); }

std::string CShuntYardAlg::getType(void) const { return stackNum[0]->getType(); }

std::string CShuntYardAlg::getSize(void) const { return stackNum[0]->getSize(); }

std::vector<long long int> CShuntYardAlg::getInt(void) const { return stackNum[0]->getVecInt(); }

long double CShuntYardAlg::getFloat(void) const { return stackNum[0]->getVarFloat(); }

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

std::shared_ptr<CDataSize> CShuntYardAlg::shuntYardAlg(const std::string & variable, std::map <std::string, std::shared_ptr<CDataSize>> & var, std::ostream & history)
{
    size_t i = 0, j = 0;
    if(stackOp[j] == "=")
    {
        stackNum.erase(stackNum.begin() + i);
        stackOp.erase(stackOp.begin() + j);
    }
    
    while(stackOp[j] == "(")
    {
        j++;
    }
    
    while(stackOp.size() != 0)
    {
        if(stackOp.size() == j + 1)
        {
            typDateAndLenght(i, j, var);
//            if(stackNum[0] == "Zero")
//                return "Zero";
//            stackNum.erase(stackNum.begin() + i + 1);
//            stackOp.erase(stackOp.begin() + j);
            if(i != 0)
                i--;
            if(j != 0)
                j--;
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
            }
            
        } else if(stackOp[j + 1] != ")" && stackOp[j + 1] != "(" && stackOp[j] != "(" && stackOp[j] != "- fl"
                  && prior(stackOp[j + 1]) < prior(stackOp[j]))
        {
            typDateAndLenght(i, j, var);
//            if(stakNum[0] == "Zero")
//                return "Zero";
//            stackNum.erase(stackNum.begin() + i + 1);
//            stackOp.erase(stackOp.begin() + j);
            if(stackOp.size() == j + 1) {
                i--;
                j--;
            }
        }else if(stackOp[j + 1] == ")")
        {
            while(stackOp[j] != "(")
            {
                typDateAndLenght(i, j, var);
//                if(stakNum[0] == "Zero")
//                    return "Zero";
//                stackNum.erase(stackNum.begin() + i + 1);
//                stackOp.erase(stackOp.begin() + j);
                if(i != 0)
                    i--;
                if(j != 0)
                    j--;
            }
            stackOp.erase(stackOp.begin() + j);
            stackOp.erase(stackOp.begin() + j);
            if(j != 0)
                j--;
            if(stackNum[i + 1]->getSign() == '-' && stackOp[j] == "-")
            {
                stackNum[i + 1]->negativeNum();
                stackOp[j] = "+";
            }
        }
        
    }
    stackNum[0]->print(history);
    
    return stackNum[0];
}

void CShuntYardAlg::typDateAndLenght(size_t i, size_t j, std::map <std::string, std::shared_ptr<CDataSize>> & var)
{
    if(stackOp.size() != 1 && stackOp[j - 1] == "-")
    {
        stackNum[i]->negativeNum();
        stackOp[j - 1] = "+";
    }
    
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
    
    if(stackNum[i] ->getSize() == "big" && (stackOp[j] == "-" || stackOp[j] == "+") &&
                                           ((stackNum[i]->getSign() == '-' && stackNum[i + 1]->getSign() == '+') ||
                                            (stackNum[i]->getSign() == '+' && stackNum[i + 1]->getSign() == '-')))
        {
            if(stackOp[j] == "+")
                stackOp[j] = "-";
            
            if(whatBigger(stackNum[i]->getVecInt(), stackNum[i + 1]->getVecInt()) == "rhs")
            {
                op(stackOp[j], stackNum[i + 1], stackNum[i]);
                stackNum.erase(stackNum.begin() + i);
                stackOp.erase(stackOp.begin() + j);
            } else {
                op(stackOp[j], stackNum[i], stackNum[i + 1]);
                stackNum.erase(stackNum.begin() + i + 1);
                stackOp.erase(stackOp.begin() + j);
            }

            //stackNum[i + 1]->negativeNum();
            return;
        }
    

    if(stackNum[i] ->getSize() == "big" && stackOp[j] == "-" && whatBigger(stackNum[i]->getVecInt(), stackNum[i + 1]->getVecInt()) == "rhs" &&
       (stackNum[i]->getSign() == '+' && stackNum[i + 1]->getSign() == '+'))
    {

        op(stackOp[j], stackNum[i + 1], stackNum[i]);
        stackNum[i + 1]->negativeNum();
        stackNum.erase(stackNum.begin() + i);
        stackOp.erase(stackOp.begin() + j);
        return;
    }
    
    op(stackOp[j], stackNum[i], stackNum[i + 1]);
    stackNum.erase(stackNum.begin() + i + 1);
    stackOp.erase(stackOp.begin() + j);
}

int CShuntYardAlg::prior(const std::string & op)
{
    if(op == "+" || op == "-")
        return 1;
    else if(op == "/") //|| op == "*")
        return 2;
    else if(op == "*")
        return 3;
    
    return -10;
}

void CShuntYardAlg::op(std::string & op, std::shared_ptr<CDataSize> & leftNum, std::shared_ptr<CDataSize> & rightNum)
{
    if(op == "+")
        *leftNum + *rightNum;
    else if(op == "-")
        *leftNum - *rightNum;
    else if(op == "*")
        *leftNum * *rightNum;
    else if(op == "/")
        *leftNum / *rightNum;
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
