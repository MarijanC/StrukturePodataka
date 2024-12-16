#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define ERROR -100
#define MAX 11
#define ARTLENGTH 1024

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
	char fileName[MAX];
	int date;
	rec next;
	art articleHead;
}Receipt;

int CreateReceiptList(rec head, char* receiptList);												//funkcija za stvaranje vezane liste receiptova
rec CreateNewReceipt(rec R, int date, char* fn);												//funkcija za stavranje novog receipta
int FindDate(char* fn);																			//funkcija za pronalazenje datuma receipta
int CreateArticleList(rec head);																//funkcija za stvaranje pojedinih lista za odreðeni receipt
art CreateNewArticle(char* artName, int artQuatn, double artPrice, rec head);					//funkcija za stvaranje pojedinih articleova
int MergeDays(rec head);																		//funkcija za spajanje racuna istog dana
void PrintReceipts(rec head);																	//funkcija za printanje receiptova
int MergeArticles(rec R);																		//funkcija za spajanje istoimenih artikala u receiptu
double MoneySpent(rec head);																	//funkcija za racunanje potrosenog novca u periodu na odredeni artikl
int QuantityBought(rec head);																	//funkcija racuna broj prodabih jedinica odredenog artikla


int main()
{
	double sumSpent;
	int quantBought;

	Receipt head = {.fileName = '\0' ,.date = 0, .next = NULL, .articleHead = NULL};			//head liste receipt
	CreateReceiptList(&head, "racuni.txt");
	
	sumSpent = MoneySpent(&head);
	printf("\nKroz odabrani period je na odabrani artikl potroseno %.2lf eura\n", sumSpent);

	quantBought = QuantityBought(&head);
	printf("\nKroz obadrani period je prodano %d odabranih artikala\n", quantBought);

	return 0;
}

int CreateReceiptList(rec head, char* receiptList)
{
	FILE* rl = NULL;
	int datescan, i;
	char* line;
	rec currentRec;

	line = (char*)malloc(MAX * sizeof(char));

	rl = fopen(receiptList, "r");
	if (rl == NULL)
		return ERROR;

	while(!feof(rl)) {
		fgets(line, MAX, rl);

		if (line[strlen(line) - 2] == '\r')
			line[strlen(line) - 2] = '\0';
		//printf("%s\n", line);

		datescan = FindDate(line);
		//printf("%d\n", datescan);
		currentRec = CreateNewReceipt(head, datescan, line);
		fgets(line, MAX, rl);
		CreateArticleList(currentRec);
	}
	fclose(rl);
	//PrintReceipts(head);
	MergeDays(head);
	/*printf("\n\n");
	PrintReceipts(head);
	printf("\n\n");*/
	
	currentRec = head->next;
	while (currentRec != NULL)
	{
		MergeArticles(currentRec);
		currentRec = currentRec->next;
	}
	PrintReceipts(head);


	return EXIT_SUCCESS;
}

rec CreateNewReceipt(rec R, int date, char* fn)
{
	rec temp, new = NULL;

	temp = R;
	new = (rec)malloc(sizeof(Receipt));

	while (temp->next != NULL) {										//pronalazi pravo mjesto u listi za receipt
		if (date < temp->next->date)
			break;
		temp = temp->next;
	}

	new->next = temp->next;
	temp->next = new;
	new->date = date;
	new->articleHead = (art)malloc(sizeof(Article));
	strcpy(new->fileName, fn);

	new->articleHead->price = 0;
	new->articleHead->quant = 0;
	new->articleHead->next = NULL;
	strcpy(new->articleHead->name, "\0");

	return new;
}

int FindDate(char* fn)
{
	FILE* f = NULL;
	int date = 0, i = 0;
	char* line;


	line = (char*)malloc(MAX * sizeof(char));

	f = fopen(fn, "r");
	if (f == NULL)
		return ERROR;

	fgets(line, MAX, f);

	i = 0;
	while(line[i] != '\0')
	{
		if (line[i] != '-')
		{
			date += (line[i] - '0');
			date *= 10;
		}
		i++;
	}
	date /= 10;
	fclose(f);

	return date;
}

int CreateArticleList(rec head)
{
	FILE* f = NULL;
	char* line = (char*)malloc(ARTLENGTH * sizeof(char));
	char* tempArtName = (char*)malloc(20 * sizeof(char));
	int tempArtQuant;
	double tempArtPrice;
	rec temp = head;


	f = fopen(head->fileName, "r");
	if (f == NULL)
		return ERROR;

	fgets(line, ARTLENGTH, f);
	while (!feof(f))
	{
		fgets(line, ARTLENGTH, f);
		sscanf(line, " %s %d %lf", tempArtName, &tempArtQuant, &tempArtPrice);
		CreateNewArticle(tempArtName, tempArtQuant, tempArtPrice, temp);
	}

	return EXIT_SUCCESS;
}

