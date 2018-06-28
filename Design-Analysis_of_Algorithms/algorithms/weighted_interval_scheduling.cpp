#include <iostream>
 
 // global variables
const int SIZE = 4;
int M[SIZE];

// function prototypes
void print_array(int arr[], int SIZE);
int max(int x, int y);
int sortLists(int n, int* start, int* finish, int* weight);
int P_Compute(int SIZE, int* start, int* finish);

int main(){
	int start_times[SIZE] = {1,3,6,2};
	int finish_times[SIZE] = {2,5,19,100};
	int weights[SIZE] = {50,20,100,200};
	
	// sort jobs by finish time
	sortLists(SIZE, start_times, finish_times, weights);
	
	// compute p()
	int p[SIZE] = {0};
	for(int i = 0; i < SIZE; i++){
		p[i] = P_Compute(i, start_times, finish_times);
	}

	M[0] = 0;
	for(int j = 1; j <= SIZE; j++){
		M[j] = max(weights[j-1]+M[p[j-1]], M[j-1]);
	}
	
	std::cout << "p(): ";
	print_array(p,SIZE);
	std::cout << "M = ";
	print_array(M, SIZE+1);
	
	std::cout << "\nMaximum profit is: " << M[SIZE] << std::endl;
	
	return 0;
}

// function implementations
void print_array(int arr[], int SIZE){
	for(int i = 0; i < SIZE; i++){
		std::cout << arr[i] << " ";
	}
	std::cout << std::endl;
}

int max(int x, int y){
	return (x > y ? x : y);
}

// implement a more efficient sorting algorithm!
int sortLists(int n, int* start, int* finish, int* weight){
	for(int i = 0; i < n-1; i++){
		for(int j = i+1; j < n; j++){
			if(finish[j] < finish[i]){
				int temp_f = finish[i];
				finish[i] = finish[j];
				finish[j] = temp_f;

				int temp_s = start[i];
				start[i] = start[j];
				start[j] = temp_s;
				
				int temp_w = weight[i];
				weight[i] = weight[j];
				weight[j] = temp_w;
			}
		}
	}
}

int P_Compute(int SIZE, int* start, int* finish){
	int result = 0;
	for(int i = 0; i < SIZE; i++){
		if(finish[i] <= start[SIZE]){
			result = i+1;
		}
	}
	return result;
}
