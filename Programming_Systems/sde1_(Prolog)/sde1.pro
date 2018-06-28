/*
	Eric Paulz (epaulz)
	CPSC 3520-001
	SDE1 - Prolog
	
	file: sde1.pro
*/

%---------------------------------------------------------------------------------------------------------------

/* get_table_values_cell/3
	Prototype: get_table_values_cell([+I,+J],+Table,-ContentsL)
*/

get_table_values_cell([I,J],Table,ContentsL) :-
	nth1(J,Table,RowList), nth1(I,RowList,ContentsL).
																	 
%---------------------------------------------------------------------------------------------------------------

/* decompositions/2
	Prototype: decompositions(+N,-List_of_decomposition_sublists)
*/

% reverse a single list
reverse([],Z,Z).
reverse([H|T],Z,Acc) :- reverse(T,Z,[H|Acc]).

% create a list containing 1 through n and another that is its reverse
make_list(N, List, ReverseList) :-
	Nminus is N-1,
	numlist(1, Nminus, List), 
	reverse(List,ReverseList,[]).

% create a list of sublists containing pairs from the original two lists
subs([],[],[]).
subs([H1|T1], [H2|T2], [[X,Y]|NTail]) :-
	X is H2, Y is H1, subs(T1, T2, NTail).

decompositions(N,List_of_decomposition_sublists) :-
	make_list(N,Ls,LsR), subs(Ls,LsR,List_of_decomposition_sublists).
	
%---------------------------------------------------------------------------------------------------------------

/* one_product/3
	Prototype: one_product(+Nonterminal,+Cell,-Product)
*/

one_product([],_,[]) :- !.
one_product(_,[],[]) :- !.
one_product(Nonterminal,Cell,Product) :-
	prod1(Nonterminal,Cell,Product).

prod1(_,[],[]).
prod1(X,[Head|Tail],[Y|NTail]) :-
	string_concat(X,Head,Y), prod1(X,Tail,NTail).

%---------------------------------------------------------------------------------------------------------------

/* cell_products/3
	Prototype: cell_products(+Cell1, +Cell2, -Product)
*/

cell_products([],_,[]) :- !.
cell_products(_,[],[]) :- !.
cell_products(Cell1,Cell2,Product) :-
	bagof([X,Y],(member(X,Cell1),member(Y,Cell2)),Res), prod2(Res,Product).

prod2([],[]).
prod2([[X,Y]|T],[R|Rtail]) :- string_concat(X,Y,R), prod2(T,Rtail).

%---------------------------------------------------------------------------------------------------------------

/* form_row1_cell/3
	Prototype: form_row1_cell(+StringElement,+ProductionsList,-Row1Cell)
*/

form_row1_cell(StringElement,ProductionsList,Row1Cell) :- 
	helper(StringElement,ProductionsList,Row1Cell).

helper(_,[],[]).
helper(A,[[X,Y]|T],[R|Rtail]) :- member(A,[X,Y]), !, R=X, helper(A,T,Rtail).
helper(A,[_|T],Q) :- helper(A,T,Q).

%---------------------------------------------------------------------------------------------------------------

/* equivalent/2
	Prototype: equivalent(+A,+B)
*/

equivalent(A,B) :- msort(A,S),msort(B,T), S=T.

%---------------------------------------------------------------------------------------------------------------

/* row_equivalent/2
	Prototype: row_equivalent(+RowA,+RowB)
*/

row_equivalent(RowA,RowB) :- r_eq(RowA,RowB).

r_eq([],[]).
r_eq([H1|T1],[H2|T2]) :-
	equivalent(H1,H2), r_eq(T1,T2).

%---------------------------------------------------------------------------------------------------------------

/* table_equivalent/2
	Prototype: table_equivalent(+TableA,+TableB)
*/

table_equivalent(TableA,TableB) :- t_eq(TableA,TableB).

t_eq([],[]).
t_eq([H1|T1],[H2|T2]) :-
	row_equivalent(H1,H2), t_eq(T1,T2).

%---END---------------------------------------------------------------------------------------------------------
