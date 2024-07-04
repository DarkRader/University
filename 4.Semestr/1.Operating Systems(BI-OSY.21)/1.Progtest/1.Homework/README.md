
<h1>Equipment Rental</h1>

<p>The task is to implement a set of classes that optimize the profit of rental companies.</p>

<p>We assume that we operate a tool rental company. The rental company has various tools available for rent, such as 1 excavator, 3 vibrating rammers, ... The rental company has a website where customers enter their rental requests. The company operates with innovative business models, thus renting its tools through auctions. Customers fill out their rental requests, each request including information about the time interval and the offered payment for the rental. The rental company then selects from the filled intervals to maximize its profit. The following constraints must be observed during rental:</p>

<ul>
 <li>At any one time, we can only serve as many customers as we have units of that particular type of tool.</li>
 <li>Intervals of consecutive rentals of individual tools must not overlap or touch.</li>
 <li>Our rental company is not very wealthy, so we have a maximum of 3 units of each type of tool.</li>
</ul>

<p>The problem described above is not as trivial as it might seem at first glance. The solution can be found using dynamic programming, and the algorithm was explained in the last lecture of BI-AG1. For 1, 2, and 3 units of rented tools, the problem can be solved in times <tt>O(n log(n))</tt>, <tt>O(n<sup>2</sup>)</tt>, and <tt>O(n<sup>3</sup>)</tt>. Because this is a problem with higher time complexity, it is beneficial to use multiple threads to speed up computation.</p>

<p>For example, for the input intervals:</p>
<pre>
from  to  offered payment
 0 -  6    8
 7 -  9    2
10 - 13    2
 0 -  1    4
 2 - 11    4
12 - 13    4
 0 -  3    2
 4 -  5    2
 8 - 13    8
</pre>

<p>Rental plan, if renting 1 tool:</p>
<pre>
1:  0-6 8-13    
profit 16
</pre>

<p>Rental plan, if renting 2 tools:</p>
<pre>
1:  0-6 7-9 12-13
2:  0-1 4-5 8-13
profit 28
</pre>

<p>Rental plan, if renting 3 tools:</p>
<pre>
1:  0-6 7-9 10-13
2:  0-1 2-11 12-13
3:  0-3 4-5 8-13
profit 36
</pre>

<p>The expected solution must be properly integrated into the infrastructure described below and must properly create, plan, synchronize, and terminate threads. The actual algorithmic solution is not absolutely necessary; the testing environment provides an interface capable of sequentially solving the given problem.</p>

<hr />

<p>The problem to be solved is represented by an instance <tt>CProblem</tt>. The class contains member variables with customer requirements and information based on the number of tool units.</p>

<p>Problems are wrapped in groups (packs); a group is represented by the <tt>CProblemPack</tt> class. For example, a rental company rents multiple types of tools, and for each type of tool, there will be one problem instance in <tt>CProblemPack</tt> to solve.</p>

<p>Companies provide groups of problems continuously; communication between the solver and the rental company is handled by the <tt>CCompany</tt> class. This class contains an interface that allows loading additional problems to solve (method <tt>waitForPack</tt>) and an interface to return solved problems (method <tt>solvedPack</tt>). Your implementation will create 2 helper threads for <b>each</b> instance of <tt>CCompany</tt>. One thread will be in a loop to load new problem packs to solve, and the other thread will return solved problems (it will be in a loop calling <tt>solvedPack</tt>). These helper threads ensure correct submission order of solved problem packs, which must be returned in the same order as the problems were loaded. Multiple instances of problem packs can be loaded and processed concurrently (in fact, it is desirable and necessary). However, it is important to maintain the order when submitting them back.</p>

<p>The entire calculation is encapsulated by the <tt>COptimizer</tt> instance. This class contains references to individual rental companies, manages starting and pausing computations, and controls the operation of computing threads. Computing threads are used to solve problems for all serviced rental companies. Computing threads take over the problem from the communication thread, perform their calculations, and pass the solved problem back to the corresponding communication thread of the rental company (it is necessary to maintain order). There will be exactly the specified number of computing threads, allowing efficient utilization of the computer hardware (number of CPUs).</p>

