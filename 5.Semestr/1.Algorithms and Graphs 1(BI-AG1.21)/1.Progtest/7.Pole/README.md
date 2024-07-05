<h1>Array using AVL Tree</h1>

<td class="lrtbCell" colspan="3" align="left"><p>Your task is to implement the template class <code>Array</code> parameterized by the type of stored elements <code>T</code>. This class has an interface like an array but should maintain elements in an AVL tree structure, achieving fast insertion and deletion at any position at the cost of slightly slower access. The required methods are:</p>
<ul>
<li><code>size()</code>: Returns the number of elements in the array.</li>
<li><code>operator[](i)</code>: Returns the element at position <code>i</code>. For positions out of the range <code>[0, size())</code>, it throws an <code>std::out_of_range</code> exception.</li>
<li><code>insert(i, t)</code>: Inserts element <code>t</code> at position <code>i</code>. Increases the index of elements at position <code>i</code> and higher by 1. For positions out of the range <code>[0, size()]</code>, it throws an <code>std::out_of_range</code> exception.</li>
<li><code>erase(i)</code>: Deletes the element at position <code>i</code>. For positions out of the range <code>[0, size())</code>, it throws an <code>std::out_of_range</code> exception.</li>
</ul>
<p>Copying or moving objects of type <code>Array</code> is not tested. For testing purposes, the following static methods of the <code>Array::TesterInterface</code> class need to be implemented:</p>
<ul>
<li><code>root(array)</code>: Returns a pointer to the root of the tree. (To the node, not to the value stored in it.)</li>
<li><code>parent(n)</code>: Returns a pointer to the parent of node <code>n</code>. For the root, returns <code>nullptr</code>. If your implementation does not have parent pointers and you have <code>config::PARENT_POINTERS</code> set to <code>false</code>, you can delete the method or always return <code>nullptr</code>.</li>
<li><code>right(n)</code>: Returns a pointer to the right child of <code>n</code> or <code>nullptr</code> if it does not exist.</li>
<li><code>left(n)</code>: Returns a pointer to the left child of <code>n</code> or <code>nullptr</code> if it does not exist.</li>
<li><code>value(n)</code>: Returns a <code>const</code> reference to the value stored in node <code>n</code>.</li>
</ul>
<p>For easier development, the following configuration options are available in the template:</p>
<ul>
<li><code>config::CHECK_DEPTH</code>: If <code>true</code>, enables AVL tree shape checking, otherwise only checks that the tree is a valid binary search tree. Progtest ignores this option. Default is <code>false</code>, enable it once you implement balancing.</li>
<li><code>config::PARENT_POINTERS</code>: Specifies whether parent pointers should be tested. Progtest respects this option. Default is <code>true</code>.</li>
</ul>
<p>Note: Testing the structure of the tree is recursive, so certain tests may crash due to stack overflow for unbalanced trees.</p>
<p>There are 5 seconds for tests with a memory debugger, and 6 seconds for others.</p>
<p><em>Hint:</em> We recommend first completing the AVL tree miniprogtest and then basing your implementation on it.</p></td>