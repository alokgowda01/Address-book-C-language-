#include "contact.h"
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdio_ext.h>  
#define FILE_NAME "contacts.txt"

int isvalidname(char *name,AddressBook *addressBook)
{
        int isvalid = 1;
        int l,i;  // Reset before each loop

        l = strlen(name);  // Get length of the name

        // Validate name (alphabets and spaces only)
        for ( i = 0; i < l; i++) {
            if (!isalpha(name[i]) && name[i] != ' ') {
                printf("Invalid name. Only alphabetic characters and spaces are allowed.\n");
                return 0;
            }
        }

        // Check for duplicate names
        for (i = 0; i < addressBook->contactCount; i++) {
            if (strcasecmp(addressBook->contacts[i].name, name) == 0) {
                printf("Name already exists. Please enter a different name.\n");
                return 0;
            }
        }
     return 1;
}
int isvalidphone(char *phone,AddressBook *addressBook)
{
    int i;
if (strlen(phone) != 10) {
            printf("Invalid phone number. It should contain exactly 10 digits.\n");
            return 0;
        }

        for ( i = 0; i < 10; i++) {
            if (!isdigit(phone[i])) {
                printf("Phone number should contain only digits.\n");
                return 0;
            }
        }

        // Check for duplicate phone numbers
        for (i = 0; i < addressBook->contactCount; i++) {
            if (strcmp(addressBook->contacts[i].phone, phone) == 0) {
                printf("Phone number already exists. Please enter a different number.\n");
                return 0;
            }
        }
        return 1;
}

int isvalidemail(char *email,AddressBook *addressBook)
{
int l=strlen(email);
        int at = -1,i;
        char *dot = strstr(email, ".com");
        for(i=0;i<l;i++)
        {
            if(email[i]=='@')
            {
            at=i;
            break;
            }
        }

        if (at <=0 || dot == NULL||(dot-email)-at<=1||strlen(dot)!=4)
         {
            printf("Invalid email format.\n");
            return 0;
        }

        // Check for duplicate emails
        for (i = 0; i < addressBook->contactCount; i++) {
            if (strcmp(addressBook->contacts[i].email, email) == 0) {
                printf("Email already exists. Please enter a different email.\n");
                return 0;
            }
        }
        return 1;
}
// Function to list all contact
void listContacts(AddressBook *addressBook) {
    if (addressBook->contactCount == 0) {
        printf("No contacts found.\n");
    } else {
        printf("\nContact List:\n");
        for (int i = 0; i < addressBook->contactCount; i++) {
            printf("%d.\t%s\t\t%10.10s\t%s\n", i + 1, addressBook->contacts[i].name, addressBook->contacts[i].phone, addressBook->contacts[i].email);
        }
    }
}


// Function to create a contact
void createContact(AddressBook *addressBook) 
{
    char name[30];
    char phone[11];
    char email[30];
    int isvalid = 0;
    

    // To check if input name is valid
    do {
        isvalid = 1;  // Reset before each loop
        printf("Enter name: ");
        __fpurge(stdin);  // Clear input buffer
        scanf(" %29[^\n]", name);
     isvalid=isvalidname(name,addressBook);
        
     } while (isvalid != 1);
     
    strcpy(addressBook->contacts[addressBook->contactCount].name, name);  // Store name

    // Phone number validation
    do {
        isvalid = 1;  // Reset before each loop
        printf("Enter a phone number (10 digits): ");
        __fpurge(stdin);
        scanf("%10s", phone);
       isvalid=isvalidphone(phone,addressBook);
    } while (isvalid != 1);

    strcpy(addressBook->contacts[addressBook->contactCount].phone, phone);  // Store phone

    // Email validation
    do {
        isvalid = 1;  // Reset before each loop
        printf("Enter email: ");
        __fpurge(stdin);
        scanf("%s", email);     
    isvalid=isvalidemail(email,addressBook);
    } while (isvalid != 1);

    strcpy(addressBook->contacts[addressBook->contactCount].email, email);  // Store email

    // Increment the contact count
    addressBook->contactCount++;

    printf("Contact added successfully.\n");
}



