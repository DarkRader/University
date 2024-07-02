<h1>Numeric Sum</h1>
<td class="lrtbCell" colspan="3" align="left"><p>The task is to implement a program that determines for a given sequence of values whether a pair can be selected from it with the desired sum.</p>
<p>The input to the program is a sequence of integers <tt>x<sub>i</sub></tt>. The numbers are separated by commas. After this sequence follows a question mark and then a sequence of integers <tt>y</tt> - queries. There can be any number of queries. The task of the program is to determine whether the number <tt>y</tt> can be formed as the sum of two numbers <tt>x<sub>i</sub> + x<sub>j</sub>, i ≠ j</tt>.</p>
<p>The output of the program is a yes/no decision for each query <tt>y</tt>.</p>
<p>The program must handle input data. If the input is invalid, the program must detect it, print an error message, and terminate. Consider an error if:</p>
<ul>
 <li>non-numeric input for <tt>x<sub>i</sub></tt>,</li>
 <li>the numbers <tt>x<sub>i</sub></tt> are not separated by commas,</li>
 <li>less than 2 numbers <tt>x<sub>i</sub></tt>,</li>
 <li>missing question mark,</li>
 <li>non-numeric input for queries <tt>y</tt>.</li>
</ul>
<p>The program runs in a restricted environment. It is limited by runtime and available memory. For passing the mandatory tests, a correct implementation of a naive algorithm is sufficient. It is necessary for the program not to waste memory unnecessarily. To pass the bonus, an algorithm is needed that works quickly even for long sequences of <tt>x<sub>i</sub></tt>.</p>
<p>Example of program operation:</p>
<hr />
<pre>
<b>Input sequence:</b>
1, 5, 19, 6, 8, 24, 135,
  -90  ,   230  ,   15
?
<b>Tested values:</b>
6
<b>&gt; Sum 6 can be achieved.</b>
39
<b>&gt; Sum 39 can be achieved.</b>
3000
<b>&gt; Sum 3000 cannot be achieved.</b>
-400
<b>&gt; Sum -400 cannot be achieved.</b>
</pre>
<hr />
<pre>
<b>Input sequence:</b>
15,20,30,15,-40?20 40 -10 30 -80
<b>Tested values:</b>
<b>&gt; Sum 20 cannot be achieved.</b>
<b>&gt; Sum 40 cannot be achieved.</b>
<b>&gt; Sum -10 can be achieved.</b>
<b>&gt; Sum 30 can be achieved.</b>
<b>&gt; Sum -80 cannot be achieved.</b>
</pre>
<hr />
<pre>
<b>Input sequence:</b>
1, 5, 19 20
<b>Invalid input.</b>
</pre>
<hr />
<pre>
<b>Input sequence:</b>
1, 7, 3, 20
?
<b>Tested values:</b>
hello
<b>Invalid input.</b>
</pre>
<hr />
<p>Notes:</p>
<ul>
 <li>The example runs capture the expected outputs of your program (in bold) and user inputs (in plain text). Bold text is used here on the assignment page for clarity. Your program should simply display the text without bold formatting (without HTML markup).</li>
 <li>The newline character (\n) is also after the last line of output (including any error messages).</li>
 <li>For input processing, the function <tt>scanf</tt> with the format <tt>"%c"</tt> and <tt>" %c"</tt> is useful.</li>
 <li>Another useful function can be <tt>ungetc()</tt>.</li>
 <li>Use C language constructs to solve the problem. Do not use data structures from C++ - they are suppressed.</li>
</ul>
</td>