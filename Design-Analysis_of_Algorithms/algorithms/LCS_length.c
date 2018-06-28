#include <stdio.h>

int max(int x, int y){
	return x > y ? x : y;
}

int lcs_length(char* A, char* B){
	if(*A=='\0' || *B=='\0')
		return 0;
	
	else if(*A==*B)
		return 1 + lcs_length(A+1,B+1);
	
	else
		return max(lcs_length(A+1,B), lcs_length(A,B+1));
}

int main(){
	char A[20] = "naematode knowledge";
	char B[20] = "nanoee";
	
	printf("Length of LCS of A and B is %d\n", lcs_length(A,B));
	
	return 0;
}