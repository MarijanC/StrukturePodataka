#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 50

struct _struct;
typedef struct _person* position;
typedef struct _person
{
	char name[MAX];			//ime
	char lastName[MAX];		//prezime
	int birthYear;			//godina roðenja

	position next;
}Person;

position CreatePerson(char* name, char* lastName, int birthYear);
int PrependList(position head, char* name, char* lastname, int birthYear);
int PrintList(position first);
int AppendList(position head, char* name, char* lastName, int birthYear);
position FindLast(position head);
position FindPerson(position first, char* lastName);
int Delete(position head, char*);
position FindPrev(position head, char* name);

int main()
{
	Person head =
	{
		.name = {0},
		.lastName = {0},
		.birthYear = {0},
		.next = NULL
	};

	AppendList(&head, "Ante", "Antic", 2003);
	AppendList(&head, "Borna", "Boric", 2004);

	PrintList(&head);

	PrependList(&head, "Cvita", "Cvitic", 2002);

	PrintList(&head);

	Delete(&head, "Borna");

	return 0;
}

position CreatePerson(char* name, char* lastName, int birthYear)				//Stvara novu osobu
{
	position newPerson = NULL;
	newPerson = (position)malloc(sizeof(Person));
	if (!newPerson)
	{
		printf("Bad allocation");
		return NULL;
	}

	strcpy(newPerson->name, name);
	strcpy(newPerson->lastName, lastName);
	newPerson->birthYear = birthYear;
}

int PrependList(position head, char* name, char* lastname, int birthYear)		//Dodaje novu osobu na poèetak liste
{
	position newPerson = NULL;
	newPerson = CreatePerson(name, lastname, birthYear);
	if (newPerson == NULL)
	{
		printf("greska");
		return -1;
	}
	newPerson->next = head->next;
	head->next = newPerson;
	return EXIT_SUCCESS;
}

int PrintList(position first)													//Ispisuje listu
{
	position temp = NULL;
	temp = first;
	while (temp != NULL)
	{
		printf("%s %s %d", temp->name, temp->lastName, temp->birthYear);
		temp = temp->next;
	}
	return EXIT_SUCCESS;
}

int AppendList(position head, char* name, char* lastName, int birthYear)		//Dodaje novu osobu na kraj liste
{
	position newPerson = NULL;
	position last = NULL;

	newPerson = CreatePerson(name, lastName, birthYear);
	if (newPerson == NULL)
	{
		printf("Failed");
		return -1;
	}

	last = FindLast(head);
	last->next = newPerson;
	newPerson->next = last->next;
	last->next = newPerson;

	return EXIT_SUCCESS;
}

position FindLast(position head)												//Pronalazi osobu na kraju liste
{
	position last = NULL;
	last = head;
	while (last->next != NULL)
	{
		last = last->next;
	}
	return last;
}

position FindPerson(position first, char* lastName)								//Pronalazi na kojoj se poziciji nalazi odreðena osoba
{
	position temp = NULL;

	temp = first;
	while (temp)
	{
		if (strcmp(lastName, temp->lastName) == 0)
		{
			return temp;
		}
		temp = temp->next;
	}

	return NULL;
}

int Delete(position head, char* name)											//Briše osobu sa liste
{
	position prev = NULL;
	position toDelete = NULL;

	prev = FindPrev(head, name);

	toDelete = prev->next;
	prev->next = toDelete->next;

	free(toDelete);

	return EXIT_SUCCESS;
}

position FindPrev(position head, char* name)									//Pronalazi osobu koja se nalazi prije unešene
{
	position temp = head;

	while (temp->next->name != name)
	{
		temp = temp->next;
	}

	return temp;
}