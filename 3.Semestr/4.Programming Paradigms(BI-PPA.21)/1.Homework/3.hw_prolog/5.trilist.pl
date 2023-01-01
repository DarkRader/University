trilist([]).

trilist(Lst) :-
    len(Lst, Res),
    M is mod(Res, 3),
    M = 0,
    NumInTri is Res / 3 ,
    control_trilist(Lst, NumInTri, NumInTri).


control_trilist([Head | Tail], I, CtrI) :-
    NewCtrI is CtrI - 1,
    NewCtrI = 0,
    next_lst([Head | Tail], I, Head),
    next_lst([Head | Tail], I + I, Head).

control_trilist([Head | Tail], I, CtrI) :-
    next_lst([Head | Tail], I, Head),
    next_lst([Head | Tail], I + I, Head),
    NewCtrI is CtrI - 1,
    NewCtrI > 0,
    control_trilist(Tail, I, NewCtrI).



next_lst([Head | Tail], I, ContrNum) :- I = 0, ContrNum = Head.

next_lst([Head | Tail], I, ContrNum) :-
    I > 0,
    NewI is I - 1,
    next_lst(Tail, NewI, ContrNum).


len([], 0).
len([_|Xs], Res) :-
    len(Xs, R),
    Res is R + 1.
