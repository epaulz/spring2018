#include <iostream>
/*
// iterative
int fact(int n){
	int f = 1;
	for(int i = 2; i <= n; i++){
		f *= i;
	}
	return f;
}
*/

// recursive
int fact(int n){
	if(n==1)
		return 1;
	return n * fact(n-1);
}
int main(int argc, char** argv){
	int n;
	std::cout << "*** FACTORIAL CALCULATOR ***\n\n";
	
	while(1){
		std::cout << "Enter a number (-1 to quit): ";
		std::cin >> n;
		
		if(n == -1)
			break;
		
		int m = fact(n);
		
		std::cout << n << "! = " << m << "\n\n";
	}
	
	return 0;
}