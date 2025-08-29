
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "contact.h"
#include "file.h"
#include "populate.h"
#include <ctype.h>
int validatePhone(const char *phone);
int validateEmail(const char *email);

void listContacts(AddressBook *addressBook) 
{
    printf("______________________________________________________________________________________________________________________________________________________________\n\n");
    if (addressBook->contactCount == 0) 
    {
        printf("-----------------------------\n");
        printf("Your contact list is empty..!\n");
        printf("Press Enter Button to exit...\n");
        printf("-----------------------------\n");
        getchar();  // Wait for the user to press Enter
        return;
    }
    printf("%-22s%-22s%-22s\n", "NAME", "PHONE", "EMAIL");
   printf("_____________________________________________________________________________________________________________________________________________________________\n\n");
    for (int i = 0; i < addressBook->contactCount; i++)
    {
       
        printf("%-20s%-20s%-20s\n",
               addressBook->contacts[i].name,
               addressBook->contacts[i].phone,
               addressBook->contacts[i].email);
    }
    printf("\n_________________________________________________________________________________________________________________________________________________________\n\n");
    
    printf("--------------------------------------------\n");
    printf("Contact list is displayed successfully.\n");
    printf("Press Enter Key to exit.\n");
    printf("--------------------------------------------\n");
    
    getchar();  // Wait for the user to press Enter
}

void initialize(AddressBook *addressBook)
 {
    addressBook->contactCount = 0;
    populateAddressBook(addressBook);
    
    // Load contacts from file during initialization (After files)
    //loadContactsFromFile(addressBook);
}

void saveContactsToFile(AddressBook *addressBook) {
    FILE *file = fopen("contacts.csv", "w");
    if (file == NULL) {
        printf("Error opening file!\n");
        return;
    }

    // Write contacts to file
    for (int i = 0; i < addressBook->contactCount; i++) {
        if (fprintf(file, "%s,%s,%s\n",
                    addressBook->contacts[i].name,
                    addressBook->contacts[i].phone,
                    addressBook->contacts[i].email) < 0) {
            printf("\n--------------------\n");
            printf("Error writing to file!\n");
            printf("\n--------------------\n");
            break;
        }
    }

    //fflush(file);
    fclose(file);
    printf("\n----------------------------\n");
    printf("Contacts saved to contacts.csv\n");
    printf("\n------------------------ ---\n");
}



void createContact(AddressBook *addressBook) 
{   
    printf("-------------------\n");
    printf("Enter contact name:\n");
    printf("-------------------\n");
    scanf(" %[^\n]", addressBook->contacts[addressBook->contactCount].name);
    
    printf("--------------------\n");
    printf("Enter contact phone:\n");
    printf("--------------------\n");
    scanf(" %[^\n]", addressBook->contacts[addressBook->contactCount].phone);

    // Check if phone number already exists
    int phoneExists = 0;
    for (int i = 0; i < addressBook->contactCount; i++) 
    {
        if (strcmp(addressBook->contacts[i].phone, addressBook->contacts[addressBook->contactCount].phone) == 0) {
            phoneExists = 1;
            break;
        }
    }

    while (!validatePhone(addressBook->contacts[addressBook->contactCount].phone) || phoneExists) 
    {
        if (phoneExists)
         {
            printf("--------------------------------------------\n");
            printf("Oops..!! That phone number is already taken..!");
            printf("Please try a different one.\n");
            printf("------------------------------------------\n");
        } else {
           printf("\n---------------------------------------------\n");
           printf("Invalid phone number..!!");
           printf("Please enter a valid one:\n");
           printf("---------------------------------------------\n");
    
           

        }
        scanf(" %[^\n]", addressBook->contacts[addressBook->contactCount].phone);

        // Re-check if phone number already exists
        phoneExists = 0;
        for (int i = 0; i < addressBook->contactCount; i++) 
        {
            if (strcmp(addressBook->contacts[i].phone, addressBook->contacts[addressBook->contactCount].phone) == 0) {
                phoneExists = 1;
                break;
            }
        }
    }
    printf("\n-----------------\n");
    printf("Enter the Email Id:\n");
    scanf(" %[^\n]", addressBook->contacts[addressBook->contactCount].email);

    while (!validateEmail(addressBook->contacts[addressBook->contactCount].email)) 
    {
        printf("\n---------------------------------------------------\n");
        printf("Invalid email address\n");
        printf("Please enter a valid email Like -> example@example.com:\n");
        printf("\n---------------------------------------------------\n");

        scanf(" %[^\n]", addressBook->contacts[addressBook->contactCount].email);
    }

    addressBook->contactCount++;
    printf("\n----------------------------------------\n");
    printf("Success..! Your contact has been created.\n");
    printf("\n----------------------------------------\n");

}


