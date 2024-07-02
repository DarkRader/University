<h1>Word Comparison</h1>
<td class="lrtbCell" colspan="3" align="left"><p>The task is to implement a function (not a program, just a function) that will compare two strings to determine if they are made up of the same words.</p>
<p>The required function <tt>sameWords</tt> has the following interface:</p>
<pre>
int sameWords ( const char * a, const char * b );
</pre>
<p>The parameters are two strings that the function will compare. The parameters are read-only (<tt>const</tt>), and the function must not modify them.</p>
<p>The return value of the function is 1 (match) or 0 (no match).
A match is defined as both strings being made up of the same words.
Thus, each word in the first string must appear at least once in the second string, and vice versa. Case differences are ignored when comparing words.</p>
<p>Words are made up of characters for which the <tt>isalpha</tt> function returns a non-zero value. Other characters are considered word separators.</p> 
<p>Submit a source file that contains the implementation of the required <tt>sameWords</tt> function. Also include any additional support functions called from <tt>sameWords</tt>. The function will be called from a testing environment, so it is important to strictly adhere to the specified function interface. Use the code from the sample below as the basis for your implementation. The code is missing the implementation of the <tt>sameWords</tt> function (and possibly other support functions). The sample contains a test <tt>main</tt> function, and the provided values are used in the basic test. Note that the inclusion of header files and the <tt>main</tt> function are enclosed in conditional compilation blocks (<tt>#ifdef/#endif</tt>). Please keep the conditional compilation blocks in the submitted source file. Conditional compilation will simplify your work. When compiling on your computer, you can normally run and test the program. When compiling on Progtest, the <tt>main</tt> function and the inclusion of header files will "disappear," thus avoiding conflicts with the header files and the <tt>main</tt> function of the testing environment.</p>
<p>Your program will be run in a restricted testing environment. It is limited by runtime (the limit is visible in the log of the reference solution) and also by the amount of available memory. The time limits are set so that a reasonable implementation of a naive algorithm will pass all mandatory tests. A solution working in mandatory tests can receive a nominal 100% score. The bonus test requires a time-efficient computation for long strings containing many words.</p>
<p>You must use C strings for the implementation. C++ strings (<tt>std::string</tt>) and STL are prohibited, and their use will result in a compilation error.</p>
<p>In the attached archive, you will find the implementation basis and several sample tests.</p>
<p>A program that passes all mandatory and optional tests with 100% can be used for code review. (Passing the bonus tests is not required for code review).</p>
</td>