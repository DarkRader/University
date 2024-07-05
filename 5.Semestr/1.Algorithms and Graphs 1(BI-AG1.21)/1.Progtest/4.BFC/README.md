<h1>BFS</h1>
<td class="lrtbCell" colspan="3" align="left"><p>Your task is to implement the function
<code>size_t bfs(const Graph&amp; G, Vertex u, std::vector&lt;Vertex&gt;&amp; P, std::vector&lt;size_t&gt;&amp; D)</code>,
which performs breadth-first search (BFS). The arguments are:</p>
<ul>
<li><code>Graph G</code>: The graph you need to search. The description of the
<code>Graph</code> class is below.</li>
<li><code>Vertex u</code>: The vertex from which the search starts.</li>
<li><code>std::vector&lt;Vertex&gt;&amp; P</code>: Array of predecessors. Before
calling the <code>bfs</code> function, it is always initialized to the correct size and filled with the constant <code>NO_VERTEX</code>.</li>
<li><code>std::vector&lt;size_t&gt;&amp; D</code>: Array of distances. Before calling
the <code>bfs</code> function, it is always initialized to the correct size and filled with the constant <code>NO_DISTANCE</code>.</li>
</ul>
<p>The return value is the number of visited vertices, and the arrays <code>P</code> and <code>D</code> must be correctly filled. Set the predecessor of the starting vertex to the constant <code>ROOT</code>. Your implementation should be linear in the size of the visited part of the graph.</p>
<p>The <code>Graph</code> class represents an undirected or directed graph. Important methods are:</p>
<ul>
<li><code>vertices()</code>: The number of vertices.</li>
<li><code>operator[](Vertex v)</code>: The list of neighbors (or successors)
of vertex <code>v</code>. Vertices are integers starting from 0.</li>
<li>Methods <code>begin()</code> and <code>end()</code>, which allow
iteration over the vertices and using the <code>Graph</code> class in a range-for loop like this <code>for (Vertex v : G) ...</code>.</li>
</ul>
<p>The time limits are 5 seconds for the small test and 3.5 seconds for the large one.</p>
</td>
