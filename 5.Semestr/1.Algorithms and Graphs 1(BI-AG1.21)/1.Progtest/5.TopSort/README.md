<h1>TopSort</h1>

<td class="lrtbCell" colspan="3" align="left"><p>Your task is to implement the function
<code>std::pair&lt;bool, std::vector&lt;Vertex&gt;&gt; topsort(const Graph&amp; G)</code>.
The return value should be either:</p>
<ul>
<li><code>true</code> and a list of all vertices in topological order, or</li>
<li><code>false</code> and a list of vertices forming a cycle (there must also be an edge from the last to the first vertex in the list).</li>
</ul>
<p>The <code>Graph</code> class represents a directed graph. Important methods are:</p>
<ul>
<li><code>vertices()</code>: The number of vertices.</li>
<li><code>operator[](Vertex v)</code>: The list of neighbors of vertex
<code>v</code>. Vertices are integers starting from 0.</li>
<li>Methods <code>begin()</code> and <code>end()</code>, which allow
iteration over the vertices and using the <code>Graph</code> class in a range-for loop like this <code>for (Vertex v : G) ...</code>.</li>
<li><code>reversed()</code>: Returns a new graph obtained by reversing the direction of all edges.</li>
</ul>
<p>The time limits are 5 seconds for the small test and 3 seconds for the large one.</p></td>