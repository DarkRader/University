<h1>Best-selling Products</h1>
<td class="lrtbCell" colspan="3" align="left"><p>The task is to create a program that will process completed purchases and analyze product sales.</p>
<p>We assume that we are recording individual product sales. We are mainly interested in the products that sell the most. Therefore, the program will be able to calculate the N types of products that have sold the most units. The value of N (the number of types of products that sell the most) will be given as the first input to the program.</p>
<p>Products are identified by their name - a string. The name must be at most 99 characters long and must not contain white spaces. The program learns about the sale of a product through the input <tt>+ product-name</tt>. The input may also contain commands that can display sales analysis. Specifically:</p>
<ul>
 <li>The command # displays an overview of the N types of products that have sold the most units so far. The output will be in the format shown in the example below, with each type of product showing the name and the number of units sold. The total sum (the sum of the units sold for the displayed top-selling products) will also be displayed.</li>
 <li>The command ? displays only the total sum.</li>
</ul>
<p>The program operation becomes a bit more complicated for inputs where the same number of units have been sold for two or more different types of products:</p>
<ul>
 <li>A simpler situation is shown in the first example. The output shows 4 units sold for eggs and flour. Therefore, these products are tied for 2nd to 3rd place in the output, and the format of the output reflects this. The exact order in the output is not specified. The testing environment therefore accepts both (all) possibilities, so specifically here both of the following would be correct:
   <pre>
   1. Milk, 5x
   2.-3. Eggs, 4x
   2.-3. Flour, 4x
   4. Beer, 3x
   </pre>
   and:
   <pre>
   1. Milk, 5x
   2.-3. Flour, 4x
   2.-3. Eggs, 4x
   4. Beer, 3x
   </pre></li>
 <li>A more complicated situation is shown in the second example. It was specified that N=3 top-selling types of products should be tracked, but it is clear that the displayed list is sometimes longer, for example in the output:
   <pre>
   1.-4. Black_tea, 1x
   1.-4. Caffeine, 1x
   1.-4. C/C++_for_dummies, 1x
   1.-4. Introduction_to_Algorithms, 1x
   </pre>
   <pre>
   1.-2. Black_tea, 2x
   1.-2. Caffeine, 2x
   3.-5. C/C++_for_dummies, 1x
   3.-5. Energy_drink, 1x
   3.-5. Introduction_to_Algorithms, 1x
   </pre>
