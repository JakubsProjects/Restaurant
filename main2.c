#include "main.h"


/*  Author: Jakub Glebocki
NETID: jglebo2
*  Date: 2/2/2017
*/
void doAdd(RestauranStruct**head, STATUS currstatus, int DEBUGMODE)
{
	/* get group size from input */
	int size = getPosInt();
	if (size < 1)
	{
		printf("Error: Add command requires an integer value of at least 1\n");
		printf("Add command is of form: a <size> <name>\n");
		printf("  where: <size> is the size of the group making the reservation\n");
		printf("         <name> is the name of the group making the reservation\n");
		return;
	}

	/* get group name from input */
	char *name = getName();
	if (NULL == name)
	{
		printf("Error: Add command requires a name to be given\n");
		printf("Add command is of form: a <size> <name>\n");
		printf("  where: <size> is the size of the group making the reservation\n");
		printf("         <name> is the name of the group making the reservation\n");
		return;
	}

	printf("Adding group \"%s\" of size %d\n", name, size);

	int returnval = doesNameExist(&(*head), name, DEBUGMODE); //Function returns 1 or 0

	if (returnval == TRUE) { //If returns 1, person is already on list
		printf("Name already exists, cannot add\n");
	}
	else {
		addToList(&(*head), name, size, currstatus, DEBUGMODE); //Ptherwise add to list
	}
}


void doCallAhead(RestauranStruct **head, STATUS currstatus, int DEBUGMODE)
{
	/* get group size from input */
	int size = getPosInt();
	if (size < 1)
	{
		printf("Error: Call-ahead command requires an integer value of at least 1\n");
		printf("Call-ahead command is of form: c <size> <name>\n");
		printf("  where: <size> is the size of the group making the reservation\n");
		printf("         <name> is the name of the group making the reservation\n");
		return;
	}

	/* get group name from input */
	char *name = getName();
	if (NULL == name)
	{
		printf("Error: Call-ahead command requires a name to be given\n");
		printf("Call-ahead command is of form: c <size> <name>\n");
		printf("  where: <size> is the size of the group making the reservation\n");
		printf("         <name> is the name of the group making the reservation\n");
		return;
	}

	printf("Call-ahead group \"%s\" of size %d\n", name, size);

	int returnval = doesNameExist(&(*head), name, DEBUGMODE);//Function returns 1 or 0

	if (returnval == TRUE) {//If returns 1, ,means person is on list
		fprintf(stderr,"Name already exists, cannot add\n");
	}
	else {
		addToList(&(*head), name, size, currstatus, DEBUGMODE);//If 0 add to list
	}
}

void doWaiting(RestauranStruct **head, int DEBUGMODE)
{
	/* get group name from input */
	char *name = getName();
	if (NULL == name)
	{
		printf("Error: Waiting command requires a name to be given\n");
		printf("Waiting command is of form: w <name>\n");
		printf("  where: <name> is the name of the group that is now waiting\n");
		return;
	}

	printf("Waiting group \"%s\" is now in the restaurant\n", name);

	int returnval = doesNameExist(&(*head), name, DEBUGMODE);//Function returns 1 or 0

	if (returnval == TRUE) { //If returns 1 name is already on list
		fprintf(stderr,"Name already exists, cannot add\n");
	}
	else { //If returns 0, name does not exist
		fprintf(stderr,"Name does not exist\n");
		return;
	}


	int returnval2 = updateStatus(head, name, DEBUGMODE);//Return value to update whether on call OR in restuarant
	if (DEBUGMODE == TRUE) { //If returns 1, up
		printf("DEBUG:Entering updateStatus function\n");
	}
		if (returnval2 == FALSE) { //If false, cannot update anem
			fprintf(stderr,"Cannot update name, already in waitinglist.\n");
		}
		else {
			fprintf(stderr,"Name Successfully updated to in restaurant\n");//Else successfully updated name
		}
}

void doRetrieve(RestauranStruct **head, int DEBUGMODE)
{
	/* get table size from input */
	int size = getPosInt();
	if (size < 1)
	{
		printf("Error: Retrieve command requires an integer value of at least 1\n");
		printf("Retrieve command is of form: r <size>\n");
		printf("  where: <size> is the size of the group making the reservation\n");
		return;
	}
	clearToEoln();
	printf("Retrieve (and remove) the first group that can fit at a tabel of size %d\n", size);

	RestauranStruct *returnVal = retrieveAndRemove(head, size, DEBUGMODE);

	if (returnVal == NULL) {
		fprintf(stderr,"List is empty or DID not find\n");
	}

	else {
		fprintf(stderr,"Name: %s", returnVal->name);
		free(returnVal);
	}
}

void doList(RestauranStruct **head, int DEBUGMODE)
{
	/* get group name from input */
	char *name = getName();
	if (NULL == name)
	{
		fprintf(stderr,"Error: List command requires a name to be given\n");
		fprintf(stderr,"List command is of form: l <name>\n");
		fprintf(stderr,"  where: <name> is the name of the group to inquire about\n");
		return;
	}

	printf("Group \"%s\" is behind the following groups\n", name);

	int returnval = doesNameExist(&(*head), name, DEBUGMODE); //Returns 1 or 0

	if (returnval == TRUE) { //If returns 1, naem already exists
		fprintf(stderr,"Name already exists, cannot add\n");
	}
	else { //otherwise name doesnt exist
		fprintf(stderr,"Name Does not exist\n");
		return;
	}

	int howMany = countGroupsAhead(head, name); //Return the number of groups ahead
	fprintf(stderr,"There are %d groups waiting to be seated ahead of %s\n", howMany, name);

	displayGroupSizeAhead(head, name); //Displays how many groups are ahead

}

void doDisplay(RestauranStruct *head, int DEBUGMODE)
{
	clearToEoln();
	printf("Display information about all groups\n");
	if (DEBUGMODE == TRUE) {
		fprintf(stderr,"entering the displayInfo Function\n");
	}
	displayListInformation(&head); //Displays lists of linked list
}
