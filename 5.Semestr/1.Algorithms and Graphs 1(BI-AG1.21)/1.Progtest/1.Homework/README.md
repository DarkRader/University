<h1>Race Track</h1>

<td class="lrtbCell" colspan="3" align="left"><p>Many of you may have noticed Ester Ledecká's success at the 2018 Winter Olympics, where she astonishingly won a gold medal in alpine skiing. BBC even called Ledecká's victory "one of the most astonishing Olympic stories of all time." As it often happens in our country, once our representatives succeed in a particular discipline, the whole nation becomes not only absolute experts but also (semi-)professional athletes. After Nagano, we had 10 million hockey players, then everyone became speed skaters (by the way, do you know if they have built the hall for Martina yet?). Later, the focus shifted to biathlon, and the current king is alpine skiing.</p>
<p>One of your acquaintances, let's call him SkiLiftOperator, thought he could capitalize on this enthusiasm for skiing. It didn't take long for SkiLiftOperator to come up with a concrete idea – he will organize the Czech Republic Alpine Skiing Championship on his ski slope in Osvětimany. Why the raised eyebrows? Are you surprised that someone allowed organizing downhill races in a ski area with the longest slope being 400 meters long and with a vertical drop of 98 meters? Even though the minimum length for a downhill course according to official rules is 800 meters? That's not a problem for SkiLiftOperator; he can handle even bigger challenges!</p>
<p>But seriously, it is a bit of a problem. It could easily happen that one of the competitors complains, and the race will have to be canceled for being non-compliant. That would mean not only wasted preparations and disappointed fans but also the need to return the subsidy SkiLiftOperator received for the race. And no one wants that, right?</p>
<p>When you learned about the problem, you immediately thought of a solution. The Osvětimany area consists of several ski slopes. Maybe if you could connect them into one big slope, you might reach the limit. SkiLiftOperator liked your idea, of course, and immediately asked you to plan the longest possible track.</p>
<h2 id="program-interface">Program Interface</h2>
<p>Your task is to implement the function 
<code>std::vector&lt;Path&gt; longest_track(size_t points, const std::vector&lt;Path&gt;&amp; all_paths)</code>, 
which finds the longest possible track for an alpine skiing race in the given map. The track can start and end at any intersection. The parameters are the number of intersections <code>points</code> and a list of usable paths between the intersections <code>all_paths</code>. Each path contains the starting intersection <code>from</code> and the target <code>to</code> and can only be traversed in this direction, as all sections must go downhill. It also contains the length of the given path <code>length</code>. The length is always a non-negative integer.</p>
<p>The output is a list of consecutive paths (i.e., <code>to</code> of one path is <code>from</code> of the next) that form the longest possible track. If there are multiple longest tracks, any of them can be returned.</p>
<p>You can assume that the input is always valid, meaning:</p>
<ul>
<li>The intersections where paths start and end are in the range 
<code>[0, points)</code>.</li>
<li>All paths go downhill.</li>
</ul>
<h2 id="scoring-conditions">Scoring Conditions</h2>
<ul>
<li>For 3 points, the task must be correctly solved for very small instances. All paths have a length of 10 or less.</li>
<li>For 5 or 7 points, the task must be correctly solved for larger instances, but the lengths of individual paths are still limited to 10.</li>
<li>For 10 points, the task must be correctly and quickly solved for large instances containing very long paths. However, the length of the permissible track will not exceed the range of the <code>int</code> data type.</li>
</ul>
<p>Time limits are 13 seconds for the basic test and 6, 11, and 5 seconds for individual speed tests. Additionally, all speed tests together must complete within 15 seconds.</p>

</td>