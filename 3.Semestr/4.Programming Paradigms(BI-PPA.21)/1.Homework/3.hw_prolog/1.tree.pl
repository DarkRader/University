bt_identical(ControlR, ControlL) :-
    ControlR = empty,
    ControlL = empty.

bt_identical(t(_, L, R), t(_, Lsec, Rsec)) :-
    bt_identical(R,Rsec),
    bt_identical(L,Lsec).

