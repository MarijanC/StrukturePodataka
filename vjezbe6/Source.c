#include <stdio.h>
#define ERROR -100

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
rec CreateReceipt(int recDate);

int main()
{
	Receipt head = { .date = 0, .next = NULL, .articleHead = NULL};		//head liste receipt

	return 0;
}

int AddNewReceipt(char* rn, rec head)
{
	FILE* f = NULL;

	f = fopen(rn, "r");
	if (f = NULL)
		return ERROR;
	

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

rec CreateReceipt(int recDate)			//Stvara novi receipt;
{
	Receipt new = ()
}