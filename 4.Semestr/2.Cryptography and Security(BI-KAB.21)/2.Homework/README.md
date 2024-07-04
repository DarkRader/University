<h1>File Encryption</h1>

<td class="lrtbCell" colspan="3" align="left"><p>Your task is to implement two (or more) functions (not an entire program) that can encrypt and decrypt an image file in <a href="http://www.paulbourke.net/dataformats/tga/">TGA format</a>.</p>
<p>For our task, we will consider a simplified form of the image:</p>
<ul>
<li>Mandatory header: 18 bytes - these bytes are not modified; they are simply copied into the encrypted image.</li>
<li>Optional header part: its size is calculated from the mandatory part of the header - we consider this part of the header as image data, so we <strong>encrypt it together</strong> with the image data.</li>
<li>Image data: the remainder of the file.</li>
</ul>
<p>The parameters of the functions you implement are:</p>
<pre>
bool encrypt_data(const string &in_filename, const string &out_filename, crypto_config &config)
</pre>
<ul>
<li><code>in_filename</code> - input file name,</li>
<li><code>out_filename</code> - output file name,</li>
<li><code>config</code> - data structure <code>crypto_config</code> described below.</li>
<li>The return value is <code>true</code> on success, <code>false</code> otherwise. Failure occurs if the file is invalid in any way (missing mandatory header, unable to open, read, write, etc.) or if an invalid <code>crypto_config</code> is provided.</li>
</ul>
<p>The function <code>decrypt_data</code> uses the same interface but performs the inverse operation compared to encryption. It copies the mandatory part of the header (which is <strong>not</strong> encrypted) and then decrypts the rest of the file in the same manner as encryption. However, it expects valid decryption key and IV parameters. If these parameters are not provided, data cannot be decrypted, and the function should return an error (<code>false</code>).</p>
<p>The <code>crypto_config</code> data structure includes:</p>
<ul>
<li>chosen block cipher specified by its name,</li>
<li>secret encryption key and its size,</li>
<li>initialization vector (IV) and its size.</li>
</ul>
<p>During encryption, the following problem may occur: if the encryption key (or IV) is insufficient (i.e., its length is not at least as required by the chosen block cipher or is completely missing), they must be securely generated. If the chosen block cipher does not require an IV (and therefore it is not passed to you), do not generate a new IV! Remember to store any generated keys and IV in the provided config structure!</p>
<hr/>
<p>The following encryption functions will be useful:</p>
<ul>
<li><code>EVP_EncryptInit_ex</code> or <code>EVP_DecryptInit_ex</code>,</li>
<li><code>EVP_EncryptUpdate</code> or <code>EVP_DecryptUpdate</code>,</li>
<li><code>EVP_EncryptFinal_ex</code> or <code>EVP_DecryptFinal_ex</code>.</li>
</ul>
<p>Refer to the openssl documentation for additional functions you may (and should) use. Hint: Is there a more general function that encapsulates these functions?</p>
<p>By default, block ciphers have padding enabled, so the length of the resulting encrypted file may be larger than the original. This behavior is desired (and expected in tests) and <strong>should not</strong> be changed.</p>
<hr/>
<p>In the testing environment, you will be limited not only by time but also by the size of available memory; your program may be forcibly terminated. Therefore, try not to unnecessarily use the heap, or ideally, avoid using it at all. In 90% of cases, you can manage with just the stack.</p>
<p>Submit a source file containing the implementation of the required functions <code>encrypt_data</code> and <code>decrypt_data</code>. You can add additional supporting functions to your source file, which are called from <code>encrypt_data</code> and <code>decrypt_data</code>. The function will be called from a testing environment, so it is important to strictly adhere to the specified function interface.</p>
<p>Use the provided archive as a basis for implementation below. The sample includes a <code>main</code> test function, and the values given are used during basic testing. Note that header file inclusion and the <code>main</code> function are wrapped in conditional compilation blocks (<code>#ifdef/#endif</code>). Please leave these conditional compilation blocks in your submitted source file. Conditional compilation will simplify your work. You can compile and test the program normally on your computer. During testing on Progtest, the <code>main</code> function and header file inclusion "disappear," thus avoiding conflicts with header files and the <code>main</code> function of the testing environment.</p>
<hr/>
<p><strong>Notes:</strong></p>
<ul>
<li><strong>WARNING!</strong> Submitting the task on Progtest does not guarantee that it will pass the task requirements! For more information, consult your instructor.</li>
<li>Handle file operations carefully. The testing environment deliberately tests your implementation with non-existent files, unreadable files, or files with incorrect data content.</li>
<li>You can use both C and C++ interfaces for file operations; the choice is yours. Similarly, you can use STL structures.</li>
<li>The task description includes runtime examples. The provided archive contains a set of test files and their equivalents encrypted with some block cipher.</li>
<li>Input and output files can be large, larger than the available memory size. Therefore, when working with files, we try to process data incrementally. It is not reasonable to load the entire input file into memory and then process it entirely in memory. The last test checks the memory requirements of your solution. It will fail if you attempt to keep entire files or large portions of them in memory at once.</li>
<li>Even if some subfunction fails, you must correctly handle dynamically allocated resources.</li>
<li>The encryption key and IV are generally "some" data; therefore, treating them as ASCII strings is a path to disaster (see exercise).</li>
<li>Encryption itself is deterministic, but key generation should not be. The testing environment verifies the correctness of the encryption function by attempting to decrypt the file you encrypted and comparing the result with the original file (binary match).</li>
<li>For easier implementation, the <code>crypto_config</code> structure includes smart pointers (<code>std::unique_ptr</code>); use <code>std::make_unique</code> to create them. If you need to pass a raw pointer somewhere, use the class method <code>get()</code>.</li>
</ul></td>