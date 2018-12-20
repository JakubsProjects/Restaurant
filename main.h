#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*  Author: Jakub Glebocki
NETID: jglebo2
*  Date: 2/2/2017
*/


//Declaring structs and setting values
typedef enum { FALSE = 0, TRUE, NO = 0, YES } boolean;
typedef enum { in_restaurant, in_callahead }STATUS;

//Defining The restaurant Linked List
typedef struct RestauranStruct {
	char name[30];
	int Groupsize;
	STATUS currstatus;
	struct RestauranStruct* pnext;
}RestauranStruct;

//Adding function prototypes for main1
void clearToEoln();
int getNextNWSChar();
int getPosInt();
char *getName();
void clearToEoln();
void printCommands();

//Adding function prototypes for main2
void doAdd(RestauranStruct**head, STATUS currstatus, int DEBUGMODE);
void doCallAhead(RestauranStruct **head, STATUS currstatus, int DEBUGMODE);
void doWaiting(RestauranStruct **head, int DEBUGMODE);
void doRetrieve(RestauranStruct **head, int DEBUGMODE);
void doList(RestauranStruct **head, int DEBUGMODE);
void doDisplay(RestauranStruct *head, int DEBUGMODE);

//I understand we dont have to include all function calls that have been created
//Only the ones that are being used in main. But i still like to include most functions.
