#include <stdio.h>
#include <limits.h>

// matrix Ai has dimension p[i-1] x p[i] for i=1..n
int matrix_chain(int p[], int i, int j){
    if(i == j)
        return 0;

    int count, min=INT_MAX;

    // place parenthesis at different places between first and last matrix
    // recursively calculate count of multiplications for each placement
    // return minimum count
    for(int k = i; k < j; k++){
        count = matrix_chain(p,i,k) + matrix_chain(p,k+1,j) + p[i-1]*p[k]*p[j];

        if (count < min)
            min = count;
    }
    return min;
}

int main(){
    int arr[] = {40,20,30,10,30};
    int n = sizeof(arr)/sizeof(arr[0]);

    int result = matrix_chain(arr,1,n-1);

    printf("Minimum number of multiplications is %d\n", result);

    return 0;
}
