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
struct node{
	struct student_t student; //student data
	struct node *next, *prev; // next and previous nodes pointers (head and tail pointer)
};


void DeleteList(struct node *head){
	 struct node *temp = NULL;
    struct node *current = head;

	while (current != NULL)
	{
		temp=current;
		current=current->next;
		free(temp);
	}
}

struct node *createNode(const struct student_t Data){    // function to create new nodes

    struct node *newNode  =(struct node*) malloc(sizeof(struct node)); // allocating the memory for new node
    newNode->student = Data;                             // setting the data of the new node
    newNode ->next = NULL;                               // setting the tail and head pointers to NULL
    newNode->prev = NULL;
    return newNode;
}

// the insertStudent function used to insert new student at any index
void insertStudent(struct node **head , const struct student_t *studentData, unsigned int n){

    if (head == NULL) return;  // checking if the head pointer is passing a NULL or itself is a NULL
    if (*head == NULL) return;

 struct node *newNode = createNode(*studentData); // creating a new node holding the new student data
 struct node *current = *head;                    // creating current node which we use to loop through the list


if (n== 0) {                  // first case is that we want to insert at the beggining
    newNode->next = *head;    // what we need is newNode > head and then setting the head to point to the first node
    (*head)->prev = newNode;  // we used two level pointer to be able to change the head pointer
    *head = newNode;
    return;
}

   while(n--) {       // while looping through the linked list we will face  cases


     if(current ->next == NULL){ // first the next node is null and n = 0
        if(n ==0 )  {            // which means we need to insert in place of that null (at the end of the linked list)
                current->next  = newNode;
                newNode ->prev = current;

                return;}
                            // if the next is null and n != 0  which means that we reached the end
         return;            // of linked list and the index we want greater than its end so we return


    }else{current  = current->next ;} // if no case of the above occurred we loop through the list until reach the inedx

    }


    newNode->prev = current ->prev; // after reached the n we set the pointers of each node as if
    newNode->next = current;        // we inject the new node between them
    current ->prev = newNode;
    newNode->prev->next = newNode;


}
//----------------------- end student 2




//----------------------- start student 3
struct studentArray{
	struct student_t *arr;
	unsigned int size ;
};

struct studentArray studentsArray ;


struct studentArray initArray(){		// intiate the studentAarray type

	struct studentArray *studentArr = (struct studentArray*) malloc(sizeof(struct studentArray)); // creating new studentArray and reserve a place to one element
	studentArr->size = 0;				// setting the value of the array size to 0
	return *studentArr;					// return the array
}





// Adds student info to array at nth position (from start)
void pushStudent(struct studentArray *students, const student_t *student,unsigned int n)
{

    if (n > students->size) return;  // checking if the array is valid
        
    student_t *temp = (struct student_t *)malloc((students->size + 1) * sizeof(struct student_t));
   
    if (n == 0)						 // Check insert from head
    {
          if (students->size != 0)	 // check if the array has elements to copy if not then set the element value
			 {
			memcpy(temp + 1, students->arr, students->size * sizeof(struct student_t));
			free(students->arr);
			  }	
    }

    else if (n == students->size)														// Check insert from tail
    {
			  memcpy(temp, students->arr, students->size * sizeof(struct student_t));   // copy the elements from the beggining   
			  free(students->arr);
    }

	else																					// insert in between
	{
    memcpy(temp, students->arr, n * sizeof(struct student_t));								// copy the elements from the start to n
    memcpy(temp + n + 1, students->arr + n, (students->size - n) * sizeof(struct student_t));// copy the elements from the n to the end
	free(students->arr);
	}

	students->arr = temp;		
    students->arr[n] = *student;  // setting the element data
    students->size++;			  // increasing the size of the student array
}

void pushStudent2(struct studentArray *stdArr , struct student_t data , unsigned int n){
	if (( stdArr->arr == NULL) && stdArr->size != 0)		   // checking if the array is valid
		return;
	if (n > stdArr->size) return;							  //check if the input index is valid
	int eSize = sizeof(data);
	struct student_t *newArr = (struct student_t*) malloc((stdArr->size +1) * eSize);	// reserving new array location

	// copying memory
	if (n == 0)												 // insert at the start
	{
	if (stdArr->size == 0) goto exitIF;						 // insert at the start and there is no elements in the array
		memcpy(newArr+1 ,stdArr->arr ,stdArr->size*eSize);   // copy old memory but shifted one forward to the new memory

	}
	else if (n == stdArr->size)									// insert at the end
	{
		memcpy(newArr ,stdArr->arr ,stdArr->size *eSize);		// copy old memory to the new one as it

	}
	else
	{															   	 // insert in between
		memcpy(newArr ,stdArr->arr ,stdArr->size * eSize);			 // copy the elements before the n index as it to the new memory
		memcpy(newArr+n+1 ,stdArr->arr+n ,(stdArr->size-n) * eSize); // copy the elements after the n index  shifted by one
	}

	// setting element value
exitIF:

	*(newArr+n) = data;		// setting the element value
	stdArr->arr = NULL;
	//free((stdArr->arr) );			// free the old array memory
	stdArr->arr= newArr;		// setting the new pointer
	stdArr->size++;				// increasing the size of the array
}



