% Here's where we'll design, implement and test
% mmember/2 (file mmember.pro)

/* 
	X is an element of a list if X is the head of the list
	OR
	X is a member of the tail of the list
*/

mmember(X,[X|_]).	 % <-- search for X in list [X|_]

% OR

mmember(X,[_|Y]) :- mmember(X,Y).
