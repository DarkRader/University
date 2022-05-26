/**
 * @author Artem Kuznetsov  <kuznear1@fit.cvut.cz>
 * @date 08.05.2021
 */
#pragma once
#include <string>

class CVariable
{
public:
    
    void findVariable();
    
protected:
    
    std::string m_variable;
    std::string m_content; //maybe do something for work with bytes
};
