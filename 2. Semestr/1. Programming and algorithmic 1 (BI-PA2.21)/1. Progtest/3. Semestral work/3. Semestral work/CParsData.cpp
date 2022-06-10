/**
 * @author Artem Kuznetsov  <kuznear1@fit.cvut.cz>
 * @date 26.05.2021
 */
#include "CParsData.h"

std::string CParsData::getRes(void) const { return m_res; }

bool CParsData::parsingDate(const std::string & operation, std::ostream & history)
{
    if(operation == "konec") {
        std::cout << "End of work, thanks for using my calculator" << std::endl;
        return true;
    }
    
    if(operation == "") {
        std::cout << "Write something!" << std::endl;
        return false;
    }
    
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
    
    if(fillStack(seqNum, a) != true)
        return false;
    
    if(fillSymbol(newOper, a) != true)
        return false;
    
    int flag = 0;
    std::string variable = "";
    
    if(a.getOp(0) == "=")
    {
        flag = 1;
        variable = seqNum[0];
        auto iter = m_var.find(variable);
        if(iter == m_var.end()) {
            std::shared_ptr<CDataSize> tmp = a.shuntYardAlg(variable, m_var, history);
            m_var.insert({seqNum[0], tmp});
        } else {
            iter->second = a.shuntYardAlg(variable, m_var, history);
        }
    } else {
        a.shuntYardAlg(variable, m_var, history);
    }
    
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

bool CParsData::fillSymbol(std::string & operation, CShuntYardAlg & a)
{
    for(size_t i = 0; i < operation.size(); i++)
    {
        if(symbol(operation[i]) == true || operation[i] == '(' || operation[i] == ')')
        {
            if(i + 1 != operation.size()) {
                if(operation[i] == '=' && a.sizeStackOp() > 0) {
                    std::cout << "The equal sign is in the wrong place!" << std::endl;
                    return false;
                }
                
                if(symbol(operation[i]) == true && symbol(operation[i + 1]) == true && operation[i] != '=') {
                    std::cout << "Two characters follow each other, check the location of the brackets!" << std::endl;
                    return false;
                }
                
                if(operation[i] == '(' && operation[i + 1] == ')') {
                    std::cout << "Empty brackets without an expression inside!" << std::endl;
                    return false;
                }
                }
            
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
    
    return true;
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
            
        default:
            return false;
    }

    return false;
}

bool CParsData::fillStack(const std::vector<std::string> & seqNum, CShuntYardAlg & a)
{
    for(size_t i = 0; i < seqNum.size(); i++)
    {
        if(seqNum[i] != "") {
           if(findVariable(seqNum[i]) == true)
           {
               if(seqNum[i].size() > 1) {
                   std::cout << "Incorrect variable name!" << std::endl;
                   return false;
               }
               auto itVar = m_var.find(seqNum[i]);
               if(itVar != m_var.end()) {
                   if(itVar->second->getSize() == "small") {
                       if(itVar->second->getType() == "int")
                           a.addSmallVar(itVar->second->getVarInt(), 0, "int", "small");
                       else
                           a.addSmallVar(itVar->second->getVarInt(), itVar->second->getVarFloat(), "float", "small");
                   } else {
                       if(itVar->second->getType() == "int") {
                           std::vector<long long int> tmp;
                           a.addBigVar(itVar->second->getVecInt(), tmp, "int", "small");
                       }
                       else
                           a.addBigVar(itVar->second->getVecInt(), itVar->second->getVecFloat(), "float", "small");
                   }
               } else {
                   a.addSmallNum("", "", "", "");
               }
               //replaceComma(itVar->second, i, a);
               //a.addVariable(itVar->second);
           } else
               replaceComma(seqNum[i], i, a);
        }
    }
    
    return true;
}

bool CParsData::findVariable(const std::string & var)
{
//    auto iter = m_var.find(var);
//    if(iter != m_var.end())
//        return false;
    
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
    std::string num = "";
    std::string numFloat = "";
    if(repNum.size() < 18)
    {
        size_t j;
        for(j = 0; j < repNum.size(); j++)
        {
            if(repNum[j] == ',')
            {
                flag = 1;
                continue;
            }
            if(flag == 1 && repNum[j] != ',')
            {
                numFloat += repNum[j];
            } else {
                num += repNum[j];
            }
        }
        if(flag == 0) {
            a.addSmallNum(num, "", "int", "small");
        } else {
            a.addSmallNum(num, numFloat, "float", "small");
        }
    } else
    {
        std::vector<std::string> splitNum;
        std::vector<std::string> splitFloatNum;
        std::string partOfNum = "";
        std::string partOfFloatNum = "";
        size_t count = 0;
        for(size_t j = 0; j < repNum.size(); j++)
        {
            if(repNum[j] == ',')
            {
                flag = 1;
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
            a.addBigNum(splitNum, splitFloatNum, "float", "big");
        }
    }
}

void CParsData::fillVec(std::vector<std::string> & splitNum, const std::string & oper)
{
    size_t size = oper.size();
    std::string splitStr = "";
    while(size > 17)
    {
        size = size - 18;
        for(size_t i = size; i < size + 18; i++)
        {
            splitStr = splitStr + oper[i];
        }
        splitNum.push_back(splitStr);
        splitStr = "";
    }
    if(size != 0)
    {
        for(size_t i = 0; i < size; i++)
        {
            splitStr = splitStr + oper[i];
        }
        splitNum.push_back(splitStr);
    }
}
