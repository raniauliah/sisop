#include<stdio.h>
#include<pthread.h>
#include<stdlib.h>

struct arg_struct {
	int bil;
	int* count_ptr;
}

void *count_prime(void *args){
	int j, counter=0;
	struct arg_struct* argumen=(struct arg_struct*)args;	

	for(j=1; j<=argumen->a; j++){
		if(argumen->a%j==0) counter++;
	}
	if(counter==2) *(argumen->count_ptr)=*(argumen->count_ptr)+1;
}

int main()
{
	pthread_t thread1;
	int angka, i, count=0;
	
	scanf("%d", &angka);
	
	struct arg_struct args=(struct arg_struct*)malloc(sizeof(struct arg_struct)*(angka+1));
	pthread_t* thread=(pthread_t*)malloc(sizeof(pthread_t)*(angka+1));
	
	for(i=2; i<angka; i++){
		args[i].bil=i;
		args[i].counter_ptr=&count;
		pthread_create(&thread[i], NULL, count_prime, &args[i]);
	}
	
	for(i=2; i<angka; i++){
		pthread_join(thread[i], NULL);
	}
	
	printf("Jumlah bilangan prima: %d\n", count);
	
	return 0;
}

