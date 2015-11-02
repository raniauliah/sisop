#include<stdio.h>
#include<pthread.h>

struct arg_struct {
	int a;
	int* c;	
};

void* cekprima(void* args) {
	struct arg_struct* argumen = (struct arg_struct*)args;
	int i, status_prima = 1, flag;
	
	for(i=2 ;i<argumen->a; i++){
		if((argumen->a)%i==0) { 
			status_prima = 0;
			break;
		}	
	}
		
	if(status_prima==1) *(argumen->c)=*(argumen->c)+1;
//	printf("%d %d\n", argumen->a, *(argumen->c));
}

int main () {
	pthread_t thread[3];
	int i, N, count=0;

	struct arg_struct args1, args2, args3;
	args1.c=&count;	
	args2.c=&count;	
	args3.c=&count;	

	printf("Masukkan N :");
	scanf("%d", &N);

	for(i=2; i<N; i=i+3){
		//=============thread 1=================
		args1.a=i;
		pthread_create(&thread[i%3], NULL, cekprima, &args1);
		
		if(i+1>=N) {
			pthread_join(thread[i%3], NULL);
			break;
		}
		
		//=============thread 2=================
		args2.a=i+1;
		pthread_create(&thread[(i%3)+1], NULL, cekprima, &args2);

		if(i+2>=N) {
			pthread_join(thread[i%3], NULL);
			pthread_join(thread[(i%3)+1], NULL);
			break;
		}
		
		//=============thread 3=================
		args3.a=i+2;
		pthread_create(&thread[(i%3)+2], NULL, cekprima, &args3);		

		pthread_join(thread[i%3], NULL);
		pthread_join(thread[(i%3)+1], NULL);
		pthread_join(thread[(i%3)+2], NULL);
	}

	printf("Terdapat %d bilangan prima untuk bilangan kurang dari %d\n", count, N);
}

//pthread_exit() : digunakan utk memberikan return value pada thread ini (thread dimana fungsi ini dipanggil). terdapat pada thread start funtion
//nilai return value sebuah thread, akan di panggil melalui pthread_join() pada fungsi main.

//untuk menggunakan multiple argumen pada pthread_create, argumen2 yg akan dipassing perlu dibungkus dalam bentuk struck
