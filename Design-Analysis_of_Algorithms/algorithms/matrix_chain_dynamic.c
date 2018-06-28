#include <stdio.h>
#include <limits.h>

// matrix Ai has dimension p[i-1] x p[i] for i=1..n
int matrix_chain(int p[], int n){
    int m[n][n];

    // m[i,j] = minimum number of scalar multiplications needed to compute
    // the matrix A[i]A[i+1]...A[j] = A[i..j] when dimension of A[i] is
    // p[i-1] x p[i]

    // cost of multiplying one matrix is zero
    for(int i=1; i<n; i++)
        m[i][i]=0;

    // 'len' is chain length
    for(int len=2; len<n; len++){
        for(int i=1; i<(n-len+1); i++){
            int j = i+len-1;
            m[i][j] = INT_MAX;

            for(int k=i; k<j; k++){
                // q = cost/scalar multiplications
                int q = m[i][k] + m[k+1][j] + p[i-1]*p[k]*p[j];
                if(q < m[i][j])
                    m[i][j] = q;
            }
        }
    }
    return m[1][n-1];
}

int main(){
    int arr[] = {40,20,30,10,30};
    int size = sizeof(arr)/sizeof(arr[0]);

    int result = matrix_chain(arr,size);
    
    printf("Minimum number of multiplications is %d\n", result);

    return 0;
}
