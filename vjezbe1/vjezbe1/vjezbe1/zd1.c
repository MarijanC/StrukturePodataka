#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#define MAX 1024
#define ERROR -1

int ReadRows(const char* filename);

typedef struct {
	char *ime;
	char* prezime;
	int bodovi;
}listastudenata;

typedef struct llist {
	listastudenata* st;
	struct llist* next;
}list;

listastudenata* unos(const char *filename, int numberOfRows, list *studenti)
{
	int i = 0;
	FILE* fp = NULL;
	fp = fopen(filename, "r");
	list* s = studenti;

	listastudenata* list = malloc(sizeof(listastudenata));

	//for (i = 0; i < numberOfRows; i++)
	//{
		fgets(s->st->ime, sizeof(s->st->ime), fp);
	//}
		printf("%s", s->st->ime);

}

int main()
{
	int numberOfRows = 0;

	numberOfRows = ReadRows("dat.txt");
	printf("Broj redova u datoteci je %d\n", numberOfRows);
	unos("dat.txt", numberOfRows, );

	return 0;
}

int ReadRows(const char* filename)
{
	int numberOfRows = 0;
	FILE* fp = NULL;
	char buffer[MAX] = { '\0' };

	fp = fopen(filename, "r");
	if (!fp)
	{
		return ERROR;
	}
	while (!feof(fp))
	{
		fgets(buffer, MAX, fp);
		numberOfRows++;
	}
	fclose(fp);
	return numberOfRows;
}