void searchContact(AddressBook *addressBook) 
{
    int choice;
    char search_the_contact[50];
    printf("---------------------\n");
    printf("Search Contact By:\n");
    printf("1. Name\n");
    printf("2. Phone\n");
    printf("3. Email\n");
    printf("---------------------\n");
    printf("Enter your choice:\n");
    printf("---------------------\n");
    scanf("%d", &choice);
    switch (choice) {
        case 1:
            printf("---------------------\n");
            printf("Enter contact name:\n");
            printf("---------------------\n");
            scanf(" %[^\n]", search_the_contact);
            int count = 0;
            for (int i = 0; i < addressBook->contactCount; i++) 
            {
                if (strcmp(addressBook->contacts[i].name, search_the_contact) == 0) 
                {
                    printf("-----------------------------\n");
                    printf("Contact %d found:\n",count + 1);
                    printf("-----------------------------\n");
                    printf("Name:  %s\n", addressBook->contacts[i].name);
                    printf("Phone: %s\n", addressBook->contacts[i].phone);
                    printf("Email: %s\n\n", addressBook->contacts[i].email);
                    count++;
                }
            }
            if (count == 0) 
            {
                printf("-------------------\n");
                printf("Contact not found.\n");
                printf("-------------------\n");
            } else if (count > 1) 
            {
                printf("---------------------------------------------------\n");
                printf(" NOTE: Multiple contacts found with the same name.\n");
                printf("---------------------------------------------------\n");
            }
            break;
        case 2:
            printf("--------------------\n");
            printf("Enter contact phone:\n");
            printf("--------------------\n");
            scanf(" %[^\n]", search_the_contact);
            for (int i = 0; i < addressBook->contactCount; i++) 
            {
                if (strcmp(addressBook->contacts[i].phone, search_the_contact)==0) 
                {
                    printf("\n-------------\n");
                    printf("Contact found:\n");
                    printf("\n-------------\n");
                    printf("Name:  %s\n", addressBook->contacts[i].name);
                    printf("Phone: %s\n", addressBook->contacts[i].phone);
                    printf("Email: %s\n", addressBook->contacts[i].email);
                    return;
                }
            }
            printf("--------------------\n");
            printf("Contact not found.\n");
            printf("--------------------\n");
            break;
        case 3:
            printf("--------------------\n");
            printf("Enter contact email:\n");
            printf("--------------------\n");
            scanf(" %[^\n]", search_the_contact);
            for (int i = 0; i < addressBook->contactCount; i++) 
            {
                if (strcmp(addressBook->contacts[i].email, search_the_contact) == 0) 
                {  
                    printf("------------ --\n");
                    printf("Contact found:\n");
                    printf("---------------\n");
                    printf("Name:  %s\n", addressBook->contacts[i].name);
                    printf("Phone: %s\n", addressBook->contacts[i].phone);
                    printf("Email: %s\n", addressBook->contacts[i].email);
                    return;
                }
            }
            printf("------------------\n");
            printf("Contact not found.\n");
            printf("------------------\n");
            break;
        default:
            printf("----------------------------------\n");
            printf("Invalid choice. Please try again.\n");
            printf("----------------------------------\n");
            getchar(); // Clear input buffer

    }
}


