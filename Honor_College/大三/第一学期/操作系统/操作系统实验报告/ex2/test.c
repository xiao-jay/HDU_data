#include <stdio.h>
#include <string.h>
char ind[100];
int main() {
	int l = 25;
	snprintf(ind, 99, "%s", "gg");
	snprintf(ind, 99, "%saa", ind);
	printf("%s", ind);
}
