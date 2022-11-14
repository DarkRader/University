#pragma once
#include "CTask.hpp"
#include <queue>
#include <set>

class CTaskScheduler
{
	public:
		CTaskScheduler & add ( const CTask & );
		// ==========================================
		const CTask & get ( void ) const;
		// ==========================================
		bool remove ( void );
		// ==========================================
		size_t size ( void ) const;
		// ==========================================
	private:
		// TODO
};