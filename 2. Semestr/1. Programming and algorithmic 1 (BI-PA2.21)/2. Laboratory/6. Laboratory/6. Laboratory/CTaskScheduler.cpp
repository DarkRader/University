#include "CTaskScheduler.hpp"


CTaskScheduler & CTaskScheduler::add ( const CTask & task );

const CTask & CTaskScheduler::get ( void ) const;

bool CTaskScheduler::remove ( void );

size_t CTaskScheduler::size ( void ) const;