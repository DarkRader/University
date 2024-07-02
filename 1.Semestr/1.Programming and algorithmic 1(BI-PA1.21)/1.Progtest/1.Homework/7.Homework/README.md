<h1>Towers from Blocks</h1>

<td class="lrtbCell" colspan="3" align="left">
    <p>Small children love playing with blocks. Blocks can be used to build towers, which can then be knocked down, another fun activity. Additionally, playing with blocks helps children develop the ability to compare sizes, which is important for their psychosomatic development. However, some children may ask adults tricky questions while playing with blocks. The task is to implement a program that can answer some of these questions.</p>

<p>We assume we have <tt>N</tt> blocks of different sizes available. We also know the sizes of the individual blocks. We want to build towers from the blocks. A tower has a height of at least one block. When building, blocks can be stacked on top of each other, but a larger block cannot be placed on a smaller one. The task is to calculate how many unique towers can be built and display their configurations.</p>

<p>The input of the program is the number of blocks <tt>N</tt> followed by the sizes of the individual blocks.</p>

<p>The output of the program is a list of the individual towers, i.e., the order of block sizes, always from the base (left) to the top (right). One tower is listed on each line. The program also displays the number of found towers.</p>

<p>The program must handle input data validation. If the input data is invalid, the program must detect it, print an error message, and terminate. The following are considered errors:</p>
<ul>
        <li>non-numeric, negative, or zero number of blocks <tt>N</tt>,</li>
        <li>block size is not an integer, is negative, or zero.</li>
    </ul>

<p>The program is tested in a limited environment. It is limited by runtime and memory size. The task is not memory-intensive, but it is time-intensive for large inputs. Relatively small data volumes, which can be handled by a program that reasonably implements a naive algorithm, are tested.</p>

<b>Program Example:</b>
<hr />
<pre>
<b>Number of blocks:</b>
5
<b>Sizes:</b>
1 2 3 4 5
<b>5, 4, 3, 2, 1</b>
<b>5, 4, 3, 2</b>
<b>5, 4, 3, 1</b>
<b>5, 4, 3</b>
<b>5, 4, 2, 1</b>
<b>5, 4, 2</b>
<b>5, 4, 1</b>
<b>5, 4</b>
<b>5, 3, 2, 1</b>
<b>5, 3, 2</b>
<b>5, 3, 1</b>
<b>5, 3</b>
<b>5, 2, 1</b>
<b>5, 2</b>
<b>5, 1</b>
<b>5</b>
<b>4, 3, 2, 1</b>
<b>4, 3, 2</b>
<b>4, 3, 1</b>
<b>4, 3</b>
<b>4, 2, 1</b>
<b>4, 2</b>
<b>4, 1</b>
<b>4</b>
<b>3, 2, 1</b>
<b>3, 2</b>
<b>3, 1</b>
<b>3</b>
<b>2, 1</b>
<b>2</b>
<b>1</b>
<b>Total: 31</b>
</pre>
    <hr />
    <pre>
