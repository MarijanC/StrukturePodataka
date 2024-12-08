#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define ERROR -1
#define MAX 1024

typedef struct Cvor* Stog;
typedef struct Cvor {
	float br;

	Stog next;
	Stog prev;
}st;

int Izvod(Stog head, char* fn);
Stog CreateNewElement(Stog prev, float br);

int main()
{
	st head = { .br = 0.0, .next = NULL, .prev = NULL };
	Izvod(&head, "dat.txt");

	printf("%f\n", head.next->br);

	return 0;
}

int Izvod(Stog head, char* fn)
{
	char* buffer = (char*)malloc(MAX * sizeof(char));
	char opr = '\0';
	float tempbr;
	FILE* f = NULL;
	Stog temp = head, pr;

	memset(buffer, '\0', 1024);

	f = fopen(fn, "r");
	if (f == NULL)
		return ERROR;

	fgets(buffer, MAX, f);

	while (*buffer != '\0')
	{
		while (sscanf(buffer, " %f", &tempbr) == 1)
		{
			CreateNewElement(temp, tempbr);
			temp = temp->next;
			buffer++;
			buffer++;
		}
		sscanf(buffer, " %c", &opr);

		pr = temp->prev;
		switch (opr) 
		{
			case '+':
				tempbr = pr->br + temp->br;
				pr->br = tempbr;
				free(temp);
				temp = pr;
				break;

			case '-':
				tempbr = pr->br - temp->br;
				pr->br = tempbr;
				free(temp);
				temp = pr;
				break;

			case '/':
				tempbr = pr->br / temp->br;
				pr->br = tempbr;
				free(temp);
				temp = pr;
				break;

			case '*':
				tempbr = pr->br * temp->br;
				pr->br = tempbr;
				free(temp);
				temp = pr;
				break;

			default:
				return ERROR;
		}
		buffer++;
		buffer++;
	}

	return EXIT_SUCCESS;
}

Stog CreateNewElement(Stog previous, float num)
{
	Stog new = (st*)malloc(sizeof(st));

	new->br = num;
	new->next = NULL;
	previous->next = new;
	new->prev = previous;

	return new;
}