#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<signal.h>

//#define COLOR_RED "\33[0:31m\\]"
//#define COLOR_END "\33[0m\\]"
#define BUFFSIZE 1024
#define DELIMITER " \t\r\n\a"

void signalhandler(int signum) {
	/*do nothing*/
	char cwd[1024];
//	printf("\nERROR: Cannot be stopped by ctrl+c\n");
	getcwd(cwd, sizeof(cwd));	
	printf("\ne14shell:%s>> ", cwd);
	fflush(stdout);
}

char* read_line() {
	int bufsize = BUFFSIZE;
	int position = 0;

	char* buffer=(char*)malloc(sizeof(char)*bufsize);
	char c;

	while(1) {
		c=getchar();
		if(c==EOF){
			printf("\n");
//			getchar();
			exit(1);
		}
		else if(c=='\n') {
			buffer[position]='\0';
			return buffer;
		}
		else buffer[position] = c;

		position = position + 1;
	}
}

char** split_line(char* line, int* isBg_ptr) {
	int bufsize = BUFFSIZE;
	int position = 0;
	char** tokens = malloc(sizeof(char)*bufsize);
	char* token;

	token = strtok(line, DELIMITER);
	while(token!=NULL){
		tokens[position]=token;
		position=position+1;

		token=strtok(NULL, DELIMITER);
	}

	if(strcmp(tokens[position-1], "&")==0) {
		*isBg_ptr=1;
		tokens[position-1]=NULL;
	}

	tokens[position]=NULL;
	return tokens;
}

int execute(char** args, int* isBg_ptr){
	if(strcmp(args[0], "cd")==0){
		if(args[1] == NULL) {
			fprintf(stderr, "ERROR: expected argument for \"cd\"\n");
		}
		else {
			if(chdir(args[1])) perror("TEST");
		}
	}

	else {
		pid_t pid, wpid;
		int status;

		pid = fork();
		if(pid == 0) {
			execvp(args[0], args);
		}
		else if (pid<0){
			printf("error\n");
		}
		else if (*isBg_ptr==1) {	
			/*dont wait*/
		}
		else {
			do {
			wpid = waitpid(pid, &status, WUNTRACED);
			} while (!WIFEXITED(status) && !WIFSIGNALED(status));
		}
	}

	return 1;
}

int main (int argc, char** argv)
{
	char* cmdLine; 
	char** command;	
	int status;
	char cwd[1024];
	int isBackground=0;

	signal(SIGINT, signalhandler);
	signal(SIGTSTP, signalhandler);

	while(1) {
		getcwd(cwd, sizeof(cwd));

		printf("e14shell:%s>> ", cwd);
		cmdLine=read_line();

		command=split_line(cmdLine, &isBackground);

		if(command[0]==NULL) continue;

		status=execute(command, &isBackground);

		free(cmdLine);
		free(command);
		status=0;
		memset(cwd, 0, sizeof(cwd));
		isBackground=0;
	}
}
