values_in([], _).

values_in([Head | Lst1], Lst2) :-
    member(Head, Lst2),
    values_in(Lst1, Lst2).
