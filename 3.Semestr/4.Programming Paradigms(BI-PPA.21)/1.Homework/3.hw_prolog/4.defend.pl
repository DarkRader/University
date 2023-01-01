onlyfirst(Goal) :- Goal, !.

can_x_defend([Head | Tail]) :-
    Head = o,
    onlyfirst(last([Head | Tail], Last)),
    Last = o,
    onlyfirst(len_of_x([Head | Tail], 0, ResX)),
    onlyfirst(len_of_o([Head | Tail], 0, ResO)),
    ResX < ResO, !.

can_x_defend([Head | Tail]) :-
    onlyfirst(len_of_x([Head | Tail], 0, ResX)),
    onlyfirst(len_of_o([Head | Tail], 0, ResO)),
    ResX =< ResO.

len_of_x([], Res, ResX) :- ResX = Res.

len_of_x([Head1, Head2 | Tail], Res, ResX) :-
    Head1 = x,
    Head1 = Head2,
    len_of_x([Head2 | Tail], Res, ResX).

len_of_x([Head | Tail], Res, ResX) :-
    Head = x,
    Tail = [],
    TmpRes is Res + 1,
    len_of_x(Tail, TmpRes, ResX).

len_of_x([Head1, Head2 | Tail], Res, ResX) :-
    Head1 = x,
    TmpRes is Res + 1,
    len_of_x([Head2 | Tail], TmpRes, ResX).

len_of_x([Head | Tail], Res, ResX) :-
    len_of_x(Tail, Res, ResX).

len_of_o([], Res, ResO) :- ResO = Res.

len_of_o([Head1, Head2 | Tail], Res, ResO) :-
    Head1 = o,
    Head1 = Head2,
    len_of_o([Head2 | Tail], Res, ResO).

len_of_o([Head | Tail], Res, ResO) :-
    Head = o,
    Tail = [],
    TmpRes is Res + 1,
    len_of_o(Tail, TmpRes, ResO).

len_of_o([Head1, Head2 | Tail], Res, ResO) :-
    Head1 = o,
    TmpRes is Res + 1,
    len_of_o([Head2 | Tail], TmpRes, ResO).

len_of_o([Head | Tail], Res, ResO) :-
    len_of_o(Tail, Res, ResO).

app([], E, [E]).
app([H|T], E, [H|Tmp]) :-
    app(T, E, Tmp).
    %Res = [H|Tmp].

last(Lst, Res) :-
    app(_, Res, Lst).

