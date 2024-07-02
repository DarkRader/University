<h1>Unique Visits</h1>
<td class="lrtbCell" colspan="3" align="left"><p>The task is to create a program that processes logs and counts unique visits.</p>
<p>We assume we are recording individual accesses to a web server. We record users who access it - each user is marked with a unique identifier. The identifier is an integer from the closed interval 0 to 99999. The input consists of individual accesses entered as <tt>+ id</tt>, for example:
<pre>
+ 123
+ 456
+ 123
+ 123
+ 789
</pre>
Here at positions 0, 2, and 3 are accesses by user 123, at position 1 is an access by user 456, and at position 4 is an access by user 789.</p>
<p>From the recorded accesses, it is necessary to calculate the information about the number of unique users. For the calculation, a range that is to be analyzed will be provided. The query is in the form <tt>? from to</tt>, where <tt>from</tt> and <tt>to</tt> are the positions from/to which we are to count unique users. For example, for the given example, a query like <tt>? 0 4</tt> would result in the response <tt>3 / 5</tt> - 3 unique users out of a total of 5 records in the queried range.</p>
<p>The input of the program consists of accesses and queries, which can be interspersed in any order. The program processes the input, stores information about the accesses, and handles queries continuously. The input processing ends either by detecting an error (invalid input) or by reaching the end of input (EOF). There are a maximum of 1000000 accesses in total, the number of queries for calculating unique accesses is unlimited.</p>
<p>The output of the program is a response to each input:
<ul>
 <li>for each access, the program displays how many times the user has accessed,</li>
 <li>for a query on the number of unique accesses, the program displays the information about the number of unique users in the given range / the total number of accesses in the specified range.</li>
</ul></p>
<p>If the input is invalid, the program must detect this and display an error message.
Display the error message on standard output (not on error output). Consider an error in adding an access if:</p>
<ul>
 <li>the user <tt>id</tt> is missing,</li>
 <li><tt>id</tt> is not an integer,</li>
 <li><tt>id</tt> is not in the interval &lt; 0 ; 99999 &gt;, or</li>
 <li>there are more than 1000000 accesses.</li>
</ul>
<p>Consider an error in a query if:</p>
<ul>
 <li>information <tt>from</tt> and <tt>to</tt> is missing,</li>
 <li><tt>from</tt> / <tt>to</tt> are not integers,</li>
 <li><tt>from</tt> is less than 0,</li>
 <li><tt>to</tt> is greater than or equal to the number of registered accesses so far, or</li>
 <li><tt>from</tt> is greater than <tt>to</tt>.</li>
</ul>
<p>It is also an error if the input is neither an addition of an access nor a query.</p>
<hr />
<pre>
<b>Requests:</b>
+ 10
<b>&gt; first visit</b>
+ 20
<b>&gt; first visit</b>
+ 99999
<b>&gt; first visit</b>
+ 5
<b>&gt; first visit</b>
+ 20
<b>&gt; visit #2</b>
+ 25
<b>&gt; first visit</b>
+ 10
<b>&gt; visit #2</b>
? 0 6
<b>&gt; 5 / 7</b>
? 0 5
<b>&gt; 5 / 6</b>
? 1 6
<b>&gt; 5 / 6</b>
? 1 5
<b>&gt; 4 / 5</b>
? 2 6
<b>&gt; 5 / 5</b>
? 2 5
<b>&gt; 4 / 4</b>
? 2 4
<b>&gt; 3 / 3</b>
? 2 3
<b>&gt; 2 / 2</b>
? 2 2
<b>&gt; 1 / 1</b>
+ 5
<b>&gt; visit #2</b>
+ 10
<b>&gt; visit #3</b>
+ 5
<b>&gt; visit #3</b>
+ 20
<b>&gt; visit #3</b>
? 0 10
<b>&gt; 5 / 11</b>
? 7 10
<b>&gt; 3 / 4</b>
? 1 11
<b>Invalid input.</b>
</pre>
<hr />
<pre>
<b>Requests:</b>
+ 10
<b>&gt; first visit</b>
+ 20
<b>&gt; first visit</b>
+ 30
<b>&gt; first visit</b>
? 2 1
<b>Invalid input.</b>
</pre>
<hr />
<pre>
<b>Requests:</b>
+ 12
<b>&gt; first visit</b>
* 33
<b>Invalid input.</b>
</pre>
<hr />
<b>Notes:</b>
<ul>
 <li>The example runs capture the expected outputs of your program (in bold) and user inputs (in plain text). Bold text is used here on the assignment page for clarity.
     Your program should simply display the text without bold formatting (without HTML markup).</li>
 <li>The newline character (\n) is also after the last line of output (including any error messages).</li>
 <li>Use the fact that the number of different visitor identifiers is limited (0 to 99999) and the number of accesses is also limited (1000000). If you need to store, for example, all input accesses in memory, a statically allocated array will suffice.</li>
 <li>The submitted program is tested with more tests of increasing difficulty. First, the correctness of the solution is checked, then the correctness of working with the array (tested by a memory debugger), and finally the efficiency of the solution.</li>
 <li>A basic solution does not need to be efficient; a naive (quadratic) algorithm for finding unique values is sufficient. Such a solution will pass mandatory tests and some optional tests. It will be evaluated with a maximum of 100% points.</li>
 <li>The first bonus test checks the efficiency of the submitted program. Long inputs and queries over long intervals are provided. A naive algorithm is not efficient enough and cannot handle the computation within the set time limit.</li>
 <li>The second bonus test further checks the efficiency of the algorithm used. Long inputs are provided, queries process large intervals of accesses, and many queries are given. To meet the time limit, the recorded accesses need to be preprocessed so that the program does not have to repeatedly count what needs to be counted only once during the analysis.</li>
 <li>A program that passes all mandatory and optional tests with 100% can be used for code review. 
     (Passing the bonus tests is not required for code review).</li>
</ul>
</td>