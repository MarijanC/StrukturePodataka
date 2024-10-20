#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 50

struct _person;
typedef struct _person* position;
typedef struct _person {
    char name[MAX];
    char lastName[MAX];
    int birthYear;
    position next;
} Person;

position CreatePerson(char* name, char* lastName, int birthYear);
int PrependList(position head, char* name, char* lastName, int birthYear);
int AppendList(position head, char* name, char* lastName, int birthYear);
int PrintList(position first);
position FindLast(position head);
position FindPerson(position first, char* lastName);
int Delete(position head, char* lastName);
position FindPrev(position head, char* lastName);

int main() {
    Person head = { .name = "", .lastName = "", .birthYear = 0, .next = NULL };

    AppendList(&head, "Ante", "Antic", 2003);
    AppendList(&head, "Borna", "Boric", 2004);

    PrintList(&head);

    PrependList(&head, "Cvita", "Cvitic", 2002);
    PrintList(&head);

    Delete(&head, "Boric");
    PrintList(&head);

    return 0;
}

position CreatePerson(char* name, char* lastName, int birthYear) {
    position newPerson = (position)malloc(sizeof(Person));
    if (!newPerson) {
        printf("Memory allocation failed.\n");
        return NULL;
    }

    strcpy(newPerson->name, name);
    strcpy(newPerson->lastName, lastName);
    newPerson->birthYear = birthYear;
    newPerson->next = NULL;

    return newPerson;
}

int PrependList(position head, char* name, char* lastName, int birthYear) {
    position newPerson = CreatePerson(name, lastName, birthYear);
    if (newPerson == NULL) {
        return -1;
    }

    newPerson->next = head->next;
    head->next = newPerson;

    return EXIT_SUCCESS;
}

int AppendList(position head, char* name, char* lastName, int birthYear) {
    position newPerson = CreatePerson(name, lastName, birthYear);
    if (newPerson == NULL) {
        return -1;
    }

    position last = FindLast(head);
    last->next = newPerson;

    return EXIT_SUCCESS;
}

position FindLast(position head) {
    position temp = head;
    while (temp->next != NULL) {
        temp = temp->next;
    }
    return temp;
}

int PrintList(position first) {
    position temp = first->next;  // Preska�emo head �vor
    while (temp != NULL) {
        printf("%s %s %d\n", temp->name, temp->lastName, temp->birthYear);
        temp = temp->next;
    }
    printf("\n");  // Novi redak nakon ispisa liste
    return EXIT_SUCCESS;
}

position FindPerson(position first, char* lastName) {
    position temp = first->next;
    while (temp != NULL) {
        if (strcmp(temp->lastName, lastName) == 0) {
            return temp;
        }
        temp = temp->next;
    }
    return NULL;
}

position FindPrev(position head, char* lastName) {
    position temp = head;
    while (temp->next != NULL && strcmp(temp->next->lastName, lastName) != 0) {
        temp = temp->next;
    }
    return temp->next ? temp : NULL;
}

int Delete(position head, char* lastName) {
    position prev = FindPrev(head, lastName);
    if (prev == NULL) {
        printf("Person with last name %s not found.\n", lastName);
        return -1;
    }

    position toDelete = prev->next;
    prev->next = toDelete->next;
    free(toDelete);

    return EXIT_SUCCESS;
}