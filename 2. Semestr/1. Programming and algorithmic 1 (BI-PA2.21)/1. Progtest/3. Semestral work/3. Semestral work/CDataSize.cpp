/**
 * @author Artem Kuznetsov  <kuznear1@fit.cvut.cz>
 * @date 04.06.2021
 */
#include "CDataSize.h"

std::string CDataSize::getSize(void) const { return m_size; }

std::string CDataSize::getType(void) const { return m_type; }

CDataSize::CDataSize(void) {}

void CDataSize::writeSize(const std::string & size)
{
    m_size = size;
}

void CDataSize::writeType(const std::string & type)
{
    m_type = type;
}

void CDataSize::writeFloat(long double num) { m_floatPart[0] = num; };

void CDataSize::pushNum(long long int num)
{
    m_varInt.push_back(num);
}

long long int CDataSize::getVarInt(void) const { return m_varInt[0]; }

long double CDataSize::getVarFloat(void) const { return m_floatPart[0]; }

std::vector<long long int> CDataSize::getVecInt(void) const { return m_varInt; }

std::vector<long long int> CDataSize::getVecFloat(void) const { return m_floatPart; }