void editContact(AddressBook *addressBook) {
    int choice;
    char search_the_contact[50];

   printf("-----------------\n");
    printf("Edit Contact By\n");
    printf("-----------------\n");
    printf("Press 1. Name\n");
    printf("Press 2. Phone number\n");
    printf("Press 3. Email Id\n");
    printf("------------------------------\n");
    scanf("%d", &choice);

    switch (choice) {
        case 1:
            
            printf("Enter Contact Name:\n");
            scanf(" %[^\n]", search_the_contact);
            break;
        case 2:
            printf("Enter contact Phone Number:\n");
            scanf(" %[^\n]", search_the_contact);
            break;
        case 3:
            printf("Enter contact email:\n");
            scanf(" %[^\n]", search_the_contact);
            break;
        default:
            printf("---------------------------------\n");
            printf("Invalid choice. Please try again.\n");
            printf("---------------------------------\n");
            getchar();
            return;
    }

    int found = 0;
    int indices[100]; // Store indices of matching contacts
    int count = 0; // Count of matching contacts

    // Search for contacts
    for (int i = 0; i < addressBook->contactCount; i++) {
        if ((choice == 1 && strcmp(addressBook->contacts[i].name, search_the_contact) == 0) ||
            (choice == 2 && strcmp(addressBook->contacts[i].phone, search_the_contact) == 0) ||
            (choice == 3 && strcmp(addressBook->contacts[i].email, search_the_contact) == 0)) {
            found = 1;
            indices[count] = i;
            count++;
        }
    }

    if (found) {
        if (count == 1) {
            // Only one contact found, edit it
            int index = indices[0];
            printf("--------------\n");
            printf("Contact Found:\n");
            printf("--------------\n");
            printf("Name: %s\n", addressBook->contacts[index].name);
            printf("Phone: %s\n", addressBook->contacts[index].phone);
            printf("Email: %s\n", addressBook->contacts[index].email);

            // Ask user what they want to edit
            printf("-------------------------\n");
            printf("What do you want to edit?\n");
            printf("-------------------------\n");

            printf("1. Name\n");
            printf("2. Phone\n");
            printf("3. Email\n");
            printf("-----------------\n");
            printf("Enter your choice: ");
            printf("-----------------\n");
            int editChoice;
            scanf("%d", &editChoice);

            // Edit contact
            switch (editChoice) {
                case 1:
                    printf("Enter new name:\n");
                    char newName[50];
                    scanf(" %[^\n]", newName);
                    if (strlen(newName) > 0) {
                        strcpy(addressBook->contacts[index].name, newName);
                    }
                    break;
                case 2:
                    printf("Enter new phone:\n");
                    char newPhone[15];
                    scanf(" %[^\n]", newPhone);
                    // Check if phone number already exists
                    int phoneExists = 0;
                    for (int i = 0; i < addressBook->contactCount; i++) {
                        if (i != index && strcmp(addressBook->contacts[i].phone, newPhone) == 0) {
                            phoneExists = 1;
                            break;
                        }
                    }
                    while (!validatePhone(newPhone) || phoneExists) {
                        if (phoneExists) {
                            printf("---------------------------------------\n");
                            printf("Phone number already exist");
                            printf("Please enter a different phone number:\n ");
                            printf("---------------------------------------\n");
                        } else {
                            printf("----------------------------------\n");
                            printf("Invalid phone number\n");
                            printf("Please enter a valid phone number:\n");
                            printf("----------------------------------\n");
                        }
                        scanf(" %[^\n]", newPhone);
                        phoneExists = 0;
                        for (int i = 0; i < addressBook->contactCount; i++) {
                            if (i != index && strcmp(addressBook->contacts[i].phone, newPhone) == 0) {
                                phoneExists = 1;
                                break;
                            }
                        }
                    }
                    strcpy(addressBook->contacts[index].phone, newPhone);
                    break;
                case 3:
                    printf("Enter new email: ");
                    char newEmail[50];
                    scanf(" %[^\n]", newEmail);
                    if (strlen(newEmail) > 0) {
                        while (!validateEmail(newEmail)) {
                            printf("--------------------------\n");
                            printf("Invalid email. Enter again: ");
                            printf("--------------------------\n");
                            scanf(" %[^\n]", newEmail);
                        }
                        strcpy(addressBook->contacts[index].email, newEmail);
                    }
                    break;
                default:
                    printf("-----------------\n");
                    printf("Invalid choice.\n");

                    getchar();
                    return;
            }
            printf("------------------------------\n");
            printf("Contact updated successfully!\n");
            printf("------------------------------\n");
        } 
        else 
        {
            // Multiple contacts found, display options and ask user to select
            printf("------------------------------\n");
            printf("Multiple contacts found..!:\n");
            printf("------------------------------\n");
            for (int i = 0; i < count; i++) 
            {
                printf("%d. %s\t%s\t%s)\n", i + 1, addressBook->contacts[indices[i]].name, addressBook->contacts[indices[i]].phone,addressBook->contacts[indices[i]].email);
            }

            int selectChoice;
            printf("----------------------------------\n");
            printf("Enter the serial number to edit it: ");
            printf("----------------------------------\n");
            scanf("%d", &selectChoice);

            if (selectChoice >= 1 && selectChoice <= count) {
                int index = indices[selectChoice - 1];
                printf("-----------------\n");
                printf("Contact selected:\n");
                printf("-----------------\n");
                printf("Name: %s\n", addressBook->contacts[index].name);
                printf("Phone: %s\n", addressBook->contacts[index].phone);
                printf("Email: %s\n", addressBook->contacts[index].email);

                // Ask user what they want to edit
                printf("-------------------------\n");
                printf("What do you want to edit?\n");
                printf("-------------------------\n");
                printf("1. Name\n");
                printf("2. Phone\n");
                printf("3. Email\n");
                printf("------------------\n");
                printf("Enter your choice:\n");
                printf("------------------\n");
                int editChoice;
                scanf("%d", &editChoice);

                // Edit contact
                switch (editChoice) {
                    case 1:
                        printf("---------------\n");
                        printf("Enter new name:\n");
                        printf("---------------\n");
                        char newName[50];
                        scanf(" %[^\n]", newName);
                        if (strlen(newName) > 0) {
                            strcpy(addressBook->contacts[index].name, newName);
                        }
                        break;
                    case 2:
                        printf("----------------\n");
                        printf("Enter new phone:\n");
                        printf("----------------\n");
                        char newPhone[15];
                        scanf(" %[^\n]", newPhone);
                        // Check if phone number already exists
                        int phoneExists = 0;
                        for (int i = 0; i < addressBook->contactCount; i++) {
                            if (i != index && strcmp(addressBook->contacts[i].phone, newPhone) == 0) {
                                phoneExists = 1;
                                break;
                            }
                        }
                        while (!validatePhone(newPhone) || phoneExists) {
                            if (phoneExists) {
                                printf("------------------------------\n");
                                printf("Phone number already exists.\nPlease enter a different phone number:\n");
                                printf("------------------------------\n");
                            } else {
                                printf("----------------------\n");
                                printf("Invalid phone number.\nPlease enter a valid phone number:\n");
                                printf("----------------------\n");
                            }
                            scanf(" %[^\n]", newPhone);
                            phoneExists = 0;
                            for (int i = 0; i < addressBook->contactCount; i++) {
                                if (i != index && strcmp(addressBook->contacts[i].phone, newPhone) == 0) {
                                    phoneExists = 1;
                                    break;
                                }
                            }
                        }
                        strcpy(addressBook->contacts[index].phone, newPhone);
                        break;
                    case 3:
                        printf("---------------\n");
                        printf("Enter new email:\n");
                        printf("----------------\n");
                        char newEmail[50];
                        scanf(" %[^\n]", newEmail);
                        if (strlen(newEmail) > 0) {
                            while (!validateEmail(newEmail)) {
                                printf("-----------------------\n");
                                printf("Invalid email. Enter again:\n");
                                printf("--------------------- -\n");
                                scanf(" %[^\n]", newEmail);
                            }
                            strcpy(addressBook->contacts[index].email, newEmail);
                        }
                        break;
                    default:
                        printf("---------------\n");
                        printf("Invalid choice.\n");
                        printf("---------------\n");
                        getchar();
                        return;
                }
                printf("-----------------------------\n");
                printf("Contact updated successfully!\n");
                printf("-----------------------------\n");
            } else 
            {
                printf("---------------\n");
                printf("Invalid choice.\n");
                printf("---------------\n");
            }
        }
    } else {
        printf("------------------\n");
        printf("Contact not found.\n");
        printf("------------------\n");
    }
}


