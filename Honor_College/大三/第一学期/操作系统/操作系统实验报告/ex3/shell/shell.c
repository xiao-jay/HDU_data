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
	while (1) {
		printf("$ ");
		fgets(S, N, stdin);
		fflush(stdin);
		strip(S, T);
		// printf("%s", T);
		// printf("|\n");
		if(!strcmp(T, "cmd1") || !strcmp(T, "cmd2") || !strcmp(T, "cmd3")) {
			snprintf(tmp, N, "./%s", T);
			system(tmp);
		}
		else if (!strcmp(T, "exit")) {
			printf("shell exit\n");
			break;
		}
		else system(T);
	}
}
