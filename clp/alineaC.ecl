:- lib(ic).
:- lib(ic_global).
:- lib(branch_and_bound).
:- lib(lists).

model1(Points, Len) :-
    getMatrix(M), flatten(M, MF), sort(MF, MFS),

    nrec(N), div(N, 3, TMin), div(N, 2, Max),

    ( mod(N, 3, 0), Min is TMin; not(mod(N, 3, 0)), Min is TMin + 1 ),
    
    Len #>= Min, Len #=< Max, 
    
    length(Points, Len), Points #:: MFS,

    ic_global:ordered(<, Points),

    isSolution(Points, M),

    ic_global:alldifferent(Points),
    
    branch_and_bound:minimize(labeling(Points), Len).
    

getMatrix(M) :-
    guardar(RecList),
    aux_getMatrix(M, RecList).

aux_getMatrix([], []).
aux_getMatrix([Line|M], [R|Rec]) :-
    rec(R, _, Line),
    aux_getMatrix(M, Rec).

isSolution(_, []).
isSolution(Points, [Line|M]) :-
    intersect(Points, Line),
    isSolution(Points, M).

intersect([X|_], Line) :- member(X, Line).
intersect([_|XS], Line) :- intersect(XS, Line).
