/**
 * @author Artem Kuznetsov  <kuznear1@fit.cvut.cz>
 * @date 04.06.2021
 */
#include "CDataSize.h"

CDataSize::CDataSize(void) {}

std::string CDataSize::getSize(void) const { return m_size; }

std::string CDataSize::getType(void) const { return m_type; }

long long int CDataSize::getVarInt(void) const { return m_varInt[0]; }

long long int CDataSize::getVarFloat(void) const { return m_floatPart[0]; }

long long int CDataSize::getRemains(void) const { return m_remains[0]; }

std::vector<long long int> CDataSize::getVecInt(void) const { return m_varInt; }

std::vector<long long int> CDataSize::getVecFloat(void) const { return m_floatPart; }

std::vector<long long int> CDataSize::getVecRem(void) const { return m_remains; }

void CDataSize::pushNum(long long int num) { m_varInt.push_back(num); }

void CDataSize::writeRem(std::vector<long long int> rem) { m_remains = rem; }
