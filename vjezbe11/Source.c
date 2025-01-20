#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAXNAME 25
#define HASHSIZE 11

struct _grad;
typedef struct _grad* Child;
typedef struct _grad {
	char ime[MAXNAME];
	int stanovnici;
	Child left;
	Child right;
}Grad;

struct _drzava;
typedef struct _drzava* Susjed;
typedef struct _drzava {
	char ime[MAXNAME];
	char fileGradova[MAXNAME];
	Susjed next;
	Child root;
}Drzava;

int InputCountries(Drzava* list);
int AddCountry(Drzava* list, char *imeDrzave, char *fileIme);
Susjed CreateCountry(Susjed prev, char *imeDrzave, char *fileIme);

int main()
{
	int i;

	Drzava listaDrzava[HASHSIZE];
	Drzava head = { .ime = NULL, .fileGradova = NULL, .next = NULL, .root = NULL };
	for (i = 0; i < HASHSIZE; i++)
		listaDrzava[i] = head;

	InputCountries(listaDrzava);
}

int InputCountries(Drzava* list)
{
	char *nameBuffer, *fileBuffer;

	FILE* drzave = NULL;

	drzave = fopen("drzave.txt", "r");
	if (drzave == NULL)
	{
		printf("Greska u otvaranju datoteke sa drzavama");
		return -1;
	}

	nameBuffer = (char*)malloc(MAXNAME * sizeof(char));
	fileBuffer = (char*)malloc(MAXNAME * sizeof(char));

	while (!feof(drzave))
	{
		fscanf(drzave, "%s\t%s", nameBuffer, fileBuffer);
	}
}

int AddCountry(Drzava* list, char* imeDrzave, char* fileIme)
{
	int key, sum = 0, i;
	Susjed temp;

	for (i = 0; i < 5; i++)
		sum += imeDrzave[i];
	key = sum % HASHSIZE;

	temp = &list[key];

	while (temp->next != NULL)
	{
		//ode si sta, sada triba ici strcmp i poziv CreateCountry funkcije!!!
	}
}

Susjed CreateCountry(Susjed prev, char* imeDrzave, char* fileIme)
{
	Susjed temp = prev;
	Susjed new = (Drzava*)malloc(sizeof(Drzava));

	strcpy(new->ime, imeDrzave);
	strcpy(new->fileGradova, fileIme);
	new->root = NULL;
	new->next = temp->next;
	temp->next = new;
}