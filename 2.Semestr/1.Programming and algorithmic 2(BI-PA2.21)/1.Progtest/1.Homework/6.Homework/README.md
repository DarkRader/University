<h1>Data Types</h1>
<td class="lrtbCell" colspan="3" align="left"><p>The task is to implement a set of classes that will describe certain data types in C/C++.</p>
<p>During compilation, the compiler must keep track of the properties of data types. Some data types are built into the compiler (e.g., int, double), while others can be defined by the programmer in their program (derived types: e.g., enum, struct). The set of implemented classes should capture the description of such types. Specifically, we want to describe only certain types (int, double, enum, and struct), and only for certain operations.</p>
<p>It is expected that you implement the following classes with the following interfaces:</p>
<h2>CDataTypeInt</h2>
<p>This class represents the primitive type <tt>int</tt>. It has the following interface:</p>
<dl>
  <dt>default constructor</dt><dd>initializes an instance of the class,</dd>
  <dt>getSize()</dt><dd>method returns the size of the type, always 4 in this case,</dd>
  <dt>operator ==</dt><dd>compares this type with another type, returns true if both types are the same (both are int types),</dd>
  <dt>operator !=</dt><dd>compares this type with another type, returns true if the types are different,</dd>
  <dt>operator &lt;&lt;</dt><dd>outputs the name of the type to the given stream.</dd>
</dl>
<h2>CDataTypeDouble</h2>
<p>This class represents the primitive type <tt>double</tt>. It has the following interface:</p>
<dl>
  <dt>default constructor</dt><dd>initializes an instance of the class,</dd>
  <dt>getSize()</dt><dd>method returns the size of the type, always 8 in this case,</dd>
  <dt>operator ==</dt><dd>compares this type with another type, returns true if both types are the same (both are double types),</dd>
  <dt>operator !=</dt><dd>compares this type with another type, returns true if the types are different,</dd>
  <dt>operator &lt;&lt;</dt><dd>outputs the name of the type to the given stream.</dd>
</dl>
<h2>CDataTypeEnum</h2>
<p>This class represents an enumerated type. It has the following interface:</p>
<dl>
  <dt>default constructor</dt><dd>initializes an instance of the class,</dd>
  <dt>getSize()</dt><dd>method returns the size of the type, always 4 in this case,</dd>
  <dt>add()</dt><dd>method adds another value to the enumeration. If the same value already exists in the enumeration, an exception is thrown (see sample run),</dd>
  <dt>operator ==</dt><dd>compares this type with another type, returns true if both types are the same (both are enum types and have the same set of values in the same order),</dd>
  <dt>operator !=</dt><dd>compares this type with another type, returns true if the types are different,</dd>
  <dt>operator &lt;&lt;</dt><dd>outputs the name of the type to the given stream. Note, the values of the enumeration must be displayed in the order they were added.</dd>
</dl>
<h2>CDataTypeStruct</h2>
<p>This class represents a structure type. It has the following interface:</p>
<dl>
  <dt>default constructor</dt><dd>initializes an instance of the class,</dd>
  <dt>getSize()</dt><dd>method returns the size of the type (based on the contained fields),</dd>
  <dt>addField(name, type)</dt><dd>method adds another field with the given name and type (int/double/enum) to the end of the field list. If the field name is duplicated, an exception is thrown (see sample run),</dd>
  <dt>field(name)</dt><dd>accesses the field with the given name, or throws an exception if a field with such a name does not exist (see sample run). The field accessed by this method will be read-only,</dd>
  <dt>operator ==</dt><dd>compares this type with another type, returns true if both types are the same (both types are structs, have the same number of fields, and the fields at each position have the same type, but the names of the fields can differ),</dd>
  <dt>operator !=</dt><dd>compares this type with another type, returns true if the types are different,</dd>
  <dt>operator &lt;&lt;</dt><dd>outputs the name of the type to the given stream. The order of the fields corresponds to the order they were added using the <tt>addField</tt> method.</dd>
</dl>
<p>Submit the source code with the implementation of the classes <tt>CDataTypeInt</tt>, <tt>CDataTypeDouble</tt>, <tt>CDataTypeEnum</tt>, and <tt>CDataTypeStruct</tt>. The classes must implement the interfaces described above. However, you can add additional methods to the classes to simplify the implementation.</p>
<p>Notes:</p>
<ul>
 <li>In the implementation, you can use STL and the C++ string type. The basis of the implementation, however, is a good class design and the use of polymorphism. Your solution will not be accepted if it does not use polymorphism.</li>
 <li>When comparing type representations (outputs of the &lt;&lt; operator), white spaces are not checked.
  For testing, you will implement a function <tt>whitespaceMatch</tt>) in the sample usage, which compares strings regardless of white spaces.</li>
 <li>For the return value of the <tt>getSize</tt> method, use the type <tt>size_t</tt>.</li>  
 <li>A sample usage of the classes is included in the attached archive.</li>
 <li>The solution to this task <b>cannot</b> be used for code review. (The correct solution to the follow-up task - Data Types II - can be used for code review.)</li>
 <li><b>Addendum 9.4.2022:</b> if the method's input parameter is a string, allow the use of both C-strings (<tt>const char *</tt>) and C++ strings (<tt>std::string</tt>).</li>
</ul> 
</td> 
