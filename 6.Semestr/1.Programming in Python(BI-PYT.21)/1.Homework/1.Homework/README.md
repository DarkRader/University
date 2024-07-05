## Task

The goal is to render a tree defined by a list of values in "UTF16-art". Each internal node of the tree always contains two items: the node name and a list of children (not necessarily in this order). The name can be any object except a list.

### Examples of valid trees:
- A trivial tree with 1 node: `[1, []]`
- A trivial tree with 1 node with the opposite order of ID and children: `[[], 2]`
- A trivial tree with 3 nodes: `[1, [2, 3]]` (leaf nodes in a tree of height >= 2 can be simplified without an empty list of children)

### Examples of invalid trees:
- `None`
- `[]`
- `[666]`
- `[1, 2]`
- `(1, [2, 3])`

### The tree will be rendered according to the following rules:
- It is rendered top to bottom, left to right.
- A node is represented by its name, which is the string serialization of the object specified in the node definition.
- A node at depth `N` will be indented from the left by `N×{indent}` characters, where the value of `{indent}` is always a positive integer > 1.
- If a node has `K` children, the arrows will be:
    - starting with the character ├ (UTF16: 0x251C) to the 1st to (K-1)th child
    - starting with the character └ (UTF16: 0x2514) to the Kth child
- The arrow to a child node is always terminated by the character `>` (UTF16: 0x003E; classic "greater than").
- The total length of the arrow (including the initial character and the final `>`) is always `{indent}`, with the filler character being the repeated character ─ (UTF16: 0x2500).
- All children of a node are connected at the level of the start of the arrows by a vertical line │ (UTF16: 0x2502); that is, where the initial character is not ├ or └.
- If the node name contains the character `\n`, do not indent the rest of the name after this character.
- Each line is terminated by the character `\n`.

### Additional requirements:
- For invalid input, the implementation must raise an exception `raise Exception('Invalid tree')`.
- The code style must conform to PEP8 (you can ignore the requirement for line length - C0301 and use single-letter variables in justified cases - C0103).
    - test with `pylint --disable=C0301,C0103 trees.py`
- Use built-in methods only, i.e., no importing additional modules.

### Examples of input and output:
#### INPUT:
[[[1, [True, ['abc', 'def']]], [2, [3.14159, 6.023e23]]], 42]

PARAMS:<br>
indent = 4<br>
separator = '.'<br>

OUTPUT:<br>
42<br>
├──>1<br>
│...└──>True<br>
│.......├──>abc<br>
│.......└──>def<br>
└──>2<br>
....├──>3.14159<br>
....└──>6.023e+23<br>

INPUT:<br>
[[[1, [[True, ['abc', 'def']], [False, [1, 2]]]], [2, [3.14159, 6.023e23, 2.718281828]], [3, ['x', 'y']], [4, []]], 42]

PARAMS:<br>
indent = 4<br>
separator = '.'<br>

OUTPUT:<br>
42<br>
├──>1<br>
│...├──>True<br>
│...│...├──>abc<br>
│...│...└──>def<br>
│...└──>False<br>
│.......├──>1<br>
│.......└──>2<br>
├──>2<br>
│...├──>3.14159<br>
│...├──>6.023e+23<br>
│...└──>2.718281828<br>
├──>3<br>
│...├──>x<br>
│...└──>y<br>
└──>4<br>

INPUT:<br>
[6, [[[[1, [2, 3]], [42, [-43, 44]]], 4], 5]]

PARAMS:<br>
indent = 2<br>
separator = ' '<br>

OUTPUT:<br>
6<br>
└>5<br>
└>4<br>
├>1<br>
│ ├>2<br>
│ └>3<br>
└>42<br>
├>-43<br>
└>44<br>

INPUT:<br>
[6, [5, ['dva\nradky']]]

PARAMS:<br>
indent = 2<br>
separator = ' '<br>

OUTPUT:<br>
6<br>
└>5<br>
└>dva<br>
radky<br>

Potřebné UTF16-art znaky:<br>
└ ├ ─ │<br>

Odkazy:<br>
https://en.wikipedia.org/wiki/Box_Drawing