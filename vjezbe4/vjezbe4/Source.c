
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define ERROR -1
#define MAX 1024

typedef struct Polinom* listPoli;
typedef struct Polinom {
	int koef;
	int pot;
	listPoli next;
} Pol;

int Unos(listPoli P1, listPoli P2, char* fileName);
int Suma(listPoli P1, listPoli P2, listPoli sum);
int Produkt(listPoli P1, listPoli P2, listPoli produkt);

int Print(listPoli P)
{
	listPoli temp = P->next;
	while (temp) {
		printf("%d %d\n", temp->koef, temp->pot);
		temp = temp->next;
	}
	return EXIT_SUCCESS;
}

int main()
{
	Pol head1 = {.koef = 0, .pot = 0, .next = NULL};
	Pol head2 = { .koef = 0, .pot = 0, .next = NULL };
	Pol sum = { .koef = 0, .pot = 0, .next = NULL };
	Pol prod = { .koef = 0, .pot = 0, .next = NULL };

	Unos(&head1, &head2, "dat.txt");
	Suma(&head1, &head2, &sum);
	Produkt(&head1, &head2, &prod);

	Print(&head1);
	printf("\n");
	Print(&head2);
	printf("\n\n");

	Print(&sum);
	printf("\n\n");
	Print(&prod);
	printf("\n");

	return 0;
}

int Unos(listPoli P1, listPoli P2, char*fileName)
{
	FILE* f;
	f = fopen(fileName, "r");

	int buffk, buffp, i;
	listPoli temp, newPol;
	char* buffer;

	buffer = (char*)malloc(MAX * sizeof(char));

	fgets(buffer, MAX, f);

	temp = P1;
	while (sscanf(buffer, " %d %d", &buffk, &buffp) == 2)
	{
		newPol = (listPoli)malloc(sizeof(Pol));

		newPol->koef = buffk;
		newPol->pot = buffp;
		newPol->next = NULL;

		temp->next = newPol;
		temp = temp->next;

		for (i = 0; i < 4; i++)
		{
			*buffer++;
		}
	}

	fgets(buffer, MAX, f);

	temp = P2;
	while (sscanf(buffer, " %d %d", &buffk, &buffp) == 2)
	{
		newPol = (listPoli)malloc(sizeof(Pol));

		newPol->koef = buffk;
		newPol->pot = buffp;
		newPol->next = NULL;

		temp->next = newPol;
		temp = temp->next;

		for (i = 0; i < 4; i++)
		{
			*buffer++;
		}
	}

	return EXIT_SUCCESS;
}

int Suma(listPoli P1, listPoli P2, listPoli sum)
{
	listPoli end = NULL;
	listPoli temp1, temp2, temps, new;

	temp1 = P1->next;
	temp2 = P2->next;
	temps = sum;

	while (temp1 != end)
	{
		temp2 = P2->next;
		while (temp2 != end)
		{
			if (temp1->pot == temp2->pot)
			{
				new = (listPoli)malloc(sizeof(Pol));
				temps->next = new;
				temps = temps->next;
				temps->next = NULL;
				temps->koef = temp1->koef + temp2->koef;
				temps->pot = temp1->pot;
			}
			temp2 = temp2->next;
		}
		temp1 = temp1->next;
	}

	return EXIT_SUCCESS;
}

int Produkt(listPoli P1, listPoli P2, listPoli prod)
{
	listPoli end = NULL;
	listPoli temp1, temp2, tempp, new, prev, temp11;

	temp1 = P1->next;
	temp2 = P2->next;
	tempp = prod;

	while (temp1 != end)
	{
		temp2 = P2->next;
		while (temp2 != end)
		{
			new = (listPoli)malloc(sizeof(Pol));
			tempp->next = new;
			tempp = tempp->next;
			tempp->next = NULL;
			tempp->koef = temp1->koef * temp2->koef;
			tempp->pot = temp1->pot + temp2->pot;

			temp2 = temp2->next;
		}
		temp1 = temp1->next;
	}

	return EXIT_SUCCESS;
}