<h1>Memory Manager</h1>

<td class="lrtbCell" colspan="3" align="left"><p>Your task is to implement a function (or set of functions, not an entire program) that finds <strong>any</strong> message whose hash (<strong>SHA-512</strong>) starts from the left with a sequence of zero bits.</p>
<p>The bit order is big-endian: Byte 0 from MSB to LSB, Byte 1 from MSB to LSB, ..., the last byte from MSB to LSB.</p>
<p>In other words, two zero bits correspond to, for example, byte <code>0010 0111</code> (<code>0x27</code>).</p>
<p>The function is required in two variants:</p>
<ul>
<li>Basic solution (function <code>findHash</code>). Implementation of this function is mandatory.</li>
<li>Enhanced solution (function <code>findHashEx</code>). Implementation of this function is not mandatory, but without a provided "dummy" implementation, the task will not compile. Implement this function if you aim for a bonus.</li>
</ul>
<p>The parameters of the functions you implement are:</p>
<pre>
int findHash(int bits, string &message, string &hash)
</pre>
<ul>
<li><code>bits</code> - the desired number of zero bits in the hash of the message.</li>
<li><code>message</code> - an output parameter. This parameter contains the data for which the corresponding hash was found. The result is stored as a <strong>hexadecimal</strong> string.</li>
<li><code>hash</code> - an output parameter. This is the hash of the <code>message</code> from the previous parameter, again in <strong>hexadecimal</strong> string format.</li>
<li>The return value of the function is <code>1</code> on success, <code>0</code> on failure or incorrect parameters. Typically, this includes an invalid number of requested zero bits.</li>
</ul>
<pre>
int findHashEx(int bits, string &message, string &hash, string_view hashFunction)
</pre>
<ul>
<li>An extension of the <code>findHash</code> function. All parameters and return value remain the same as in the basic variant.</li>
<li><code>hashFunction</code> - a new parameter specifying which hash function should be used to find the sequence of zero bits. The provided hash function name is compatible with the <code>EVP_get_digestbyname</code> function.</li>
</ul>
<p>Submit a source file containing the implementation of the required function <code>findHash</code> or <code>findHashEx</code>. You can add additional supporting functions to your source file, which are called from <code>findHash</code> (or <code>findHashEx</code>). The function will be called from a testing environment, so it is important to strictly adhere to the specified function interface.</p>
<p>Use the provided archive below as a basis for implementation. The sample includes a <code>main</code> test function, and the values given are used during basic testing. Note that header file inclusion and the <code>main</code> function are wrapped in conditional compilation blocks (<code>#ifdef/#endif</code>). Please leave these conditional compilation blocks in your submitted source file. Conditional compilation will simplify your work. You can compile and test the program normally on your computer. During testing on Progtest, the <code>main</code> function and header file inclusion "disappear", thus avoiding conflicts with header files and the <code>main</code> function of the testing environment.</p>
<p>The sample also includes the <code>dumpMatch</code> function, which you will likely need to implement for your local testing. The function is wrapped in a conditional compilation block (=it will not be tested). However, it is advisable to implement it to verify the correctness of your solution.</p>
<hr/>
<p><strong>Notes:</strong></p>
<ul>
<li><strong>WARNING!</strong> Submitting the task on Progtest does not guarantee that it will pass the task requirements! For more information, consult your instructor.</li>
<li>You can use resources from both C and C++ languages for implementation. Only <code>std::vector</code> and <code>std::string</code> from the STL are available for this task.</li>
<li>Do not add additional header files; the current list is more than sufficient. Adding additional header files will result in a compilation error.</li>
<li>A correct solution does not involve precomputing a (sufficiently long) hash and presenting it as a result. Such a solution will not be considered valid. The correct solution should be randomized with each program execution.</li>
<li>During compilation, do not forget to link the OpenSSL crypto library using <code>-lcrypto</code>.</li>
<li>The version of OpenSSL on Progtest is 3.0.11.</li>
</ul></td>