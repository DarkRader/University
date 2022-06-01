/**
 * @author Artem Kuznetsov  <kuznear1@fit.cvut.cz>
 * @date 26.05.2021
 */
#include "CParsData.h"

std::string CParsData::getRes(void) const { return m_res; }

bool CParsData::parsingDate(const std::string & operace)
{
    const std::regex re_control(R"(((\+)|(\-)|(\*)|(\/)|(\()|(\))|(\=)|(\s)|(,)|([a-zA-Z0-9])))");
    
    std::sregex_token_iterator it_control{operace.begin(), operace.end(), re_control, -1};

    std::vector<std::string> control( it_control, {} );
    
    if(controlSynErr(control) == false)
        std::cout << "Syntax error, try again!" << std::endl;
    
    const std::regex re(R"((\+)|(\-)|(\*)|(\/)|(\()|(\))|(\=)|(\s))");

    std::sregex_token_iterator it{operace.begin(), operace.end(), re, -1};

    std::vector<std::string> seqNum( it, {} );
    
    CShuntYardAlg a;
    
    fillSymbol(operace, a);
    
    fillStack(seqNum, a);
    
    m_res = a.shuntYardAlg();
    
    return true;
}

bool CParsData::controlSynErr(const std::vector<std::string> & control)
{
    for(size_t i = 0; i < control.size(); i++)
    {
        if(control[i] != "") {
            return false;
        }
    }
    
    return true;
}

void CParsData::fillSymbol(const std::string & operace, CShuntYardAlg & a)
{
    for(size_t i = 0; i < operace.size(); i++)
    {
        if(symbol(operace[i]) == true)
        {
            std::string s(1, operace[i]);
            a.addOp(s);
        }
    }
}

bool CParsData::symbol(const char & symbol)
{
    if(symbol == '+')
        return true;
    else if(symbol == '-')
        return true;
    else if(symbol == '*')
        return true;
    else if(symbol == '/')
        return true;
    else if(symbol == '=')
        return true;
    else if(symbol == '(')
        return true;
    else if(symbol == ')')
        return true;
    
    return false;
}

void CParsData::fillStack(std::vector<std::string> & seqNum, CShuntYardAlg & a)
{
    for(size_t i = 0; i < seqNum.size(); i++)
    {
        if(seqNum[i] != "") {
            a.addNum(seqNum[i]);
        }
    }
}
