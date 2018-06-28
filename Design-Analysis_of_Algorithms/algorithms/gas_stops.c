#include <stdio.h>

/*
int* gas_stops(int *distances, int n){
    int m = 350;
    int i = 1, j = 0;
    int stops[100];

    while(i < n-1){
        if(distances[i] + distances[i+1] > m){
            stops[j] = distances[i];
            j++;
        }

        i++;
    }

    return *stops;
}
*/

int main(void){
    int d[10] = {0, 150, 210, 100, 20, 80, 120, 175, 25, 200};
	int stops[10];
	int m = 350, i = 0, j = 0, mileage = 0;
	
	while(i < 10){
		mileage += d[i];
		if(mileage > m){
			stops[j] = d[i-1];
			j++;
			mileage = 0;
		}
		else
			i++;		
	}

    printf("Stop at the following gas stations:\n");
    for(i = 0; i < j; i++)
        printf("%d, ", stops[i]);

    printf("\n");

    return 0;
}
