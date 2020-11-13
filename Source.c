#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct _set;
typedef struct _set *Position;
typedef struct _set {
	int el;
	Position next;
}Set;

Position createSet(int el);
void readFile(char*, Position, Position);
void printList(Position);
void Sort(int, Position);
void Union(Position, Position, Position);
void Intersection(Position, Position, Position);

int main() {
	FILE *FILE;
	Position P = NULL, Q = NULL;
	Set head1, head2, head3, head4;
	head1.next = NULL, head2.next = NULL, head3.next = NULL, head4.next = NULL;
	
	char fileName[256];
	printf("Insert file name (including .txt extension): ");
	scanf("%s", fileName);

	readFile(fileName, &head1, &head2);

	printf("\nList1 content:\n\t\n");
	printList(&head1);
	printf("\nList2 content:\n\t\n");
	printList(&head2);

	Union(&head1, &head2, &head3);
	printf("\nUnion of 2 sets:\n\t\n");
	printList(&head3);
	
	Intersection(&head1, &head2, &head4);
    printf("\nIntersection of 2 sets:\n\t\n");
	printList(&head4);

	return 0;
}

void readFile(char *fileName, Position head1, Position head2) {
	FILE *File;
	int el;
	
	File = fopen(fileName, "r");
	if (!File)
		printf("File failed to open!");
	char c;
	while (!feof(File))
	{
		c = fgetc(File);
		if (c != '\n') {
			fscanf(File, "%d", &el);
			Sort(el, head1);
		}
		else {
			while (!feof(File)) {
				fscanf(File, "%d", &el);
				Sort(el, head2);
			}
		}
	}


}

void Intersection(Position P, Position Q, Position head) {

	Position S = NULL;
	P = P->next;
	Q = Q->next;

	while (P != NULL || Q != NULL) {

		if (P == NULL)
			break;
		if (Q == NULL)
			break;

		if (Q->el == P->el) {
			Sort(Q->el, head);
		}

		Q = Q->next;
		P = P->next;
	}

}

void Union(Position P, Position Q, Position head) {

	Position S = NULL;
	P = P->next;
	Q = Q->next;

	while (P != NULL || Q != NULL) {
		
		if (P == NULL)
			break;
		if (Q == NULL)
			break;
		
		if (P->el != Q->el) {
			Sort(P->el, head);
		}
		
		if (Q->el != P->el) {
			Sort(Q->el, head);
		}

		if (Q->el == P->el) {
			Sort(Q->el, head);
		}

		Q = Q->next;
		P = P->next;
	}

	if (P == NULL) {
		while (Q != NULL){
			Sort(Q->el, head);
			Q = Q->next;
		}
	}
	
	if (Q == NULL) {
		while (P != NULL) {
			Sort(P->el, head);
			P = P->next;
		}
	}

}

Position createSet(int el) {
	Position K = NULL;

	K = (Position)malloc(sizeof(Set));
	if (!K)
		printf("Memory failed to allocate!");

	K->el = el;
	K->next = NULL;

	return K;
}


void Sort(int el,Position head) {
	
	Position K=NULL;

	while (head->next != NULL && head->next->el < el)
		head = head->next;

	K = createSet(el);

	K->next = head->next;
	head->next = K;

}


void printList(Position head) {
	
	if (head->next == NULL)
		printf("Linked list is empty!");
	
	head = head->next;
	
	while (head != NULL) {
		printf("\t%d\n", head->el);
		head = head->next;
	}

	puts("\n");
}