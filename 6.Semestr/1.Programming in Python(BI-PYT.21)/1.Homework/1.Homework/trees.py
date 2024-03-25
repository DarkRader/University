#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Version 0.1

Cílem je vykreslit v "UTF16-artu" strom definovaný listem hodnot. Každý vnitřní uzel stromu obsahuje vždy dvě položky: název uzlu a seznam potomků (nemusí být nutně v tomto pořadí). Názvem může být jakýkoli objekt kromě typu list (seznam).

Příklady validních stromů:
    - triviální strom o 1 uzlu: [1, []]
    - triviální strom o 1 uzlu s opačným pořadím ID a potomků: [[], 2]
    - triviální strom o 3 uzlech: [1, [2, 3]]
        (listové uzly ve stromu o výšce >= 2 mohou být pro zjednodušení zapsány i bez prázdného seznamu potomků)

Příklady nevalidních stromů:
    - None
    - []
    - [666]
    - [1, 2]
    - (1, [2, 3])


Strom bude vykreslen podle následujících pravidel:
    - Vykresluje se shora dolů, zleva doprava.
    - Uzel je reprezentován jménem, které je stringovou serializací objektu daného v definici uzlu.
    - Uzel v hloubce N bude odsazen zlava o N×{indent} znaků, přičemž hodnota {indent} bude vždy kladné celé číslo > 1.
    - Má-li uzel K potomků, povede:
        - k 1. až K-1. uzlu šipka začínající znakem ├ (UTF16: 0x251C)
        - ke K. uzlu šipka začínající znakem └ (UTF16: 0x2514)
    - Šipka k potomku uzlu je vždy zakončena znakem > (UTF16: 0x003E; klasické "větší než").
    - Celková délka šipky (včetně úvodního znaku a koncového ">") je vždy {indent}, výplňovým znakem je zopakovaný znak ─ (UTF16: 0x2500).
    - Všichni potomci uzlu jsou spojeni na úrovni počátku šipek svislou čarou │ (UTF16: 0x2502); tedy tam, kde není jako úvodní znak ├ nebo └.
    - Pokud název uzlu obsahuje znak `\n` neodsazujte nijak zbytek názvu po tomto znaku.
    - Každý řádek je ukončen znakem `\n`.

Další požadavky na vypracovní:
    - Pro nevalidní vstup musí implementace vyhodit výjimku `raise Exception('Invalid tree')`.
    - Mít codestyle v souladu s PEP8 (můžete ignorovat požadavek na délku řádků - C0301 a používat v odůvodněných případech i jednopísmenné proměnné - C0103)
        - otestujte si pomocí `pylint --disable=C0301,C0103 trees.py`
    - Vystačit si s buildins metodami, tj. žádné importy dalších modulů.


Příklady vstupu a výstupu:
INPUT:
[[[1, [True, ['abc', 'def']]], [2, [3.14159, 6.023e23]]], 42]

PARAMS:
    indent = 4
    separator = '.'

OUTPUT:
42
├──>1
│...└──>True
│.......├──>abc
│.......└──>def
└──>2
....├──>3.14159
....└──>6.023e+23

INPUT:
[[[1, [[True, ['abc', 'def']], [False, [1, 2]]]], [2, [3.14159, 6.023e23, 2.718281828]], [3, ['x', 'y']], [4, []]], 42]

PARAMS:
    indent = 4
    separator = '.'

OUTPUT:
42
├──>1
│...├──>True
│...│...├──>abc
│...│...└──>def
│...└──>False
│.......├──>1
│.......└──>2
├──>2
│...├──>3.14159
│...├──>6.023e+23
│...└──>2.718281828
├──>3
│...├──>x
│...└──>y
└──>4

INPUT:
[6, [[[[1, [2, 3]], [42, [-43, 44]]], 4], 5]]

PARAMS:
    indent = 2
    separator = ' '

OUTPUT:
6
└>5
  └>4
    ├>1
    │ ├>2
    │ └>3
    └>42
      ├>-43
      └>44

INPUT:
[6, [5, ['dva\nradky']]]

PARAMS:
    indent = 2
    separator = ' '

OUTPUT:
6
└>5
  └>dva
radky

Potřebné UTF16-art znaky:
└ ├ ─ │