void deleteContact(AddressBook *addressBook) {
    char name[50];
    printf("\n--------------------------\n");
    printf("Enter contact name to delete: ");
    printf("\n-------------------------\n");
    scanf(" %[^\n]", name);

    int found = 0;
    int indices[100]; // Store indices of matching contacts
    int count = 0; // Count of matching contacts

    // Search for contacts with the given name
    for (int i = 0; i < addressBook->contactCount; i++) {
        if (strcmp(addressBook->contacts[i].name, name) == 0) {
            found = 1;
            indices[count] = i;
            count++;
        }
    }

    if (found) {
        if (count == 1) {
            // Only one contact found, delete it
            int index = indices[0];
            for (int i = index; i < addressBook->contactCount - 1; i++) {
                addressBook->contacts[i] = addressBook->contacts[i + 1];
            }
            addressBook->contactCount--;
            printf("-----------------------------\n");
            printf("Contact deleted successfully!\n");
            printf("-----------------------------\n");
        } else {
// Multiple contacts found, display options and ask user to select
            printf("------------------------\n");
            printf("Multiple contacts found:\n");
            printf("------------------------\n");
            for (int i = 0; i < count; i++)
             {
                printf("\n-------------------------------------------------------------------");
                printf("\n%d. %s\t\t%s\t|\t %s", i + 1, addressBook->contacts[indices[i]].name,addressBook->contacts[indices[i]].phone,addressBook->contacts[indices[i]].email);
            }   printf("\n-------------------------------------------------------------------");

            int choice;
            printf("\n-----------------------------------------------------------------\n");
            printf("\nEnter the serial number of the contact which you want to delete: ");
            printf("\n-----------------------------------------------------------------\n");
            scanf("%d", &choice);

            if (choice >= 1 && choice <= count) {
                int index = indices[choice - 1];
                for (int i = index; i < addressBook->contactCount - 1; i++) {
                    addressBook->contacts[i] = addressBook->contacts[i + 1];
                }
                addressBook->contactCount--;
                printf("------------------------------\n");
                printf("Contact deleted successfully!\n");
                printf("------------------------------\n");
            } else {
                printf("---------------\n");
                printf("Invalid choice.\n");
                printf("---------------\n");
            }
        }
    } else {
        printf("------------------\n");
        printf("Contact not found.\n");
        printf("------------------\n");
    }
}



int validatePhone(const char *phone) 
{
    if (strlen(phone) != 10)
    {
        return 0;
    }

    for (int i = 0; i < 10; i++)
     {
        if (phone[i] < '0' || phone[i] > '9') 
        {
            return 0;
        }
     }
    return 1;

}
int validateEmail(const char *email) 
{
    int at = 0, dot = 0;
    int len = strlen(email);
    for (int i = 0; i < len; i++) 
    {
        if(email[i]>='A' && email[i]<='Z')
        {
           return 0;

        }
        else if (email[i] == '@')
        {
            at++;
        } 
        else if (email[i] == '.')
        {
            dot++;
        }
         
    }
    if (at == 1 && dot>=1 && strstr(email, ".com") != NULL && strcmp(email + len - 4, ".com") == 0)
    {
        return 1;
    }
    return 0;
}