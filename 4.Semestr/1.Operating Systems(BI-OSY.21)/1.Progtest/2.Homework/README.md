<h1>Memory Manager</h1>

<td class="lrtbCell" colspan="3" align="left"><p>The assigned task focuses on gaining a deeper understanding of memory allocation in operating systems. This is a highly simplified variant that involves implementing a basic dynamic memory manager for a user process.</p>

<p>In a simple modeled environment (disconnected in the Progtest testing environment), there are no heap managers. Therefore, functions like <tt>malloc</tt>, <tt>free</tt>, etc., and operators like <tt>new</tt> and <tt>delete</tt> do not exist. Your task is to implement simplified equivalents of these.</p>

<p>Your interface will work with a block of entrusted memory of a specified size (you will be provided with a pointer to an existing memory block and information about its size during initialization). The passed memory block will be contiguous and relatively large (units to hundreds of MiB). Your memory subsystem implementation will manage this entrusted memory block. Thus, it will allow its use in smaller parts according to incoming requests, maintain information about allocated and unused parts of the entrusted memory block, enable block allocation, deallocation of allocated blocks, and merge freed blocks into contiguous units.</p>

<p>You will submit source code containing functions with the specified interface. The testing environment will attach your submitted source code and begin using functions from the defined interface. Based on their response, it will determine the functionality or non-functionality of the submitted implementation. It is therefore necessary to strictly adhere to the interface specification (function names, parameter types, etc.). Your submitted code will not be a complete program. It will not have a <tt>main</tt> function; rather, it will be more like a module (function library).</p>

<p>Required functions and their meanings:</p>

<dl>
 <dt><tt>int  HeapInit ( void * startAddr, int size );</tt></dt><dd>

<p>The <tt>HeapInit</tt> function will be called at the beginning during subsystem initialization, before calling other implemented functions. The function takes a parameter <tt>startAddr</tt>, which specifies the memory address of the block your memory subsystem will manage. The second parameter is <tt>size</tt>, the size of the entrusted memory block in bytes.</p>

<p>In this memory block (starting at address <tt>startAddr</tt> and of size <tt>size</tt> bytes), a heap will be implemented. Therefore, all allocated blocks and your service information about which parts of your heap are used/free will be stored here.</p></dd>


 <dt><tt>void HeapDone ( int * pendingBlk );</tt></dt><dd>

<p>The <tt>HeapDone</tt> function will be called at the end of heap usage. The function will determine how many memory blocks are still allocated on the heap and pass this information to the caller through the output parameter <tt>pendingBlk</tt>.</p></dd>


 <dt><tt>void * HeapAlloc ( int size );</tt></dt><dd>

<p>The <tt>HeapAlloc</tt> function will serve as the entry point for allocating a memory block within the managed heap. The function takes the size of the requested block as a parameter and returns a pointer to the allocated memory space. If the function fails, it returns <tt>NULL</tt>. Failure can occur if the space in the entrusted memory is already exhausted or if the entrusted memory block does not contain a sufficiently large contiguous space for the requested allocation after previous allocations.</p></dd>


 <dt><tt>bool HeapFree ( void * blk );</tt></dt><dd>

<p>The <tt>HeapFree</tt> function is used to deallocate a previously allocated block using <tt>HeapAlloc</tt>. The function returns <tt>true</tt> if the block was successfully freed or <tt>false</tt> if the block could not be freed (invalid address provided, block already freed, etc.).</p></dd>

</dl>

<p>You should submit a file that contains the implementation of the required functions, necessary declarations of global variables, data types, and supporting functions. Use the provided sample code as a basis. If you leave conditional compilation directives, you can submit the source file directly to Progtest.</p>

<p>During implementation, you have very limited resources (see the list of header files available). STL is not available, standard functions for dynamic allocation (malloc, ...) and their C++ equivalents (new) are not available. The submitted code will run in a restricted environment. You will be limited by available memory (aside from the entrusted memory block, only a few kilobytes are available to store a few global variables). This extra available memory is insufficient to store all service information about allocations (you will need to store this information within the managed memory and manage its allocation).</p>


<p>Evaluation is divided into mandatory and optional parts. The mandatory part tests the correctness of the allocator. It must correctly allocate memory, ensure allocated blocks do not overlap, and properly merge freed memory.</p>

<p>Optional tests assess how your implementation handles fragmentation and its speed when dealing with a large number of allocated blocks. Failure to pass these tests will result in a deduction from your score.</p>

</td>