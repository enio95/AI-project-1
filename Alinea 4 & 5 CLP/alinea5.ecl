:-lib(ic).
:-lib(lists).
:-lib(ic_global).
:-lib(branch_and_bound).

%executa o algoritmo. 
model1(Points, Color, Len, Sum) :-
    getMatrix(M), flatten(M, MF), sort(MF, MFS),

    nrec(N), div(N, 3, TMin), div(N, 2, Max),

    ( mod(N, 3, 0), Min is TMin; not(mod(N, 3, 0)), Min is TMin + 1 ),
    
    Len #>= Min, Len #=< Max, 
    
    length(Points, Len), Points #:: MFS,

    length(Color, Len), Color #:: 1..N,

    ic_global:ordered(<, Points),

    labeling(Points),
    
    isSolution(Points, M),

    restrictColor(Points, Color, M),
    
    Sum #>= Len, N1 is N*Len, Sum #=< N1,
    
    ic_global:sumlist(Color, Sum), 
    
    minimize(labeling(Color), Sum).
 
restrictColor(_, _, []).
restrictColor(Points, Color, [Line|M]) :-
    lists:intersection(Points, Line, Inter),
    getColor(Points, Color, Inter, SubColor),
    ic_global:alldifferent(SubColor),
    restrictColor(Points, Color, M).

getColor([], _, _, []).
getColor([X|Points], [C|Color], Inter, [C|SubColor]) :-
    member(X, Inter), 
    getColor(Points, Color, Inter, SubColor).
getColor([X|Points], [_|Color], Inter, SubColor) :-
    not(member(X, Inter)),
    getColor(Points, Color, Inter, SubColor).

%cria uma matriz a partir das listas List correspondentes a cada identificador de retângulos, rec(R,_,List)
getMatrix(M) :-
    guardar(RecList),
    aux_getMatrix(M, RecList).

aux_getMatrix([], []).
aux_getMatrix([Line|M], [R|Rec]) :-
    rec(R, _, Line),
    aux_getMatrix(M, Rec).

%retorna true se a lista de pontos Points contiver pelo menos um ponto em cada uma das linhas da matriz M
isSolution(_, []).
isSolution(Points, [Line|M]) :-
    intersect(Points, Line),
    isSolution(Points, M).

%retorna true se a interseção das duas listas não for nula 
intersect([X|_], Line) :- member(X, Line).
intersect([_|XS], Line) :- intersect(XS, Line).
