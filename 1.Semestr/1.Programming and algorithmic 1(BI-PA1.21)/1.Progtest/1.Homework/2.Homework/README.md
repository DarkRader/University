<h1>Number Sequence</h1>

<td class="lrtbCell" colspan="3" align="left">
  <p>The task is to create a program that analyzes a sequence of numbers.</p>

  <p>We assume a sequence of non-negative integers (0, 1, 2, ...). The sequence starts with the number 0,
  and the individual numbers are written in ascending order without inserted spaces and unnecessary zeros. The sequence
  will start as follows:
  <pre>
01234567891011121314151617181920...
  </pre>
  For a human, such writing is difficult to read, so we present it in a colored form:
  <pre>
<span style="color: darkred">0</span><span style="color: blue">1</span><span style="color: darkred">2</span><span style="color: blue">3</span><span style="color: darkred">4</span><span style="color: blue">5</span><span style="color: darkred">6</span><span style="color: blue">7</span><span style="color: darkred">8</span><span style="color: blue">9</span><span style="color: darkred">10</span><span style="color: blue">11</span><span style="color: darkred">12</span><span style="color: blue">13</span><span style="color: darkred">14</span><span style="color: blue">15</span><span style="color: darkred">16</span><span style="color: blue">17</span><span style="color: darkred">18</span><span style="color: blue">19</span><span style="color: darkred">20</span>...
  </pre>

The task of the program is to read the position (ordinal number from the beginning) from the input and determine which digit
of which number is at the given position in the sequence. For example:
  <ul>
    <li>at position 0 is digit 0 of number 0,</li>
    <li>at position 15 is digit 2 of number 12,</li>
    <li>at position 2021 is digit 1 of number 710, ...</li>
  </ul></p>

  <p>To make the program more versatile, it can solve the given problem for different numeral systems.
  For example, for binary numeral system, the sequence would look like this:
  <pre>
<span style="color: darkred">0</span><span style="color: blue">1</span><span style="color: darkred">10</span><span style="color: blue">11</span><span style="color: darkred">100</span><span style="color: blue">101</span><span style="color: darkred">110</span><span style="color: blue">111</span><span style="color: darkred">1000</span><span style="color: blue">1001</span>...
  </pre>
  For the binary system, for example, at position 14, there is digit 0 of number 110.</p>

  <p>The program will have the individual problems to solve given in its input. Each problem will be
  given as two decimal numbers. The first number indicates the position in the sequence, the second number
  is the base of the numeral system for which the problem is being solved. For each such given problem, the program will calculate the result
  and display it in the format according to the example (number with the specified digit marked). Input of problems
  ends when the program reaches the end of input (signaled by active EOF).</p>

  <p>If the input is invalid, the program must detect this and display an error message.
  Display error messages to the standard output (not to the error output). Consider the following as an error:</p>

  <ul>
    <li>the position in the sequence is invalid (invalid number format, negative value),</li>
    <li>the base of the numeral system is invalid (non-numeric input, outside the closed interval &lt; 2 ; 36 &gt;).</li>
  </ul>

<b>Example of program operation:</b><br />
  <hr />
  <pre>
<b>Position and base:</b>
0 10
<b>0</b>
<b>^</b>
3 10
<b>3</b>
<b>^</b>
9 10
<b>9</b>
<b>^</b>
10 10
<b>10</b>
<b>^</b>
11 10
<b>10</b>
<b> ^</b>
12 10
<b>11</b>
<b>^</b>
13 10
<b>11</b>
<b> ^</b>
189 10
<b>99</b>
<b> ^</b>
190 10
<b>100</b>
<b>^</b>
191 10
<b>100</b>
<b> ^</b>
192 10
<b>100</b>
<b>  ^</b>
193 10
<b>101</b>
<b>^</b>
  </pre>
  <hr />
  <pre>
<b>Position and base:</b>
42 10
<b>26</b>
<b>^</b>
666 10
<b>258</b>
<b>  ^</b>
1889 10
<b>666</b>
<b> ^</b>
12345 10
<b>3363</b>
<b>   ^</b>
1000000 10
<b>185185</b>
<b>^</b>
1234321 10
<b>224238</b>
<b>   ^</b>
  </pre>
  <hr />
  <pre>
<b>Position and base:</b>
abc 10
<b>Invalid input.</b>
  </pre>
  <hr />
  <pre>
<b>Position and base:</b>
12 37
<b>Invalid input.</b>
  </pre>
  <hr />

<b>Notes:</b>
  <ul>
    <li>The sample runs capture the expected output of your program (in bold) and the input given
        by the user (normal font). Bold text is used only here on the task page for better readability.
        Your program should only display text without highlighting (without HTML markup).</li>

  <li>The newline character (\n) is also at the end of the last line of output (even after a possible error message).</li>

  <li>The submitted program is tested with multiple tests of increasing difficulty. The basic solution
        does not have to be efficient and must work correctly only with the decimal system (it does not have to handle
        other numeral systems, it can report an error for them). Such a solution will pass the mandatory tests
        and some optional tests. It will be graded 75% of the points.</li>

  <li>An enhanced solution must work correctly with various numeral bases. To pass this
        test, the program does not need to implement any efficient algorithm (a naive algorithm is sufficient).
        Successfully passing this test (and all previous tests) will be graded with
        a nominal 100% of points.</li>

  <li>The last (bonus) test checks the efficiency of the used algorithm. Large numbers are given
        as the input - positions in the sequence. The program has no chance to generate all necessary
        intermediate numbers within the allotted time. It is necessary to devise a suitable algorithm that can efficiently skip intermediate numbers. Successfully passing this test can earn more than the nominal 100% points.</li>

  <li>The basic solution can manage with variables of type <tt>int</tt>. In the bonus efficiency test,
        large position values are given that do not fit into the <tt>int</tt> type. If you want to solve
        the bonus test, use the <tt>long</tt> or <tt>long long</tt> type to store the position.</li>

  <li>For displaying numbers in numeral bases greater than 10, use lowercase letters (e.g., <tt>ff</tt>
        to display the number 255 in hexadecimal).</li>

  <li>Do not store the sequence of numbers <tt>01234567891011...</tt> in a string or array. It is unnecessarily complicated,
        memory-intensive, inappropriate, and not fast, and it is not needed. Generate the numbers in the sequence (e.g., with a for-loop),
        but there is no need to store them anywhere. It is not even necessary to convert individual numbers
        to strings.</li>
  </ul>
</td>