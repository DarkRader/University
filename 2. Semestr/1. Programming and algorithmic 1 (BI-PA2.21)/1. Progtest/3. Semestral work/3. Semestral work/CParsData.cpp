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
    
    const std::regex re(R"((\+)|(\-)|(\*)|(\/)|(\()|(\))|(\=)|(\s))");

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
        variable = seqNum[0];
        std::shared_ptr<CDataSize> tmp = a.shuntYardAlg(variable, m_var);
        m_var.insert({seqNum[0], tmp});
    }
    
    a.shuntYardAlg(variable, m_var);
    
    
    
    
    if(m_res == "Zero")
        return false;
    
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
            if(i == 0 && operation[i] == '-')
            {
                a.changeNum(0);
                operation.erase(operation.begin() + i);
                continue;
            }
            if(i == 0 && operation[i] == '(' && operation[i + 1] == '-')
            {
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
           if(findVariable(seqNum[i]) == true)
           {
               auto itVar = m_var.find(seqNum[i]);
               a.addVariable(itVar->second);
           } else
               replaceComma(seqNum[i], i, a);
        }
    }
}

bool CParsData::findVariable(const std::string & var)
{
    char variable = var[0];
    
    switch (variable) {
        case 'A' ... 'Z':
            return true;
        
        case 'a' ... 'z':
            return false;
            
        default:
            return false;
    }
    
    
    return false;
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
        std::vector<std::string> splitFloatNum;
        std::string partOfNum = "";
        std::string partOfFloatNum = "";
        size_t pos = 0;
        size_t count = 0;
        for(size_t j = 0; j < repNum.size(); j++)
        {
            if(repNum[j] == ',')
            {
                flag = 1;
                pos = j;
                continue;
            }
            
            if(flag == 1 && repNum[j] != ',')
            {
                partOfFloatNum += repNum[j];
                count++;
                if(count == 18)
                {
                    splitFloatNum.push_back(partOfFloatNum);
                    partOfFloatNum = "";
                    count = 0;
                }
            } else if(flag == 0) {
                partOfNum += repNum[j];
            }
            
        }
        
        if(partOfFloatNum != "")
        {
            splitFloatNum.push_back(partOfFloatNum);
        }

        fillVec(splitNum, partOfNum);
        if(flag == 0)
        {
            a.addBigNum(splitNum, splitFloatNum, "int", "big");
        }
        else {
            //fillVec(splitFloatNum, partOfFloatNum);
            a.addBigNum(splitNum, splitFloatNum, "float", "big");
        }
    }
}

void CParsData::fillVec(std::vector<std::string> & splitNum, const std::string & oper)
{
    size_t size = oper.size();
    std::string splitStr = "";
    int lostNull = 0;
    while(size > 17)
    {
        size = size - 18;
        for(size_t i = size; i < size + 18; i++)
        {
            splitStr = splitStr + oper[i];
        }
        if(lostNull == 1) {
            splitStr = splitStr + "0";
        }
        splitNum.push_back(splitStr);
        if(splitStr[0] == '0')
            lostNull = 1;
        splitStr = "";
    }
    if(size != 0)
    {
        for(size_t i = 0; i < size; i++)
        {
            splitStr = splitStr + oper[i];
        }
        if(lostNull == 1) {
            splitStr = splitStr + "0";
        }
        splitNum.push_back(splitStr);
    }
}
