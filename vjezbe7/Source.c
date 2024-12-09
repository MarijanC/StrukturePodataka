#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_NAME_LENGTH 50

struct _directory;
typedef struct _directory* PositionDirectory;
typedef struct _directory {
	char name[MAX_NAME_LENGTH];
	PositionSubdirectory child;
	PositionDirectory next;
}Directory;

struct _subdirectory;
typedef struct _subdirectory* PositionSubdirectory;
typedef struct _subdirectory {
	char name[MAX_NAME_LENGTH];
	PositionSubdirectory child;
	PositionSubdirectory next;
}Subdirectory;



int main()
{
	Directory root = { .name = "C:", .child = NULL, .next = NULL };

	return 0;
}