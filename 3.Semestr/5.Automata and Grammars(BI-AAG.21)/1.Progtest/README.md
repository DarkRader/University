<h1>Intersection and Union of Regular Languages</h1>
<p>The task of this graded programming assignment is to implement algorithms that allow you to find the minimal <em>deterministic finite automaton</em> that accepts the intersection or union of languages given by a pair of finite automata. The goal is to implement a set of two functions in C++ with the following signatures:
<ul>
  <li><code>DFA unify(const NFA&, const NFA&);</code> and
  <li><code>DFA intersect(const NFA&, const NFA&);</code>.
</ul></p>
<p>Both of these functions must return the minimal automaton for the given language.</p>
<hr>
<p>The input and output of the algorithms are finite automata in the form of the structures <code>NFA</code> and <code>DFA</code>, respectively. The first structure, <code>NFA</code>, represents a non-deterministic finite automaton (for some transition functions, it can be declared as deterministic). The second structure, <code>DFA</code>, represents only a deterministic finite automaton. These structures are just simple data structures that hold data representing the automaton and do not perform any validity checks on the content. Proper initialization and filling with content are the responsibility of the creator.</p>
<p>These structures are defined in the test environment (do not define them in your task), see the code example in the attached sample file. For simplicity, states are defined as values of type <code>unsigned</code> and alphabet symbols as values of type <code>uint8_t</code>.</p>
<p>It is guaranteed that the inputs to the <code>unify</code> and <code>intersect</code> functions will be valid non-deterministic finite automata. They will meet the following properties:
<ul>
  <li>The sets of states (<code>NFA::m_States</code>) and alphabet symbols (<code>NFA::m_Alphabet</code>) will be non-empty.</li>
  <li>The initial and final states (<code>NFA::m_InitialState</code> and <code>NFA::m_FinalStates</code>, respectively) will be elements of the set of states <code>NFA::m_States</code>.</li>
  <li>If there is no transition defined for a state <code>q</code> and alphabet symbol <code>a</code> in the automaton, then the key <code>(q, a)</code> will not exist at all in <code>NFA::m_Transitions</code>.</li>
  <li>Only symbols and states specified in the set of alphabet symbols and states will appear in the transition table <code>NFA::m_Transitions</code>.</li>
</ul></p>
<p>The comparison of automata with the reference result is done by testing the isomorphism of the transition functions of minimal deterministic finite automata and the sets of final states. Thus, your output may differ from the reference only in the naming of states; otherwise, it will be evaluated as incorrect. The resulting <code>DFA</code> must also meet the conditions of the automaton definition, that is, it must meet the same conditions as mentioned above for <code>NFA</code> (with obvious changes due to the different definitions of the transition function).</p>
<p>If the result is an automaton accepting an empty language, you need to submit a single-state automaton with the unchanged alphabet, an empty set of transitions, and an empty set of final states (see one of the tests in the sample file). It may also happen that both input automata will be over different alphabets. The result should then be an automaton over the union of these alphabets.</p>
<p>Submit a source file containing the implementation of the required functions for the task. Add any other supporting functions or data structures to the source file. The functions will be called from the test environment, so it is important to strictly adhere to the specified function interface. Failure to do so will result in a compilation error. Use the code in the example below as the basis for the implementation. The code lacks the implementations of the two mentioned functions (and any additional supporting functions or data structures). The example includes a test function <code>main</code>; the values used are for basic testing. Note that the inclusion of header files, the definitions of <code>DFA</code> and <code>NFA</code> structures, and the <code>main</code> function are enclosed in conditional compilation blocks (<code>#ifdef/#endif</code>). Keep the definitions of these structures, the include directives, and the <code>main</code> function within conditional compilation blocks in the submitted source file; otherwise, your program will not compile.</p>
<p>Conditional compilation will simplify your work. When compiling on your computer, you can normally run and test the program. However, during compilation on Progtest, everything inside these blocks will "disappear", so it will not collide with the header files, already defined structures, or the <code>main</code> function of the test environment.</p>
<p>For the basis of the implementation, you can use the file available for download below in the Sample Data section. This file also contains some basic tests, but keep in mind that the results of your implementation may differ in state naming. The tests are set according to the results given by one of the reference solutions. You may need to adjust them.</p>
<p>Your program will be run in a restricted test environment. It is limited by runtime (the limit can be seen in the reference solution log) and also by the available memory size.</p>
<hr>
<b>Notes:</b>
<ul>
  <li>The necessary algorithms for this task were covered in lectures and exercises.</li>
  <li>To be minimal, the automaton must meet certain properties.</li>
  <li>Keep in mind that the inputs are various valid automata according to the definition from the lecture. For example, the final state can be only one and in an unreachable part of the automaton (thus, the language of the automaton can be empty), or there may be no final state at all.</li>
  <li>The output of both implemented functions must be a valid automaton. Pay particular attention to the correct initialization of <code>DFA</code> attributes according to the limitations above.</li>
  <li>The time limit is set fairly leniently. It should be sufficient even for a naive implementation of the lecture algorithms. However, not all algorithms are suitable.</li>
  <li>Consider carefully which union algorithm you will implement. Choosing the right one can significantly shorten the implementation of the task.</li>
  <li>The sample data is set according to one of the reference solutions. The state numbering is chosen in the order of visiting the given state by the BFS algorithm started from the initial state of the automaton. The expansion of edges in the transition diagram is done in lexicographic order of the automaton's alphabet, i.e., if expanding state <code>q</code> and there are transitions <code>&#948;(q, b) = p</code> and <code>&#948;(q, a) = r</code>, state <code>r</code> is discovered first.</li>
  <li>The determinization algorithm performed according to the lecture creates an automaton with states that meet certain properties. You can use them to optimize your program.</li>
  <li>The hints displaying automata in a table are written in the format for the <a href="https://alt.fit.cvut.cz/" target="_blank">ALT tool</a>. See the <a href="https://alt.fit.cvut.cz/docs/parse/#finite-automata" target="_blank">documentation of the format</a>.</li>
</ul>
<hr></td>
