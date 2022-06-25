#include "CTask.hpp"
#include <tuple>

CTask::CTask ( size_t id, const std::string & description, size_t priority )
: m_id(id),
  m_description(description),
  m_priority(priority)
{
}

const std::string & CTask::description ( void ) const
{
	return m_description;
}

size_t CTask::ID ( void ) const
{
	return m_id;
}

bool CTask::operator < ( const CTask & oth ) const
{
	return m_priority < oth.m_priority;
}

bool CTask::operator == ( const CTask & oth ) const
{
	return std::tie(m_id, m_description, m_priority) == std::tie(oth.m_id, oth.m_description, oth.m_priority);
}