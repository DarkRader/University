without_second_min(Lst, R) :-
    find_sec_min(Lst, ResSecMin),
    del_min([Min | Lst], ResSecMin, R).

find_min([Head], Min) :- Min = Head.

min(X, Y, Z) :- X =< Y, !, Z =X.
min(_, Y, Y).

find_min([Head | Tail], Min) :-
    find_min(Tail, TempMin),
    min(Head, TempMin, Min).

del_min([], Min, []) :- !.

del_min([Min|Tail], Min, Res) :-
    !,
    del_min(Tail, Min, Res).

del_min([Cand|Tail], Min, Res) :-
    !,
    del_min(Tail, Min, TmpRes),
    append([Cand], TmpRes, Res).

find_sec_min([Min | Lst], Res) :-
    find_min([Min | Lst], ResMin),
    del_min([Min | Lst], ResMin, WithoutMin),
    find_min(WithoutMin, Res).
   