</ul>
<p>If the input is invalid, the program must detect it and display an error message. Display the error message to the standard output (not to the error output). Consider an error if:</p>
<ul>
 <li>The number of tracked types of products N is invalid (not an integer, zero or negative),</li>
 <li>No known command (+, ?, #) is entered,</li>
 <li>The product name is invalid (missing, 100 or more characters long).</li>
</ul>
<hr />
<pre>
<b>Number of tracked:</b>
4
<b>Requests:</b>
+ Fruits
+ Milk
+ Milk
+ Sugar
+ Butter
+ Beer
+ Vegetables
+ Milk
+ Beer
+ Milk
+ Beer
+ Sugar
+ Eggs
+ Milk
+ Eggs
+ Eggs
+ Eggs
#
<b>1. Milk, 5x</b>
<b>2. Eggs, 4x</b>
<b>3. Beer, 3x</b>
<b>4. Sugar, 2x</b>
<b>Top-selling products: sold 14 units</b>
+ Flour
+ Flour
+ Flour
+ Flour
#
<b>1. Milk, 5x</b>
<b>2.-3. Eggs, 4x</b>
<b>2.-3. Flour, 4x</b>
<b>4. Beer, 3x</b>
<b>Top-selling products: sold 16 units</b>
+ Flour
?
<b>Top-selling products: sold 17 units</b>
+ Flour
#
<b>1. Flour, 6x</b>
<b>2. Milk, 5x</b>
<b>3. Eggs, 4x</b>
<b>4. Beer, 3x</b>
<b>Top-selling products: sold 18 units</b>
</pre>
<hr />
<pre>
<b>Number of tracked:</b>
3
<b>Requests:</b>
+ Introduction_to_Algorithms
+ Black_tea
#
<b>1.-2. Black_tea, 1x</b>
<b>1.-2. Introduction_to_Algorithms, 1x</b>
<b>Top-selling products: sold 2 units</b>
+ Caffeine
?
<b>Top-selling products: sold 3 units</b>
+ C/C++_for_dummies
#
<b>1.-4. Black_tea, 1x</b>
<b>1.-4. Caffeine, 1x</b>
<b>1.-4. C/C++_for_dummies, 1x</b>
<b>1.-4. Introduction_to_Algorithms, 1x</b>
<b>Top-selling products: sold 4 units</b>
+ Black_tea
#
<b>1. Black_tea, 2x</b>
<b>2.-4. Caffeine, 1x</b>
<b>2.-4. C/C++_for_dummies, 1x</b>
<b>2.-4. Introduction_to_Algorithms, 1x</b>
<b>Top-selling products: sold 5 units</b>
+ Energy_drink
+ Caffeine
#
<b>1.-2. Black_tea, 2x</b>
<b>1.-2. Caffeine, 2x</b>
<b>3.-5. C/C++_for_dummies, 1x</b>
<b>3.-5. Energy_drink, 1x</b>
<b>3.-5. Introduction_to_Algorithms, 1x</b>
<b>Top-selling products: sold 7 units</b>
?
<b>Top-selling products: sold 7 units</b>
+ Energy_drink
?
<b>Top-selling products: sold 6 units</b>
+ Energy_drink
?
<b>Top-selling products: sold 7 units</b>
+ Caffeine
?
<b>Top-selling products: sold 8 units</b>
+ Energy_drink
+ Energy_drink
#
<b>1. Energy_drink, 5x</b>
<b>2. Caffeine, 3x</b>
<b>3. Black_tea, 2x</b>
<b>Top-selling products: sold 10 units</b>
+ C/C++_for_dummies
#
<b>1. Energy_drink, 5x</b>
<b>2. Caffeine, 3x</b>
<b>3.-4. C/C++_for_dummies, 2x</b>
<b>3.-4. Black_tea, 2x</b>
<b>Top-selling products: sold 12 units</b>
</pre>
<hr />
<pre>
<b>Number of tracked:</b>
3
<b>Requests:</b>
* Avoiding_invalid_input_3-rd_edition
<b>Invalid input.</b>
</pre>
<hr />
<b>Notes:</b>
<ul>
 <li>The example runs capture the expected outputs of your program (in bold) and user inputs (in plain text). Bold text is used here on the assignment page for clarity. Your program should simply display the text without bold formatting (without HTML markup).</li>
 <li>The newline character (\n) is also after the last line of output (including any error messages).</li>
 <li>The number of types of products and the length of the input is not explicitly limited. For storing input / storing individual types of products, static allocation cannot be used.</li>
 <li>The product name length is limited to 99 characters. Thus, the name itself can (and should) be stored in a statically allocated character array.</li>    
 <li>To represent a product, it is appropriate to use structures combining, for example, the product name and the number of units sold.</li>
  <li>The submitted program is tested with multiple tests of increasing difficulty. First, the correctness 
     of the solution is checked, then the correctness of array handling and dynamic memory allocation is checked 
     (tested with a memory debugger), and finally the efficiency of the solution is evaluated.</li>
 <li>A basic solution does not need to be efficient; a naive algorithm is sufficient. Such a solution will pass the required 
     tests and some optional tests. It will be graded with a maximum of 100% points.</li>
 <li>The first bonus test checks the efficiency of the submitted program. Long inputs 
     with many different product types are given. At the same time, the value of N will be relatively low. A naive algorithm is not 
     efficient enough and will not be able to complete the calculation within the set time limit.</li>
 <li>The second bonus test further checks the efficiency of the used algorithm. Long inputs with many different product types 
     are given. Additionally, a high value of N is specified. You can assume that the input will contain 
     many + and ? commands, but significantly fewer # commands (long outputs would significantly slow down the calculation).</li>
 <li>A program that passes all required and optional tests with 100% can be used for code review. 
     (For code review, it is not necessary to pass the bonus tests).</li>
 <li>Use C language constructs to solve the task. Do not use data structures from C++ - they are not allowed.</li>
</ul>

