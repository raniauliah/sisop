#include<stdio.h>
#include<pthread.h>

int count_p=0;

void *count_prime(void *args){
	int j, counter=0;
	int *i=(int *)args;	

	for(j=1; j<=*i; j++){
		if(*i%j==0) counter++;
	}
	if(counter==2) count_p++;
}

int main()
{
	pthread_t thread1;
	int angka, i, j, counter;
	scanf("%d", &angka);
	
	for(i=2; i<angka; i++){
		pthread_create(&thread1, NULL, count_prime, (void *)&i);
		pthread_join(thread1, NULL);
	}
	
	printf("Jumlah bilangan prima: %d\n", count_p);
	
	return 0;
}

