/*
	Eric Paulz (epaulz)
	CPSC 3300-002
	Project 3
*/

//     *********************************
//     *    Matrix Multiply Project    *
//     *                               *
//     *********************************

//     ** MAIN PROGRAM  **


//     *************************************************
//     ** Any changes you make to this code must      **
//     ** maintain the correctness of the matrix      **
//     ** multiply computed by the original version.
//     **					      **
//     ** An implementation with incorrect results for**
//     ** matrix C earns zero point for this project. **
//     ** 
//     ** To print matrix compile with -DPRINT_MATRIX **
//     ** e.g., g++ -DPRINT_MATRIX                    **
//     **                                             **
//     ** A sample Makefile is provided.
//     ** You may assume m = n = k for your matrices  **
//     *************************************************

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>

double **dmatrix(int nrl,int nrh,int ncl,int nch);
void nerror(char *error_text);
int min(int x, int y);

int main(int argc, char** argv)  {

	int m,n,o;
	int i,ii,j,jj,k,kk;
	double temp;
	double **A, **B, **C;

	int block_size = 48;
	int sum = 0;

//  ****************************************************
//  * The following allows matrix parameters to be     *
//  * entered on the command line to take advantage    *
//  * of dynamically allocated memory.  You may modify *
//  * or remove it as you wish.                        *
//  ****************************************************

	if (argc != 4) {
		nerror("Usage:  <executable> <m-value> <n-value> <k-value>");
	}

	m = atoi(argv[1]);
	n = atoi(argv[2]);
	o = atoi(argv[3]);

	int N = m = n = o;
	
// *********************************************************
// * Call the dmatrix() subroutine to dynamically allocate *
// * storage for the matrix sizes specified by m, n, and k *  
// *********************************************************

	A=dmatrix(0,m-1,0,o-1);
	B=dmatrix(0,o-1,0,n-1);
	C=dmatrix(0,m-1,0,n-1);

// *********************************************************
//  * Initialize matrix elements so compiler does not      *
//  * optimize out                                         *
// *********************************************************

	for(j=0;j<N;j++) {
		for(i=0;i<N;i++) {
			A[i][j] = i+j+4.0;
		}
	}

	for(j=0;j<N;j++) {
		for(i=0;i<N;i++) {
			B[i][j] = i+j+5.0;
		}
	}

	for(j=0;j<N;j++) {
		for(i=0;i<N;i++) {
			C[i][j] = 0.0;
		}
	}

// ******************************
// * Start embedded timing here *
// ******************************
	struct timeval start, end;

	gettimeofday(&start,NULL);

// **********************************
// * Perform simple matrix multiply *
// **********************************
/*
	// simple
    for(j=0;j<N;j++) {
        for(k=0;k<N;k++) {
			for(i=0;i<N;i++) {
				C[i][j] = C[i][j] + B[k][j]*A[i][k];
            }
        }
	}
*/

/*
	// interchange (T1)
	for(i=0;i<N;i++){
		for(j=0;j<N;j++){
			for(k=0;k<N;k++){
				C[i][j] += A[i][k]*B[k][j];
			}
		}
	}
*/

/*
	// interchange + unrolling (T1+T2)
	for(i=0;i<N;i++){
		for(j=0;j<N;j++){
			for(k=0;k<N;k+=2){
				C[i][j] += A[i][k]*B[k][j];
				C[i][j] += A[i][k+1]*B[k+1][j];
			}
		}
	}	
*/

	// interchange + unroll + blocking (T1+T2+T3)
	for(ii=0;ii<N;ii+=block_size){
		for(jj=0;jj<N;jj+=block_size){
			for(kk=0;kk<N;kk+=block_size){
				for(i=ii;i<min(ii+block_size,N);i++){
					for(j=jj;j<min(jj+block_size,N);j++){
						sum = 0;
						for(k=kk;k<min(kk+block_size,N);k++){
							sum += A[i][k]*B[k][j];
						}
						C[i][j] += sum;
					}
				}
			}
		}
	}

// ******************************
// * Stop embedded timing here  *
// ******************************

	gettimeofday(&end,NULL);

	double elapsed_time = (end.tv_sec - start.tv_sec) + ((end.tv_usec - start.tv_usec)/1000000.0);

	printf("%lf seconds\n", elapsed_time);

// **************************************************
// * Print out a 10 x 10 matrix for testing only    *
// * Comment out when timing                        *
// **************************************************


	#ifdef PRINT_MATRIX
		fprintf(stdout, "Here is the matrix A:\n\n");
		for(i=0;i<m;i++) {
			for(j=0;j<k;j++) {
				fprintf(stdout, "%10.2f ",A[i][j]);
			}
			fprintf(stdout, "\n");
		}
		fprintf(stdout, "Here is the matrix B:\n\n");
		for(i=0;i<k;i++) {
			for(j=0;j<n;j++) {
				fprintf(stdout, "%10.2f",B[i][j]);
			}
			fprintf(stdout, "\n");
		}
		fprintf(stdout, "Here is the matrix C:\n\n");
		for(i=0;i<m;i++) {
			for(j=0;j<n;j++) {
				fprintf(stdout, "%10.2f",C[i][j]);
			}
			fprintf(stdout, "\n");
		}
	#endif        

}
//     **  END MAIN PROGRAM  **

//     ********************************************************
//     *******    BEGIN SUBROUTINES    ************************
//     ********************************************************

int min(int x, int y){
	return x < y ? x : y;
}

double **dmatrix(int nrl,int nrh,int ncl,int nch)
// Allocates a double matrix with range [nrl..nrh][ncl..nch]
{
	int i;
	double **m;

	//    Allocate pointers to rows
	m=(double **) malloc((unsigned)(nrh-nrl+1)*sizeof(double *));
	if (!m) nerror("allocation failure in malloc in dmatrix()");
	m -= nrl;
	//    Allocate rows and set pointers to them
	for(i=nrl;i<=nrh;i++) {
		m[i]=(double*) malloc((unsigned) (nch-ncl+1)*sizeof(double));
		if (!m[i]) nerror("allocaion failure in malloc in dmatrix()");
		m[i] -= ncl;
	}
	return m;
}

void nerror(char *error_text)
{
	void exit();
	fprintf(stderr, "Run-time error...\n");
	fprintf(stderr,"%s\n",error_text);
	fprintf(stderr,"Exiting...\n");
	exit(1);
}
