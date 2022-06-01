/**
 * @author Artem Kuznetsov  <kuznear1@fit.cvut.cz>
 * @date 31.05.2021
 */
#include "CShuntYardAlg.h"

void CShuntYardAlg::addOp(const std::string & op)
{
    stakOp.push_back(op);
}

void CShuntYardAlg::addNum(const std::string & num)
{
    stakNum.push_back(num);
}

std::string CShuntYardAlg::shuntYardAlg()
{
    size_t i = 0, j = 0;
    
    if(stakOp[0] == "(") {
        j++;
    }
    
    while(stakOp.size() != 0)
    {
        if(stakOp.size() == j + 1)
        {
            typDateAndLenght(i, j);
//            long long int leftNum = 0;
//            long long int rightNum = 0;
//            if(stakOp.size() != 1 && stakOp[j - 1] == "-") {
//                leftNum = atoi(stakNum[i].c_str());
//                leftNum = leftNum * (-1);
//                rightNum = atoi(stakNum[i + 1].c_str());
//                stakOp[j - 1] = "+";
//            } else {
//                leftNum = atoi(stakNum[i].c_str());
//                rightNum = atoi(stakNum[i + 1].c_str());
//            }
//            CInteger leftVariable(leftNum);
//            CInteger righVariable(rightNum);
//            op(stakOp[j], leftVariable, righVariable);
//            stakNum[i] = leftVariable.getNewVariable();
            stakNum.erase(stakNum.begin() + i + 1);
            stakOp.erase(stakOp.begin() + j);
            if(i != 0)
                i--;
            if(j != 0)
                j--;
        } else if(stakOp[j + 1] != ")" && stakOp[j + 1] != "(" && stakOp[j] != "(" &&
           prior(stakOp[j + 1]) >= prior(stakOp[j]))
        {
            i++;
            j++;
        } else if(stakOp[j + 1] == "(")
        {
            i++;
            j = j + 2;
        } else if(stakOp[j + 1] != ")" && stakOp[j + 1] != "(" && stakOp[j] != "("
                  && prior(stakOp[j + 1]) < prior(stakOp[j]))
        {
            typDateAndLenght(i, j);
//            long long int leftNum = atoi(stakNum[i].c_str());
//            long long int rightNum = atoi(stakNum[i + 1].c_str());
//            CInteger leftVariable(leftNum);
//            CInteger righVariable(rightNum);
//            op(stakOp[j], leftVariable, righVariable);
//            stakNum[i] = leftVariable.getNewVariable();
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
//                long long int leftNum = 0;
//                long long int rightNum = 0;
//                if(stakOp.size() != 1 && stakOp[j - 1] == "-") {
//                    leftNum = atoi(stakNum[i].c_str());
//                    leftNum = leftNum * (-1);
//                    rightNum = atoi(stakNum[i + 1].c_str());
//                    stakOp[j - 1] = "+";
//                } else {
//                    leftNum = atoi(stakNum[i].c_str());
//                    rightNum = atoi(stakNum[i + 1].c_str());
//                }
//                CInteger leftVariable(leftNum);
//                CInteger righVariable(rightNum);
//                op(stakOp[j], leftVariable, righVariable);
//                stakNum[i] = leftVariable.getNewVariable();
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
        }
        
    }
    
    return stakNum[0];
}

void CShuntYardAlg::typDateAndLenght(size_t i, size_t j)
{
    size_t x = 0, y = 0;
    std::string leftNum = stakNum[i], rightNum = stakNum[i + 1];
    std::string typ = "int";
    while(x < leftNum.size() && y < rightNum.size())
    {
        if(leftNum[x] == ',') {
            typ = "float";
            break;
        }
        if(rightNum[y] == ',') {
            typ = "float";
            break;
        }
        if(x < leftNum.size())
            x++;
        if(y < rightNum.size())
            y++;
    }
    
    if(typ == "int")
    {
        long long int leftNum = 0;
        long long int rightNum = 0;
        if(stakOp.size() != 1 && stakOp[j - 1] == "-") {
            leftNum = atoi(stakNum[i].c_str());
            leftNum = leftNum * (-1);
            rightNum = atoi(stakNum[i + 1].c_str());
            stakOp[j - 1] = "+";
        } else {
            leftNum = atoi(stakNum[i].c_str());
            rightNum = atoi(stakNum[i + 1].c_str());
        }
        CInteger leftVarInt(leftNum);
        CInteger righVarInt(rightNum);
        op(stakOp[j], leftVarInt, righVarInt);
        stakNum[i] = leftVarInt.getNewVariable();
    } else if(typ == "double")
    {
        long double leftNum = 0;
        long double rightNum = 0;
        if(stakOp.size() != 1 && stakOp[j - 1] == "-") {
            leftNum = atoi(stakNum[i].c_str());
            leftNum = leftNum * (-1);
            rightNum = atoi(stakNum[i + 1].c_str());
            stakOp[j - 1] = "+";
        } else {
            leftNum = atoi(stakNum[i].c_str());
            rightNum = atoi(stakNum[i + 1].c_str());
        }
        CFloat leftVarFloat(leftNum);
        CFloat righVarFloat(rightNum);
        op(stakOp[j], leftVarFloat, righVarFloat);
        stakNum[i] = leftVarFloat.getNewVariable();
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

