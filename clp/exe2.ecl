:- lib(ic).
:- lib(ic_global).
:- lib(branch_and_bound).

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

data1(X) :- X = [ [7, 27, 37, 38, 8],
		  [20, 30, 37, 27, 26, 25, 24, 22, 21],
		  [6, 16, 26, 27, 7],
		  [15, 25, 26, 16],
		  [14, 24, 25, 15],
		  [12, 22, 24, 14, 13],
		  [3, 13, 14, 15, 16, 6],
		  [2, 12, 13, 3],
		  [1, 21, 22, 12, 2],
		  [0, 20, 21, 1] ].


solve(Points) :-
    data1(M), flatten(M, MF), sort(MF, MFS),

    length(Points, Len), Len #>= N, Len #>= 4,

    Points #:: MFS,

    ic_global:alldifferent(Points),

    ic_global:ordered(<, Points),

    contains(M, Points),

    minimize(labeling(Points), Len).

contains([], _).
contains([Line|M], Points) :- intersect(Line, Points),
			      contains(M, Points).

intersect([X|_], Points) :- member(X, Points).
intersect([_|XS], Points) :- intersect(XS, Points).
