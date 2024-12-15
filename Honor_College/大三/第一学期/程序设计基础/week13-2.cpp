#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <windows.h>

void File();
void Edit();
void Help();
void Exit();

int showmenu(char *menu[], int n){
	int i;
	int choice;
	for (i = 0; i < n; ++i){
		puts(menu[i]);
	}
	printf("Enter your choice: ");
	scanf("%d", &choice);
	return choice;
}

int main(){
	int choice;
	char *mainmenu[] = {"1.File", "2.Edit", "3.Help", "0.Exit"};
	while (1){
		choice = showmenu(mainmenu, 4);
		switch (choice){
			case 1:
				File();
				break;
			case 2:
				Edit();
				break;
			case 3:
				Help();
				break;
			case 0:
				Exit();
				break;
			default:
				printf("Invalid Choice.");
				system("cls");
		}
	}
	return 0;
} 



