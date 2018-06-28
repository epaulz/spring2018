#include <iostream>

int fib(int n){
	if(n <= 1)
		return n;
	
	return fib(n-1) + fib(n-2);
}

int main(int argc, char** argv){
	int n;
	std::cout << "*** FIBONACCI CALCULATOR ***\n\n";
	
	while(1){
		std::cout << "Enter a number (-1 to quit): ";
		std::cin >> n;
		
		if(n == -1)
			break;
		
		int m = fib(n);
		
		std::cout << "fib(" << n << ") = " << m << "\n\n";
	}
}