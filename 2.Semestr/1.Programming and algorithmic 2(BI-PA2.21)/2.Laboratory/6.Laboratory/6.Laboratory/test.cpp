#include "CTaskScheduler.hpp"
#include <cassert>


int main ( void )
{
	CTaskScheduler ts;
	ts.add( {1, "najist se", 5} )
	  .add( {2, "Udelat progtest 2", 10} )
	  .add( {4, "udelat progtest 3", 8} )
	  .add( {3, "jit dnes brzy spat", 7} )
	  .add( {18, "task a", 24} );

	assert ( ts.size() == 5 );
	
	assert ( ts.get() == CTask(18, "task a", 24) );
	assert ( ts.remove() && ts.size() == 4 );
		
	assert ( ts.get() == CTask(2, "Udelat progtest 2", 10) );
	assert ( ts.remove() && ts.size() == 3 );
	
	assert ( ts.get() == CTask(4, "udelat progtest 3", 8) );
	assert ( ts.remove() && ts.size() == 2 );
	
	assert ( ts.get() == CTask(3, "jit dnes brzy spat", 7) );
	assert ( ts.remove() && ts.size() == 1 );
	
	assert ( ts.get() == CTask(1, "najist se", 5) );
	assert ( ts.remove() && ts.size() == 0 );
	assert ( ! ts.remove() );

	ts.add( {1, "najist se znovu", 20} );
	assert ( ts.size() == 1 );
	assert ( ts.get() == CTask(1, "najist se znovu", 20) );

	ts.add( {2, "Udelat progtest 3", 30} );
	assert ( ts.size() == 2 );
	assert ( ts.get() == CTask(2, "Udelat progtest 3", 30) );

	ts.add( {4, "udelat progtest 4", 8} );
	assert ( ts.size() == 3 );
	assert ( ts.get() == CTask(2, "Udelat progtest 3", 30) );

	assert ( ts.remove() && ts.size() == 2 );
	ts.add( {3, "jit dnes brzy spat", 0} );
	assert ( ts.size() == 3 );
	assert ( ts.get() == CTask(1, "najist se znovu", 20) );

	ts.add( {3, "jit dnes brzy spat", 0} );
	assert ( ts.size() == 3 );
	assert ( ts.get() == CTask(1, "najist se znovu", 20) );

	ts.add( {18, "task a", 24} );
	assert ( ts.size() == 4 );
	assert ( ts.get() == CTask(18, "task a", 24) );

	ts.add( {19, "task b", 24} );
	assert ( ts.size() == 5 );
	assert ( ts.get() == CTask(18, "task a", 24) );

	assert ( ts.remove() );
	ts.add ( {18, "task a", 24} );
	assert ( ts.size() == 5 );
	assert ( ts.get() == CTask(19, "task b", 24) );
	return 0;
}