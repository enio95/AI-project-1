:- lib(ic).
:- lib(ic_global).
:- lib(branch_and_bound).
:- lib(lists).

%eu amanha vou meter isto no relatório e reformular para aqui mas deixo aqui até poder meter
/*executa o algoritmo. Obtém a matriz, "alisa-sa", tornando numa única lista, e ordena-a, e constrói uma lista Points, ordenada e
de todos valores únicos de tamanho entre o nº de retângulos a dividir por 3 e o nº de retângulos a dividir por 2, 
que será instanciada por todas as permutações dos valores da matriz, encontrando-se a solução mínima utilizando-se branch_and_bound*/
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