//----------------------- end student 3

//----------------------- start utatlities


char *formatString(char *str,int max,char delemeter){			//function used to format the string input
	char *output = (char*) malloc(sizeof(char) * max);			// reserveing memory to be the output of the function

	int i =(int) strlen(str);									// get the length of the input string(it's actually char array)

    if(i<max){													// if the  length of the input is less than the required legnth
            memcpy(output,str,sizeof(char) * (i+1));			// copy the legnth of the input and fill the rest of the places with a delemiter
            memset(output+(i) , delemeter, sizeof(char)*(max-i));
            return output;
        }

    memcpy(output,str,(max)* sizeof(char));						// if the length of the input was greater then copy part of the input string only
  
    return output;

}

#define TabelNameLength 20		//define the tabel Name column size
#define TabelIDLength	6		//define the tabel ID column size
#define	TableDelemeter " "		//define the tabel Delemeter

void displayColumnsNames()
{
	printf(formatString("ID",TabelIDLength+1,' '));			// Id column name
	printf(formatString("Name",TabelNameLength+1,' '));		// Name column name
	printf(formatString("Birth" , 10+1,' '));				// Date column name
	printf(formatString("Score" , 5 ,'0'));					// Score column name

}

void displayStudent( struct student_t *student) // void to display the student in table formulla
{
	char num[10];

	sprintf_s(num ,"%d" , student->id);                      //printing the ID
	printf(formatString(num , TabelIDLength , ' '));
	printf(TableDelemeter);

	printf(formatString(student->name , TabelNameLength,' '));	 //printing the Name
	printf(TableDelemeter);

	sprintf_s(num ,"%d" , student->birth[0]);					 //printing the birth day
	printf(formatString(num , 2, ' '));
	printf("/");
	sprintf_s(num ,"%d" , student->birth[1]);					//printing the birth month
	printf(formatString(num , 2, ' '));
	printf("/");
	sprintf_s(num ,"%d" , student->birth[2]);					//printing the birth year
	printf(formatString(num , 4, ' '));
	printf(TableDelemeter);

	sprintf_s(num ,"%d" , student->score);						//printing the score
	printf(formatString(num , 3,' '));
	printf("\%");

}

void displayLL(struct node *head)			// void to display the Linked List student
{
if (head == NULL) return;					// check if the head points to nothing
	struct node * current = head;			// creating pointer which we will use to loop through the linked list

	while(current != NULL)					// looping while the current element is not null
	{
	    printf("\n");
		displayStudent(&current->student);  // passing the address of the student data as it only 4byte insted passing the student data itself (72byte)
		current = current ->next;			// jump to the next elemnt

	}

}
void displayArr(const struct studentArray *stdArr)  // void to display the students data in the studentArray
{
for (unsigned int i = 0 ; i<stdArr->size ; i++)		// looping through every element of the array
	{
	    displayStudent(&(stdArr->arr[i]));				// passing the address of the student data for beter performance
printf("\n"); }
}



//----------------- start Timing
float refrenceTick;											// used as a refrence to calculate the time 
void setRefrenceTick(){	refrenceTick = (float)clock();}		// setting the current clock as reference 

// calculate the difference time between setting refrence and calling getTimeMS in mille seconds
float getTimeMS(){ return ((float)clock() -refrenceTick)/(CLOCKS_PER_SEC/1000.0); } 
//----------------- end Timing



//--------------- start filling utalities

