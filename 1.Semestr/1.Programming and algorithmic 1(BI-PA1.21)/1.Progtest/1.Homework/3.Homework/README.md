<h1>New Green Deal</h1>

<td class="lrtbCell" colspan="3" align="left"><p>The task is to implement a function (not the whole program, just the function) that will calculate the power consumption of a digital clock.</p>

<p>The European Union rightly understands that energy needs to be conserved, whatever the cost. So far, this applies to light bulbs, lamps, vacuum cleaners, but it is expected that this progressive trend will also affect other energy-intensive devices. To help the diligent work of EU officials, we will provide them in this task with an analytical tool that can be used to study the energy consumption of digital clocks with a mechanical seven-segment display in the long run.</p>

<p>The clock displays time on a seven-segment display. The time is shown in a 24-hour format, from <tt>00 00 00</tt> to <tt>23 59 59</tt>. The display is mechanical, each digit is formed from 7 segments, each segment is either a lit or unlit rectangle. If there is no change in a given segment, no energy is required. On the other hand, changing an unlit segment to lit or vice versa requires energy, and for simplicity, we assume 1J per segment change. The digits on the seven-segment display have a standard shape, i.e.:</p>

<pre>
 -         -    -         -    -    -    -    -                                                                     
| |    |    |    |  | |  |    |      |  | |  | |                                                                       
           -    -    -    -    -         -    -                                                                     
| |    |  |      |    |    |  | |    |  | |    |                                                                       
 -         -    -         -    -         -    -                                                                     
</pre>

<p>Our function will take two time points as parameters - the start and end of the interval. The start and end are given by year, month, day, hour, and minute. The function calculates how much energy the clock consumes over this period.</p>

<p>The required function has the following interface:</p>
<pre>
int energyConsumption ( int y1, int m1, int d1, int h1, int i1,
                        int y2, int m2, int d2, int h2, int i2, 
                        long long int * consumption )
</pre>
<dl>
 <dt><tt>y1, m1, d1, h1, i1</tt></dt><dd>are input parameters representing the year, month, day, hour, and minute of the start of the interval,</dd>

 <dt><tt>y2, m2, d2, h2, i2</tt></dt><dd>are input parameters representing the year, month, day, hour, and minute of the end of the interval,</dd>

 <dt><tt>consumption</tt></dt><dd>is the output parameter into which the function stores the calculated consumption for the specified period. The consumption should be returned in joules (J). The parameter will be set by the function only if the input parameters are correct. If the inputs are incorrect, the function will signal failure and leave this output parameter unchanged. The calculated value includes the consumption for all changes to the display made between the first and last displayed time point. For example, for the given input: 
   <pre>
     assert ( energyConsumption ( 2400,  2, 29, 12,  0,
                             2400,  2, 29, 12,  1, &amp;consumption ) == 1
              &amp;&amp; consumption == 204LL );
   </pre>
   During this time, 60 seconds changed (200J) and the minute changed from 00 to 01 (4J).
   </dd>

 <dt>return value of the function</dt><dd>will be set to 1 for success (correct input parameters) or 0 for failure (incorrect input parameters).</dd>
</dl>

<p>If the input parameters are incorrect, it is necessary to return a value of 0 (failure). The correct values of the input parameters must meet:</p>
<ul>
 <li>the year is greater than or equal to 1600,</li>
 <li>the month is valid (1 to 12),</li>
 <li>the day is valid (1 to the number of days in the month),</li>
 <li>the hour is valid (0 to 23),</li>
 <li>the minute is valid (0 to 59),</li>
 <li>the specified start time of the interval does not occur after the specified end time of the interval.</li>
</ul>

<p>Submit a source file that contains the implementation of the required function <tt>energyConsumption</tt>. Include any additional support functions called from <tt>energyConsumption</tt>. The function will be called from the testing environment, so it is important to strictly adhere to the specified function interface. Use the code example below as a basis for implementation. The example includes a test function <tt>main</tt>, with sample values used in the basic test. Note that the inclusion of header files and the <tt>main</tt> function are wrapped in a conditional compilation block (<tt>#ifdef/#endif</tt>). Please keep the conditional compilation blocks in the submitted source file. Conditional compilation will simplify your work. When compiling on your computer, you can normally run and test the program. When compiling on Progtest, the <tt>main</tt> function and the inclusion of header files will "disappear," so they will not conflict with the header files and the <tt>main</tt> function of the testing environment.</p>

<p>When calculating time, we consider the Gregorian calendar. Thus, months always have 30 or 31 days, with the exception of February, which has 28 days (non-leap year) or 29 days (leap year). According to the Gregorian calendar:</p>
<ol>
 <li>years are not leap years,</li>
 <li>except for years divisible by 4, which are leap years,</li>
 <li>except for years divisible by 100, which are not leap years,</li>
 <li>except for years divisible by 400, which are leap years,</li>
 <li>except for years divisible by 4000, which are not leap years.</li>
</ol>

<p>Thus, years 1901, 1902, 1903, 1905, ... are non-leap years (rule 1), years 1904, 1908, ..., 1996, 2004, ... are leap years (rule 2), years 1700, 1800, 1900, 2100, ... are non-leap years (rule 3), years 1600, 2000, 2400, ..., 3600, 4400, ... are leap years (rule 4), and years 4000, 8000, ... are non-leap years (rule 5).</p>

<p>Your program will run in a limited test environment. It is limited by runtime (the limit is visible in the reference solution log) and also by the amount of available memory. Time limits are set so that a reasonable implementation of a naive algorithm will pass all mandatory tests. A solution that works in the mandatory tests can get a nominal 100% score. The bonus test requires a time-efficient calculation even for large intervals (years significantly exceeding 4000).</p>
<hr />
<b>Hints:</b><br />
<ul>
 <li>Copy the attached file and use it as the basis for your solution.</li>

 <li>You can add other tests to the <tt>main</tt> function, or you can modify it as you like. It is important to keep the conditional compilation block. Note that using foreign tests is considered cheating.</li>

 <li>Working with the five values (year, month, day, hour, minute) is cumbersome (e.g., when comparing). It is better to convert these values to some other representation, ideally resulting in a single number.</li>

 <li>In the program, you will have to perform many calculations twice - for the start and end of the interval. It is a good idea to create support functions that you call twice.</li>

 <li>In the mandatory tests, the specified years do not exceed the year 4000.</li>

 <li>For large intervals (bonus test), the total consumption is enormous. The range of the <tt>int</tt> data type is insufficient. Therefore, the function has a <tt>long long int</tt> parameter, which is sufficient.</li>

 <li>The example uses the <tt>assert</tt> macro. If the parameter is non-zero, the macro does nothing. If the parameter is false (zero), the macro terminates the program and prints the line where the failure occurred. If your implementation passes the sample tests, the program will run and display nothing.</li>

 <li>A naive solution might try to generate all time values in the specified range and count the number of changed segments. Such an approach will be very slow and likely will not pass the time limit. Try to make the solution more efficient by skipping longer time periods for which you pre-calculate their consumption. A suitable granularity is, for example, one whole day; for one whole day, the consumption will always be the same.</li>
</ul>
</td> 