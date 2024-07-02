<h1>Mean of Three</h1>

<td class="lrtbCell" colspan="3" align="left"><p>The task is to implement a function (not the whole program, just the function) that computes the mean of three integers.</p>
<p>The function has the following interface:</p>
<pre>
long long avg3(long long a, long long b, long long c);
</pre>
<ul>
<li>The function takes three integers as input parameters, computes their mean,</li>
<li>returns the computed mean value,</li>
<li>if the mean is not an integer, the function truncates the decimal part (rounds towards zero),</li>
<li>the function cannot fail; the mean is defined for every triplet of input numbers.</li>
</ul>
<p><strong>Sample usage of the function:</strong></p>
<hr/>
<pre>
assert(avg3(1, 2, 3) == 2);
assert(avg3(-100, 100, 30) == 10);
assert(avg3(1, 2, 2) == 1);
assert(avg3(-1, -2, -2) == -1);
assert(avg3(LLONG_MAX, LLONG_MAX, LLONG_MAX) == LLONG_MAX);
</pre>
<hr/>
<p><strong>Notes:</strong></p>
<ul>
<li>Use the provided source code file as a basis for your solution.</li>
<li>You can add additional tests to the <code>main</code> function or modify it as needed. It's important to maintain conditional compilation.</li>
<li>The sample uses the <code>assert</code> macro. If the argument is non-zero, the macro does nothing. If the argument is false (zero), the macro terminates the program and prints the line where the failure occurred. Thus, if your implementation passes the sample tests, the program will finish without displaying anything.</li>
<li>At first glance, the problem seems trivial. However, the function must correctly handle all input values, including the highest value <code>LLONG_MAX</code> as shown in the sample.</li>
<li>The data type <code>long long</code> is 64 bits on the target platform. There is no larger data type available. Non-standard types like <code>__int128</code> and <code>__float128</code> cannot be used (they are disabled).</li>
<li>Edge case testing is evaluated at either 0% (function returns incorrect results for some values) or 100% (everything works correctly).</li>
<li><strong>Update:</strong> Only the header files visible in the provided example are available. No other header files are needed or allowed. Do not include additional header files using <code>#include</code>; the program will fail to compile.</li>
</ul>
</td>