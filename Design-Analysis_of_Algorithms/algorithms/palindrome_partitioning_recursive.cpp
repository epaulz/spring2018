#include <iostream>
#include <climits>
#include <string>

int MinPal(std::string word);
bool isPalindrome(std::string a);
int min(int x, int y);

int main(int argc, char* argv[]){
	
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

bool isPalindrome(std::string a){
	unsigned int i = 0, len = a.length()-1;
	
	while(i < a.length()/2){
		if(a[i] != a[len])
			return false;
		i++;
		len--;
	}
	return true;
}

int MinPal(std::string word){
	if(word.length()==0 || isPalindrome(word))
		return 0;
	
	int cuts = word.length()-1;

	for(unsigned int i = 1; i < word.length(); i++){
		cuts = min(MinPal(word.substr(0,i)) + MinPal(word.substr(i,word.length())) + 1, cuts);
	}
	
	return cuts;
}