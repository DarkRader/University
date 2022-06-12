/**
 * @author Artem Kuznetsov  <kuznear1@fit.cvut.cz>
 * @date 26.05.2021
 */
#include "CParsData.h"

std::string CParsData::getRes(void) const { return m_res; }

bool CParsData::parsingDate(const std::string & operation)
{
    std::string newOper = operation;
    clWhiteSpace(newOper);
    if(newOper == "quit") {
        std::cout << "End of work, thanks for using my calculator" << std::endl;
        return true;
    }
    else if(newOper == "") {
        std::cout << "Write something!" << std::endl;
        return false;
    }
    
    const std::regex re_control(R"(((\+)|(\-)|(\*)|(\/)|(\()|(\))|(\=)|(\s)|(,)|([a-zA-Z0-9])))");
    
    std::sregex_token_iterator it_control{operation.begin(), operation.end(), re_control, -1};

    std::vector<std::string> control( it_control, {} );
    
    if(controlSynErr(control) == false)
        return false;
    
    const std::regex re(R"((\+)|(\-)|(\*)|(\/)|(\()|(\))|(\=)|(\s))");

    std::sregex_token_iterator it{newOper.begin(), newOper.end(), re, -1};

    std::vector<std::string> seqNum( it, {} );
    
    CShuntYardAlg a;
    
    if(fillStack(seqNum, a) != true)
        return false;
    
    if(fillSymbol(newOper, a) != true)
        return false;
    
    std::string variable = "";
    
    if(writeRes(variable, seqNum, a) != true)
        return false;
    
    return true;
}

bool CParsData::writeRes(std::string & variable, std::vector<std::string> & seqNum, CShuntYardAlg & a)
{
    if(a.getOp(0) == "=")
    {
        variable = seqNum[0];
        auto iter = m_var.find(variable);
        if(iter == m_var.end()) {
            if(a.shuntYardAlg() == true) {
            std::shared_ptr<CDataSize> tmp = a.getRes(2);
            m_var.insert({seqNum[0], tmp});
            } else {
                return false;
            }
        } else {
            if(a.shuntYardAlg() == true) {
            iter->second = a.getRes(2);
            } else {
                return false;
            }
        }
    } else {
        if(a.shuntYardAlg() == true) {
        a.getRes(1);
        } else {
            return false;
        }
    }
    
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
        } else {
            i++;
        }
    }
}

bool CParsData::fillSymbol(std::string & operation, CShuntYardAlg & a)
{
    int count = 0;
    int bracket = 0;
    
    if(operation.size() > 0 && (operation[0] == '*' || operation[0] == '/' || operation[0] == '=' || operation[0] == '+')) {
        if(symbol(operation[0]) == true && operation[0] != '=') {
            std::cout << "The operation cannot be at the beginning of the expression!" << std::endl;
            return false;
        }
    }
    
    if(writeSymbol(operation, a, count, bracket) != true)
        return false;
    
    if(bracket > 0) {
        std::cout << "There is an opening bracket, but no closing one!" << std::endl;
        return false;
    }
    
    if(count == 0) {
        std::cout << "There are no operators, enter the correct expression!" << std::endl;
        return false;
    }
    
    return true;
}

bool CParsData::writeSymbol(std::string & operation, CShuntYardAlg & a, int & count, int & bracket)
{
    for(size_t i = 0; i < operation.size(); i++)
    {
        if(symbol(operation[i]) == true || operation[i] == '(' || operation[i] == ')')
        {
            
            if(errorInSymbol(operation, i, bracket, a) == false)
                return false;

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
                count++;
                i++;
                a.addOp("- fl");
                continue;
            }
            a.addOp(s);
            count++;
        }
    }
    
    return true;
}

bool CParsData::errorInSymbol(std::string & operation, size_t i, int & bracket, CShuntYardAlg & a)
{
    
    if(operation[i] == ')' && bracket == 0) {
        std::cout << "You can't write a closing bracket without an opening one!" << std::endl;
        return false;
    }
    
    if(operation[i] == '=' && a.sizeStackOp() > 0) {
        std::cout << "The equal sign is in the wrong place!" << std::endl;
        return false;
    }
    
    if(i + 1 != operation.size()) {
        
        if(symbol(operation[i]) == true && symbol(operation[i + 1]) == true && operation[i] != '=') {
            std::cout << "Two characters follow each other, check the location of the brackets!" << std::endl;
            return false;
        }
        
        if(operation[i] == '(' && operation[i + 1] == ')') {
            std::cout << "Empty brackets without an expression inside!" << std::endl;
            return false;
        }
        
        if(i > 0 && operation[i] == '(' && operation[i - 1] != '(' && symbol(operation[i - 1]) == false) {
            std::cout << "You don't have a sign in front of the brackets, check it out!" << std::endl;
            return false;
        }
        
        if(i != operation.size() - 1 && operation[i] == ')' && operation[i + 1] != ')' && symbol(operation[i + 1]) != true) {
            std::cout << "You don't have a sign after the brackets, check it out!" << std::endl;
            return false;
        }
            
    }
    
    if(operation[i] == '(')
        bracket++;
    
    if(operation[i] == ')')
        bracket--;
    
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
                   if(i > 0) {
                       std::cout << "A nonexistent variable is present in the expression!" << std::endl;
                       return false;
                   } else
                       a.addSmallNum("", "", "", "");
               }
           } else
               if(transformNum(seqNum[i], i, a) != true)
                   return false;
        }
    }
    
    return true;
}

bool CParsData::findVariable(const std::string & var)
{
    if(var.size() > 1)
    {
        return false;
    }
    
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

bool CParsData::transformNum(std::string repNum, size_t i, CShuntYardAlg & a)
{
    int flag = 0;
    std::string num = "";
    std::string numFloat = "";
    if(repNum.size() < 18)
    {
        for(size_t j = 0; j < repNum.size(); j++)
        {
            if(repNum[j] != ',' && (repNum[j] < 48 || repNum[j] > 57)) {
                std::cout << "Syntax error in numbers or variables!" << std::endl;
                return false;
            }
            
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
            if(repNum[j] != ',' && (repNum[j] < 48 || repNum[j] > 57)) {
                std::cout << "Syntax error in numbers or variables!" << std::endl;
                return false;
            }
            
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
    
    return true;
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
