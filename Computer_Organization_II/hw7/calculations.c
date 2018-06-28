#include <stdio.h>

int main(){
/*
    unsigned int x = 0x002468ac;
   
    printf("x = %d\n", x);
    printf("x / 64 = %d R %d\n", x/64, x%64);
    printf("x >> 6 = %d\n", x>>6);
*/

	int a[10] = {0,16,1,31,2,32,3,17,4,18};
	for(int i = 0; i < 10; i++){
		printf("%d ", a[i]%4);
	}
	printf("\n");
	
    return 0;
}
