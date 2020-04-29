:- lib(ic).
:- lib(ic_global).

data(X) :- X = [ [40, 50, 56, 46, 43, 42, 41],
		 [23, 33, 43, 46, 26, 24],
		 [14, 24, 26, 16, 15],
		 [5, 15, 16, 6],
		 [4, 14, 15, 5],
		 [3, 23, 24, 14, 4],
		 [32, 42, 43, 33],
		 [31, 41, 42, 32],
		 [1, 31, 32, 33, 23, 3],
		 [0, 40, 41, 31, 1] ].

data(X) :- X = [ [7, 27, 37, 38, 8],
		  [20, 30, 37, 27, 26, 25, 24, 22, 21],
		  [6, 16, 26, 27, 7],
		  [15, 25, 26, 16],
		  [14, 24, 25, 15],
		  [12, 22, 24, 14, 13],
		  [3, 13, 14, 15, 16, 6],
		  [2, 12, 13, 3],
		  [1, 21, 22, 12, 2],
		  [0, 20, 21, 1] ].


solve(Points, Adj) :-
    data1(M), flatten(M, MF), sort(MF, MFS),

    length(Points, 4),

    generatePoints(Points, MFS),

    recAdj(Points, M, Adj),

    length(Adj, 10).


generatePoints([_], _).
generatePoints([X, Y|Points], Array) :-
    member(X, Array), member(Y, Array), X #< Y,
    generatePoints([Y|Points], Array).
    

recAdj(Points, M, Adj) :- aux_recAdj(Points, M, Adj1, 1),
			  sort(Adj1, Adj).

aux_recAdj(_, [], [], _).
aux_recAdj(Points, [Line|M], [N|Adj], N) :-
    someContained(Points, Line),
    N1 is N + 1,
    aux_recAdj(Points, M, Adj, N1).
aux_recAdj(Points, [Line|M], Adj, N) :-
    not(someContained(Points, Line)),
    N1 is N + 1,
    aux_recAdj(Points, M, Adj, N1).


someContained([X|_], List) :- member(X, List).
someContained([_|R], List) :- someContained(R, List).
