#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define ERROR -1
#define MAX 1024

typedef struct Cvor* Stog;
typedef struct Cvor {
	int br;
	char opr;

	Stog next;
}st;

int izvod(Stog head, char* fn);
Stog NewCharacter(float broj, char operand);
Stog FindPrev(Stog A, Stog head);

int main()
{
	st head = { .br = 0, .opr = NULL, .next = NULL};

	izvod(&head, "dat.txt");

	return 0;
}

int izvod(Stog head, char* fn)
{
	FILE* f = NULL;
	char* buffer = (char*)malloc(MAX * sizeof(char));
	//float tempbr, temprez;
	int tempbr;
	char tempopr;
	Stog temp = head, temp2, prev, pprev;

	f = fopen(fn, "r");
	if (f == NULL)
		return ERROR;

	fgets(buffer, MAX, f);
	//while (!feof(f))
	//{
		while (sscanf(buffer, " %d", &tempbr) == 1)
		{
			temp->next = NewCharacter(tempbr, NULL);
			temp = temp->next;
			*buffer++;
		}
		temp = head->next;
		while (temp->next != NULL)
		{
			printf("%d\n", temp->br);
			temp = temp->next;
		}

		/*sscanf(buffer, " %c", tempopr);
		temp->next = NewCharacter(0, &tempopr);
		temp = temp->next;
		*buffer++;

		temp2 = head->next;
		switch (temp->opr) {
		case '+':
			temprez = 0;
			while (temp2->next != NULL)
			{
				temprez += temp2->br;
				prev = temp2;
				temp2 = temp2->next;
				pprev = FindPrev(prev, head);
				pprev->next = temp2;
				free(prev);
			}
			break;

		case '-':
			temprez = 0;
			while (temp2->next != NULL)
			{
				temprez -= temp2->br;
				prev = temp2;
				temp2 = temp2->next;
				pprev = FindPrev(prev, head);
				pprev->next = temp2;
				free(prev);
			}
			break;

		case '*':
			temprez = 1;
			while (temp2->next != NULL)
			{
				temprez *= temp2->br;
				prev = temp2;
				temp2 = temp2->next;
				pprev = FindPrev(prev, head);
				pprev->next = temp2;
				free(prev);
			}
			break;

		case '/':
			temprez = 1;
			while (temp2->next != NULL)
			{
				temprez /= temp2->br;
				prev = temp2;
				temp2 = temp2->next;
				pprev = FindPrev(prev, head);
				pprev->next = temp2;
				free(prev);
			}
			break;
		}*/
	//}
}

Stog NewCharacter(float broj, char operand)
{
	Stog newChar = (Stog)malloc(sizeof(st));
	newChar->next = NULL;
	newChar->br = broj;
	newChar->opr = operand;

	return newChar;
}

Stog FindPrev(Stog A, Stog head)
{
	Stog temp = head;

	while (temp->next != A)
	{
		temp = temp->next;
	}

	return temp;
}