<p>The <tt>COptimizer</tt> class will be used according to the following scenario:</p>

<ul>
 <li>An instance of <tt>COptimizer</tt> is created,</li>
 <li>Rental companies are registered (by calling the <tt>addCompany</tt> method),</li>
 <li>The main computation is started (by calling the <tt>start</tt> method). The <tt>start</tt> method takes the number of computing threads (<tt>workThreads</tt>) as a parameter. These threads are created and wait for incoming requests. Communication threads are also created for each rental company, one for receiving requests and the other for returning results. After starting the threads, the <tt>start</tt> method returns to the caller,</li>
 <li>Communication threads continuously receive requests (calling the <tt>waitForPack</tt> method in a loop). The thread receiving requests terminates when it retrieves an empty request (smart pointer containing <tt>nullptr</tt>),</li>
 <li>Computing threads take problems from communication threads and solve them. After solving a problem, they pass it to the corresponding return thread of the rental company,</li>
 <li>Return threads wait for solved problems and, once received, return them in the correct order (using the <tt>solvedPack</tt> method). Solved problems must be returned immediately as soon as it is possible given the order (solved problems cannot be stored and returned only at the end of the computation). The return thread terminates if no further problems from the rental company are received (<tt>waitForPack</tt> returns <tt>nullptr</tt>), and all problems of this rental company have been solved and returned,</li>
 <li>The testing environment calls the <tt>stop</tt> method at some point. The call waits for all rental companies to finish servicing, terminates working threads, and returns to the caller,</li>
 <li>The <tt>COptimizer</tt> instance is released.</li>
</ul>

Used classes and their interfaces:
<ul>
  <li><tt>CInterval</tt> is a class representing a customer's rental request. It is a very simple class that encapsulates the rental interval and the offered price. The class is implemented in the testing environment, and its interface should not be modified. The interface includes:
    <ul>
      <li><tt>m_From</tt> indicates the start of the interval,</li>
      <li><tt>m_To</tt> indicates the end of the interval,</li>
      <li><tt>m_Payment</tt> indicates the offered price.</li>
    </ul>
    It can be relied upon that <tt>m_From</tt> < <tt>m_To</tt>.
  </li>

  <li><tt>CProblem</tt> is a class representing a single problem to solve. It is an abstract class, and its implementation (more precisely, the implementation of its subclass) is completed in the testing environment. Its interface should not be modified. The interface includes:
    <ul>
      <li><tt>m_Count</tt> indicates the number of units of rented equipment (1, 2, or 3),</li>
      <li><tt>m_Intervals</tt> is a list of rental requests from customers,</li>
      <li><tt>m_MaxProfit</tt> is the result of the calculation - the maximum achievable profit from rentals. This value needs to be computed and set,</li>
      <li>The class also includes a constructor and an <tt>add</tt> method for simplifying work (see the attached implementation).</li>
    </ul>
  </li>

  <li><tt>CProblemPack</tt> is a class representing a pack of problems to solve. It is an abstract class, and its implementation (more precisely, the implementation of its subclass) is completed in the testing environment. Its interface should not be modified. The interface includes:
    <ul>
      <li><tt>m_Problems</tt> is an array of instances of problems to solve,</li>
      <li>The class also includes an <tt>add</tt> method for simplifying work (see the attached implementation).</li>
    </ul>
  </li>

  <li><tt>CCompany</tt> is a class representing a rental company. The class only defines the interface, and the actual implementation in the testing environment is a descendant of <tt>CCompany</tt>. Therefore, you cannot change the class's interface. The following methods are available:
    <ul>
      <li><tt>waitForPack</tt> to fetch the next problem pack from the rental company. The method returns an instance for processing or an invalid pointer (smart pointer containing <tt>nullptr</tt>) if there are no more problem instances to process for this rental company. Calling this method may take a long time, so you must allocate a separate thread to handle it, which will call the method in a loop. The thread must not perform any computationally intensive tasks but must pass the acquired <tt>CProblemPack</tt> instance to the processing worker threads. It is checked that only one (same) thread calls this method in one rental company instance,</li>

