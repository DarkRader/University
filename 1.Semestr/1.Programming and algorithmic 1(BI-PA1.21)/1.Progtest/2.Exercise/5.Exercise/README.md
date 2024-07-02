<h1>Chessboard</h1>

<td class="lrtbCell" colspan="3" align="left"><p>The task is to implement a program that displays a chessboard on the screen.</p>

<p>The program takes two integers as input - the size of the chessboard (number of squares in width and height) and the size of each square (number of characters in height and width of one square).</p>

<p>The output of the program is the displayed chessboard. The chessboard will be composed of space characters (white squares) and the character X (black squares). The entire chessboard will be framed. The top-left corner will always be a white square. The chessboard is square (number of squares is the same in both directions), and the squares are also square (the number of characters per square is the same in both directions).</p>

<p>If the input is invalid, the program must detect it and display an error message. Display error messages on the standard output (not the error output). Consider the following as errors:</p>
<ul>
<li>the input does not consist of two valid integers,</li>
<li>the numbers in the input are negative or zero.</li>
</ul>
<p><strong>Sample program operation:</strong></p>
<hr />

<pre>
<b>Enter number of squares:</b>
5
<b>Enter size of each square:</b>
3
<b>+---------------+</b>
<b>|   XXX   XXX   |</b>
<b>|   XXX   XXX   |</b>
<b>|   XXX   XXX   |</b>
<b>|XXX   XXX   XXX|</b>
<b>|XXX   XXX   XXX|</b>
<b>|XXX   XXX   XXX|</b>
<b>|   XXX   XXX   |</b>
<b>|   XXX   XXX   |</b>
<b>|   XXX   XXX   |</b>
<b>|XXX   XXX   XXX|</b>
<b>|XXX   XXX   XXX|</b>
<b>|XXX   XXX   XXX|</b>
<b>|   XXX   XXX   |</b>
<b>|   XXX   XXX   |</b>
<b>|   XXX   XXX   |</b>
<b>+---------------+</b>
</pre>
<hr />
<pre>
<b>Enter number of squares:</b>
8
<b>Enter size of each square:</b>
4
<b>+--------------------------------+</b>
<b>|    XXXX    XXXX    XXXX    XXXX|</b>
<b>|    XXXX    XXXX    XXXX    XXXX|</b>
<b>|    XXXX    XXXX    XXXX    XXXX|</b>
<b>|    XXXX    XXXX    XXXX    XXXX|</b>
<b>|XXXX    XXXX    XXXX    XXXX    |</b>
<b>|XXXX    XXXX    XXXX    XXXX    |</b>
<b>|XXXX    XXXX    XXXX    XXXX    |</b>
<b>|XXXX    XXXX    XXXX    XXXX    |</b>
<b>|    XXXX    XXXX    XXXX    XXXX|</b>
<b>|    XXXX    XXXX    XXXX    XXXX|</b>
<b>|    XXXX    XXXX    XXXX    XXXX|</b>
<b>|    XXXX    XXXX    XXXX    XXXX|</b>
<b>|XXXX    XXXX    XXXX    XXXX    |</b>
<b>|XXXX    XXXX    XXXX    XXXX    |</b>
<b>|XXXX    XXXX    XXXX    XXXX    |</b>
<b>|XXXX    XXXX    XXXX    XXXX    |</b>
<b>|    XXXX    XXXX    XXXX    XXXX|</b>
<b>|    XXXX    XXXX    XXXX    XXXX|</b>
<b>|    XXXX    XXXX    XXXX    XXXX|</b>
<b>|    XXXX    XXXX    XXXX    XXXX|</b>
<b>|XXXX    XXXX    XXXX    XXXX    |</b>
<b>|XXXX    XXXX    XXXX    XXXX    |</b>
<b>|XXXX    XXXX    XXXX    XXXX    |</b>
<b>|XXXX    XXXX    XXXX    XXXX    |</b>
<b>|    XXXX    XXXX    XXXX    XXXX|</b>
<b>|    XXXX    XXXX    XXXX    XXXX|</b>
<b>|    XXXX    XXXX    XXXX    XXXX|</b>
<b>|    XXXX    XXXX    XXXX    XXXX|</b>
<b>|XXXX    XXXX    XXXX    XXXX    |</b>
<b>|XXXX    XXXX    XXXX    XXXX    |</b>
<b>|XXXX    XXXX    XXXX    XXXX    |</b>
<b>|XXXX    XXXX    XXXX    XXXX    |</b>
<b>+--------------------------------+</b>
</pre>
<hr />
<pre>
<b>Enter number of squares:</b>
2
<b>Enter size of each square:</b>
0
<b>Invalid input.</b>
</pre>
<hr />
<pre>
<b>Enter number of squares:</b>
asdf
<b>Invalid input.</b>
</pre>

<hr />
<p><strong>Notes:</strong></p>
<ul>
<li>The sample runs capture the expected outputs of your program (bold text) and the inputs provided by the user (regular text). Bold formatting is used here on the assignment page to enhance readability. Your program's task is to display text without any formatting (without HTML markup).</li>
<li>A newline character (\n) follows even after the last line of output (including any error messages).</li>
<li>Pay attention to the exact format of the outputs when programming. Your program's output will be checked against reference outputs for exact matches. Differences in output are considered errors. Missing or extra spaces/newlines are also considered errors. To quickly eliminate these issues, use the provided archive with input and expected output data. Watch the video tutorial on how to use the test data and automate testing (<a href="https://courses.fit.cvut.cz/BI-PA1/video.html">Courses -&gt; Video tutorials</a>).</li>
<li>The program output can be very wide/long. It's advisable to redirect the output to a file and view it in a text editor.</li>
</ul>

</td>