#include <stdio.h>
#include "contact.h"

int main() 
{
    int choice;

    AddressBook addressBook;
    initialize(&addressBook); // Initialize the address book
	printf("\n");
    printf("%65s\n\n"," A D D R E S S  B O O K ");
    do 
    {
	printf("\n********  ");

	printf("Address Book Menu");	
	
	printf("  ********\n\n");	

	printf("1. Create contact\n");
	printf("2. Search contact\n");
	printf("3. Edit contact\n");
	printf("4. Delete contact\n");
	printf("5. List all contacts\n");
	printf("6. Save and Exit\n");
	printf("--------------------\n");
	printf("Enter your choice:\n");
	printf("--------------------\n");
	scanf("%d", &choice);
	char ch;
	if (choice == ch) 
	{
        printf("Invalid input. Try again.\n");
        getchar();// Clear input buffer
    }

	switch (choice) 
	{
	    case 1:
		createContact(&addressBook);
		break;
	    case 2:
		searchContact(&addressBook);
		break;
	    case 3:
		editContact(&addressBook);
		break;
	    case 4:
		deleteContact(&addressBook);
		break;
	    case 5:
		listContacts(&addressBook);
		break;
	    case 6:
		//printf("Saving and Exiting...\n");
		saveContactsToFile(&addressBook);
		break;
	    default:
		printf("Invalid choice.Please enter the choice between 1 and 7:\n");
	}
    } while (choice != 6);
     
    //cleanup(); // Cleanup any resources before exiting
    return 0;
}