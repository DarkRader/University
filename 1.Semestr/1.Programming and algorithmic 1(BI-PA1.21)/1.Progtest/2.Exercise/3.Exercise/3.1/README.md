<h1>RGB Converter</h1>

<td class="lrtbCell" colspan="3" align="left"><p>The task is to create a program that converts a color from RGB format to hexadecimal format.</p>
<p>You will receive the color definition in the form <code>rgb ( x, y, z )</code> as input. <code>x</code>, <code>y</code>, and <code>z</code> are integers ranging from 0 to 255 inclusive, representing the color components. The goal is to convert this format to a format starting with <code>#</code> and followed by the hexadecimal representation of each color component in two digits (e.g., for the value <code>12</code>, output <code>0C</code>). The input and output format are shown below in the program's operation example.</p>
<p>If the input is invalid, the program must detect it and display an error message. Display error messages on the standard output (not the error output). Consider the following as errors:</p>
<ul>
<li>the input does not contain the string <code>rgb</code>,</li>
<li>missing comma or parenthesis,</li>
<li>missing color component,</li>
<li>color component is not a valid number,</li>
<li>color component is not within the range of 0 to 255.</li>
</ul>
<p><strong>Sample runs:</strong></p>
<hr />
<pre>
<b>Enter the color in RGB format:</b>
rgb ( 255, 0, 0 )
<b>#FF0000</b>
</pre>
<hr />
<pre>
<b>Enter the color in RGB format:</b>
    rgb			(  0  ,   255  ,   0   )
<b>#00FF00</b>
</pre>
<hr />
<pre>
<b>Enter the color in RGB format:</b>
rgb(0,0,255)
<b>#0000FF</b>
</pre>
<hr />
<pre>
<b>Enter the color in RGB format:</b>
rgb ( 127, 127, 0 )
<b>#7F7F00</b>
</pre>
<hr />
<pre>
<b>Enter the color in RGB format:</b>
hsl ( 0, 127, 0 )
<b>Invalid input.</b>
</pre>
<hr />
<pre>
<b>Enter the color in RGB format:</b>
rgb ( 255, 0 )
<b>Invalid input.</b>
</pre>
<hr />
<pre>
<b>Enter the color in RGB format:</b>
rgb ( 1000, 127, 0 )
<b>Invalid input.</b>
</pre>
<hr />
<pre>
<b>Enter the color in RGB format:</b>
RGB ( 100, 200, 0 )
<b>Invalid input.</b>
</pre>
<hr />
<p><strong>Notes:</strong></p>
<ul>
<li>The sample runs capture the expected outputs of your program (bold text) and the inputs provided by the user (regular text). Bold formatting is used here on the assignment page to enhance readability. Your program's task is to display text without any formatting (without HTML markup).</li>
<li>A newline character follows even after the last line of output (including any error messages).</li>
<li>For reading input, you can use the <code>scanf</code> function. It allows for easy checking of commas, parentheses, and the presence of the <code>rgb</code> string.</li>
<li>Do not attempt to read the <code>rgb</code> string into memory and then check it. Handling strings in C is complex and error-prone. In this task, <code>scanf</code> is sufficient for checking.</li>
<li>Display hexadecimal numbers in uppercase format using the appropriate format specifier for the <code>printf</code> function.</li>
<li>When programming, pay attention to the exact format of the outputs. Your program's output will be checked against reference outputs for exact matches. Differences in output are considered errors. Missing or extra spaces/newlines are also considered errors. To quickly eliminate these issues, use the provided archive with input and expected output data. Watch the video tutorial on how to use the test data and automate testing (<a href="https://courses.fit.cvut.cz/BI-PA1/video.html">Courses -&gt; Video tutorials</a>).</li>
<li>This program will run in a restricted testing environment with limits on runtime and available memory. The runtime limit is visible in the reference solution's log. Additionally, certain "dangerous functions" are prohibited in the testing environment — functions for running other programs, working with networks, etc. If these functions are used, the program will not start. (Even if the program starts, it will be rejected. There would be no one to "press" pause, and the program would wait indefinitely, exceeding the maximum runtime.) If you want to keep the pause for testing on your computer and ensure that the program runs correctly, use the following trick:</li>
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