// Function to search for a contact by name, phone number, email, or surname
void searchContact(AddressBook *addressBook) {
    char searchTerm[50];
    int found = 0;
    int choice;
    int fc=0;

        // Menu for choosing the search type
        printf("\nSearch with:\n");
        printf("1. Name\n");
        printf("2. Phone number\n");
        printf("3. Email\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        __fpurge(stdin);  // Clear any leftover input

        switch (choice) 
        {
            case 1:
                // Search by name or surname
                printf("Enter the name or surname to search: ");
                scanf(" %49[^\n]", searchTerm);
                found = 0;  // Reset found flag

                for (int i = 0; i < addressBook->contactCount; i++) 
                {
                    // Check for surname match or full name match
                    if (strcasestr(addressBook->contacts[i].name, searchTerm)) {
                        printf("%d. %s\t\t%10.10s\t%s\n",fc+1,
                               addressBook->contacts[i].name,
                               addressBook->contacts[i].phone,
                               addressBook->contacts[i].email);
                        found = 1;
                        fc++;
        
                    }
                }
                if(found==1)
                printf("Contact Found Successfully\n");
                if (!found) 
                {
                    printf("No contacts found with the name or surname: %s\n", searchTerm);
                }
                break;
    
            case 2:
                // Search by phone number
                printf("Enter the phone number to search: ");
                scanf(" %[^\n]%*c", searchTerm);
                found = 0;
                 // Reset found flag

                for (int i = 0; i < addressBook->contactCount; i++) {
                    if (strstr(addressBook->contacts[i].phone, searchTerm)!=NULL) {
                       printf("%d. %s\t\t%10.10s\t%s\n",fc+1,
                               addressBook->contacts[i].name,
                               addressBook->contacts[i].phone,
                               addressBook->contacts[i].email);
                        found = 1;
                        fc++;
                    }
                }
            if(found==1)
                printf("Contact Found Successfully\n");
                if (!found) {
                    printf("No contacts found with the phone number: %s\n", searchTerm);
                }
                break;
            case 3:
                // Search by email
                printf("Enter the email to search: ");
                scanf(" %[^\n]%*c", searchTerm);
                found = 0;  // Reset found flag
            for(int i=0;i<addressBook->contactCount;i++)
        {
            if(strstr(addressBook->contacts[i].email,searchTerm)!=NULL)
            {
                printf("%d. %s\t\t%10.10s\t%s\n",fc+1,
                               addressBook->contacts[i].name,
                               addressBook->contacts[i].phone,
                               addressBook->contacts[i].email);
                found=1;
                fc++;
            }
        }
        if(found==1)
                printf("Contact Found Successfully\n");
            
                if (!found) {
                    printf("No contacts found with the email: %s\n", searchTerm);
                }
                break;

            case 4:
                // Exit the search function
                printf("Exiting search...\n");
                break;

            default:
                printf("Invalid choice, please try again.\n");
    }
}


void editContact(AddressBook *addresBook)
{
 int choice;
 char editTerm[30];
 int arr[100];
 int count=0,flag=0,ch,var,isvalid;
 char name[30],phone[30],email[30];
 
        printf("Enter name,phone number or email to edit:");
        __fpurge(stdin);
        scanf("%29[^\n]",editTerm);
        __fpurge(stdin);
        for(int i=0;i<addresBook->contactCount;i++)
        {
            if(strstr(addresBook->contacts[i].name,editTerm)!=NULL||
            strstr(addresBook->contacts[i].phone,editTerm)!=NULL||
            strstr(addresBook->contacts[i].email,editTerm)!=NULL)
            {
           printf("%d. %s\t\t%10.10s\t%s\n",
                              count+1, addresBook->contacts[i].name,
                               addresBook->contacts[i].phone,
                               addresBook->contacts[i].email);
              arr[count]=i;
              count++;
              flag=1;
            }
        }
        if(flag==0)
        {
            printf("Matching contact not found");
            return;
        }
        printf("Enter the Serial number to  edit:");
        __fpurge(stdin);
        scanf("%d",&ch);
        __fpurge(stdin);
        ch--;
        if(ch<0||ch>=count)
        {
            printf("Invalid Input");
            return;
        }
        var=arr[ch];
            printf("Edit By\n");
            printf("1. Name\n");
            printf("2.Phone Number\n");
            printf("3.Email\n");
            printf("\nEnter choice:");
            scanf("%d",&choice);
            switch(choice){
                case 1:
                  do {
                      isvalid = 1;  // Reset before each loop
                    printf("\nEnter name: ");
                    __fpurge(stdin);  // Clear input buffer
                    scanf(" %29[^\n]", name);
                    isvalid=isvalidname(name,addresBook);   
                   } while (isvalid != 1);
                   if(isvalid==1)
                   {
                    strcpy(addresBook->contacts[var].name,name);
                    printf("\nName Updated\n");
                   }
                break;
            case 2:
              do {
              isvalid = 1;  // Reset before each loop
              printf("\nEnter a phone number (10 digits): ");
             __fpurge(stdin);
             scanf("%10s", phone);
             isvalid=isvalidphone(phone,addresBook);
             } while (isvalid != 1);
             if(isvalid==1)
             {
                strcpy(addresBook->contacts[var].phone,phone);
                printf("\nPhone Number Updated\n");
             }
             break;
             case 3:
             do {
              isvalid = 1;  // Reset before each loop
              printf("\nEnter a Email : ");
             __fpurge(stdin);
             scanf("%10s", email);
             isvalid=isvalidemail(email,addresBook);
             } while (isvalid != 1);
             if(isvalid==1)
             {
                strcpy(addresBook->contacts[var].email,email);
                printf("\nPhone Number Updated\n");
             }
             break;
             default:
             printf("Invalid Choice");
            }
} 
void deleteContact(AddressBook *addressBook)
{
 int choice;
 char deleteTerm[30];
 int arr[100];
 int count=0,flag=0,ch,var,isvalid;
 char name[30],phone[30],email[30];
 
        printf("Enter name,phone number or email to delete:");
        __fpurge(stdin);
        scanf("%29[^\n]",deleteTerm);
        __fpurge(stdin);
        for(int i=0;i<addressBook->contactCount;i++)
        {
            if(strstr(addressBook->contacts[i].name,deleteTerm)!=NULL||
            strstr(addressBook->contacts[i].phone,deleteTerm)!=NULL||
            strstr(addressBook->contacts[i].email,deleteTerm)!=NULL)
            {
                printf("%d. %s\t\t%10.10s\t%s\n",
                              count+1, addressBook->contacts[i].name,
                               addressBook->contacts[i].phone,
                               addressBook->contacts[i].email);
              arr[count]=i;
              count++;
              flag=1;
            }
        }
        if(flag==0)
        {
            printf("Matching contact not found");
            return;
        }
        printf("Enter the Serial number to  delete:");
        __fpurge(stdin);
        scanf("%d",&ch);
        __fpurge(stdin);
        ch--;
        if(ch<0||ch>=count)
        {
            printf("Invalid Input");
            return;
        }
        var=arr[ch];   
for(int i=var;i<addressBook->contactCount-1;i++)
{
    addressBook->contacts[i]=addressBook->contacts[i+1];

}
addressBook->contactCount--;
printf("Contact deleted SUccessfully\n");
}
//function to load contact from the file
void loadContactsFromFile(AddressBook *addressBook) {
    FILE *file = fopen(FILE_NAME, "r");
    if (file == NULL) {
        printf("No contacts file found. Starting with an empty address book.\n");
        return;
    }
    addressBook->contactCount = 0;
    while (fscanf(file, "%49[^,],%19[^,],%49[^\n]\n", 
                  addressBook->contacts[addressBook->contactCount].name, 
                  addressBook->contacts[addressBook->contactCount].phone, 
                  addressBook->contacts[addressBook->contactCount].email) == 3) {
        addressBook->contactCount++;
    }

    fclose(file);
}
// Function to save contacts to the file
void saveContactsToFile(AddressBook *addressBook) {
    FILE *file = fopen(FILE_NAME, "w");
    if (file == NULL) {
        printf("Error opening file to save contacts.\n");
        return;
    }
    for (int i = 0; i < addressBook->contactCount; i++) {
        fprintf(file, "%s,%s,%s\n", addressBook->contacts[i].name, 
                                    addressBook->contacts[i].phone, 
                                    addressBook->contacts[i].email);
    }
    fclose(file);
    printf("Contacts saved to file successfully.\n");
}