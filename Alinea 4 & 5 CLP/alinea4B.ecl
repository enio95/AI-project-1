:- lib(lists).

%executa o algoritmo
solve(Points, Len) :-
    length(Points, Len),
    generate(Points),
    isGoal(Points).

/*gera uma lista de pontos únicos e ordenados de forma descrescente com os identificadores dos pontos contidos no predicado p/3 */
generate(Points) :-
    aux_generate(Points, []).


aux_generate([], _).
aux_generate([X|Points], Prev) :-
    p(X, _, _),
    not(member(X, Prev)),
    sorted([X|Prev]),
    aux_generate(Points, [X|Prev]).

%ordena a lista por ordem decrescente
sorted([]).
sorted([_]).
sorted([X, Y|R]) :- compare(>, X, Y), 
		    sorted([Y|R]).    

/*retorna a lista Points que foi retornada de aux_isGoal/2*/
isGoal(Points) :-
    guardar(Rec), %lista de todos os identificadores de retângulos
    aux_isGoal(Points, Rec).

/*retorna a lista de pontos Points que, para cada lista, List, correspondete ao identificador de retângulos ( rec(R,_,List))
para todos os identificadores de retângulos, a sua interseção com a respetiva List não é nula */
aux_isGoal(_, []).
aux_isGoal(Points, [R|Rec]) :-
    rec(R, _, List),
    lists:intersection(Points, List, Result),
    Result \= [],
    aux_isGoal(Points, Rec).