<li><tt>solvedPack</tt> for submitting a solved instance of <tt>CProblemPack</tt>. The parameter is a solved instance of the problem pack previously obtained from <tt>waitForPack</tt> call. Since submission may take a long time, you must create a dedicated thread for submission. The thread will receive solved problem instances from worker threads and call the <tt>solvedPack</tt> method on them. Solved problem instances must be returned in the same order as they were received from <tt>waitForPack</tt>. The submission thread must not perform any computationally intensive activity. It is checked that only one (same) thread calls this method in one rental company instance.</li>
    </ul>
  </li>

  <li><tt>COptimizer</tt> is a class encapsulating the entire computation. You will create this class, but you must adhere to the following public interface:
    <ul>
     <li>A parameterless constructor initializes a new instance of the class. Threads are not created yet,</li>

<li>A method <tt>addCompany(x)</tt> registers a rental company <tt>x</tt>,</li>
     
<li>A method <tt>start(workThr)</tt> creates communication threads for all registered rental companies and starts <tt>workThr</tt> worker threads. After starting the threads, the <tt>start</tt> method returns to the caller,</li>
     
<li>A method <tt>stop</tt> that waits for the completion of rental company handling and terminates the created threads. After this, the <tt>stop</tt> call returns to the caller,</li>
     
<li>A method <tt>usingProgtestSolver()</tt> returns <tt>true</tt> if you are using the provided problem solver <tt>CProgtestSolver</tt> or <tt>false</tt> if you are implementing the entire computation using your own code. If this method returns <tt>true</tt>, the testing environment does not use the method <tt>COptimizer::checkAlgorithm(problem)</tt> below (you can leave it empty). If the method returns <tt>false</tt>, the testing environment adjusts the behavior of the provided solver <tt>CProgtestSolver</tt> to deliberately fill incorrect results.</li>

