<h1>Text Editor</h1>

<td class="lrtbCell" colspan="3" align="left"><p>Long ago, in a galaxy far, far away, there lived on planet Earth two utterly irreconcilable tribes of users. Each tribe worshipped one of two very powerful text editors as their god: Vim and Emacs. One of the most important activities (and some say the only activity) of these users was to engage in passionate online discussions about which editor was better. Each claimed that their editor was the best and that the other should be banned by the authorities for its inefficiency.</p>
<p>However, in a small corner of this planet, a young and promising programmer named Elon was born, whose thoughts were different from the others. He saw the relentless battle between Vim and Emacs as a waste of time and energy. He was convinced it would be much better if the best features of both editors were combined into one versatile tool.</p>
<p>So Elon began working on a project that would bring unity between Vim and Emacs users. He decided to create an amazing text editor that would combine the power of Vim's shortcuts with the flexibility of Emacs' extensions. But that wasn't all. Elon wanted his editor to be so revolutionary that it would excite not only advanced text editor users but the entire planet, including so-called BFU. Therefore, he decided to combine two more important features of each editor: from Emacs' environment, he incorporated the principle "a good operating system, but a bad editor," and from Vim, he brought into the new editor the impossibility of quitting the editor.</p>
<p>Elon, who enjoyed efficiency, decided to name his editor χ. χ was to become a symbol of unity, progress, freedom, and peace on Earth. From then on, programmers lived in harmony, everyone could use χ as they wished, and no one argued about Vim versus Emacs anymore. They were happy and created amazing programs and projects together because χ allowed them to reach their maximum creative potential.</p>
<p><br></p>
<p>Do you really believe something like that could happen? No way, it's just a fairy tale. In reality, Elon isn't much of a programmer himself; he's better at impulsive decision-making, crisis management, and marketing. Therefore, he asked you to help him with programming the editor. In exchange for your 120 hours of work per week, he promises that once χ is released to the world, you will be listed as the second author.</p>
<h2 id="program-interface">Program Interface</h2>
<p>Your task is to implement the class <code>TextEditorBackend</code>, which represents the backend of the text editor. The required interface:</p>
<ul>
<li><p><code>TextEditorBackend(const std::string&amp; text)</code>: Constructor that initializes the editor's content with the given text.</p></li>
<li><p><code>size_t size() const</code>: Number of characters in the text, including newlines.</p></li>
<li><p><code>size_t lines() const</code>: Number of lines. An empty text has one line. Each <code>\n</code> character adds a line.</p></li>
<li><p><code>char at(size_t i) const</code>: Returns the <code>i</code>-th character. Allowed range is <code>[0, size())</code>.</p></li>
<li><p><code>void edit(size_t i, char c)</code>: Replaces the character at position <code>i</code> with the character <code>c</code>. Allowed range is <code>[0, size())</code>.</p></li>
<li><p><code>void insert(size_t i, char c)</code>: Inserts the character <code>c</code> before the character at position <code>i</code>. Allowed range is <code>[0, size()]</code>.</p></li>
<li><p><code>void erase(size_t i)</code>: Deletes the character at position <code>i</code>. Allowed range is <code>[0, size())</code>.</p></li>
<li><p><code>size_t line_start(size_t r) const</code>: Returns the start of the <code>r</code>-th line. The <code>\n</code> character is part of the line it ends. Allowed range is <code>[0, lines())</code>.</p></li>
<li><p><code>size_t line_length(size_t r) const</code>: Returns the length of the <code>i</code>-th line, including any <code>\n</code> character at the end. Allowed range is <code>[0, lines())</code>.</p></li>
<li><p><code>size_t char_to_line(size_t i) const</code>: Returns the line number on which the <code>i</code>-th character is located. Allowed range is <code>[0, size())</code>.</p></li>
</ul>
<p>If a method is called with an out-of-range argument, it must throw an <code>std::out_of_range</code> exception. The methods <code>size</code> and <code>lines</code> should have constant complexity. The other methods should have logarithmic complexity. The constructor should not be slower than repeatedly calling the <code>insert</code> method.</p>
<h2 id="scoring-conditions">Scoring Conditions</h2>
<ul>
<li>For 1 point, the interface must be correctly implemented, but the time complexity of the methods (almost) doesn't matter. (The time limit is 15 seconds.)</li>
<li>For 5 points, a naive implementation is not sufficient, but operations are still performed randomly. Thus, the testing environment does not try to unbalance your editor. (The time limit is 1 second.)</li>
<li>For 10 points, the interface must be correctly implemented with the specified or better complexities. (The time limit is 10 seconds.)</li>
</ul>
</td>