<h1>Interval Length</h1>

<td class="lrtbCell" colspan="3" align="left"><p>The task is to create a program that calculates the length of a time interval.</p>
<p>The program will receive the start time <code>t1</code> and end time <code>t2</code> of the interval. The time is always provided in the format <code>h:m:s,ms</code> (hour, minute, second, millisecond). The program calculates the duration of this time interval and displays it in the format <code>h:m:s,ms</code>. The expected behavior is illustrated in the examples below.</p>
<p>If the input is invalid, the program must detect it and display an error message. Display error messages on the standard output (not the error output). Consider the following as errors:</p>
<ul>
<li>non-numeric values,</li>
<li>values out of range (max. 23 hours, max. 59 minutes, max. 59 seconds, max. 999 milliseconds),</li>
<li>missing comma or colon,</li>
<li>the start time is greater than the end time.</li>
</ul>
<p><strong>Sample runs:</strong></p>
<hr />
<pre>
<b>Enter time t1:</b>
11:45:20,456
<b>Enter time t2:</b>
12:07:54,349
<b>Duration:  0:22:33,893</b>
</pre>
<hr />
<pre>
<b>Enter time t1:</b>
15:18:34,232
<b>Enter time t2:</b>
15:18:34,293
<b>Duration:  0:00:00,061</b>
</pre>
<hr />
<pre>
<b>Enter time t1:</b>
12:00:00,000
<b>Enter time t2:</b>
12:00:00,000
<b>Duration:  0:00:00,000</b>
</pre>
<hr />
<pre>
<b>Enter time t1:</b>
01:01:01,001
<b>Enter time t2:</b>
07:07:07,007
<b>Duration:  6:06:06,006</b>
</pre>
<hr />
<pre>
<b>Enter time t1:</b>
 1 : 1 : 1 , 001
<b>Enter time t2:</b>
 7 : 7 : 7 , 007
<b>Duration:  6:06:06,006</b>
</pre>
<hr />
<pre>
<b>Enter time t1:</b>
1:1:1,001
<b>Enter time t2:</b>
17:7:7,007
<b>Duration: 16:06:06,006</b>
</pre>
<hr />
<pre>
<b>Enter time t1:</b>
12:30:00,000
<b>Enter time t2:</b>
12:00:00,000
<b>Invalid input.</b>
</pre>
<hr />
<pre>
<b>Enter time t1:</b>
15:30:34,123
<b>Enter time t2:</b>
15:60:34,123
<b>Invalid input.</b>
</pre>
<hr />
<pre>
<b>Enter time t1:</b>
15:40:21.745
<b>Invalid input.</b>
</pre>
<hr />
<p><strong>Notes:</strong></p>
<ul>
<li>The sample runs capture the expected outputs of your program (bold text) and the inputs provided by the user (regular text). Bold formatting is used here on the assignment page to enhance readability. Your program's task is to display text without any formatting (without HTML markup).</li>
<li>A newline character follows even after the last line of output (including any error messages).</li>
<li>For reading input, you can use the <code>scanf</code> function. It allows for easy checking of commas, colons, and the presence of the time format.</li>
<li>Using floating-point numbers (decimal points) for input is not suitable (the input intentionally uses commas, not periods). Furthermore, processing input as a string is unnecessarily cumbersome.</li>
<li>Pay attention to the exact format of the outputs when programming. Your program's output will be checked against reference outputs for exact matches. Differences in output are considered errors. Missing or extra spaces/newlines are also considered errors. To quickly eliminate these issues, use the provided archive with input and expected output data. Watch the video tutorial on how to use the test data and automate testing (<a href="https://courses.fit.cvut.cz/BI-PA1/video.html">Courses -&gt; Video tutorials</a>).</li>
<li>Display hours with 2 digits without leading zeros, minutes and seconds with 2 digits with leading zeros, and milliseconds with 3 digits with leading zeros.</li>
<li>You can assume that milliseconds are always provided as 3 digits. The exception is the last (bonus) test, where the number of milliseconds can be specified with 1, 2, or 3 digits (e.g., 1:2:3,4 represents 400 ms). Such input is harder to process, but <code>scanf</code> should suffice.</li>
<li><p>Your program will run in a restricted testing environment. It has a runtime limit (visible in the reference solution's log) and a limited amount of available memory (though this task should not have any issues with either limit). The testing environment also prohibits the use of certain "dangerous functions" — functions for running other programs, working with networks, etc. If these functions are used, the program will not start. You might be using the following call in your program:</p>
<div class="sourceCode"><pre class="sourceCode c"><code class="sourceCode c"><span class="dt">int</span> main ( <span class="dt">void</span> )
{
    ...
    system ( <span class="st">&quot;pause&quot;</span> ); <span class="co">/* so the program window does not close */</span>
    <span class="cf">return</span> <span class="dv">0</span>;
}</code></pre></div>
<p>This will not work in the testing environment — launching another program is prohibited. (Even if the program starts, it would be rejected. There would be no one to "press" pause, and the program would wait indefinitely, exceeding the maximum runtime.) If you want to keep the pause for testing on your computer and ensure that the program runs correctly, use the following trick:</p>
<div class="sourceCode"><pre class="sourceCode c"><code class="sourceCode c"><span class="dt">int</span> main ( <span class="dt">void</span> )
{
    ...
    <span class="pp">#ifndef __PROGTEST__</span>
    system ( <span class="st">&quot;pause&quot;</span> ); <span class="co">/* Progtest does not see this */</span>
    <span class="pp">#endif </span><span class="co">/* __PROGTEST__ */</span>
    <span class="cf">return</span> <span class="dv">0</span>;
}</code></pre></div></li>
</ul>


</td>