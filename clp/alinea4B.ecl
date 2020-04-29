:- lib(lists).

solve(Points, Len) :-
    length(Points, Len),
    generate(Points),
    isGoal(Points).

generate(Points) :-
    aux_generate(Points, []).

aux_generate([], _).
aux_generate([X|Points], Prev) :-
    p(X, _, _),
    not(member(X, Prev)),
    sorted([X|Prev]),
    aux_generate(Points, [X|Prev]).

sorted([]).
sorted([_]).
sorted([X, Y|R]) :- compare(>, X, Y), 
		    sorted([Y|R]).    

isGoal(Points) :-
    guardar(Rec),
    aux_isGoal(Points, Rec).

aux_isGoal(_, []).
aux_isGoal(Points, [R|Rec]) :-
    rec(R, _, List),
    lists:intersection(Points, List, Result),
    Result \= [],
    aux_isGoal(Points, Rec).
