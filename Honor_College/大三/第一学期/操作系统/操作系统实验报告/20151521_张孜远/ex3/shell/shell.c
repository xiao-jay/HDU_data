#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <wait.h>
#include <unistd.h>
#define N 1010

char S[N], T[N], tmp[N];
void strip(char *in, char *out) {
	for (; *in == ' '; ++in);
	strncpy(out, in, N);
	// printf("%d\n", strlen(out));
	char *p = out + strlen(out);
	if (*(p - 1) == '\n') *(--p) = '\0';
	for (; p > out && *(p - 1) == ' ';) *(--p) = '\0';
}
int main() {
	int f = 0;
	while (1) {
		printf("$ ");
		fgets(S, N, stdin);
		fflush(stdin);
		strip(S, T);
		// printf("%s", T);
		// printf("|\n");
		if(!strcmp(T, "cmd1") || !strcmp(T, "cmd2") || !strcmp(T, "cmd3")) {
			f = 1;
			snprintf(tmp, N, "./%s", T);
			system(tmp);
		}
		else if (!strcmp(T, "exit")) {
			f = 1;
			printf("Simulating Shell Experiment exits\n");
			break;
		}else if(T[0] == 'f' && T[1] == 'i' && T[2] == 'n' && T[3] == 'd' || T[0] == 'g' && T[1] == 'r' && T[2] == 'e' && T[3] == 'p') system(T);
		else printf("Command not found\n");
	}
}
