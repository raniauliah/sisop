#include<stdio.h>
#include<pthread.h>

void *salin1(void *args) {
	int* status_file1=(int*)args
	
	FILE* inp, *out;
	inp = fopen("tmp.txt", "r");
	out = fopen("salin1_tmp.txt", "w");
	
	char kar;

	while(1){
		kar = fgetc(inp);
		if(kar == EOF) break;
		else fputc(kar, out);
	}

	fclose(inp);
	fclose(out);
	
	*status_file1=0;
}

void *salin2(void *args) {
	int* status_file1=(int*)args;
	
	FILE* inp, *out;
	inp = fopen("salin1_tmp.txt", "r");
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


int main () {
	pthread_t t1, t2;
	int status_file1=1;
	
	pthread_create(&t1, NULL, salin1, &status_file1);
	pthread_create(&t2, NULL, salin2, &status_file1);
	
	pthread_join(t1, NULL);
	pthread_join(t2, NULL);	
	

	return 0;
}
