#include "contact.h"
#include<string.h>
void populateAddressBook(AddressBook* addressBook) 
{
    FILE* file = fopen("contacts.csv", "r");
    if (file == NULL) 
    {
        printf("Error opening file!\n");
        return;
    }

    char line[100];
    while (fgets(line, sizeof(line), file)) 
    {
        char* token = strtok(line, ",");
        if (token != NULL) 
        {
            strcpy(addressBook->contacts[addressBook->contactCount].name, token);

            token = strtok(NULL, ",");
            if (token != NULL) 
            {
                strcpy(addressBook->contacts[addressBook->contactCount].phone, token);

                token = strtok(NULL, "\n");
                if (token != NULL) 
                {
                    strcpy(addressBook->contacts[addressBook->contactCount].email, token);
                    addressBook->contactCount++;
                }
            }
        }
    }
    fclose(file);
}
// Dummy contact data
/* static Contact dummyContacts[] = {
    {"Raj", "1234567898", "john@exaple.com"},
    {"Raj", "1234567890", "john@example.com"},
    {"Alice Smith", "0987654321", "alice@example.com"},
    {"Bob Johnson", "1112223333", "bob@company.com"},
    {"Carol White", "4445556666", "carol@company.com"},
    {"David Brown", "7778889999", "david@example.com"},
    {"Eve Davis", "6665554444", "eve@example.com"},
    {"Frank Miller", "3334445555", "frank@example.com"},
    {"Grace Wilson", "2223334444", "grace@example.com"},
    {"Hannah Clark", "5556667777", "hannah@example.com"},
    {"Ian Lewis", "8889990000", "ian@example.com"}
};

void populate(AddressBook *addressBook)
{
    // finding the size of an dummy arr
    int size=sizeof(dummyContacts)/sizeof(dummyContacts[0]);
    // coping arr elements to stc arr
    for(int i=0;i<size;i++)
    {
        addressBook->contacts[i]=dummyContacts[i];
    }
    addressBook->contactCount=size;
} */