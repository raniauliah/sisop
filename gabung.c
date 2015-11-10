#include<stdio.h>
#include<pthread.h>
#include<stdlib.h>

void *salin1(void *args) {
	int* status_file1=(int*)args;
	
	FILE* inp, *out;
	inp = fopen("tmp.txt", "r");
	out = fopen("salin1_tmp.txt", "w");
	*status_file1=1;	

	char kar;

	while(1){
		kar = fgetc(inp);
		if(kar == EOF) break;
		else fputc(kar, out);
	}

	fclose(inp);
	fclose(out);
	
	*status_file1=2;
}

void *salin2(void *args) {
	int* status_file1=(int*)args;
	
	FILE* inp, *out;

	while(1){
		if(*status_file1==0) continue;
		else {
			inp = fopen("salin1_tmp.txt", "r");
			break;
		}
	}
	
	out = fopen("salin2_tmp.txt", "w");
	
	char kar;

	while(1){
		kar = fgetc(inp);
		if(kar == EOF) {
			if((*status_file1)==1) continue;
			else break;
		}
		else fputc(kar, out);
	}

	fclose(inp);
	fclose(out);
}

struct arg_struct {
	int bil;
	int* count_ptr;
};

void *count_prime(void *args){
	int j, counter=0;
	struct arg_struct* argumen=(struct arg_struct*)args;	

	for(j=1; j<=(argumen->bil); j++){
		if((argumen->bil)%j==0) counter++;
	}
	if(counter==2) *(argumen->count_ptr)=*(argumen->count_ptr)+1;
}

int main()
{
	int perintah;
	
	while(1){
		printf("Masukkan Perintah:\n0 Keluar\n");
		printf("1 Mencari Jumlah Bilangan Prima Kurang dari N\n");		
		printf("2 Menyalin Isi File\n");
		scanf("%d", &perintah);
		if(perintah==0){
			printf("Terima Kasih! :D\n");
			break;	
		}
		else if(perintah==1){
			pthread_t thread1;
			int angka, i, count=0;
	
			printf("Masukkan N: ");
			scanf("%d", &angka);
	
			struct arg_struct* args=(struct arg_struct*)malloc(sizeof(struct arg_struct)*(angka+1));
			pthread_t* thread=(pthread_t*)malloc(sizeof(pthread_t)*(angka+1));
	
			for(i=2; i<angka; i++){
				args[i].bil=i;
				args[i].count_ptr=&count;
				pthread_create(&thread[i], NULL, count_prime, &args[i]);
			}
	
			for(i=2; i<angka; i++){
				pthread_join(thread[i], NULL);
			}
	
			printf("Jumlah bilangan prima: %d\n\n", count);
		}

		else if(perintah==2){
			pthread_t t1, t2;
			int status_file1=0;
	
			pthread_create(&t1, NULL, salin1, &status_file1);
			pthread_create(&t2, NULL, salin2, &status_file1);
	
			pthread_join(t1, NULL);
			pthread_join(t2, NULL);
			
			printf("Selesai!\n\n");
		}

		else printf("Perintah Tidak Ditemukan!\n\n");
	}
	
	return 0;
}
