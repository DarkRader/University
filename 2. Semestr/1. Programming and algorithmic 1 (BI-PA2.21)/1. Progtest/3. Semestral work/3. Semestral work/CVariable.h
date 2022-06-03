/**
 * @author Artem Kuznetsov  <kuznear1@fit.cvut.cz>
 * @date 08.05.2021
 */
#pragma once
#include <string>
#include <map>

class CVariable
{
public:
    
    std::string findVariable(const std::string & var);
    
    void addVariable(const std::string & var, const std::string & value, const std::string & content);
    
protected:
    
    std::map <std::string, std::string> m_variable;
    std::string m_content; //maybe do something for work with bytes
};
