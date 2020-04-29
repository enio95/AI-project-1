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


color(Points, Color) :-
    length(Points, Len), length(Color, Len), Color #:: 1..10,

    member(X, Points), member(Y, Points), X #\= Y,

    data1(M), neighbor(M, X, Y), 

    getColor(Points, Color, X, XC), getColor(Points, Color, Y, YC),
    
    XC #\= YC, sort(Color, ColorS), length(ColorS, N),

    minimize(labeling(Color), N).


getColor([P|_], [C|_], P, C).
getColor([P1|Points], [_|Color], P, C) :-
    P1 #\= P,
    getColor(Points, Color, P, C).

neighbor(Matrix, P1, P2) :-
    recAdj(Matrix, P1, 1, Adj1),
    recAdj(Matrix, P2, 1, Adj2),
    intersect(Adj1, Adj2).

recAdj([], _, _, []).
recAdj([Line|Matrix], P, N, [N|Adj]) :-
    member(P, Line),
    N1 is N + 1,
    recAdj(Matrix, P, N1, Adj).
recAdj([Line|Matrix], P, N, Adj) :-
    not(member(P, Line)),
    N1 is N + 1,
    recAdj(Matrix, P, N1, Adj).