<b>Number of blocks:</b> 7
<b>Sizes:</b> 3 8 23
5 2 1 8
<b>23, 8, 5, 3, 2, 1</b>
<b>23, 8, 5, 3, 2</b>
<b>23, 8, 5, 3, 1</b>
<b>23, 8, 5, 3</b>
<b>23, 8, 5, 2, 1</b>
<b>23, 8, 5, 2</b>
<b>23, 8, 5, 1</b>
<b>23, 8, 5</b>
<b>23, 8, 3, 2, 1</b>
<b>23, 8, 3, 2</b>
<b>23, 8, 3, 1</b>
<b>23, 8, 3</b>
<b>23, 8, 2, 1</b>
<b>23, 8, 2</b>
<b>23, 8, 1</b>
<b>23, 8</b>
<b>23, 8, 8, 5, 3, 2, 1</b>
<b>23, 8, 8, 5, 3, 2</b>
<b>23, 8, 8, 5, 3, 1</b>
<b>23, 8, 8, 5, 3</b>
<b>23, 8, 8, 5, 2, 1</b>
<b>23, 8, 8, 5, 2</b>
<b>23, 8, 8, 5, 1</b>
<b>23, 8, 8, 5</b>
<b>23, 8, 8, 3, 2, 1</b>
<b>23, 8, 8, 3, 2</b>
<b>23, 8, 8, 3, 1</b>
<b>23, 8, 8, 3</b>
<b>23, 8, 8, 2, 1</b>
<b>23, 8, 8, 2</b>
<b>23, 8, 8, 1</b>
<b>23, 8, 8</b>
<b>23, 5, 3, 2, 1</b>
<b>23, 5, 3, 2</b>
<b>23, 5, 3, 1</b>
<b>23, 5, 3</b>
<b>23, 5, 2, 1</b>
<b>23, 5, 2</b>
<b>23, 5, 1</b>
<b>23, 5</b>
<b>23, 3, 2, 1</b>
<b>23, 3, 2</b>
<b>23, 3, 1</b>
<b>23, 3</b>
<b>23, 2, 1</b>
<b>23, 2</b>
<b>23, 1</b>
<b>23</b>
<b>8, 5, 3, 2, 1</b>
<b>8, 5, 3, 2</b>
<b>8, 5, 3, 1</b>
<b>8, 5, 3</b>
<b>8, 5, 2, 1</b>
<b>8, 5, 2</b>
<b>8, 5, 1</b>
<b>8, 5</b>
<b>8, 3, 2, 1</b>
<b>8, 3, 2</b>
<b>8, 3, 1</b>
<b>8, 3</b>
<b>8, 2, 1</b>
<b>8, 2</b>
<b>8, 1</b>
<b>8</b>
<b>8, 8, 5, 3, 2, 1</b>
<b>8, 8, 5, 3, 2</b>
<b>8, 8, 5, 3, 1</b>
<b>8, 8, 5, 3</b>
<b>8, 8, 5, 2, 1</b>
<b>8, 8, 5, 2</b>
<b>8, 8, 5, 1</b>
<b>8, 8, 5</b>
<b>8, 8, 3, 2, 1</b>
<b>8, 8, 3, 2</b>
<b>8, 8, 3, 1</b>
<b>8, 8, 3</b>
<b>8, 8, 2, 1</b>
<b>8, 8, 2</b>
<b>8, 8, 1</b>
<b>8, 8</b>
<b>5, 3, 2, 1</b>
<b>5, 3, 2</b>
<b>5, 3, 1</b>
<b>5, 3</b>
<b>5, 2, 1</b>
<b>5, 2</b>
<b>5, 1</b>
<b>5</b>
<b>3, 2, 1</b>
<b>3, 2</b>
<b>3, 1</b>
<b>3</b>
<b>2, 1</b>
<b>2</b>
<b>1</b>
<b>Total: 95</b>
</pre>
<hr />
<pre>
<b>Number of blocks:</b>
6
<b>Sizes</b>
1 2 3 2 3 4
<b>4, 3, 2, 1</b>
<b>4, 3, 2</b>
<b>4, 3, 2, 2, 1</b>
<b>4, 3, 2, 2</b>
<b>4, 3, 1</b>
<b>4, 3</b>
<b>4, 3, 3, 2, 1</b>
<b>4, 3, 3, 2</b>
<b>4, 3, 3, 2, 2, 1</b>
<b>4, 3, 3, 2, 2</b>
<b>4, 3, 3, 1</b>
<b>4, 3, 3</b>
<b>4, 2, 1</b>
<b>4, 2</b>
<b>4, 2, 2, 1</b>
<b>4, 2, 2</b>
<b>4, 1</b>
<b>4</b>
<b>3, 2, 1</b>
<b>3, 2</b>
<b>3, 2, 2, 1</b>
<b>3, 2, 2</b>
<b>3, 1</b>
<b>3</b>
<b>3, 3, 2, 1</b>
<b>3, 3, 2</b>
<b>3, 3, 2, 2, 1</b>
<b>3, 3, 2, 2</b>
<b>3, 3, 1</b>
<b>3, 3</b>
<b>2, 1</b>
<b>2</b>
<b>2, 2, 1</b>
<b>2, 2</b>
<b>1</b>
<b>Total: 35</b>
</pre>
<hr />
<pre>
<b>Number of blocks:</b>
8
<b>Sizes:</b>
1 2 3 2 3 2 5 2
<b>5, 3, 2, 1</b>
<b>5, 3, 2</b>
<b>5, 3, 2, 2, 1</b>
<b>5, 3, 2, 2</b>
<b>5, 3, 2, 2, 2, 1</b>
<b>5, 3, 2, 2, 2</b>
<b>5, 3, 2, 2, 2, 2, 1</b>
<b>5, 3, 2, 2, 2, 2</b>
<b>5, 3, 1</b>
<b>5, 3</b>
<b>5, 3, 3, 2, 1</b>
<b>5, 3, 3, 2</b>
<b>5, 3, 3, 2, 2, 1</b>
<b>5, 3, 3, 2, 2</b>
<b>5, 3, 3, 2, 2, 2, 1</b>
<b>5, 3, 3, 2, 2, 2</b>
<b>5, 3, 3, 2, 2, 2, 2, 1</b>
<b>5, 3, 3, 2, 2, 2, 2</b>
<b>5, 3, 3, 1</b>
<b>5, 3, 3</b>
<b>5, 2, 1</b>
<b>5, 2</b>
<b>5, 2, 2, 1</b>
<b>5, 2, 2</b>
<b>5, 2, 2, 2, 1</b>
<b>5, 2, 2, 2</b>
<b>5, 2, 2, 2, 2, 1</b>
<b>5, 2, 2, 2, 2</b>
<b>5, 1</b>
<b>5</b>
<b>3, 2, 1</b>
<b>3, 2</b>
<b>3, 2, 2, 1</b>
<b>3, 2, 2</b>
<b>3, 2, 2, 2, 1</b>
<b>3, 2, 2, 2</b>
<b>3, 2, 2, 2, 2, 1</b>
<b>3, 2, 2, 2, 2</b>
<b>3, 1</b>
<b>3</b>
<b>3, 3, 2, 1</b>
<b>3, 3, 2</b>
<b>3, 3, 2, 2, 1</b>
<b>3, 3, 2, 2</b>
<b>3, 3, 2, 2, 2, 1</b>
<b>3, 3, 2, 2, 2</b>
<b>3, 3, 2, 2, 2, 2, 1</b>
<b>3, 3, 2, 2, 2, 2</b>
<b>3, 3, 1</b>
<b>3, 3</b>
<b>2, 1</b>
<b>2</b>
<b>2, 2, 1</b>
<b>2, 2</b>
<b>2, 2, 2, 1</b>
<b>2, 2, 2</b>
<b>2, 2, 2, 2, 1</b>
<b>2, 2, 2, 2</b>
<b>1</b>
<b>Total: 59</b>
</pre>
<hr />
<pre>
<b>Number of blocks:</b>
3
<b>Sizes:</b>
1 2 0
<b>Invalid input.</b>
</pre>
<hr />
<pre>
<b>Number of blocks:</b>
abcd
<b>Invalid input.</b>
</pre>
<hr />