Odkazy:
https://en.wikipedia.org/wiki/Box_Drawing
"""


# zachovejte interface metody
def render_tree(tree: list = None, indent: int = 2, separator: str = ' ') -> str:
    """
    Function that draws a tree in UTF16
    :param tree: Received as input by the tree
    :param indent: A node at depth N will be offset to the left by N×{indent} characters
    :param separator: A sign of separation
    :return: str of th tree in UTF16 style
    """
    if not isinstance(tree, list) or tree is None or isinstance(tree, tuple):
        raise Exception('Invalid tree')

    if not check_on_father_and_child(tree):
        raise Exception('Invalid tree')

    must_exist_one_father(tree)
    correct_tree = fix_father_on_right_place(tree)
    child_list = correct_tree[1]
    my_parameters = (indent, separator)

    res_tree = recursion(correct_tree, child_list, my_parameters, 0, [])
    res_tree = str(correct_tree[0]) + '\n' + res_tree

    return res_tree


def recursion(original_list: list, check_list: list, my_parameters: tuple,
              depth: int, end_list: list) -> str:
    """
    Function which recursively traverses all nodes and draws our tree in UTF16
    :param original_list: Outer list of the list check_list
    :param check_list: The list we work with and make checks on
    :param my_parameters: Tuple, which contains the parameters: indent and separator
    :param depth: The depth of the tree we're on
    :param end_list: Bool list, which indicates at what depth the node is end or not
    :return: str of the tree in UTF16 style
    """
    picture = ''
    end_list.append(False)
    check_father = False
    check_depth = depth

    if isinstance(check_list, tuple) or not isinstance(check_list, list) or check_list is None:
        raise Exception('Invalid tree')

    if check_on_father_and_child(check_list):
        check_list = fix_father_on_right_place(check_list)
        if original_list[-1] == check_list:
            end_list[depth] = True
        else:
            end_list[depth] = False
        must_exist_one_father(check_list)
        check_father = True
        check_depth = depth + 1

    for item in reversed(check_list):
        if isinstance(item, list):
            if check_father:
                picture = recursion(check_list, item, my_parameters, check_depth, end_list) + picture
            else:
                picture = recursion(check_list, item, my_parameters, depth, end_list) + picture
        elif (check_father and original_list[-1] == check_list) or (not check_father and check_list[-1] == item):
            picture = draw_row(item, my_parameters, depth, False, end_list) + picture
        else:
            picture = draw_row(item, my_parameters, depth, True, end_list) + picture

    return picture


def check_on_father_and_child(check_list: list) -> bool:
    """
    Function that checks whether a node has father and sons or is just a list of objects
    :param check_list: The node of the tree that is being checked
    :return: return True if node has father and sons or False if is just a list of objects
    """
    father = False
    child = False
    if isinstance(check_list, list):
        for item in check_list:
            if not isinstance(item, list):
                father = True
            else:
                child = True
        if child is True and father is True:
            return True

    return False


def must_exist_one_father(check_list: list):
    """
    Function that verifies that there's only one father
    :param check_list: The node of the tree that is being checked
    """
    num_of_father = 0

    for item in check_list:
        if not isinstance(item, list):
            num_of_father = num_of_father + 1

        if num_of_father > 1:
            raise Exception('Invalid tree')


def fix_father_on_right_place(list_with_father: list) -> list:
    """
    Function that puts the node's father in the right place
    :param list_with_father: The list that contains the father and his sons
    :return: fixed list
    """
    if not isinstance(list_with_father[0], list):
        return list_with_father

    father = list_with_father[-1]
    list_with_father.pop()
    list_with_father.insert(0, father)
    return list_with_father


def draw_row(node, my_parameters: tuple, depth: int,
             small_brother: bool, end: list) -> str:
    """
    Function that draws a tree row from the end to the beginning in UTF16
    :param node: The object we are currently processing and drawing
    :param my_parameters: Tuple, which contains the parameters: indent and separator
    :param depth: The depth of the tree we're on
    :param small_brother: Bool object that denotes whether this is the final object in the list or not
    :param end: Bool list, which indicates at what depth the node is end or not
    :return: str row of the tree in UTF16 style
    """
    sum_separator = ''

    if small_brother is True:
        crossroad = '├'
    else:
        crossroad = '└'

    for i in range(depth):
        if end[i] is True:
            sum_separator = sum_separator + (my_parameters[1] * my_parameters[0])
        else:
            sum_separator = sum_separator + '│' + (my_parameters[1] * (my_parameters[0] - 1))

    picture = sum_separator + crossroad + ('─' * (my_parameters[0] - 2)) + '>' + str(node) + '\n'
    return picture
