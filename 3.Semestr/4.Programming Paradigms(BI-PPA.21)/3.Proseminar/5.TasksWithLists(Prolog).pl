puzzle(N) :-
	Digits = [0,1,2,3,4,5,6,7,8,9],
	member(A, Digits), A \= 0,
	member(B, Digits),
	member(C, Digits),
	member(D, Digits),
	member(E, Digits),
	% Součet první, druhé a třetí cifry
	% dává pátou cifru
	E is A + B + C,

	% Třetí cifra je o čtyři menší než
	% poslední
	C is E - 4,

	% První a čtvrtá dohromady je o jedna menší,
	% než poslední
	E - (A + D) =:= 1,

	% Pátá je trojnásobkem třetí
	E is C * 3,

	N is 10000*A + 1000*B + 100*C +
	     10*D + E.


printList([]).
printList([H|T]) :-
	writeln(H),
	printList(T).

%del(+Lst, +E, -Res).
del([], _, []).
del([X|Xs], X, Res) :-
	del(Xs, X, Res), !.

del([X|Xs], E, [X|Res]) :-
	% X \= E,
	del(Xs, E, Res).

%
min(X, Y, Z) :- X =< Y, !, Z =X.
min(_, Y, Y).

min2(X, Y, X) :- X =< Y.
min2(X, Y, Y) :- Y < X.

test(Goal) :- Goal.

notProvable(Goal) :- Goal, !, fail.
notProvable(_).


split(Lst, A, B) :-
	split(Lst, Lst, A, B).

split(Slow, [], [], Slow).
split(Slow, [_], [], Slow).
split([X|Xs], [_,_|Ys], [X|A], B) :-
	split(Xs, Ys, A, B).

split2(Lst, A, B) :-
	length(Lst, L),
	L1 is L // 2,
	L2 is L - L1,
	length(A, L1),
	length(B, L2),
	append(A, B, Lst).


merge([], L2, L2) :- !.
merge(L1, [], L1) :- !.
merge([A|As], [B|Bs], [A|Res]) :-
	A =< B, !, merge(As, [B|Bs], Res).
merge([A|As], [B|Bs], [B|Res]) :-
	B < A, merge([A|As], Bs, Res).

mergesort([], []).
mergesort([A], [A]).
mergesort([L1, L2 | Lst], Res) :-
	split2([L1,L2|Lst], A, B),
	mergesort(A, AS),
	mergesort(B, BS),
	merge(AS, BS, Res).

rev(Lst, Res) :- rev(Lst, [], Res).

rev([], Acc, Acc).
rev([X|Xs], Acc, Res) :-
	rev(Xs, [X|Acc], Res).
