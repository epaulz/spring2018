/* listProcess.pro */

someOper(X,R) :- R is X*X.

listProcess([],[]). /* <-- for termination of recursion */
listProcess([AH|AT],[RH|RT]) :- someOper(AH,RH),listProcess(AT,RT).
