% bst_find(+Tree, +E).

bst_find(bst(V, _, _), V).
bst_find(bst(V, L, _), E) :-
	E < V, bst_find(L, E).
bst_find(bst(V, _, R), E) :-
	E > V, bst_find(R, E).

% bst_find(bst(V, L, R), E) :- var(E),
% 	( bst_find(L, E) ; bst_find(R, E) ; E = V).


% bst_insert(+Tree, +E, -Res).

bst_insert(empty, E, bst(E, empty, empty)).
bst_insert(bst(V, L, R), V, bst(V, L, R)).
bst_insert(bst(V, L, R), E, bst(V, LL, R)) :-
	E < V, bst_insert(L, E, LL).
bst_insert(bst(V, L, R), E, bst(V, L, RR)) :-
	E > V, bst_insert(R, E, RR).

% bst_inorder(+Tree, -Res).
bst_inorder(empty, []).
bst_inorder(bst(V, L, R), Res) :-
	bst_inorder(L, LL),
	bst_inorder(R, RR),
	append(LL, [V|RR], Res).


% ------------------------------------------

% objem/akt.objem
move(FV/FC, SV/SC, FV/NFC, SV/NSC) :-
	Available is SV - SC,
	FC > Available,
	NFC is FC - Available, NSC = SV.

move(FV/FC, SV/SC, FV/NFC, SV/NSC) :-
	Available is SV - SC,
	FC =< Available,
	NFC = 0, NSC is SC + FC.


trymove([A,B,C], [NA, NB, NC]) :-
	( move(A, B, NA, NB), NC = C ) ;
	( move(A, C, NA, NC), NB = B ) ;
	( move(B, A, NB, NA), NC = C ) ;
	( move(B, C, NB, NC), NA = A ) ;
	( move(C, A, NC, NA), NB = B ) ;
	( move(C, B, NC, NB), NA = A ).

solve(Start, Target, Path) :-
	solve(Start, [Start], Target, Path).

solve(Target, Visited, Target, Visited).

solve(Start, Visited, Target, Path) :-
	trymove(Start, NewState),
	not(member(NewState, Visited)),
	solve(NewState, [NewState|Visited], Target, Path).

selectmin(A, ALen, B, BLen, Res) :-
	ALen =< BLen, Res = A.
selectmin(A, ALen, B, BLen, Res) :-
	ALen > BLen, Res = B.

findShortest([A], A).
findShortest([H|T], Shortest) :-
	findShortest(T, Res),
	length(H, HL),
	length(Res, ResL),
	selectmin(H, HL, Res, ResL, Shortest).

% -----------------------------

% subsets(+Lst, -Res).
subsets([], []).
subsets([H|T], [H|R]) :- subsets(T, R).
subsets([H|T],    R ) :- subsets(T, R).

subsets2(Lst, R) :-
	(Lst = [], R = []) ;
	(Lst = [H|T], subsets2(T, Res),
		  (R = [H|Res] ; R = Res)).

permute([], []).
permute(Lst, [X|Res]) :-
	delete_one(X, Lst, LstNoX),
	permute(LstNoX, Res).

% delete_one(_, [], []).
delete_one(X, [X|T], T).
delete_one(X, [H|T], [H|R]) :- delete_one(X, T, R).

issorted([]).
issorted([_]).
issorted([X,Y | Lst]) :-
	X =< Y, issorted([Y|Lst]).

inefficient_sorting(Lst, Res) :-
	permute(Lst, Res),
	issorted(Res).
