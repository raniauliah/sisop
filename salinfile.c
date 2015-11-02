#include<stdio.h>
#include<pthread.h>

void *salin1(void *args) {
	FILE* inp, *out;
	inp = fopen("tmp.txt", "r");
	out = fopen("salin1_tmp.txt", "w+");
	
	char kar;

	while(1){
		kar = fgetc(inp);
		if(kar == EOF) break;
		else fputc(kar, out);
	}

	fclose(inp);
	fclose(out);
	
}

void *salin2(void *args) {
	FILE* inp, *out;
	inp = fopen("salin1_tmp.txt", "r");
	out = fopen("salin2_tmp.txt", "w+");
	
	char kar;

	while(1){
		kar = fgetc(inp);
		if(kar == EOF) break;
		else fputc(kar, out);
	}

	fclose(inp);
	fclose(out);
}


int main () {
	pthread_t t1, t2;
	
	pthread_create(&t1, NULL, salin1, NULL);
	pthread_join(t1, NULL);

	pthread_create(&t2, NULL, salin2, NULL);
	pthread_join(t2, NULL);	

	return 0;
}
