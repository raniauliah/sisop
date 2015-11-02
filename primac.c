#include<stdio.h>

int main()
{
	int angka, i, j, counter,count_p=0;
	scanf("%d", &angka);
	
	for(i=2; i<angka; i++){
		counter=0;
		for(j=1; j<=i; j++){
			if(i%j==0) counter++;
		}
		if(counter==2) count_p++;
	}
	
	printf("Jumlah bilangan prima: %d\n", count_p);
	
	return 0;
}

