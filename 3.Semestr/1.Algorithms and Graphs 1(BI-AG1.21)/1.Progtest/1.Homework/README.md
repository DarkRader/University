<h1>The Grinch's Sleigh</h1>
<div class="line-block">What's worse then!<br />
The worst is yet to come,<br />
which always aggravates the Grinch.<br />
All the Whos in Whoville, big and small,<br />
will gather together to the sound of Christmas bells,<br />
holding hands... And the singing spreads from the houses!<br />
<br />
And it won't stop! That relentless singing!<br />
Just SINGING! SINGING! SINGING! SINGING!<br />
And the more the Grinch thought about their Christmas carols,<br />
the more it gnawed at him: "I must stop it! Forever!<br />
I've put up with this for a good thirty-five years!<br />
And it would be the same next year!"<br />
<br />
And then he got an idea!<br />
A terrible idea!<br />
YES, THAT'S WHEN THE GRINCH<br />
GOT A WONDERFUL, TERRIBLE IDEA!</div>
<p>The Grinch is the worst creature you've ever seen. From head to toe, he's covered in green fur, which he never brushes. He never bathes and stinks from miles away. He has larvae in his teeth and resembles an irritable crocodile. He's utterly evil and despises little children. His heart is as hard as stone; he hates Christmas and the entire advent season. Thus, he decided to steal Christmas this year.</p>
<p>But stealing Christmas isn't simple. It requires a solid plan! The Grinch climbed to the highest peak of the mountain where his lair was located. Amid triggering avalanches aimed at Whoville, he concocted his plot. Yes, that's it! Christmas is mainly about presents. He needs to steal all the presents. But how?</p>
<p>It's clear the Grinch can't carry them all by hand. And Whoville is too far to make multiple trips in one night. Then the Grinch heard distant barking. Yes, you're right, Max! We need a sleigh to load the stolen presents. And Max, the Grinch's only friend, will pull it!</p>
<p>The Grinch immediately set out to execute his evil plan. If anyone dared to enter his cave, they would hear constant banging, hissing, welding, and cursing. Max wisely hid in the darkest corner of the cave and didn't poke his nose out.</p>
<p>Christmas is fast approaching, and the Grinch is running out of time. The sleigh is still incomplete. Several important parts are missing, such as a bell, antlers for Max, and the biggest sack Whoville has ever seen. These items need to be gathered immediately! The Grinch summoned Max, gave him a map and a list of parts to fetch right away. If Max dared to disappear again, as he often does, the Grinch promised to cut off his tail.</p>
<p>Dear reader, I haven't yet described how the Grinch's lair truly looks. This creature, in his thirty-five years of life, has woven an entire mountain with a network of corridors and rooms where he hoards his treasures. Or at least what he considers treasures. Here, we can find various scattered bones of animals he ate or tortured, different trinkets he stole in town, found in dumps, or discovered during his wanderings in the hills.</p>
<p>Will you help save Max's skin and guide him on how to quickly gather all the necessary parts?</p>
<h2 id="program-interface">Program Interface</h2>
<p>Your task is to implement the function
<code>std::list&lt;Place&gt; find_path(const Map &amp;map)</code>, which
finds the shortest possible path in the given map that collects at least
one part of each type. The first element of the path must be
<code>map.start</code>, the last <code>map.end</code>, and there must be
a corridor between every two consecutive places. If such a path does not
exist, return an empty list. The <code>Map</code> structure contains the
following elements:</p>
<ul>
<li><code>places</code>: the number of rooms in the Grinch's lair,</li>
<li><code>start</code>, <code>end</code>: the room numbers where Max
starts and where he needs to deliver the collected items (numbered from zero),</li>
<li><code>connections</code>: a list of pairs of rooms describing the
corridors,</li>
<li><code>items</code>: a list of lists, <code>items[i]</code> is a list
of rooms where the <code>i</code>-th part is located.</li>
</ul>
<p>You can assume that the room numbers are always in the range of 0 to
<code>places - 1</code> (inclusive).</p>
<h2 id="scoring-conditions">Scoring Conditions</h2>
<ul>
<li>To earn <span class="math inline">2</span> points, you need to determine
if such a path exists. If it does, it's enough to return any non-empty
list; its content is not checked. The size of the instances is the same as for 5 points.</li>
<li>To earn <span class="math inline">5</span> points, you need to correctly
and quickly solve instances with about 1000 rooms and up to 4 types of
items. Each item can appear in many rooms.</li>
<li>To earn <span class="math inline">10</span> points, you need to correctly
and quickly solve instances with about 3000 rooms and up to 6 types of
items. Each item can appear in many rooms.</li>
<li><strong>Bonus:</strong> To earn 13 points, you need to correctly and quickly
solve instances with about 10000 rooms and up to 12 types of items.
However, each item appears in at most 5 rooms.</li>
</ul></td>
