/////////////////////////////////////////////////////////////////////////////////////////

#include "main.h"

/*  Author: Jakub Glebocki
NETID: jglebo2
*  Date: 2/2/2017
*/
//Function to add to the list
void addToList(RestauranStruct **head, char* name, int size, STATUS currstatus, int DEBUGMODE) {
	if (DEBUGMODE == 1) {
		if (currstatus == in_restaurant)
			fprintf(stderr,"DEBUG:Adding: Name:%s size:%d Status: In Restarant \n", name, size);

		else if (currstatus == in_callahead) {
			fprintf(stderr,"DEBUG:Adding: Name:%s size:%d Status: In call \n", name, size);
		}
	}

	if (*head == NULL) { //If head is NULL
		RestauranStruct *newlist = (RestauranStruct*)malloc(sizeof(RestauranStruct)); //Malloc memory for NODE

		strcpy(newlist->name, name); //Copy name
		newlist->Groupsize = size;// copy size
		newlist->currstatus = currstatus; //copy current sattus

		newlist->pnext = *head; //set newlist to point to head
		*head = newlist; //Set head to point to list

	}
	else {
		addToList(&(*head)->pnext, name, size, currstatus, DEBUGMODE); //Otherwise add to list
	}
}


//DisplayInfoFucntion
void displayListInformation(RestauranStruct **head) {

	int j = 1;
	RestauranStruct *temp = *head;
	if (temp == NULL) { //If temp is NULL
		fprintf(stderr,"The List is empty\n");
	}

	while (temp != NULL) {
		if (temp->currstatus == in_restaurant) {//if status match aka person is in restaurant print this
			printf("%d. Name:%s Size:%d Status: present \n", j, temp->name, temp->Groupsize);
		}
		else {
			printf("%d. Name: %s Size: %d Status: Not present \n", j, temp->name, temp->Groupsize);//Otherwise if not in restaurant print this
		}
		j++; //Increase j
		temp = temp->pnext; //Advance pointer
	}
}


//Does name exist function
int doesNameExist(RestauranStruct **head, char *name, int DEBUGMODE) {

	RestauranStruct *temp = *head;

	if (temp == NULL) {//if temp is NULL then return 0.
		return NO;
	}

	while (temp != NULL) { //ELse if nto NULL
		if (strcmp(temp->name, name) == 0) { //and names match
			if (DEBUGMODE == 1) {
				printf("The name %s Exists\n", name);
			}
			return YES;//return 1
		}
		else {
			temp = temp->pnext; //otherwise keep searching
		}
	}

	return NO; //if here, name does not exist
}


//Set the status of on-call to in-restaurant
int updateStatus(RestauranStruct **head, char* name, int DEBUGMODE) {
	RestauranStruct *temp = *head;
	if (temp == NULL) { //if temp is NULL
		fprintf(stderr,"List is empty\n");
		return NO; //return 0
	}
	while (temp != NULL) {
		if (strcmp(temp->name, name) == NO) {
			break; //If names match the break
		}
		temp = temp->pnext;
	}

	if (temp->currstatus == in_restaurant) { //If they are already in restuarant return 0
		return NO;
	}
	else if (temp->currstatus == in_callahead) { //If status is call-ahead then return to 1
		temp->currstatus = in_restaurant;
		if (DEBUGMODE == TRUE) {
			fprintf(stderr,"DEBUG:%s has been succesfully changed to in_restaurant status\n", name);
		}
		return 1;
	}
}

//Sit people down in restaurant
RestauranStruct* retrieveAndRemove(RestauranStruct **head, int size, int DEBUGMODE) {
	RestauranStruct *temp = *head; //Set new head
	RestauranStruct *a; //temporary pointer

	if (temp == NULL) {
		return NULL; //If temp is nULL return NULL
	}

	//Checks first node
	if (temp->Groupsize <= size && temp->currstatus == in_restaurant) { //If Groupsize is less than size, and they are in restaurant
		*head = (*head)->pnext; //Advance pointer of head
		//free(temp);
		return temp; //free temp
	}
	else { //Check rest of linked list
		while (temp->pnext != NULL) { //If not NULL
			if (temp->pnext->Groupsize <= size) { //If groupsize is less than size
				if (temp->pnext->currstatus == in_restaurant) { //If status is in restuarant
					a = temp->pnext; //set pointer a to NODE
					temp->pnext = a->pnext; //advance temp pointer to next NDOE
					if (DEBUGMODE == 1) {
						printf("Returning from Remove functions, succesfully removed\n");
					}
					//free(a); //I free pointer in main. PROFFESSOR TROY SAID THIS WAS OKAY.
					return a; //return NODE
				}
			}
			temp = temp->pnext; //Advance temp
		}
	}
	//printf("groupSize DNE\n");
	return NULL; //If here, name DNE
}


//Count how many groups are ahead of a specific name
int countGroupsAhead(RestauranStruct **head, char *name) {
	RestauranStruct *temp = *head;
	int count = 0; //declare count
	if (temp == NULL) { //If NULL return 0
		return 0;
	}

	while (temp != NULL) { //WHILE NOT null
		if (strcmp(temp->name, name) == 0) { //If names match return count
			return count;
		}
		count++; //increment count until it finds the name we are searching for
		temp = temp->pnext; //advnace in LL
	}
	return 0; //If here name was not found
}


//Display the people ahead of group
void displayGroupSizeAhead(RestauranStruct **head, char* name) {
	RestauranStruct *temp = *head;
	int count = TRUE;
	if (temp == NULL) {
		return FALSE;
	}

	while (temp != NULL) {
		if (strcmp(temp->name, name) == NO) { //If names match, break the while loop
			break;
		}
		printf("%d.  Groupname:%s  GroupSize: %d\n", count, temp->name, temp->Groupsize); //Print the name's of NODE, the size of the NODE.
		count++; //increment count
		temp = temp->pnext; //Advance pointer
	}
	return 0;
}
