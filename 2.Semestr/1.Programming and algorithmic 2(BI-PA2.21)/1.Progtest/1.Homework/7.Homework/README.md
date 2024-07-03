<h1>Sequence Indexing</h1>
<td class="lrtbCell" colspan="3" align="left"><p>The task is to create a template class that will implement a generic index.</p>
<p>The implemented class <tt>CIndex</tt> will receive a collection with a sequence of elements as a parameter upon creation. This sequence of elements will be indexed. The sequence can be:</p>
<ul>
 <li><tt>string</tt> - a string of characters (C++ string of elements of type char),</li>
 <li><tt>vector&lt;T&gt;</tt> - a vector of values (of some type T),</li>
 <li><tt>list&lt;T&gt;</tt> - a list of values (of some type T).</li>
</ul>
<p>We want to search the indexed sequence. That is, we provide a sequence of elements (of the same type) and want to determine if the indexed sequence contains it somewhere. The result will be a set of positions where the searched sequence is found.</p>
<p>To make the indexing class more general, it is further enhanced by the option to provide a custom comparator (an optional second generic parameter). Thus, the search does not have to be an exact match; using a custom comparator, we can specify, for example, that case is not distinguished when comparing. The comparator will have the same form as comparators in STL: it will be a function, functor, or C++11 lambda expression that determines which of the pair of elements of type T in the sequence is smaller in the desired comparison. If the comparator is not provided, the < operator valid for stored element values is used for comparing elements.</p>
<p>The elements in the sequences themselves (elements of type T) can be arbitrary. Examples include a character (char), an integer (int), or a string (string). Generally, you know that the following operations are defined for type T:</p>
<ul>
 <li>copying (with the = operator and copy constructor),</li>
 <li>comparing "less than" with the < operator or provided comparator,</li>
 <li>releasing (destructor),</li>
 <li>other operations may or may not be available with type T, so your implementation generally cannot rely on them. Note, there may not be a default constructor, == operator, != operator, etc.</li>
</ul>
<p>Submit a file containing the implemented template class <tt>CIndex</tt> and your other supporting classes. The class must meet the public interface according to the sample - if your submitted solution does not contain the described interface, it will result in a compilation error. However, you can add additional methods (public or private) and member variables to the class. The submitted file must contain both the class declaration (interface description) and the definitions of methods, constructor, and destructor. It does not matter whether the methods are implemented inline or separately. The submitted file must not contain header file inclusions and the <tt>main</tt> function. The <tt>main</tt> function and header file inclusions may remain but must be enclosed in conditional compilation directives as in the sample below.</p>
<p>Use STL to solve the task. You can use most constructions up to C++17 inclusive.</p>
<p>The task includes mandatory and bonus tests. A solution that searches for occurrences with a naive algorithm will pass the basic test. To earn bonuses, more efficient algorithms need to be implemented. In the design, you can assume:</p>
<ul>
 <li>A once-indexed sequence is searched multiple times. Therefore, it makes sense to invest time in preprocessing, which shortens the actual search. You can assume that the <tt>search</tt> method is called on average 100 times per instance.</li>
 <li>The general implementation with a generic element type and a general comparator is tested in the mandatory tests. Performance tests work with the <tt>string</tt> data type and use the default comparator. Partial specialization of the class template for such limited inputs can significantly speed up the computation.</li>
 <li>For speeding up the search, the KMP algorithm is useful, and for indexing, a suffix array or DAWG can be utilized.</li>
</ul>
<p>A sample usage of the class can be found in the attached file.</p>
<p>The solution to this task cannot be used for code review.</p>
</td> 
