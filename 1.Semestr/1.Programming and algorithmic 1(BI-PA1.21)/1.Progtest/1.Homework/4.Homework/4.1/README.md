<h1>Tic-Tac-Toe</h1>
<td class="lrtbCell" colspan="3" align="left"><p>The task is to write a program that evaluates a game of tic-tac-toe.</p>
<p>The program's task is not to play tic-tac-toe, but only to evaluate the players' positions.
We assume a square field of size <tt>N &times; N</tt>. In this field, the rows are numbered <tt>1, 2, 3, ... </tt> and the columns <tt>a, b, c, ...</tt>.
A move is recorded using the column and row, for example, <tt>c5</tt>.
The input of the program is the record of individual moves, in the order in which the players played.
The player with the cross (X) always moves first. The second player moves with the O, then X again, and so on. Input ends when the end of file (EOF) is reached.</p>
<p>The output of the program after each move is information about the longest contiguous sequence
of characters of the last player who moved. We consider the horizontal, vertical, and both diagonal directions.
Additionally, the program displays the number of different such longest sequences.</p>
<p>The program must react to invalid inputs. If the input is invalid, the program
must detect this, print an error message, and terminate. Errors include:</p>
<ul>
 <li>The size of the playing field is not an integer or is outside the bounds of 3 to 26,</li>
 <li>The move provided by a player is not valid (out of the playing area),</li>
 <li>The move is repeated (i.e., the specified position is already occupied).</li>
</ul>
<p>Example of the program's operation:</p>
<hr />
<pre>
<b>Field size:</b>
3
b2
<b>Player 'X': longest 1 (1 x)</b>
a2
<b>Player 'O': longest 1 (1 x)</b>
c3
<b>Player 'X': longest 2 (1 x)</b>
a1
<b>Player 'O': longest 2 (1 x)</b>
a3
<b>Player 'X': longest 2 (2 x)</b>
b3
<b>Player 'O': longest 2 (2 x)</b>
c1
<b>Player 'X': longest 3 (1 x)</b>
b1
<b>Player 'O': longest 2 (4 x)</b>
c2
<b>Player 'X': longest 3 (2 x)</b>
</pre>
<hr />
<pre>
<b>Field size:</b>
5
a5
<b>Player 'X': longest 1 (1 x)</b>
b4
<b>Player 'O': longest 1 (1 x)</b>
c5
<b>Player 'X': longest 1 (2 x)</b>
d4
<b>Player 'O': longest 1 (2 x)</b>
a3
<b>Player 'X': longest 1 (3 x)</b>
b2
<b>Player 'O': longest 1 (3 x)</b>
c3
<b>Player 'X': longest 1 (4 x)</b>
d2
<b>Player 'O': longest 1 (4 x)</b>
a1
<b>Player 'X': longest 1 (5 x)</b>
</pre>
<hr />
<pre>
<b>Field size:</b>
3
b2
<b>Player 'X': longest 1 (1 x)</b>
a2
<b>Player 'O': longest 1 (1 x)</b>
c2
<b>Player 'X': longest 2 (1 x)</b>
b2
<b>Invalid input.</b>
</pre>
<hr />
<pre>
<b>Field size:</b>
test
<b>Invalid input.</b>
</pre>
<hr />
<b>Notes:</b>
<ul>
 <li>The example runs capture the expected outputs of your program (in bold) and user inputs (in plain text). Bold text is used here on the assignment page for clarity.
     Your program should simply display the text without bold formatting (without HTML markup).</li>
 <li>The newline character (\n) is also after the last line of output (including any error messages).</li>
 <li>Only lowercase alphabet letters are valid for columns.</li>
 <li>A program that passes all required and optional tests with 100% can be used for code review.</li>
</ul>
</td>