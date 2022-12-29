bigger(dog, mouse).
bigger(elephant, dog).
bigger(dog, cat).
bigger(whale, elephant).

is_bigger(X, Y) :- bigger(X, Y).
is_bigger(X, Y) :-
	bigger(X, Z),
	is_bigger(Z, Y).
% bigger(X, Y) :- bigger(X, Z),
%                 bigger(Z, Y).

vodorovna(bod(X1, Y1), bod(X2, Y1)).

factorial(0, 1).
factorial(N, Res) :-
	N > 0,
	N1 is N - 1,
	factorial(N1, Tmp),
	Res is Tmp * N.
% factorial(N, Res) :-
% 	N > 0,
% 	N1 is N - 1,
% 	between(1, 1000, Res),
% 	MM is mod(Res, N),
% 	MM = 0,
% 	Tmp is Res / N,
% 	factorial(N1, Tmp).

tmp([]).
tmp([H1, H2| Tail]) :- writeln(H1), writeln(H2), writeln(Tail).

sum([], 0).
sum([X|Xs], Res) :-
	sum(Xs, R),
	Res is R + X.

len([], 0).
len([_|Xs], Res) :-
	len(Xs, R),
	Res is R + 1.

% app(+Lst, +E, -Res)
app([], E, [E]).
app([H|T], E, [H|Tmp]) :-
	app(T, E, Tmp).
	%Res = [H|Tmp].

last(Lst, Res) :-
	app(_, Res, Lst).
