<h1>Christmas Gifts</h1>
<td class="lrtbCell" colspan="3" align="left"><p>And I forgot to tell you last time. The Whos love Christmas so much that they have a decorated Christmas tree at home all year round. In the toy store, they have not only summer Christmas but also autumn and spring Christmas. Our green alien can’t compare. And last but not least, it should be mentioned that the street system in Whoville forms a tree. Not very practical, but nobody here minds.</p>
<p>What is little known, even among the Whos, is that this small village has its own secret services. The unit is called the Grinch Resistance Unit (GRU), and its main task is, of course, to protect Whoville and Christmas from the malice of this universally hated creature.</p>
<p>As soon as the secret agents intercepted the first signs of what the Grinch was planning, the Whoville Security Council convened. They began preparing countermeasures. We do not know all the steps they prepared, but I can tell you about one that directly concerns you.</p>
<p>Due to the Mayor being the owner of the only toy store in Whoville and thanks to the newly established Advent Market Records (AET), the Mayor has complete oversight of who bought what, where, and when. Thus, he also knows what can be expected under which Christmas tree on Christmas night.</p>
<p>Since you proved yourselves in preparing the Bestselling Products, the Mayor decided to enlist your help for this task as well. Your task is to find the deployment of secret agents in the streets of the city to protect as many gifts as possible. According to ancient customs, gifts always appear under the trees located at intersections and squares so that the Whos can immediately share the joy of gifts with others.</p>
<p>But be careful! Under no circumstances should the Whos notice the agents in the streets. If panic were to break out among the residents on Christmas Eve, the Mayor might not be able to handle it. Therefore, make sure that large groups of agents do not appear close to each other in the streets. Agents are considered the same group if there is no unguarded tree between them.</p>
<h2 id="program-interface">Program Interface</h2>
<p>Your task is to implement the function <code>uint64_t solve(const TreeProblem&amp;)</code>, which calculates how many gifts can be protected with the optimal deployment of guards. The problem instance is described by the <code>TreeProblem</code> structure, which contains the following fields:</p>
<ul>
<li><p><code>max_group_size</code>: The maximum size of a group of guards. This value is 2 in the bonus test case and 1 otherwise.</p></li>
<li><p><code>gifts</code>: A vector indicating how many gifts are under each tree. The length of this vector also indicates the total number of trees.</p></li>
<li><p><code>connections</code>: A vector of pairs indicating which trees are at the opposite ends of the same street, so if both are guarded, their guards belong to the same group. We remind you that the street network of Whoville forms a tree.</p></li>
</ul>
<h2 id="scoring-conditions">Scoring Conditions</h2>
<ul>
<li><p>To earn 3 points, you need an implementation that works on small inputs with <code>max_group_size = 1</code>.</p></li>
<li><p>To earn 6 points, a naive exponential implementation is not sufficient.</p></li>
<li><p>To earn 10 points, the implementation must be efficient, the inputs are large, and the stack size is limited to 1 MiB.</p></li>
<li><p><strong>Bonus:</strong> To earn 13 points, you need to correctly handle instances with <code>max_group_size = 2</code> similar in size to the previous point.</p></li>
</ul></td>