<li>A class method <tt>checkAlgorithm(problem)</tt>. The method is used to test the correctness of your own computation algorithm. The parameter for the call is one instance of <tt>CProblem</tt>. The code of the method ensures the necessary calculations and fills the <tt>m_MaxProfit</tt> field in the <tt>problem</tt> instance. In addition to checking the correctness of implemented algorithms, the method is used to calibrate the speed of your solution. The speeds are adjusted according to the size of the problems provided so that the testing lasts for a reasonable period of time. Implement the method only if you do not use the provided problem solver <tt>CProgtestSolver</tt> (thus if your method <tt>COptimizer::usingProgtestSolver()</tt> returns <tt>false</tt>).</li>
    </ul>
  </li>

  <li><tt>CProgtestSolver</tt> is a class providing an interface for sequential solving of assigned problems. Its author decided to slightly spice up its usage, so the behavior of this class is somewhat playful. The <tt>CProgtestSolver</tt> class is abstract, and the actual implementation is provided by a subclass. Instances of <tt>CProgtestSolver</tt> are created using the factory function <tt>createProgtestSolver()</tt>. Additionally, <tt>CProgtestSolver</tt> instances solve problems in batches. Each <tt>CProgtestSolver</tt> instance has a designated capacity for how many problem instances can be placed into it at most. The <tt>CProgtestSolver</tt> class has the following interface:
    <ul>
     <li><tt>hasFreeCapacity()</tt> method returns <tt>true</tt> if another problem instance can be placed into the instance for solving, <tt>false</tt> if the instance is completely filled,</li>
     <li><tt>addProblem(x)</tt> method adds a problem instance <tt>x</tt> to be solved. The return value is <tt>true</tt> if the problem was added, <tt>false</tt> if not (because the solver's capacity was reached). After inserting the problem, it is reasonable to test if the solver's capacity is filled (<tt>hasFreeCapacity</tt>). If the capacity is used, start computation (<tt>solve</tt>).</li>
     <li><tt>solve()</tt> method starts the actual computation. Results are determined for inserted instances and placed into the appropriate <tt>m_MaxProfit</tt> folders. The method does nothing else, especially it does not attempt to inform companies about the resolution of assigned problems (does not call <tt>CCompany::solvedPack</tt>). Further processing of resolved problems is solely your responsibility. The <tt>solve</tt> method can be called only once for a given <tt>CProgtestSolver</tt> instance; further attempts end with an error. The method returns the number of solved problem instances, the return value 0 typically means an error (repeated attempt to call the method).</li>
    </ul>
<br>
    <p>Instances of <tt>CProgtestSolver</tt> do not allow inserting more problems than their capacity. On the other hand, the <tt>solve</tt> method can be called at any time (but only once for a given instance). However, do not attempt to misuse the solver and solve problems one by one:</p>
    <ul>
     <li>The testing environment creates instances of <tt>CProgtestSolver</tt> so that the sum of their capacities <tt>M</tt> covers the total number of assigned problems <tt>N</tt> in the test (typically <tt>M</tt> is slightly larger than <tt>N</tt>),</li>
     <li>If you use each instance of <tt>CProgtestSolver</tt> only to resolve one instance of a problem, you will quickly deplete the capacity <tt>M</tt> and will not have how to resolve further assigned problems,</li>
     <li>If you exceed the capacity <tt>M</tt>, calls to <tt>createProgtestSolver()</tt> will return unused solver instances (depending on the mood, an empty smart pointer will be returned, the solver will have a capacity of 0, or will deliberately fill incorrect results),</li>
     <li>Therefore, it is important to fully utilize the capacities of the solvers,</li>
     <li>The capacities of individual solver instances are randomly chosen. As already mentioned, this class tries to make the programmers' boring work more interesting.</li>
    </ul>
    <p>Furthermore, the solver provided by the testing environment is available only in mandatory and optional tests (not available in bonus tests). If you attempt to use it in a bonus test, the factory function <tt>createProgtestSolver()</tt> will return empty instances, or instances with zero capacity, or instances deliberately filling incorrect results.</p>
  </li>   
</ul>

<hr />

<p>Submit the source code with the implementation of the required class <tt>COptimizer</tt> with the required methods. You can, of course, add additional supporting classes and functions. Do not include a <tt>main</tt> function or directives for including header files in your implementation. You can keep a <tt>main</tt> function and header files only if they are wrapped in conditional compilation blocks.</p>

<p>Use the attached sample file. The entire implementation belongs to the <tt>solution.cpp</tt> file. If you keep conditional compilation blocks, you can submit the <tt>solution.cpp</tt> file as the task solution.</p>

<p>When solving the problem, you can utilize either pthread or C++11 API for thread handling (see included header files). The available compiler is g++ version 10.2, which supports most of C++11, C++14, and C++17 features. C++20 is not fully supported; it is recommended to avoid it.</p>

<hr />

<b>Recommendations:</b><br />

<ul>
 <li>Start directly with threads and synchronization. You don't need to implement your own algorithms for solving the given problems. Use the provided solution - the <tt>CProgtestSolver</tt> class. Once you have synchronization in place, you can add your own algorithmic solution.</li>

 <li>To utilize as many cores as possible, handle as many instances of <tt>CProblem</tt> simultaneously as you can. It's necessary to simultaneously accept problems, solve them, and submit them. Do not attempt to phase these activities (e.g., waiting first for all <tt>CProblemPack</tt> instances, then starting to solve accumulated problems...), as such an approach will lead to deadlock in the testing environment.</li>

 <li>Instances of <tt>COptimizer</tt> are created repeatedly for different inputs. Do not rely on initialization of global variables - upon subsequent calls, global variables will have different values. It's advisable to initialize any potential global variables in the constructor or at the beginning of the <tt>start</tt> method. Even better, avoid using global variables altogether.</li>

 <li>Do not use mutexes and conditional variables initialized using <tt>PTHREAD_MUTEX_INITIALIZER</tt>. The reason is the same as in the previous paragraph. Instead, use <tt>pthread_mutex_init()</tt> or C++11 API.</li>

 <li>Instances of problems (<tt>CProblem</tt>), problem packs (<tt>CProblemPack</tt>), companies (<tt>CCompany</tt>), and solvers (<tt>CProgtestSolver</tt>) are allocated by the testing environment when creating the respective smart pointers. Automatic deallocation will occur once all references are released. Thus, releasing these instances is not your concern; just forget all smart pointers passed in this way. However, your program is responsible for releasing all other resources it allocates.</li>

 <li>Do not terminate the <tt>stop</tt> method using <tt>exit</tt>, <tt>pthread_exit</tt>, or similar functions. If the <tt>stop</tt> function does not return to the caller, your implementation will be evaluated as incorrect.</li>

 <li>Make use of the provided sample data. In the archive, you will find an example of interface calls, as well as several test inputs and their corresponding results.</li>

 <li>The testing environment has access to the STL. However, be aware that the same STL container cannot be concurrently accessed from multiple threads. For more information, refer to <a href="http://en.cppreference.com/w/cpp/container">C++ reference - thread safety.</a></li>

 <li>The testing environment is limited in memory size. There is no explicit limit enforced, but the VM running the tests has a total available RAM of 4 GiB. The task can be memory-intensive, especially if you decide to finely divide the task into individual threads. If you choose such fine-grained subdivision, you may need to add thread execution synchronization so that the overall memory requirement never exceeds a reasonable limit. During execution, your program is guaranteed to have at least 1 GiB available for your data (data segment + stack + heap). For the curious, the rest up to 4 GiB is occupied by the running OS, other processes, stacks of your threads, and some reserve.</li>

 <li>If you decide to tackle all bonuses, it's crucial to carefully adjust the granularity of the problem being solved. If you divide the problem into too many small subproblems, overhead will dominate. Furthermore, if you concurrently work on too many problems (each divided into a large number of subproblems), computation will slow down (e.g., due to worse CPU cache utilization). To avoid this, the reference solution limits the number of concurrently processed tasks dynamically based on the size of the workload.</li>

 <li>Compute-intensive operations must be performed by worker threads. The number of worker threads is determined by the parameter of the <tt>start</tt> method. The testing environment verifies that your implementation does not perform compute-intensive operations in other threads. If detected, your solution will be rejected.</li>

 <li>Explicitly setting the number of worker threads has practical reasons. By choosing a reasonable number of worker threads, we can load the system according to our choice (e.g., based on the number of cores we can allocate to the task). If time-consuming computations were also performed in other threads (communication threads), the system could be easily overwhelmed.</li>
</ul>

<b>Recommendations for implementing your own algorithmic solution:</b><br />

<ul>
 <li>Implementing your own algorithmic solution is not entirely trivial. Besides solving the algorithmic problem itself, you need to address certain technical details, especially regarding memory requirements.</li>

 <li>Your implementation must have reasonable complexity. Both time and memory complexity strongly depend on the number of tools pieces available for borrowing. The solution implemented in the <tt>CProgtestSolver</tt> class has the following characteristics (<tt>n</tt> being the number of processed intervals):
   <table border="0">
    <tr>
      <td><tt>m_Count</tt></td><td><tt>T(n)</tt></td><td><tt>M(n)</tt></td>
    </tr>
    <tr>
      <td><tt>1</tt></td><td><tt>O(n<sup>2</sup>)</tt></td><td><tt>O(n)</tt></td>
    </tr>
    <tr>
      <td><tt>2</tt></td><td><tt>O(n<sup>3</sup>)</tt></td><td><tt>O(n<sup>2</sup>)</tt></td>
    </tr>
    <tr>
      <td><tt>3</tt></td><td><tt>O(n<sup>4</sup>)</tt></td><td><tt>O(n<sup>3</sup>)</tt></td>
    </tr>
   </table>
 </li>

 <li>The solution implemented in the <tt>CProgtestSolver</tt> class is not time-optimal. If you correctly implement your own solution with the same complexities, it will suffice for complete solution of this task. An optimal solution with lower time complexity will also pass, but such a solution requires using more tricks in the algorithmic part. As mentioned earlier, the testing environment calibrates the speed of the used algorithm and uses the measured speed to adjust the size of the problems being solved within certain limits.</li>

 <li>To successfully complete bonus #2, you need to use multiple threads to solve problems with <tt>m_Count=2</tt>, and for bonus #3, problems with <tt>m_Count=3</tt>. It doesn't make much sense to split problems with <tt>m_Count=1</tt> into multiple threads (it would be beneficial only for very large <tt>n</tt>).</li>

 <li>The testing environment provides sizes of <tt>n</tt> with consideration of expected memory requirements. In bonus tests, <tt>n</tt> is set to around 1000 for <tt>m_Count=2</tt> and around 200 for <tt>m_Count=3</tt>.</li>

 <li>It's relatively easy to devise an algorithm that sequentially solves one instance of the problem with complexities listed in the table above. Such an algorithm is sufficient to pass bonus #1.</li>

 <li>Subsequently, you can refactor this algorithm into a parallel version, which will have higher memory complexity (<tt>O(n<sup>3</sup>)</tt> for <tt>m_Count=2</tt> and <tt>O(n<sup>4</sup>)</tt> for <tt>m_Count=3</tt>). However, such a solution will not be satisfactory as the testing environment does not provide sufficient memory. Additionally, high memory requirements will slow down computation (overhead for allocations, lower CPU cache efficiency, etc.).</li>

 <li>A functional solution from the previous point can be refactored into a form with lower memory usage. It's essential to observe dependencies between computed data and realize that a significant portion of data doesn't need to be maintained throughout the computation.</li>
</ul>

<hr />

<b>Meanings of individual tests:</b><br />
<dl>
 <dt><b>Algorithm test (sequential)</b></dt><dd>The testing environment repeatedly calls the <tt>checkAlgorithm()</tt> method for various inputs and checks the computed results. This test is used to verify the implementation of your algorithm. No instance of <tt>COptimizer</tt> is created, and the <tt>start</tt> method is not called. If <tt>COptimizer::usingProgtestSolver</tt> returns <tt>true</tt>, this test will effectively be skipped.</dd>

 <dt><b>Basic test</b></dt><dd>The testing environment creates an instance of <tt>COptimizer</tt> for different numbers of companies and worker threads. The test name indicates the number of companies (C=xxx) and worker threads (W=xxx).</dd>

<dt><b>Basic Test (W=n, L=m)</b></dt><dd>This test additionally checks
   whether you are continuously submitting already solved problem instances. 
   The testing environment stops delivering new problems at one point until 
   all currently assigned problems are solved and returned. If you do not 
   pick up/solve/submit problems continuously, you will deadlock in this test.</dd>

<dt><b>Calculation Speed Test</b></dt><dd>The testing environment runs your
   implementation with the same input data using different numbers of working 
   threads. It measures the execution time (wall and CPU). With increasing 
   number of threads, the wall time should decrease, while the CPU time should 
   slightly increase (threads can run on additional CPUs). If the wall time does 
   not decrease or decreases minimally (for example, it should ideally decrease 
   to 0.5 for 2 threads, a certain reserve is maintained), the test fails.</dd>

<dt><b>Busy Waiting (slow waitForPack)</b></dt><dd>New problems are delivered slowly. 
   Computational threads have nothing to do. If these threads are not synchronized 
   in a blocking manner, CPU time will significantly increase, and the test will fail.</dd>

<dt><b>Busy Waiting (slow solvedPack)</b></dt><dd>Submitting solved problems is slow. 
   There is no one to pick up solved problems from computational threads. If these 
   threads are not synchronized in a blocking manner, CPU time will significantly 
   increase, and the test will fail.</dd>

<dt><b>Load Balancing #1</b></dt><dd>The testing environment tries to involve 
   multiple working threads in solving one instance of <tt>CProblemPack</tt>. 
   The instance contains multiple problem assignments that can be independently 
   solved by multiple working threads. <tt>CProgtestSolver</tt> is not available 
   in this test.</dd>

<dt><b>Load Balancing #2</b></dt><dd>The testing environment tries to involve 
   multiple working threads in solving one instance of <tt>CProblem</tt>. 
   Only one problem with <tt>m_Count</tt> = 2 is assigned, requiring all 
   working threads to participate in its solution. <tt>CProgtestSolver</tt> 
   is not available in this test.</dd>

<dt><b>Load Balancing #3</b></dt><dd>The testing environment tries to involve 
   multiple working threads in solving one instance of <tt>CProblem</tt>. 
   Only one problem with <tt>m_Count</tt> = 3 is assigned, requiring all 
   working threads to participate in its solution. <tt>CProgtestSolver</tt> 
   is not available in this test.</dd>
</dl>
<hr />