art CreateNewArticle(char* artName, int artQuatn, double artPrice, rec head)
{
	art temp = head->articleHead;
	art new = (art)malloc(sizeof(Article));

	while (temp->next != NULL)
		temp = temp->next;

	new->next = temp->next;
	temp->next = new;

	strcpy(new->name, artName);
	new->price = artPrice;
	new->quant = artQuatn;

	return new;
}

int MergeDays(rec head)
{
	rec temp = head, temp2;
	art final, first;

	while (temp->next != NULL) {
		if (temp->date == temp->next->date)
		{
			final = temp->articleHead;
			while (final->next != NULL) {
				final = final->next;
			}
			first = temp->next->articleHead->next;
			final->next = first;

			temp2 = temp->next->next;
			temp->next = temp2;

			//free(temp->next->articleHead);
			//free(temp->next);
		}
		else
			temp = temp->next;
	}
	return EXIT_SUCCESS;
}

void PrintReceipts(rec head)
{
	rec temp = head->next;
	art tempart;

	while (temp != NULL)
	{
		printf("%d\n", temp->date);
		tempart = temp->articleHead->next;
		while (tempart != NULL)
		{
			printf("%s %d %lf\n", tempart->name, tempart->quant, tempart->price);
			tempart = tempart->next;
		}
		temp = temp->next;
		printf("\n");
	}
}

int MergeArticles(rec R)
{
	art temp1 = R->articleHead->next, temp2, prev2;

	while (temp1 != NULL)
	{
		temp2 = temp1->next;
		prev2 = temp1;
		while (temp2 != NULL)
		{
			if (strcmp(temp1->name, temp2->name) == 0)
			{
				temp1->quant += temp2->quant;
				prev2->next = temp2->next;
				free(temp2);
				temp2 = prev2->next;
			}
			else
			{
				prev2 = temp2;
				temp2 = temp2->next;
			}
		}
		temp1 = temp1->next;
	}
	return EXIT_SUCCESS;
}

double MoneySpent(rec head)
{
	int start, end, choice;
	double sum = 0;
	char odabir[20];
	rec temp = head->next;
	art pom;

	printf("Unesite pocetni datum u formatu YYYYMMDD\n");
	scanf("%d", &start);
	printf("Unesite zavrsni datum u formatu YYYYMMDD\n");
	scanf("%d", &end);
	printf("Odaberite artikl\nJabuke - 1\nKruske - 2\nMeso - 3\n");
	scanf("%d", &choice);

	switch (choice) {
	case 1:
		strcpy(odabir, "Jabuke");
		break;

	case 2:
		strcpy(odabir, "Kruske");
		break;

	case 3:
		strcpy(odabir, "Meso");
		break;

	default:
		printf("Nevaljani unos\n");
		return ERROR;
	}

	while (temp->date < start)
	{
		temp = temp->next;
	}
	while (temp->date < end)
	{
		pom = temp->articleHead->next;
		while (pom != NULL)
		{
			if (strcmp(pom->name, odabir) == 0) {
				sum += (pom->price * (double)pom->quant);
			}
			pom = pom->next;
		}
		temp = temp->next;
	}
	return sum;
}

int QuantityBought(rec head)
{
	int start, end, choice, sum = 0;
	char odabir[20];
	rec temp = head->next;
	art pom;

	printf("Unesite pocetni datum u formatu YYYYMMDD\n");
	scanf("%d", &start);
	printf("Unesite zavrsni datum u formatu YYYYMMDD\n");
	scanf("%d", &end);
	printf("Odaberite artikl\nJabuke - 1\nKruske - 2\nMeso - 3\n");
	scanf("%d", &choice);

	switch (choice) {
	case 1:
		strcpy(odabir, "Jabuke");
		break;

	case 2:
		strcpy(odabir, "Kruske");
		break;

	case 3:
		strcpy(odabir, "Meso");
		break;

	default:
		printf("Nevaljani unos\n");
		return ERROR;
	}

	while (temp->date < start)
	{
		temp = temp->next;
	}
	while (temp->date < end)
	{
		pom = temp->articleHead->next;
		while (pom != NULL)
		{
			if (strcmp(pom->name, odabir) == 0) {
				sum += pom->quant;
			}
			pom = pom->next;
		}
		temp = temp->next;
	}
	return sum;
}