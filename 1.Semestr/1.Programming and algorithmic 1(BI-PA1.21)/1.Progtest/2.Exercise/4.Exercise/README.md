<h1>Calculator</h1>

<td class="lrtbCell" colspan="3" align="left"><p>The task is to create a program that processes simple mathematical formulas.</p>
<p>You will receive two decimal numbers separated by an arithmetic operator and terminated by an equals sign. Your task is to calculate the result based on the specified operator:</p>
<ul>
<li>for <code>+</code>, calculate the sum,</li>
<li>for <code>-</code>, calculate the difference,</li>
<li>for <code>*</code>, calculate the product,</li>
<li>for <code>/</code>, calculate the integer quotient (e.g., <code>3.5 / 1.5 = 2</code>, how many times the divisor fits into the dividend <em>completely</em>).</li>
</ul>
<p>The program will not handle any other operations and will display an error message for them. The input and output format is shown below in the example of program operation.</p>
<p>If the input is invalid, the program must detect it and display an error message. Display error messages on the standard output (not the error output). Consider the following as errors:</p>
<ul>
<li>the entered number is not a valid decimal number,</li>
<li>the divisor is 0 for the operation <code>/</code>,</li>
<li>numbers are not separated by a valid operator (<code>+</code>, <code>-</code>, <code>*</code>, or <code>/</code>),</li>
<li>the input does not end with an equals sign <code>=</code> after the last number.</li>
</ul>
<p><strong>Sample program operation:</strong></p>
<hr />
<pre>
<b>Enter formula:</b>
3.5 + 1.5 =
<b>5</b>
</pre>
<hr />
<pre>
<b>Enter formula:</b>
3.5 / 1.5 =
<b>2</b>
</pre>
<hr />
<pre>
<b>Enter formula:</b>
1000000 * 1.5e+8 =
<b>1.5e+14</b>
</pre>
<hr />
<pre>
<b>Enter formula:</b>
7 / -1 =
<b>-7</b>
</pre>
<hr />
<pre>
<b>Enter formula:</b>
abc / 1 =
<b>Invalid input.</b>
</pre>
<hr />
<pre>
<b>Enter formula:</b>
4 &amp; 10 =
<b>Invalid input.</b>
</pre>
<hr />
<p><strong>Notes:</strong></p>
<ul>
<li>The sample runs capture the expected outputs of your program (bold text) and the inputs provided by the user (regular text). Bold formatting is used here on the assignment page to enhance readability. Your program's task is to display text without any formatting (without HTML markup).</li>
<li>A newline character (\n) follows even after the last line of output (including any error messages).</li>
<li>Use double-precision decimal numbers (<code>double</code>) to represent values. Do not use <code>float</code> as its precision may not be sufficient.</li>
<li>Pay attention to the exact format of the outputs when programming. Your program's output will be checked against reference outputs for exact matches. Differences in output are considered errors. Missing or extra spaces/newlines are also considered errors. To quickly eliminate these issues, use the provided archive with input and expected output data. Watch the video tutorial on how to use the test data and automate testing (<a href="https://courses.fit.cvut.cz/BI-PA1/video.html">Courses -&gt; Video tutorials</a>).</li>
<li>The resulting value is compared as a decimal number with a tolerance of 1 per mil (0.1%).</li>
<li>Your program will run in a restricted testing environment. It has a runtime limit (visible in the reference solution's log) and a limited amount of available memory (though this task should not have any issues with either limit).</li>
<li>The verbal description of the valid input structure is not completely exact. Therefore, we also provide a formal description of the input language in EBNF:</li>
</ul>
<pre><code>    input      ::= { whiteSpace } decimal { whiteSpace } op { whiteSpace } decimal { whiteSpace } '='
    whiteSpace ::= ' ' | '\t' | '\n' | '\r'
    decimal    ::= [ '+' | '-' ] integer [ '.' integer [ ( 'e' | 'E' ) [ '+' | '-' ] integer ] ] |
                   [ '+' | '-'  ] '.' integer [ ( 'e' | 'E' ) [ '+' | '-' ] integer ]
    integer    ::= digit { digit }
    digit      ::= '0' | '1' | '2' | '3' | '4' | '5' | '6' | '7' | '8' | '9'
    op         ::= '+' | '-' | '*' | '/'</code></pre>
</td>