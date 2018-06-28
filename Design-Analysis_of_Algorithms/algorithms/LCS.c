#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void LCS(char* A, char* B){
	int i=0, j=0, sp=0, *L;
	char S[20];
	
	int m = strlen(A);
	int n = strlen(B);
	
	L = (int*)malloc((m)*(n)*sizeof(int));
	
	while(i<m && j<n){
		if(A[i]==B[j]){
			S[sp] = A[i];
			sp++;
			i++;
			j++;
		}
		else if(L[(i+1)*m+j] >= L[i*m+j+1])
			i++;
		else
			j++;
	}
	S[sp] = '\0'; // pad with a null to make it a string
	
	printf("Longest common subsequence of '%s' and '%s' is: %s\n", A,B,S);
}

int main(){
	char A[20] = "naematode knowledge";
	char B[20] = "nanoee";
	
	LCS(A,B);
	
	return 0;
}
