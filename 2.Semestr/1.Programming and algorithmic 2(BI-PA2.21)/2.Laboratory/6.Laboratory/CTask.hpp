#pragma once
#include <string>

class CTask
{
	public:
		CTask ( size_t, const std::string &, size_t );
		const std::string & description ( void ) const;
		size_t ID ( void ) const;
		bool operator < ( const CTask & ) const;
		bool operator == ( const CTask & ) const;
	private:
		size_t m_id;
		std::string m_description;
		size_t m_priority;
};