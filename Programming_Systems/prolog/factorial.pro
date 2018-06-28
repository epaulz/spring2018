% a simple fact (factorial(1)=1)
% file: factorial.pro

factorial(1,1).

% a rule to recursively define (or describe) 'factorial'

factorial(N,Result) :- 
	Iminus1 is N-1,  % 'is' means equals
factorial(Iminus1,Fminus1),
Result is N*Fminus1.
