<h1>Bestselling Products</h1>
<td class="lrtbCell" colspan="3" align="left"><p>I have traveled almost the entire world, and I can confidently say that there is no nation that enjoys Christmas as much as these Whos. From what I have seen of the Whos, I realized that it is not merely the prospect of presents, frolicking in snowdrifts, and spending time with family and friends. What the Whos feel about Christmas comes from the depths of their hearts and I wouldn't hesitate to call it an animistic desire or instinctual need for a happy and undisturbed Christmas.</p>
<p>At least, for most of them. As in any other group, there are exceptions among the Whos. And I don't mean the Grinch. I am thinking of someone even worse. What could be worse than someone who, out of their own fear and sense of injustice, wants to steal Christmas from this little nation, you ask? Well, someone who exploits these basest human instincts, fuels fear and uncertainty, and offers simple solutions to everything. And all of this with one goal – to make as much profit as possible. Yes, dear readers, you guessed it right. None other than the esteemed Mayor!</p>
<p>Given how naive the Whos are, it’s no surprise that the Mayor has been in power for several consecutive terms. Each time with more than 99% of the votes. Those of us who have been around for a while also won't be surprised to learn that, in reality, the Mayor's concern for the village is merely a side interest. The Mayor owns the largest (and also the only, to be honest) toy store in Whoville. A colossal conflict of interest, one might say! But it leaves us indifferent.</p>
<p>As the saying goes, "appetite comes with eating," and the Mayor is never satisfied. Last year, he launched an initiative called Bestselling Products. It involved massive digitization of all purchases and analysis of product sales. Based on the huge success, which increased the Mayor’s profits tenfold, he plans to continue with the digitization this year and take it to an even higher level. Ladies and gentlemen, welcome to Bestselling Products II, an even more monstrous initiative aimed at thoroughly emptying the wallets of the Whos. Some say that this initiative will not only drain their savings but might also steal a small piece of each Who's soul.</p>
<p>And how do you fit into all of this? After all, you are the good guys, and you wouldn't dirty your hands with such villainy. The truth is, however, that no one other than the city administration and the Mayor’s toy store will give you a contract. Moreover, you proved yourselves last year. Therefore, this year too, the implementation of Bestselling Products is up to you.</p>
<h2 id="program-interface">Program Interface</h2>
<p>Your task is to implement the <code>Bestsellers</code> class template
parametrized by the <code>Product</code> type, which serves as an identifier
for individual products. It is promised that the <code>Product</code> type
has a copy constructor (and assignment operator), destructor, comparison operators,
and <code>std::hash</code> implemented. The <code>Bestsellers</code> class
must implement the following public methods:</p>
<ul>
<li><p><code>size_t products() const</code> returning the number of distinct
products recorded (i.e., <strong>not</strong> the number of items sold),</p></li>
<li><p><code>void sell(const Product&amp; p, size_t amount)</code>,
which records the sale of <code>amount</code> units of the product
<code>p</code>,</p></li>
<li><p><code>size_t rank(const Product&amp; p) const</code>, which
returns the sales rank of the given product, numbered from 1 (if multiple
products have the same sales, you can order them arbitrarily),</p></li>
<li><p><code>const Product&amp; product(size_t rank) const</code>,
an inverse function to <code>rank</code> (i.e., if no exception occurs, it
always holds that <code>product(rank(p)) == p</code> and
<code>rank(product(r)) == r</code>),</p></li>
<li><p><code>size_t sold(size_t r) const</code>, the number of units sold
for the <code>r</code>-th bestselling product,</p></li>
<li><p><code>size_t sold(size_t from, size_t to) const</code>, similar
to the single-parameter version, but returns the total number of units sold
over the interval from <code>from</code> to <code>to</code> (inclusive of
both ends; i.e., <code>sold(r, r) == sold(r)</code> and
<code>sold(1, products())</code> is the total number of units sold across
all products; input <code>to &lt; from</code> is considered invalid).</p></li>
<li><p><strong>Bonus only:</strong>
<code>size_t first_same(size_t r) const</code> and
<code>size_t last_same(size_t r) const</code> return the smallest (respectively,
largest) rank <code>r'</code> for which <code>sold(r') == sold(r)</code>.
These methods are used only in the bonus test. If you do not address the bonus,
leave the default implementation, which always returns 0.</p></li>
</ul>
<p>If the call arguments are invalid (i.e., rank out of bounds or unknown
product in the <code>rank</code> method), throw a <code>std::out_of_range</code>
exception.</p>
<h2 id="scoring-conditions">Scoring Conditions</h2>
<ul>
<li><p>To earn 1 point, you need to functionally implement the above
described interface, but the implementation does not have to be very efficient.</p></li>
<li><p>To earn 3.5 points, the implementation must be efficient if the
numbers of items sold are random, but the complexity of the
<code>sold(from, to)</code> method can depend on
<code>to - from</code>.</p></li>
<li><p>To earn 7 points, the implementation must be efficient, but the
complexity of the <code>sold(from, to)</code> method can still depend on
<code>to - from</code>.</p></li>
<li><p>To earn 10 points, the <code>sold(from, to)</code> method must be
efficient even with a large <code>to - from</code>.</p></li>
<li><p><strong>Bonus:</strong> To earn 12 points, you need to correctly
and efficiently implement the <code>first_same</code> and
<code>last_same</code> methods.</p></li>
</ul>
<h2 id="notes">Notes</h2>
<ul>
<li><p>Consider what needs to be implemented to pass the individual
tests.</p></li>
<li><p>Tackle the tests gradually. Do not try to achieve everything with
your first submission, including the bonus.</p></li>
<li><p>When improving the implementation, you can use an older, slower
version to test it on large data sets.</p></li>
<li><p>The <code>Product</code> type always has a default constructor,
but anyone who has completed PA2 should not use it.</p></li>
</ul>
</td>
