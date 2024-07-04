<section class="doc-section level-1"><h2 id="_task-assignment"><a class="anchor" href="#_task-assignment" aria-hidden="true"></a>Task Assignment</h2><section class="doc-section level-2"><h3 id="palindrome"><a class="anchor" href="#palindrome" aria-hidden="true"></a>Palindrome</h3><p>Write a function <code>is-palindrome?</code> that tests whether a given list, except its first and the last element, is a palindrome. For more intuition see examples below.</p>
<p>An empty list and a list of a single element is considered to be a palindrome too.</p>
<div class="ulist"><ul><li><code>(is-palindrome? '(0 1 2 1 3)) &#8594; #t</code></li><li><code>(is-palindrome? '(1 2 1)) &#8594; #t</code></li><li><code>(is-palindrome? '(1 1 1 1)) &#8594; #t</code></li><li><code>(is-palindrome? '(0 1 1 1)) &#8594; #t</code></li><li><code>(is-palindrome? '(1 1 2 1)) &#8594; #f</code></li><li><code>(is-palindrome? '(1 1 2 2 1)) &#8594; #f</code></li><li><code>(is-palindrome? '(1 1)) &#8594; #t</code></li><li><code>(is-palindrome? '(1)) &#8594; #t</code></li><li><code>(is-palindrome? '()) &#8594; #t</code></li><li><code>(is-palindrome? '(1 (1 2) 5 (1 2) 10))</code> &#8594; <code>#t</code></li><li><code>(is-palindrome? '(1 (1 2) 5 (2 1) 10))</code> &#8594; <code>#f</code></li></ul></div></section>
<section class="doc-section level-2"><h3 id="partition-by"><a class="anchor" href="#partition-by" aria-hidden="true"></a>Partition-by</h3><aside class="admonition-block tip" role="doc-tip"><h6 class="block-title label-only"><span class="title-label">Tip: </span></h6><p>A smart use of some higher order function(s) may make the implementation much simpler.</p></aside>
<p>Write a function <code>partition-by</code> that takes a list <code>s</code> as its first argument and a function <code>f</code> as its second one.
Your function should return a list of two elements - a pair of two sub-lists of the original one.
The first one contains all the elements of the original list that satisfy the predicate function <code>f</code> and the second one contains those that do not.</p>
<p>The relative order of elements in both lists should remain unchaged.</p>
<p>See the examples below:</p>
<div class="ulist"><ul><li><code>(partition-by (lambda (e) (= e (* 2 (floor (/ e 2))))) '(1 2 3 4 5))</code> &#8594; <code>'( (2 4) (1 3 5))</code></li><li><code>(partition-by (lambda (e) (&lt; 0 e)) '(2 4))</code> &#8594; <code>'( (2 4) () )</code></li><li><code>(partition-by (lambda (e) (&gt; e 5)) '(3 4 5 6 7))</code> &#8594; <code>'( (6 7) (3 4 5))</code></li></ul></div></section>
<section class="doc-section level-2"><h3 id="tree-balance"><a class="anchor" href="#tree-balance" aria-hidden="true"></a>Tree Balancing</h3><p>Write a function <code>is-balanced?</code> that takes a Binary Tree as its argument and checks it for being balanced.
A tree is balanced if at all levels the heights of both sub-trees do not differ more than by one.</p>
<p>The Binary Tree is represented as a list of three elements (for a branch) or an empty list (for an empty tree).
The first value in the triple is the key-value stored in that node. The second one is a left sub-tree and the third one is a right sub-tree.</p>
<div class="ulist"><ul><li><code>(is-balanced? '(5 () ()))</code> &#8594; <code>#t</code></li><li><code>(is-balanced? '(5 (3 () ()) (4 () ())) )</code> &#8594; <code>#t</code></li><li><code>(is-balanced? '(5 () (4 (6 () ()) ()) ) )</code> &#8594; <code>#f</code></li><li><code>(is-balanced? '())</code> &#8594; <code>#t</code></li><li><code>(is-balanced? '(1 (3 (5 () ()) (10 () ()) ) (8 (3 (5 () ()) () ) () ) ) )</code> &#8594; <code>#f</code></li><li><code>(is-balanced? '(1 (3 (5 () ()) (10 (15 () ()) ())) (8 () ())))</code> &#8594; <code>#f</code></li><li><code>(is-balanced? '(1 (2 (3 (4 (5 () ()) ()) ()) ()) ()))</code> &#8594; <code>#f</code></li></ul></div></section>
<section class="doc-section level-2"><h3 id="intersect"><a class="anchor" href="#intersect" aria-hidden="true"></a>Intersection of Unordered Lists</h3><p>Write a function <code>intersect</code> that takes two lists as its arguments. It returns a list containing only those elements that are present on both argument-lists.</p>
<p>The resulting list does not contain any duplicate elements and is sorted.</p>
<div class="ulist"><ul><li><code>(intersect '(1 5 2 2) '(3 4 2 1))</code> &#8594; <code>'(1 2)</code></li><li><code>(intersect '(1 2) '(3))</code> &#8594; <code>'()</code></li><li><code>(intersect '(6 3 4 2 3 3 1 3) '(3 2 1 6 1))</code> &#8594; <code>'(1 2 3 6)</code></li></ul></div></section>
<section class="doc-section level-2"><h3 id="compose-chain"><a class="anchor" href="#compose-chain" aria-hidden="true"></a>Compose-chain</h3><aside class="admonition-block tip" role="doc-tip"><h6 class="block-title label-only"><span class="title-label">Tip: </span></h6><p>A smart use of some higher order function(s) may make the implementation much simpler.</p></aside>
<p>Write a function <code>compose-chain</code> that performs a chain of function compositions.
The function takes a single argument - a list of functions that will be composed together going from the right to the left.</p>
<p>The function returns a function that is a composition of all of the functions from the list.</p>
<section class="admonition-block important" role="doc-notice"><h6 class="block-title label-only"><span class="title-label">Important: </span></h6><p>Carefully inspect the following examples. Function <code>compose-chain</code> returns a function that is then applied to some number (in the example). Your function will not be given that number.</p></section>
<div class="ulist"><ul><li><code>( (compose-chain `(,(lambda (e) (+ e 1)) ,(lambda (e) (* e 2))) ) 5)</code> &#8594; <code>11</code></li><li><code>( (compose-chain `(,(lambda (e) (* e 4)) ,(lambda (e) (+ e 2))) ) 6)</code> &#8594; <code>32</code></li><li><code>( (compose-chain `() ) 6)</code> &#8594; <code>6</code></li></ul></div>
<p>For the first example the result is supposed to be a function of <code>e</code> computing <code>(+ (* e 2) 1)</code>.</p></section>
<section class="doc-section level-2"><h3 id="intervals"><a class="anchor" href="#intervals" aria-hidden="true"></a>Intervals</h3><aside class="admonition-block tip" role="doc-tip"><h6 class="block-title label-only"><span class="title-label">Tip: </span></h6><p>A smart use of some higher order function(s) may make the implementation much simpler.</p></aside>
<p>Write a function <code>intervals</code> that takes a list of lists as its single argument.
Those sub-lists always contain exactly two numbers. (They are pairs.)</p>
<p>Example: <code>'( (1 5) (2 6) (0 1) (8 10) )</code>.</p>
<p>Each one of those sub-lists (pairs) represents an interval. For instance <code>(1 5)</code> is an interval from <code>1</code> to <code>5</code> both bounds included.</p>
<p>Your function will compute for each one of them how many of the other intervals do intersect with it. It will return that information as a list of the same length containing the number of intersects for each element at the corresponding position.</p>
<section class="admonition-block important" role="doc-notice"><h6 class="block-title label-only"><span class="title-label">Important: </span></h6><p>The intersection with itself does not count.</p></section>
<p>Example for: <code>'( (1 5) (2 6) (0 1) (8 10) )</code>:</p>
<div class="ulist"><ul><li><code>(1 5)</code> intersects with <code>(2 6)</code> and <code>(0 1)</code>, so two.</li><li><code>(2 6)</code> intersects with <code>(1 5)</code>, so one.</li><li><code>(0 1)</code> intersects with <code>(1 5)</code>, so one.</li><li><code>(8 10)</code> does not intersect with any of them, so zero intersections.</li></ul></div>
<p>The result should look like: <code>(2 1 1 0)</code>.</p>
<p>More Examples:</p>
<div class="ulist"><ul><li><code>(intervals '( (1 10) (4 6) (2 3) (5 11) (9 10) (11 15) ))</code> &#8594; <code>'(4 2 1 4 2 1)</code></li><li><code>(intervals '() )</code> &#8594; <code>'()</code></li><li><code>(intervals '( (1 2) ))</code> &#8594; <code>'(0)</code></li><li><code>(intervals '( (1 2) (3 4) ))</code> &#8594; <code>'(0 0)</code></li><li><code>(intervals '( (5 5) (5 5) ))</code> &#8594; <code>'(1 1)</code></li></ul></div></section>
<section class="doc-section level-2"><h3 id="matrix-mul"><a class="anchor" href="#matrix-mul" aria-hidden="true"></a>Matrix Multiplication</h3><aside class="admonition-block tip" role="doc-tip"><h6 class="block-title label-only"><span class="title-label">Tip: </span></h6><p>A smart use of some higher order function(s) may make the implementation much simpler.</p></aside>
<p>Write a function <code>matrix-mul</code> that takes two matrices as its two arguments. Its result is a matrix obtained by multiplying those two matrices.</p>
<p>The matrix is represented as a list of rows (so list of lists of numbers).</p>
<p>You can assume that the dimensions of both matrices will be legal in regards to the multiplication. All matrices will always have at least one row and one column.</p>
<p>Example 1:</p>
<div class="listing-block"><pre class="highlightjs-ext highlight"><code>(matrix-mul '((1 2 3)
              (4 1 1))
            '((1 2)
              (3 4)
              (2 1)))</code></pre></div>
<p>Result</p>
<div class="listing-block"><pre class="highlightjs-ext highlight"><code>'((13 13)
  (9 13 ))</code></pre></div>
<p>Example 2:</p>
<div class="listing-block"><pre class="highlightjs-ext highlight"><code>(matrix-mul '((1 2 3))
            '((1)
              (2)
              (3)))</code></pre></div>
<p>Result</p>
<div class="listing-block"><pre class="highlightjs-ext highlight"><code>'( (14) )</code></pre></div></section></section>