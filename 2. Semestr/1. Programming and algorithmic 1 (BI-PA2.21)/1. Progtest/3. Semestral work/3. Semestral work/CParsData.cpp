/**
 * @author Artem Kuznetsov  <kuznear1@fit.cvut.cz>
 * @date 26.05.2021
 */
#include "CParsData.h"

std::string CParsData::getRes(void) const { return m_res; }

bool CParsData::parsingDate(const std::string & operation)
{
    const std::regex re_control(R"(((\+)|(\-)|(\*)|(\/)|(\()|(\))|(\=)|(\s)|(,)|([a-zA-Z0-9])))");
    
    std::sregex_token_iterator it_control{operation.begin(), operation.end(), re_control, -1};

    std::vector<std::string> control( it_control, {} );
    
    if(controlSynErr(control) == false)
        return false;
    
    std::string newOper = operation;
    
    clWhiteSpace(newOper);
    
    const std::regex re(R"((\+)|(\-)|(\*)|(\/)|(\()|(\))|(\=))");

    std::sregex_token_iterator it{newOper.begin(), newOper.end(), re, -1};

    std::vector<std::string> seqNum( it, {} );
    
    CShuntYardAlg a;
    
    fillStack(seqNum, a);
    
    fillSymbol(newOper, a);
    
    int flag = 0;
    std::string variable = "";
    
    if(a.getOp(0) == "=")
    {
        flag = 1;
        variable = a.getNum(0);
    }
    
    m_res = a.shuntYardAlg(m_var);
    
    if(m_res == "Zero")
        return false;
    
    //if(m_res == "var")
        //m_var.addVariable(seqNum[0], a.getType(), a.getSize(), a.getInt(), a.getFloat(), newOper);
    
    return true;
}

bool CParsData::controlSynErr(const std::vector<std::string> & control)
{
    for(size_t i = 0; i < control.size(); i++)
    {
        if(control[i] != "") {
            std::cout << "Syntax error, try again!" << std::endl;
            return false;
        }
    }
    
    return true;
}

void CParsData::clWhiteSpace(std::string & operation)
{
    for(size_t i = 0; i < operation.size(); )
    {
        if(operation[i] == ' ') {
            operation.erase(operation.begin() + i);
        }
        i++;
    }
}

void CParsData::fillSymbol(std::string & operation, CShuntYardAlg & a)
{
    for(size_t i = 0; i < operation.size(); i++)
    {
        if(symbol(operation[i]) == true)
        {
            std::string s(1, operation[i]);
            if(i == 0 && operation[i] == '(' && operation[i + 1] == '-')
            {
                std::string newNum = '-' + a.getNum(0);
                a.changeNum(0);
                operation.erase(operation.begin() + i + 1);
            } else if(operation[i] == '(' && operation[i + 1] == '-')
            {
                a.addOp(s);
                i++;
                a.addOp("- fl");
                continue;
            }
            a.addOp(s);
        }
    }
}

bool CParsData::symbol(const char & symbol)
{
    switch (symbol) {
        case '+':
            return true;
        case '-':
            return true;
        case '*':
            return true;
        case '/':
            return true;
        case '=':
            return true;
        case '(':
            return true;
        case ')':
            return true;
            
        default:
            return false;
    }

    return false;
}

void CParsData::fillStack(const std::vector<std::string> & seqNum, CShuntYardAlg & a)
{
    for(size_t i = 0; i < seqNum.size(); i++)
    {
        if(seqNum[i] != "") {
            replaceComma(seqNum[i], i, a);
        }
    }
}

void CParsData::replaceComma(std::string repNum, size_t i, CShuntYardAlg & a)
{
    int flag = 0;
    if(repNum.size() < 18)
    {
        size_t j;
        for(j = 0; j < repNum.size(); j++)
        {
            if(repNum[j] == ',')
            {
                repNum[j] = '.';
                a.addSmallNum(repNum, "float", "small", j);
                flag = 1;
                break;
            }
        }
        if(flag == 0) {
            a.addSmallNum(repNum, "int", "small", j);
        }
    } else
    {
        std::vector<std::string> splitNum;
        std::string partOfNum = "";
        size_t count = 0;
        for(size_t j = 0; j < repNum.size(); j++, count++)
        {
            if(repNum[j] == ',')
            {
                splitNum.push_back(partOfNum);
                splitNum.push_back("");
                flag = 1;
                count = 0;
                partOfNum = "";
                continue;
            }
            
            partOfNum = partOfNum + repNum[j];
            
            if(count == 18)
            {
                splitNum.push_back(partOfNum);
                count = 0;
                partOfNum = "";
            }
        }
        if(partOfNum != "")
            splitNum.push_back(partOfNum);
        if(flag == 0)
            a.addBigNum(splitNum, "int", "big");
        else
            a.addBigNum(splitNum, "float", "big");
    }
}