char *NameList[] = {"Ahmed" , "Taha" , "Tarek" , "Sabry" ,"Mohamed", "Khaled"}; // Dictionary for the randome generation
struct student_t *getRandomData()
{
	struct student_t *student = (struct student_t*)malloc(sizeof(struct student_t)); // reserving data in the memory
	char *firstName = *(NameList + rand() % 6);										 // generate the first name
	char *lastName =  *(NameList + rand() % 6); 									 // generate the last name
	int firstNameLength = (int)strlen(firstName);									 // getting the lengths for memory copy
	memcpy(student->name ,firstName , sizeof(char) *firstNameLength);				 // copy the first name 
	student->name[firstNameLength] = ' ';
	memcpy(student->name+firstNameLength +1 ,lastName , sizeof(char) * (int)strlen(lastName));  // copy the last name 

	student->id = rand() %	9999 +1;											  	 // generate the ID
	student->score = rand() % 100; 									  		  	     // generate the score

	student->birth[0] = rand() % 28 +1;											  	 // generate birth day
	student->birth[1] = rand() % 12 +1;											  	 // generate the month
	student->birth[2] = rand() % 70 +1950;											 // generate the year
	return student;					
}


//--------------- start filling utalities
void testList(int n) // testing linked list
{
	float t; // represent the time
	struct node *head = createNode(*getRandomData());
	for (int i = 1 ; i <n ;i++)
		insertStudent(&head ,  getRandomData(),0);
	printf("    Size of Linked List in the Memory: %d = %.2f KB\n" , sizeof(struct node) * n, sizeof(struct node) * n /1024.0);
	printf("    Size of node : %d = %.2f KB\n", sizeof(struct node) , sizeof(struct node)/1024.0);

	setRefrenceTick();
	insertStudent(&head,getRandomData()  ,0);  // insert at the begging
	t=getTimeMS();
	printf("    Time to Insert at the start: %.2f ms\n" , t);

	setRefrenceTick();
	insertStudent(&head,getRandomData()  ,(n+1)/2);  // insert at the middle
	t=getTimeMS();
	printf("    Time to Insert at the middle: %.2f ms\n" , t);

	setRefrenceTick();
	insertStudent(&head,getRandomData()  ,n+2);  // insert at the end
	t=getTimeMS();
	printf("    Time to Insert at the end: %.2f ms\n" , t);

	DeleteList(head);

}

void DeleteArr(struct studentArray *students){ // deleting array to free its memory
    struct student_t *temp = students->arr;
    students->arr = NULL;
    students->size = 0;
    free(temp);

}
void testArray(int n)			//test the array list structure
{
struct studentArray StdArr = initArray();
    float t;
   
    for (int i=0 ; i< n; i++) pushStudent(&StdArr , getRandomData(),0);
    printf("    Size of the Array in the Memory: %d = %.2f KB\n" , sizeof(StdArr) * n, sizeof(StdArr) * n /1024.0);

    setRefrenceTick();
	pushStudent(&StdArr ,getRandomData(),0);  // insert at the begging
	t=getTimeMS();
	printf("    Time to Insert at the start: %.2f ms\n" , t);

	setRefrenceTick();
	pushStudent(&StdArr ,getRandomData(),(n+1)/2);  // insert at the middle
	t=getTimeMS();
	printf("    Time to Insert at the middle: %.2f ms\n" , t);

	setRefrenceTick();
	pushStudent(&StdArr ,getRandomData(),n+2);  // insert at the end
	t=getTimeMS();
	printf("    Time to Insert at the end: %.2f ms\n" , t);
	
}
int main()
{
	int n;
	char input [1];
	printf("Welcome To DataStructure Testing\n");
	getchar();

	printf("Procedures will be tested\n");
	printf("  1- Size of Array and Size of Linked list in the memory\n");
	printf("  2- size of one node of the linked list \n");
	printf("  3- time taken to insert student at (first , middle , end) of the array and linked list\n");
	printf("\n\n\n");


  
	struct node *head = createNode(*getRandomData());
	for (int i = 0; i < 5 ; i++) insertStudent(&head,getRandomData() ,0);
	
	getchar();

	printf("Testing Linked List");
	printf("\n\n  for n = 1000 (small)\n");
	testList(1000);

	printf("\n\n  for n = 10000 (medium)\n");
	testList(10000);
	printf("\n\n  for n = 100000 (large)\n");
	testList(100000);



	
	struct studentArray StdArr = initArray();



	
	getchar();
	printf("\n\n");
	printf("Testing array List");
	printf("\n\n  for n = 1000 (small)\n");
	testArray(1000);

	printf("\n\n  for n = 10000 (medium)\n");
	testArray(10000);
	printf("\n\n  for n = 100000 (large)\n");
	testArray(100000);


	printf("\n\nDone!!");
	getchar();


}

