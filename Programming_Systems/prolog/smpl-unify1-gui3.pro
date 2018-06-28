/* smpl-unify1-gui3.pro */

startDebug :- spy(first), spy(second), spy(goal1), spy(goal2).
guitracer.

goal1(X,Y) :- first(X), second(Y).

goal2(X) :- first(X), second(X).

first(1).
first(2).
first(3).
second(2).
second(4).
second(6).