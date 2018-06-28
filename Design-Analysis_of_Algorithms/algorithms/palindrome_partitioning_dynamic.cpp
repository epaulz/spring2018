#include <iostream>
#include <string>
#include <climits>

int MinPal(std::string s);
int min(int x, int y);

int main(int argc, char* argv[]){
	
	// for usage
	if(argc != 2){
		std::cout << "Usage: <executable> <string>\n";
		return 1;
	}
	
	std::string s = argv[1];
	
	int x = MinPal(s);
	
	std::cout << "\nThe minimum number of palindromes in '" << s << "' is " << x+1;
	std::cout << std::endl << std::endl;
		
	return 0;
}

int min(int x, int y){
	return(x < y ? x : y);
}

int MinPal(std::string s){
	// get string length
	int strLen = s.length();
	int i, j, k, subStrLen;
	
	int C[strLen][strLen];	   // min number of palindrome cuts in each substring
	bool P[strLen][strLen];  // true if substring is a palindrome
	
	// every substring of length 1 is a palindrome
	for(i = 0; i < strLen; i++){
		C[i][i] = 0;
		P[i][i] = true;
	}
	
	// consider all substrings of length subStrLen starting from 2 to strLen
	for(subStrLen = 2; subStrLen <= strLen; subStrLen++){
		// for substring of length subStrLen, check all different starting indexes
		for(i = 0; i < strLen-subStrLen+1; i++){
			j = i+subStrLen-1; // set ending index
			
			// if subStrLen is 2, only compare those two characters
			// otherwise, check those two characters AND the value of P[i+1][j-1]
			if(subStrLen==2)
				P[i][j] = (s[i] == s[j]);
			else
				P[i][j] = (s[i] == s[j]) && P[i+1][j-1];
			
			// if string[i..j] is a palindrome, then C[i][j] is 0 (minimum cuts is 0)
			if(P[i][j])
				C[i][j] = 0;
			else{
				// make a cut at every location starting from i to j-1
				// and compute the minimum cost cut
				C[i][j] = INT_MAX;
				for(k = i; k <= j-1; k++){
					C[i][j] = min(C[i][j], C[i][k] + C[k+1][j] + 1);
				}
			}
		}
	}	
	//C[0][strLen-1] represents minimum cuts over the whole original string... return it
	return C[0][strLen-1];
}

