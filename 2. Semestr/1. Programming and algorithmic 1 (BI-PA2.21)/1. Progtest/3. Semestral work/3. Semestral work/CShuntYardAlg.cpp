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

void CShuntYardAlg::addSmallNum(const std::string & num, const std::string & type, const std::string & size, size_t i)
{
    std::shared_ptr<CDataSize> tmp;
    if(type == "float")
    {
        long double numFloat = ::atof(num.c_str());
        tmp = std :: make_shared<CFloat>(numFloat, "float", "small");
    } else
    {
        long long int numInt = atoll(num.c_str());
        tmp = std :: make_shared<CInteger>(numInt, "int", "small");
    }
    stackNum.push_back(tmp);
}

void CShuntYardAlg::addBigNum(const std::vector<std::string> & num, const std::string & type, const std::string & size)
{
    std::shared_ptr<CDataSize> tmp;
    
    if(type == "float")
    {
        tmp = std :: make_shared<CFloatBig>(num, "float", "big");
    } else
    {
        tmp = std :: make_shared<CIntegerBig>(num, "int", "big");
    }
    stackNum.push_back(tmp);
}

void CShuntYardAlg::print(void)
{
    std::cout << "Result: ";
    
    if(stackNum[0]->getSize() == "small")
    {
        if(stackNum[0]->getType() == "float")
            std::cout << std::fixed << std::setprecision(5) << stackNum[0]->getVarFloat() << std::endl;
            //std::cout << stackNum[0]->getVarFloat() << std::endl;
        else
            std::cout << stackNum[0]->getVarInt() << std::endl;
    } else {
        
    }
}

std::string CShuntYardAlg::shuntYardAlg(CVariable & var)
{
    size_t i = 0, j = 0;
    std::string variable = "";
    if(stackOp[j] == "=")
    {
        variable = "var";
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
            stackNum.erase(stackNum.begin() + i + 1);
            stackOp.erase(stackOp.begin() + j);
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
            stackNum.erase(stackNum.begin() + i + 1);
            stackOp.erase(stackOp.begin() + j);
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
                stackNum.erase(stackNum.begin() + i + 1);
                stackOp.erase(stackOp.begin() + j);
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
    
    print();
    
    return variable;
}

void CShuntYardAlg::typDateAndLenght(size_t i, size_t j, CVariable & var)
{
//    if(stakNum[i] == "A" || stakNum[i] == "B")
//    {
//        stakNum[i] = var.findVariable(stakNum[i]);
//    }
//    if(stakNum[i + 1] == "A" || stakNum[i + 1] == "B")
//    {
//        stakNum[i] = var.findVariable(stakNum[i]);
//    }
    
    if(stackOp.size() != 1 && stackOp[j - 1] == "-")
    {
        stackNum[i]->negativeNum();
        stackOp[j - 1] = "+";
    }
    
    if(stackNum[i]->getType() == "float" && stackNum[i + 1]->getType() == "int")
    {
        stackNum[i + 1] = std :: make_shared<CFloat>(stackNum[i + 1]->getVarInt(), stackNum[i + 1]->getVarInt(), "float", "small");
    } else if (stackNum[i]->getType() == "int" && stackNum[i + 1]->getType() == "float")
    {
        stackNum[i] = std :: make_shared<CFloat>(stackNum[i]->getVarInt(), stackNum[i]->getVarInt(), "float", "small");
    }
    
    op(stackOp[j], stackNum[i], stackNum[i + 1]);
}

int CShuntYardAlg::prior(const std::string & op)
{
    if(op == "+" || op == "-")
        return 1;
    else if(op == "*" || op == "/")
        return 2;
    
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

void CShuntYardAlg::op(std::string & op, CFloat & leftNum, CFloat & rightNum)
{
    if(op == "+")
        leftNum + rightNum;
    else if(op == "-")
        leftNum - rightNum;
    else if(op == "*")
        leftNum * rightNum;
    else if(op == "/") {
        if(rightNum.getVarInt() == 0)
        {
            std::cout << "You can't divide by zero" << std::endl;
            //stakNum[0] = "Zero";
        }
        leftNum / rightNum;
    }
}