<b>Notes:</b>
<ul>
 <li>The sample runs capture the expected outputs of your program (bold text) and the inputs provided by the user (regular text). Bold formatting is used here on the assignment page to enhance readability. Your program's task is to display text without any formatting (without HTML markup).</li>

 <li>A newline character (\n) follows even after the last line of output (including any error messages).</li>

 <li>The order of towers in the output is not specified. Your program can display the found towers in any order; the testing environment will match results before comparison. Therefore, for example, for input dice sizes of <tt>1 2 3 2 3 4</tt>, the program can output towers like:

<pre>
4, 3, 2, 1
4, 3, 2
4, 3, 2, 2, 1
4, 3, 2, 2
4, 3, 1
4, 3
4, 3, 3, 2, 1
4, 3, 3, 2
4, 3, 3, 2, 2, 1
4, 3, 3, 2, 2
4, 3, 3, 1
4, 3, 3
4, 2, 1
4, 2
4, 2, 2, 1
4, 2, 2
4, 1
4
3, 2, 1
3, 2
3, 2, 2, 1
3, 2, 2
3, 1
3
3, 3, 2, 1
3, 3, 2
3, 3, 2, 2, 1
3, 3, 2, 2
3, 3, 1
3, 3
2, 1
2
2, 2, 1
2, 2
1
</pre>

or

<pre>
3, 2, 1
3, 2
3, 2, 2, 1
3, 2, 2
3, 1
3
3, 3, 2, 1
3, 3, 2
3, 3, 2, 2, 1
3, 3, 2, 2
3, 3, 1
3, 3
2, 1
2
2, 2, 1
2, 2
1
4, 3, 2, 1
4, 3, 2
4, 3, 2, 2, 1
4, 3, 2, 2
4, 3, 1
4, 3
4, 3, 3, 2, 1
4, 3, 3, 2
4, 3, 3, 2, 2, 1
4, 3, 3, 2, 2
4, 3, 3, 1
4, 3, 3
4, 2, 1
4, 2
4, 2, 2, 1
4, 2, 2
4, 1
4
</pre>

or any of the remaining 10333147966386144929666651337523299999998 orders.</li>
</ul>