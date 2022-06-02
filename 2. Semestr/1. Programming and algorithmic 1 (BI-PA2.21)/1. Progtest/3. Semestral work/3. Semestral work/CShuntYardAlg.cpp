/**
 * @author Artem Kuznetsov  <kuznear1@fit.cvut.cz>
 * @date 31.05.2021
 */
#include "CShuntYardAlg.h"

std::string CShuntYardAlg::getNum(size_t i) const { return stakNum[i]; }

std::string CShuntYardAlg::getOp(size_t i) const { return stakOp[i]; }

void CShuntYardAlg::addOp(const std::string & op)
{
    stakOp.push_back(op);
}

void CShuntYardAlg::addNum(const std::string & num)
{
    stakNum.push_back(num);
}

void CShuntYardAlg::changeNum(const std::string & num, size_t i)
{
    stakNum[i] = num;
}

void CShuntYardAlg::changeOp(const std::string & op, size_t i)
{
    stakOp[i] = op;
}

std::string CShuntYardAlg::shuntYardAlg()
{
    size_t i = 0, j = 0;
    
    while(stakOp[j] == "(")
    {
        j++;
    }
    
    while(stakOp.size() != 0)
    {
        if(stakOp.size() == j + 1)
        {
            typDateAndLenght(i, j);
            stakNum.erase(stakNum.begin() + i + 1);
            stakOp.erase(stakOp.begin() + j);
            if(i != 0)
                i--;
            if(j != 0)
                j--;
        } else if(stakOp[j + 1] != ")" && stakOp[j + 1] != "(" && stakOp[j] != "(" && stakOp[j] != "- fl" &&
           prior(stakOp[j + 1]) >= prior(stakOp[j]))
        {
            i++;
            j++;
        } else if(stakOp[j + 1] == "(")
        {
            i++;
            j = j + 2;
            while(stakOp[j] == "(")
            {
                j++;
            }
        } else if(stakOp[j] == "- fl")
        {
            std::string tmp = '-' + stakNum[i];
            stakNum[i] = tmp;
            stakOp.erase(stakOp.begin() + j);
            if(stakOp[j] == ")" && stakOp[j - 1] == "(")
            {
                stakOp.erase(stakOp.begin() + j);
                stakOp.erase(stakOp.begin() + j - 1);
                j = j - 2;
                if(stakNum.size() - 1 != i) {
                    i++;
                    j++;
                }  else {
                    i--;
                }
            }
            
        } else if(stakOp[j + 1] != ")" && stakOp[j + 1] != "(" && stakOp[j] != "(" && stakOp[j] != "- fl"
                  && prior(stakOp[j + 1]) < prior(stakOp[j]))
        {
            typDateAndLenght(i, j);
            stakNum.erase(stakNum.begin() + i + 1);
            stakOp.erase(stakOp.begin() + j);
            if(stakOp.size() == j + 1) {
                i--;
                j--;
            }
        }else if(stakOp[j + 1] == ")")
        {
            while(stakOp[j] != "(")
            {
                typDateAndLenght(i, j);
                stakNum.erase(stakNum.begin() + i + 1);
                stakOp.erase(stakOp.begin() + j);
                if(i != 0)
                    i--;
                if(j != 0)
                    j--;
            }
            stakOp.erase(stakOp.begin() + j);
            stakOp.erase(stakOp.begin() + j);
            if(j != 0)
                j--;
            std::string tmp = stakNum[i + 1];
            if(tmp[0] == '-' && stakOp[j] == "-") {
                tmp.erase(0, 1);
                stakNum[i + 1] = tmp;
                stakOp[j] = "+";
            }
        }
        
    }
    
    return stakNum[0];
}

void CShuntYardAlg::typDateAndLenght(size_t i, size_t j)
{
    size_t x = 0, y = 0;
    std::string leftNum = stakNum[i], rightNum = stakNum[i + 1];
    std::string typ = "int";
    while(x < leftNum.size() || y < rightNum.size())
    {
        if(x < leftNum.size()) {
            x++;
            if(leftNum[x] == ',' || leftNum[x] == '.') {
                typ = "float";
                if(leftNum[x] == ',')
                    leftNum[x] = '.';
            }
        }
        if(y < rightNum.size()) {
            y++;
            if(rightNum[y] == ',' || leftNum[x] == '.') {
                typ = "float";
                if(rightNum[y] == ',')
                    rightNum[y] = '.';
            }
        }
    }
    
    if(typ == "int")
    {
        long long int leftIntNum = 0;
        long long int rightIntNum = 0;
        if(stakOp.size() != 1 && stakOp[j - 1] == "-") {
            leftIntNum = atoi(leftNum.c_str());
            leftIntNum = leftIntNum * (-1);
            rightIntNum = atoi(rightNum.c_str());
            stakOp[j - 1] = "+";
        } else {
            leftIntNum = atoi(leftNum.c_str());
            rightIntNum = atoi(rightNum.c_str());
        }
        CInteger leftVarInt(leftIntNum);
        CInteger righVarInt(rightIntNum);
        op(stakOp[j], leftVarInt, righVarInt);
        stakNum[i] = leftVarInt.getNewVariable();
    } else if(typ == "float")
    {
        long double leftFloatNum = 0;
        long double rightFloatNum = 0;
        if(stakOp.size() != 1 && stakOp[j - 1] == "-") {
            leftFloatNum = atoi(leftNum.c_str());
            leftFloatNum = leftFloatNum * (-1);
            rightFloatNum = atoi(rightNum.c_str());
            stakOp[j - 1] = "+";
        } else {
            leftFloatNum = ::atof(leftNum.c_str());
            rightFloatNum = ::atof(rightNum.c_str());
        }
        CFloat leftVarFloat(leftFloatNum);
        CFloat righVarFloat(rightFloatNum);
        op(stakOp[j], leftVarFloat, righVarFloat);
        stakNum[i] = leftVarFloat.getNewVariable();
        stakNum[i].erase(stakNum[i].find_last_not_of('0') + 1);
        stakNum[i].erase(stakNum[i].find_last_not_of('.') + 1);
    }
}

int CShuntYardAlg::prior(const std::string & op)
{
    if(op == "+" || op == "-")
        return 1;
    else if(op == "*" || op == "/")
        return 2;
    
    return -10;
}

void CShuntYardAlg::op(std::string & op, CInteger & leftNum, CInteger & rightNum)
{
    if(op == "+")
        leftNum + rightNum;
    else if(op == "-")
        leftNum - rightNum;
    else if(op == "*")
        leftNum * rightNum;
    else if(op == "/")
        leftNum / rightNum;
}

void CShuntYardAlg::op(std::string & op, CFloat & leftNum, CFloat & rightNum)
{
    if(op == "+")
        leftNum + rightNum;
    else if(op == "-")
        leftNum - rightNum;
    else if(op == "*")
        leftNum * rightNum;
}
