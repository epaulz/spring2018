#include <iostream>

int max(int x, int y){
	return x > y ? x : y;
}

//returns maximum value that can be put in a knapsack of capacity W
int knapsack(int W, int wt[], int val[], int n){
	int K[n+1][W+1];
	
	// build table K[][] in a bottom up manner
	for(int i=0; i<=n; i++){
		for(int w=0; w<=W; w++){
			if(i==0 || w==0)
				K[i][w] = 0;
			else if(wt[i-1]<=w)
				K[i][w] = max(val[i-1]+K[i-1][w-wt[i-1]], K[i-1][w]);
			else
				K[i][w] = K[i-1][w];
		}
	}
	return K[n][W];
}

int main(){
	int val[] = {60,100,120};
	int wt[] = {10,20,30};
	int W = 50;
	int n = sizeof(val)/sizeof(val[0]);
	
	std::cout << "Maximum value is: " << knapsack(W,wt,val,n) << std::endl;
	
	return 0;
}