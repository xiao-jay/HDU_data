#include <stdio.h>
#include <stdlib.h>

struct node{
    int data;
    int count;
    struct node *next;
};

struct node *insert(struct node *head, int x){
	struct node *p1, *p2, *p; // Ç°ÏòÖ¸Õë ºÍ ¸úËæÖ¸Õë
	p1 = head;
	p2 = NULL;
	while (p1 != NULL && p1->data > x){
		p2 = p1;
		p1 = p1->next;
	} 
	p = (struct node*)malloc(sizeof(struct node));
	p->data = x;
	if (p1 == head){
		// insert before head
		p->next = head;
		head = p;
	}else if (p1 == NULL){
		// insert after tail
		p2->next = p;
		p->next = NULL;
	}else{
		p->next = p1;
		p2->next = p;
	}
	return head;
}

struct node *find(struct node *head, int x){
	struct node *p;
	p = head;
	while (p != NULL && p->next != x){
		p = p->next;
	}
	return p;
}

struct node *create(){
	int x;
	struct node *head, *tail, *p, *fp;
	head = NULL;
	tail = NULL;
	while (scanf("%d", &x) && x != -1){
		fp = find(head, x);
		p = (struct node*)malloc(sizeof(struct node));
		if (fp != NULL){
			fp->count++;
		}else{
			if (p == NULL){
				printf("ÉêÇë¿Õ¼äÊ§°Ü!");
				exit(-1); 
		}else{
			p->data = x;
			p->count = 1;
			if (head == NULL){
				// empty link
				head = p;
				tail = p;
				p->next = NULL;
			}else{
//				// Í·²å
//				p->next = head;
//				head = p; 
				
				// Î²²å
				tail->next = p;
				p->next = NULL;
				tail = p; 
			}
			}	
		}
	}
	return head; 
}

void show(struct node *head){
	struct node *p;
	p = head;
	while (p != NULL){
		printf("%d %d", p->data, p->count);
		p = p->next;
	}
}

void freelink(struct node *head){
	struct node *p;
	p = head;
	while (p != NULL){
		head = p->next;
		free(p);
		p = head;
	}
}

int main(){
    struct node *head;
    head = create();
    show(head);
    printf("enter inserted x: ");
    scanf("%d", &x);
    head = insert(head, x);
    show(head);
    freelink(head);
    return 0;
}



