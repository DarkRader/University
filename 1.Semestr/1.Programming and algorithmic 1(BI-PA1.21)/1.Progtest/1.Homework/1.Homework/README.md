<h1>Planar shapes</h1>

<td class="lrtbCell" colspan="3" align="left"><p>The task is to create a program that will compare pairs of geometric shapes. It will compare their content and perimeter.</p>

<p>The input to the program is a pair of geometric shapes in the plane. For each shape, its size is specified. 
The shape can be:</p>
<ul>
 <li>triangle - the input is the pattern identification (letter T) followed by a trio of decimal numbers (side lengths),</li>
 <li>rectangle - the input is the pattern identification (letter R) followed by a pair of decimal numbers (side lengths) or </li>
 <li>square - the input is the pattern identification (letter S) followed by one decimal number (side length).</li>
</ul>

<p>The program determines whether the specified shapes have the same content/circumference and displays the result according to the format shown in the example (see below).</p>

<p>If the input is invalid, the program must detect this and display an error message.
Display the error message on the standard output (not on the error output). Consider the following as an error:</p>

<ul>
 <li>no allowed shape (triangle/rectangle/square) has been entered,</li>
 <li>the required number of decimal numbers - the dimensions of the pattern was not specified,</li>
 <li>the specified dimension was invalid, did not have the form of a valid number, was negative or zero,</li>
 <li>the specified side sizes do not form a triangle or</li>
 <li>the rectangle has both sides the same length (it should have been specified as a square).</li>
</ul>


<b>Demonstration of how the program works:</b><br />
<hr />
<pre>
<b>Form #1</b>
S 4.5
<b>Form #2</b>
R 2 10.125
<b>Perimeter: square #1 &lt; processor #2</b>
<b>Contents: square #1 = processor #2</b>
</pre>
<hr />
<pre>
<b>Form #1</b>
R 4 5
<b>Form #2</b>
T 4.5 6 7.5
<b>Perimeter: processor #1 = triangle #2</b>
<b>Contents: processor #1 &gt; triangle #2</b>
</pre>
<hr />
<pre>
<b>Form #1</b>

T
1
1
1
<b>Form #2</b>
S
2
<b>Perimeter: triangle #1 &lt; square #2</b>
<b>Contents: triangle #1 &lt; square #2</b>
</pre>
<hr />
<pre>
<b>Form #1</b>
T 7.981 8.899 2.996
<b>Form #2</b>
R 2.959 6.979
<b>Perimeter: triangle #1 = processor #2</b>
<b>Contents: triangle #1 &lt; processor #2</b>
</pre>
<hr />
<pre>
<b>Form #1</b>
R 6.474 0.559
<b>Form #2</b>
T 0.507 14.276 14.285
<b>Perimeter: processor #1 &lt; triangle #2</b>
<b>Contents: processor #1 = triangle #2</b>
</pre>
<hr />
<pre>
<b>Form #1</b>
T 20 30 50
<b>Incorrect input.</b>
</pre>
<hr />
<pre>
<b>Form #1</b>
S -4
<b>Incorrect input.</b>
</pre>
<hr />
<pre>
<b>Form #1</b>
R 20 30
<b>Form #2</b>
T 0.444 0.521 0.965
<b>Incorrect input.</b>
</pre>
<hr />
<pre>
<b>Form #1</b>
R 12 12
<b>Incorrect input.</b>
</pre>
<hr />
<pre>
<b>Form #1</b>
R 1 abcd
<b>Incorrect input.</b>
</pre>
<hr />

<b>Notes:</b>
<ul>
 <li>Sample runs capture the expected output of your program (bold font) and the inputs entered 
     by the user (basic font). Bold font highlighting is only used here on the input page, 
     to make the listing easier to read. Your program only has to display the text without highlighting 
     (no HTML markup).</li>
 <li>The line break character (\n) is also after the last line of the output (also after any error message).</li>

 <li>To represent values, use decimal numbers of type <tt>double</tt>. Do not use 
   type <tt>float</tt>, its accuracy may not be sufficient.</li>

 <li>The task can be solved without using functions. But if you use the functions correctly, 
     the program will be clearer and easier to debug.</li>

 <li>Numeric input values are entered to fit within the data range 
     type <tt>double</tt>. The reference solution makes do with numeric types <tt>double</tt> 
     and <tt>int</tt>.</li>

 <li>The function is useful for loading the input <tt>scanf</tt>.</li>

 <li>When programming, pay attention to the exact form of the statements. Output of your program
     is checked by the machine, which requires an exact match between the outputs of your program and the outputs   
     reference. It is considered an error if the output differs. Even missing or excessive
     spacing/unspacing is considered an error. To eliminate these problems quickly, 
     use the attached archive with a set of input and expected output data. See
     video tutorial (materials -&gt; tutorials -&gt; video tutorials) on how to test 
     data and how to automate the testing.</li>

 <li>Heron's formula can be used to calculate the area of a triangle.</li>    

 <li>    
  <p>Your program will run in a limited test environment. It is limited
  by the run time (the limit is visible in the log of the reference solution) and is also limited by the
  the amount of memory available (but this task should not have either limitation
  problem). The test environment also prohibits the use of some "unsafe
  functions" -- functions for program execution, for networking, ... If they are
  these functions are used, the program will not run. You may be using 
  call:</p>

  <pre>
  int main ( int argc, char * argv [] )
  {
   
    ...
       
    system ( "pause" ); /* to prevent the program window from closing */
    return 0;
  }
  </pre>

  <p>This will not work in the test environment - it is forbidden to run another
  (Even if the program did run, it would be rejected. It would not 
  because no one would pause, the program would wait forever and exceed
  the maximum run time.) So if you want to keep the pause for testing on
  your computer, you want to make sure that the program runs correctly,    
  use the following trick:</p>

  <pre>
  int main ( int argc, char * argv [] )
  {
   
    ...
  
  #ifndef __PROGTEST__
    system ( "pause" ); /* progtest does not "see" this */
  #endif /* __PROGTEST__ */
    return 0;
  } 
  </pre>
 </li>
</ul>

</td>  