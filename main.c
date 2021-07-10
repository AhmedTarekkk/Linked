#include "stdafx.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

//----------- start student 1

struct student_t{
char name[20]; // assume that the longest student name consist of 20 char
int id;
int birth[3]; // day month year
int score;
};

//------------- end student 1


// ------------start student 2
struct node {
    struct student_t student; //student data
    struct node* next, * prev; // next and previous nodes pointers (head and tail pointer)
};


void DeleteList(struct node* head) {
    struct node* temp = NULL;
    struct node* current = head;

    while (current != NULL)
    {
        temp = current;
        current = current->next;
        free(temp);
    }
}

struct node* createNode(const struct student_t Data) {    // function to create new nodes

    struct node* newNode = (struct node*) malloc(sizeof(struct node)); // allocating the memory for new node
    newNode->student = Data;                             // setting the data of the new node
    newNode->next = NULL;                               // setting the tail and head pointers to NULL
    newNode->prev = NULL;
    return newNode;
}

// the insertStudent function used to insert new student at any index
void insertStudent(struct node** head, const struct student_t* studentData, unsigned int n) {

    if (head == NULL) return;  // checking if the head pointer is passing a NULL or itself is a NULL
    if (*head == NULL) return;

    struct node* newNode = createNode(*studentData); // creating a new node holding the new student data
    struct node* current = *head;                    // creating current node which we use to loop through the list


    if (n == 0) {                  // first case is that we want to insert at the beggining
        newNode->next = *head;    // what we need is newNode > head and then setting the head to point to the first node
        (*head)->prev = newNode;  // we used two level pointer to be able to change the head pointer
        *head = newNode;
        return;
    }

    while (n--) {       // while looping through the linked list we will face  cases


        if (current->next == NULL) { // first the next node is null and n = 0
            if (n == 0) {            // which means we need to insert in place of that null (at the end of the linked list)
                current->next = newNode;
                newNode->prev = current;

                return;
            }
            // if the next is null and n != 0  which means that we reached the end
            return;            // of linked list and the index we want greater than its end so we return


        }
        else { current = current->next; } // if no case of the above occurred we loop through the list until reach the inedx

    }


    newNode->prev = current->prev; // after reached the n we set the pointers of each node as if
    newNode->next = current;        // we inject the new node between them
    current->prev = newNode;
    newNode->prev->next = newNode;


}
//----------------------- end student 2


int main()
{
	int n;
	char input [1];
	printf("Welcome To DataStructure Testing\n");
	getchar();

return 0;}




