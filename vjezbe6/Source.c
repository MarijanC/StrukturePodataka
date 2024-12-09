#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define ERROR -100
#define MAX 1024

struct _article;
typedef struct _article* art;
typedef struct _article
{
	char name[20];
	int quant;
	double price;
	art next;
}Article;

struct _receipt;
typedef struct _receipt* rec;
typedef struct _receipt
{
	int date;
	rec next;
	art articleHead;
}Receipt;

int AddNewReceipt(char* rn, rec head);
rec FindSpot(rec head, int date);
rec CreateReceipt(int recDate, rec head);
art AddArticle(rec Receipt, char* artName, int kvant, double cijena);

int main()
{
	Receipt head = { .date = 0, .next = NULL, .articleHead = NULL};		//head liste receipt
	AddNewReceipt("racuni.txt", &head);

	printf("%s %d %lf\n", head.next->articleHead->next->name, head.next->articleHead->next->quant, head.next->articleHead->next->price);

	return 0;
}

int AddNewReceipt(char* rn, rec head)
{
	FILE* f = NULL;
	FILE* rcs = NULL;
	char* buffer = (char*)malloc(MAX * sizeof(char));
	char* line = (char*)malloc(MAX * sizeof(char));
	char namebuff[MAX];
	int tempdat = 0, i = 0, offset = 0;
	double temppric;
	rec temp = head;
	art tempart;

	f = fopen(rn, "r");
	if (f == NULL)
		return ERROR;
	
	while (!feof(f))
	{
		memset(buffer, '\0', sizeof(buffer));
		fgets(buffer, MAX, f);
		buffer[strcspn(buffer, "\n")] = 0;
		rcs = fopen(buffer, "r");
		if (rcs == NULL)
			return ERROR;

		fgets(line, MAX, rcs);
		sscanf(line, "%d%n", &tempdat, &offset);
		line += offset;
		sscanf(line, "%d", &i);
		tempdat *= 100;
		tempdat += i;
		for (i = 0; i < 3; i++)
			line++;
		sscanf(line, "%d", &i);
		tempdat *= 100;
		tempdat += i;

		free(buffer);
		free(line);

		temp = CreateReceipt(tempdat, head);
		tempart = temp->articleHead;
		while (!feof(rcs))
		{
			fgets(line, MAX, rcs);
			sscanf(line, "%s", namebuff);
			while (sscanf(line, "%d", &tempdat) != 1)
			{
				line++;
			}
			line++; line++;
			sscanf(line, "%lf", &temppric);
			AddArticle(tempart, namebuff, tempdat, temppric);
			tempart = tempart->next;
		}
		free(line);
		fclose(rcs);
	}
	fclose(f);
	return EXIT_SUCCESS;
}

rec FindSpot(rec head, int date)		//Pronalazi receipt iza kojeg se dodaje novi
{
	rec temp = head;

	while (temp->next != NULL)
	{
		if (temp->next->date > date)
			break;
		temp = temp->next;
	}
	return temp;
}

rec CreateReceipt(int recDate, rec head)			//Stvara novi receipt i postavlja ga u listu
{
	rec new = (Receipt*)malloc(sizeof(Receipt));
	rec temp = FindSpot(head, recDate);
	new->date = recDate;
	new->articleHead = NULL;

	new->next = temp->next;
	temp->next = new;

	return new;
}

art AddArticle(art Receipt, char* artName, int kvant, double cijena)
{
	art new = (Article*)malloc(sizeof(Article));
	art temp = Receipt;

	new->quant = kvant;
	new->price = cijena;
	strcpy(new->name, artName);

	while (temp->next != NULL)
	{
		if (strcmp(temp->name, artName) > 0)
			break;
		temp = temp->next;
	}
	new->next = temp->next;
	temp->next = new;

	return new;
}