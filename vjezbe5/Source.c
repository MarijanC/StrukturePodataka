#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define ERROR -1
#define MAX 1024

typedef struct Cvor* Stog;
typedef struct Cvor {
	float br;
	char opr;

	Stog next;
}st;

int izvod(Stog head, char* fn);
Stog NewCharacter(float broj, char operand);
Stog FindPrev(Stog A, Stog head);
int PrintStog(Stog head);
int ReadFile(Stog head, char* fn);

int main()
{
	st head = { .br = 0, .opr = NULL, .next = NULL};

	ReadFile(&head, "dat.txt");
	PrintStog(&head);

	return 0;
}

int izvod(Stog head, char* fn)
{
	FILE* f = NULL;
	char* buffer = (char*)malloc(MAX * sizeof(char));
	float temprez;
	float tempbr;
	char tempopr;
	Stog temp = head, temp2, prev, pprev = NULL;

	f = fopen(fn, "r");
	if (f == NULL)
		return ERROR;

	fgets(buffer, MAX, f);
	while (!feof(f))
	{
		while (sscanf(buffer, " %f", &tempbr) == 1)
		{
			temp->next = NewCharacter(tempbr, NULL);
			temp = temp->next;
			buffer++;
			buffer++;
		}

		sscanf(buffer, " %c", &tempopr);
		temp->next = NewCharacter(0, &tempopr);
		temp = temp->next;
		buffer++;
		buffer++;

		temp2 = head->next;
		switch (temp->opr) {
		case '+':
			temprez = 0;
			while (temp2 != '+')
			{
				temprez += temp2->br;
				prev = temp2;
				temp2 = temp2->next;
				pprev = FindPrev(prev, head);
				pprev->next = temp2;
				free(prev);
			}
			pprev->next = NULL;
			free(temp);
			break;

		case '-':
			temprez = 0;
			while (temp2 != '-')
			{
				temprez -= temp2->br;
				prev = temp2;
				temp2 = temp2->next;
				pprev = FindPrev(prev, head);
				pprev->next = temp2;
				free(prev);
			}
			pprev->next = NULL;
			free(temp);
			break;

		case '*':
			temprez = 1;
			while (temp2 != '*')
			{
				temprez *= temp2->br;
				prev = temp2;
				temp2 = temp2->next;
				pprev = FindPrev(prev, head);
				pprev->next = temp2;
				free(prev);
			}
			pprev->next = NULL;
			free(temp);
			break;

		case '/':
			temprez = 1;
			while (temp2 != '/')
			{
				temprez /= temp2->br;
				prev = temp2;
				temp2 = temp2->next;
				pprev = FindPrev(prev, head);
				pprev->next = temp2;
				free(prev);
			}
			pprev->next = NULL;
			free(temp);
			break;
		}
	}

	return EXIT_SUCCESS;
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

int PrintStog(Stog head)
{
	Stog temp = head->next; // Assuming head is a dummy node.

	while (temp != NULL)
	{
		printf("%f\n", temp->br);
		temp = temp->next;
	}

	return EXIT_SUCCESS;
}

int ReadFile(Stog head, char* fn)
{
	char buffer[MAX];
	int tempbr;
	char tempopr;
	Stog temp = head;
	FILE* f = NULL;

	f = fopen(fn, "r");
	if (f == NULL)
		return ERROR;

	// Read the file line-by-line
	while (fgets(buffer, MAX, f))
	{
		char* ptr = buffer; // Pointer to traverse the buffer.

		while (*ptr != '\0')
		{
			// Check for numbers
			if (sscanf(ptr, " %d", &tempbr) == 1)
			{
				temp->next = NewCharacter((float)tempbr, '\0'); // Use '\0' for no operator.
				temp = temp->next;

				// Move the pointer past the parsed number
				while (*ptr != ' ' && *ptr != '\0')
					ptr++;
			}
			// Check for operators
			else if (sscanf(ptr, " %c", &tempopr) == 1 && (tempopr == '+' || tempopr == '-' || tempopr == '*' || tempopr == '/'))
			{
				temp->next = NewCharacter(0, tempopr); // Use 0 for no numeric value.
				temp = temp->next;

				// Move the pointer past the parsed operator
				ptr++;
			}
			else
			{
				ptr++; // Skip invalid characters
			}
		}
	}

	fclose(f);
	return EXIT_SUCCESS;
}