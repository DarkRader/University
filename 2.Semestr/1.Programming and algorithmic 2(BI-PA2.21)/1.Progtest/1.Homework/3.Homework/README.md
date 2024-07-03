<h1>Date</h1>

<td class="lrtbCell" colspan="3" align="left">
    <p>The task is to implement a class that will represent a date. The represented dates will follow the rules of the Gregorian calendar. It is required to represent dates at least in the range of years 2000 to 2030.</p>

<p>The <tt>CDate</tt> class must meet the following interface:</p>

<ul>
<li>A constructor with parameters (y,m,d) creates a new instance of the class with the date set according to the given values. The constructor must check whether the given date is valid. If it is not valid, it must throw an <tt>InvalidDateException</tt>.</li>
        
<li>With the + operator, you can add an integer to the <tt>CDate</tt> instance to move forward by the given number of days (backward for a negative number).</li>
        
<li>With the - operator, you can subtract an integer from the <tt>CDate</tt> instance to move backward by the given number of days (forward for a negative number).</li>
        
<li>With the - operator, you can subtract one <tt>CDate</tt> instance from another to get the number of days between these two dates.</li>
        
<li>The ++ and -- operators in both prefix and postfix notation can increase/decrease the date by 1 day. The operators have the usual behavior.</li>
        
<li>The ==, !=, &gt;, &gt;=, &lt;, and &lt;= operators can compare a pair of <tt>CDate</tt> instances. In this relation, future dates are greater than past dates.</li>
        
<li>With the &lt;&lt; operator, you can display the <tt>CDate</tt> instance in the given stream. When displaying, the ISO format (%Y-%m-%d, e.g., 2000-01-31) is used. In mandatory tests, this default format will always be used. The bonus tests require the implementation of the <tt>date_format</tt> manipulator, which allows you to control the format.</li>
        
<li>With the &gt;&gt; operator, you can read the <tt>CDate</tt> instance from the given stream. In mandatory tests, the input is expected to be in the ISO format %Y-%m-%d. If the date cannot be read (due to format, invalid date, etc.), the operator ensures the fail bit is set and the original content of the <tt>CDate</tt> instance remains unchanged. Like the output operator, the input can also be controlled using the <tt>date_format</tt> manipulator. This option is required in the bonus test.</li>
</ul>

<hr />

<p>Submit a file that contains the implemented <tt>CDate</tt> class and any additional supporting classes and functions. The class must meet the described public interface - if your submitted solution does not contain the described interface, a compilation error will occur. However, you can add other methods (public or private) and member variables to the class. The submitted file must contain both the class declaration (interface description) and the method, constructor, and destructor definitions. It does not matter whether the methods are implemented inline or separately. The submitted file must not contain header file inclusions and the <tt>main</tt> function (the <tt>main</tt> function and header file inclusions may remain but must be wrapped in conditional compilation directives as in the example below).</p>

<p>This task is not focused on speed. Given the range of tested values, you can use library calls for date conversions (<tt>ctime</tt>) with some caution.</p>

<p>The task has a mandatory and a bonus part. The mandatory part does not use the <tt>date_format</tt> manipulator, so only the default date format (%Y-%m-%d) is tested. In the bonus part, it is additionally required that this manipulator works correctly. If you decide to skip the bonus part, leave the provided "dummy" implementation of the manipulator in your source code (otherwise, the code will not compile).</p>

<p>The bonus tests use the <tt>date_format</tt> manipulator you provide, which describes the required conversions using a string. The format can contain:
<ul>
<li>Characters other than the percent sign - on input, such a character is expected at the given position and is skipped. If the character is not found on input, it is considered an error. On output conversion, such a character is added to the output. In ISO format %Y-%m-%d, the hyphens are such characters.</li>
<li>The percent sign introduces a day (%d), month (%m), or year (%Y), which appears at the given position in the date string. For input, a whole number representing the day/month/year is expected. For output conversion, it means that the decimal value of the day/month/year is appended to the output, left-padded with zeros.</li>
<li>A percent sign followed by a character other than Y, m, or d (e.g., %x, %%, ...) indicates that such a character (e.g., x, %, ...) appears/should appear at that position in the date string. Thus, the ISO date format could be equivalently rewritten as %Y%-%m%-%d.</li>
    </ul>
    </p>

<p>Once the <tt>date_format</tt> manipulator is sent to the stream, the format applies to all subsequent conversions until a possible format change (it behaves similarly to manipulators like <tt>hex</tt>, ...). When implementing, keep in mind that each stream can have a different manipulator set.</p>

<p>The output format can be arbitrary (an extreme example is the "hello kitty" format in the example). The input format has a restriction so that the input can be unambiguously processed: the day, month, and year (%d, %m, and %Y) must be included in the format and must appear exactly once. The examples show that input formats with missing or redundant conversions lead to an error in subsequent reading.</p>

<p>Notes:</p>

<ul>
        <li>The attachment contains the basic implementation, run examples, and bonus test run examples.</li>
        <li>Depending on the chosen implementation, it may matter that some days do not have 24 hours.</li>
        <li>If you implement the manipulator, study the methods <tt>xalloc</tt>, <tt>register_callback</tt>, <tt>pword</tt>, and <tt>iword</tt> in the <tt>ios_base</tt> class.</li>
        <li>When solving the task, you will encounter the problem of leap years. A year is considered a leap year if it is divisible by 4 (e.g., 2020, 2024, ...). An exception is years divisible by 100, which are <b>not</b> leap years (e.g., 1900 and 2100 were/will not be leap years). An exception to this exception is years divisible by 400, which are leap years (e.g., the year 2000 was a leap year). However, the task is simplified by the fact that only years within the range 2000 - 2030 are considered.</li>
        <li>When reading the day, month, and year from the stream, you should check that the read number has the correct number of digits (2 for day and month, 4 for year). In the basic tests, you do not need to check this (generated day and month values have possible leading zeros). In the bonus test, this needs to be checked more carefully, otherwise, input reading in the general format may not work. In the example run, there is a test case for this.</li>
        <li>The solution to the task in the basic version is very short and straightforward. Such a solution cannot be used for code review. For code review, only solutions that have successfully passed all tests, including bonus tests, can be submitted this time.</li>
    </ul>
</td>