<h1>AVL Tree</h1>

<td class="lrtbCell" colspan="3" align="left"><p>Your task is to implement the template class <code>Tree</code> parameterized by the type of stored elements <code>T</code>. This class should maintain elements in an AVL tree structure according to the <code>std::less&lt;T&gt;</code> ordering (or the <code>&lt;</code> operator). The required methods are:</p>
<ul>
<li><code>size()</code>: Returns the number of elements in the tree.</li>
<li><code>find(t)</code>: Finds the element <code>t</code> in the tree and returns a <code>const</code> pointer to it, or <code>nullptr</code> if the element is not in the tree.</li>
<li><code>insert(t)</code>: Attempts to insert <code>t</code>. Returns whether the insertion was successful. Insertion fails if the tree already contains an element with the same value.</li>
<li><code>erase(t)</code>: Deletes the element <code>t</code> if <code>t</code> is in the tree. Returns whether the element was deleted.</li>
</ul>
<p>Copying or moving objects of type <code>Tree</code> is not tested. For testing purposes, the following static methods of the <code>Tree::TesterInterface</code> class need to be implemented:</p>
<ul>
<li><code>root(tree)</code>: Returns a pointer to the root of the tree. (To the node, not to the value stored in it.)</li>
<li><code>parent(n)</code>: Returns a pointer to the parent of node <code>n</code>. For the root, returns <code>nullptr</code>. If your implementation does not have parent pointers and you have <code>config::PARENT_POINTERS</code> set to <code>false</code>, you can delete the method or always return <code>nullptr</code>.</li>
<li><code>right(n)</code>: Returns a pointer to the right child of <code>n</code> or <code>nullptr</code> if it does not exist.</li>
<li><code>left(n)</code>: Returns a pointer to the left child of <code>n</code> or <code>nullptr</code> if it does not exist.</li>
<li><code>value(n)</code>: Returns a <code>const</code> reference to the value stored in node <code>n</code>.</li>
</ul>
<p>For easier development, the following configuration options are available in the template:</p>
<ul>
<li><code>config::CHECK_DEPTH</code>: If <code>true</code>, enables AVL tree shape checking, otherwise only checks that the tree is a valid binary search tree. Progtest ignores this option. Default is <code>false</code>, enable it once you implement balancing.</li>
<li><code>config::PARENT_POINTERS</code>: Specifies whether parent pointers should be tested. Progtest respects this option at the cost of a slight point penalty if parent pointers are not implemented. Default is <code>true</code>.</li>
</ul>
<p>Note: Testing the structure of the tree is recursive, so certain tests may crash due to stack overflow for unbalanced trees.</p>
<p>There are 5 seconds for tests with a memory debugger, and 3 seconds for others.</p>
</td> 