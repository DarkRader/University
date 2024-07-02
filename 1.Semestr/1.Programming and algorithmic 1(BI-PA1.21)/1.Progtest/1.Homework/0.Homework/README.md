<h1>Quotes</h1>

<td class="lrtbCell" colspan="3" align="left"><p>The task is to create a program that will display selected quotes.</p>

<p>The program input is a single integer. This number is from the range 1 to 5 and 
specifies the quote to be displayed.</p>

<p>The output of the program is a quote corresponding to the specified number on the input. 
The quotes corresponding to each number are shown in the sample runs of the program below.
Note that the quote text is followed by a line break (\n).</p>

<p>If the input is invalid, the program must detect this and display an error message.
Display the error message on the standard output (not on the error output). Consider the following as an error:</p>

<ul>
 <li>whole number cannot be read from the input,</li>
 <li>the number read from the input is outside the interval 1 to 5.</li>
</ul>

<p>When programming, pay attention to the exact form of the statements. Output of your program
is checked by the machine, which requires an exact match between the outputs of your program and the outputs   
reference. It is considered an error if the output differs. Even missing or excessive
spacing/unspacing is considered an error. To eliminate these problems quickly, 
use the attached archive with a set of input and expected output data. See
video tutorial (courses -&gt; tutorial videos) on how to use the test data and how to 
automate the testing.</p>

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

<b>Demonstration of how the program works:</b><br />
<hr />

<pre>
ml' nob:
1
Qapla'
noH QapmeH wo' Qaw'lu'chugh yay chavbe'lu' 'ej wo' choqmeH may' DoHlu'chugh lujbe'lu'.
</pre>
<hr />
<pre>
ml' nob:
2
Qapla'
Qu' buSHa'chugh SuvwI', batlhHa' vangchugh, qoj matlhHa'chugh, pagh ghaH SuvwI''e'.
</pre>
<hr />
<pre>
ml' nob:
3
Qapla'
qaStaHvIS wa' ram loS SaD Hugh SIjlaH qetbogh loD.
</pre>
<hr />
<pre>
ml' nob:
4
Qapla'
Ha'DIbaH DaSop 'e' DaHechbe'chugh yIHoHQo'.
</pre>
<hr />
<pre>
ml' nob:
5
Qapla'
leghlaHchu'be'chugh mIn lo'laHbe' taj jej.
</pre>
<hr />
<pre>
ml' nob:
0
luj
</pre>
<hr />
<pre>
ml' nob:
6
luj
</pre>
<hr />
<pre>
ml' nob:
abc
luj
</pre>

<hr />
<b>Notes:</b>
<ul>
 <li>The line break character (\n) is also after the last line of the output (also after any error message).</li>

 <li>The program prompts and quotes are deliberately chosen to make them difficult to copy by hand. The task is 
    among other things, teaches you how to work effectively with a computer, e.g. with the copy & paste functions (which 
    unfortunately some students do not know or cannot use). Try and learn how to copy & paste 
    both under Windows and UNIX (Linux), it will come in handy for the final test!</li>

 <li>Manually checking the match between your output and the reference output is tedious, one often 
    overlook a subtle difference. This is especially true for text in a task, which for most people is not 
    understandable to most people. Again, this is the intention. Take advantage of the free time at the beginning of the semester to learn in this 
    simple problem to effectively test your programs. Watch the video tutorial mentioned above 
    (courses -&gt; tutorial videos) and use your computer for comparison. This will save you money in future assignments. 
    a lot of time.</li>

 <li>Vstup typu <code>1.23</code> případně <code>1abcd</code> považujte za správný. Základní použití funkce 
   <code>scanf</code> bude takové vstupy interpretovat jako číslo (zde číslo <code>1</code>) a zbytek vstupu 
   nebude číst. Šlo by samozřejmě program rozšířit, aby takovéto vstupy odmítal, v této úloze to ale není 
   potřeba dělat. Automatizované testování vstupy tohoto typu se nezadává.</li> 
</ul>
</td>