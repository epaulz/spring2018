adj-to(car,road).
adj-to(road,grass).
adj-to(road,trees).
adj-to(sky,trees).
adj-to(grass,trees).

adjacent-to(X,Y) :- adj-to(X,Y).
adjacent-to(X,Y) :- adj-to(Y,X).

/* observations of adjacency */

goal([R1,R2,R3,R4,R5,R6]) :- adjacent-to(R1,R2),
									  adjacent-to(R2,R6),
									  adjacent-to(R2,R3),
									  adjacent-to(R3,R4),
									  adjacent-to(R2,R4),
									  adjacent-to(R4,R6),
									  adjacent-to(R4,R5),
									  highest(R1).
