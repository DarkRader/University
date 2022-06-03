/**
 * @author Artem Kuznetsov  <kuznear1@fit.cvut.cz>
 * @date 08.05.2021
 */
#include "CVariable.h"

std::string CVariable::findVariable(const std::string & var)
{
    auto itVar = m_variable.find(var);
        
    return itVar->second;
}

void CVariable::addVariable(const std::string & var, const std::string & value, const std::string & content)
{
    m_variable[var] = value;
    m_content = content;
}
