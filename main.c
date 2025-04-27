#include "contact.h"
#include<string.h>
int main()
{
   AddressBook addressbook;
   addressbook.contactCount = 0;
   initialize(&addressbook);
   loadContactsFromFile(&addressbook);
    //use switch case to call the different function
    //display menu(create,search,edit,delete,list)
    //read the input from the user
    //based on input call a function
    int choice;
    do{
        printf("\nAddress Book Menu:\n");
        printf("1. Create Contact\n");
        printf("2. Search Contacts\n");
        printf("3. List Contact\n");
        printf("4. Delete Contact\n");
        printf("5. Edit Contact\n");
        printf("6. Save and Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                createContact(&addressbook);
                break;
            case 2:
                searchContact(&addressbook);
                break;
            case 3:
                listContacts(&addressbook);
                break;
                case 4:
                deleteContact(&addressbook);
                break;
                case 5:
                editContact(&addressbook);
                break;
                case 6:
                saveContactsToFile(&addressbook);
                //printf("Contact saved successfully and exiting program\n");
                break;
            default:
                printf("Invalid choice, please try again.\n");
        }
    }while(choice!=6);

    return 0;

}