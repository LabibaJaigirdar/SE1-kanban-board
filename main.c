#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//struct for items
struct item
{
    char itemName[100]; //name of item
    struct item *nextPtr; //pointer to next item in list
};

struct list
{
    char listName[100]; //name of list
    struct item *firstItem; //pointer to the first item in the list
    struct list *nextPtr; //pointer to next item in list
};

typedef struct list List; //synonym for struct list
typedef List *ListPtr; //synonym for *List
typedef struct item Item; //synonym for struct item
typedef Item *ItemPtr; //synonym for *Item

//prototypes
void initializeBoard(ListPtr *startPtr);
void displayBoard(ListPtr currentlist);
int searchList(ListPtr *sPtr, char listName[]);
int isEmpty(ListPtr sPtr);
void menu();
void editList(ListPtr *sPtr, char listName[]);
void addItem(ListPtr *sPtr, char listName[], char itemName[]);
void deleteItem(ListPtr *sPtr, char listName[], char itemName[]);
void editItem(ListPtr *sPtr, char listName[], char itemName[]);
void editBoard(ListPtr *sPtr);
void addList(ListPtr *sPtr, char listName[]);
void deleteList(ListPtr *sPtr, char listName[]);
void editListName(ListPtr *sPtr, char listName[]);

int main()
{
    char item[100]; //char entered by user
    int choice; //user choice

    ListPtr startPtr = NULL;

    initializeBoard(&startPtr);


    menu(); //display menu
    printf("\nEnter your choice (1-5): ");
    scanf("%d", &choice);

    //loop while user does not choose to quit
    while (choice != 6)
    {
        if (choice == 1)
        {
            displayBoard(startPtr);
        }

        if (choice == 2) //load board from a file
        {
            puts("Enter filename:");
            char fileName[100];
            fflush(stdin);
            fgets(fileName, 100, stdin);
        }

        if (choice == 3) //edit list
        {
            printf("\nEnter the name of the list to edit: ");
            char listName[100];
            fflush(stdin);
            fgets(listName, 100, stdin); //get name of list
            listName[strlen(listName) - 1] = '\0'; //remove trailing newline

            //take input while the list name is not found
            while(searchList(&startPtr, listName) != 0) {

                if (searchList(&startPtr, listName)) {
                    printf("Can't find list.\n");
                }

                else
                {
                    break;
                }

                puts("Enter the name of the list to edit:");
                fgets(listName, 100, stdin);
                listName[strlen(listName) - 1] = '\0';
            }

            editList(&startPtr, listName);

        }

        if (choice == 4)//edit board
        {
            editBoard(&startPtr);
        }

        if (choice == 5) //save board to a file
        {

        }

        if (choice == 6) // quit
        {
            return 0;
        }

        if (choice > 6 || choice < 1)
        {
            printf("Invalid input. Please enter a number from 1-6\n");
        }

        printf("\n");
        menu(); //display menu
        printf("Enter your choice (1-6):");
        scanf("%d", &choice);

    }

   return 0;
}

void menu()
{
    printf("Menu\n1. Display board\n2. Load board from a file\n3. Edit list\n4. Edit board\n5. Save board to a file\n6. Quit\n");
}

int isEmpty(ListPtr sPtr)
{
    return sPtr == NULL;
}

void initializeBoard(ListPtr *startPtr)
{
    //create first list
    ListPtr currentlist = (List *)malloc(sizeof(List));
    currentlist->firstItem = (Item *)malloc(sizeof(Item));
    strcpy(currentlist->listName, "Nick");
    strcpy(currentlist->firstItem->itemName, "3070 RTX");
    currentlist->nextPtr = NULL;
    ItemPtr currentitem = currentlist->firstItem;
    currentitem->nextPtr = NULL;

    ListPtr listhead = currentlist;

    //create second list
    currentlist->nextPtr = (List *)malloc(sizeof(List));
    currentlist = currentlist->nextPtr;
    currentlist->firstItem = (Item *)malloc(sizeof(Item));
    strcpy(currentlist->listName, "Tim");
    strcpy(currentlist->firstItem->itemName, "Oculus Quest 2");
    currentlist->nextPtr = NULL;
    currentitem = currentlist->firstItem;
    currentitem->nextPtr = NULL;

    //create third list
    currentlist->nextPtr = (List *)malloc(sizeof(List));
    currentlist = currentlist->nextPtr;
    currentlist->firstItem = (Item *)malloc(sizeof(Item));
    strcpy(currentlist->listName, "Dante");
    strcpy(currentlist->firstItem->itemName, "Oculus Quest 1");
    currentlist->firstItem->nextPtr = (Item *)malloc(sizeof(Item));
    currentitem = currentlist->firstItem->nextPtr;
    strcpy(currentitem->itemName, "3070 RTX");
    currentlist->nextPtr = NULL;
    currentitem->nextPtr = NULL;

    //create fourth list
    currentlist->nextPtr = (List *)malloc(sizeof(List));
    currentlist = currentlist->nextPtr;
    currentlist->firstItem = (Item *)malloc(sizeof(Item));
    currentitem = currentlist->firstItem;
    strcpy(currentlist->listName, "Abey");
    strcpy(currentitem->itemName, "Oculus Pro");
    currentlist->firstItem->nextPtr = (Item *)malloc(sizeof(Item));
    currentitem = currentlist->firstItem->nextPtr;
    strcpy(currentitem->itemName, "Oculus Quest 1");
    currentlist->nextPtr = NULL;
    currentitem->nextPtr = NULL;

    *startPtr = listhead;
}

void displayBoard(ListPtr currentlist)
{
    if(isEmpty(currentlist))
    {
        puts("The list is empty.");
    }

    ItemPtr currentitem = currentlist->firstItem;

    while(currentlist != NULL)
    {
        printf("\n%s:\n", currentlist->listName);
        currentitem = currentlist->firstItem;

        while(currentitem != NULL)
        {
            printf("%s\n", currentitem->itemName);
            currentitem = currentitem->nextPtr;
        }

        currentlist = currentlist->nextPtr;
    }

}

int searchList(ListPtr *sPtr, char listName[])
{
    ListPtr currentList = *sPtr;
    int listFound = 1;

    while (currentList != NULL)
    {
        if (strcmp(currentList->listName, listName) == 0)
        {
            listFound = 0;
            break;
        }

        else
        {
            if(currentList->nextPtr != NULL)
            {
                currentList = currentList->nextPtr;
            }
            else
            {
                break;
            }
        }
    }

    return listFound;
}

void editList(ListPtr *sPtr, char listName[])
{
    int choice = 0;
    char itemName[100];

    ListPtr currentPtr = *sPtr;

    //find correct list
    while (currentPtr->nextPtr != NULL && strcmp(currentPtr->listName, listName) != 0) {
        currentPtr = currentPtr->nextPtr; //walk to next node
    }

    printf("\nOptions for list '%s'", listName);
    printf("\n1. Edit an item\n2. Add a new item\n3. Delete an item\n4. Return to main menu\n");
    printf("Enter your option:");
    scanf("%d", &choice);

    while (choice != 4)
    {
        if (choice == 1) //edit an item
        {
            if (currentPtr->firstItem == NULL)
            {
                printf("Item cannot be edited as the list is empty.");
            }
            else {
                puts("Enter the name of the item to edit:");
                fflush(stdin);
                fgets(itemName, 100, stdin); //get name of item
                itemName[strlen(itemName) - 1] = '\0'; //remove trailing newline
                editItem(sPtr, listName, itemName);
            }
        }
        if (choice == 2) //add a new item
        {
            puts("Enter the name of the item to add:");
            fflush(stdin);
            fgets(itemName, 100, stdin); //get name of item
            itemName[strlen(itemName) - 1] = '\0'; //remove trailing newline
            addItem(sPtr, listName, itemName);
        }

        if (choice == 3) //delete an item
        {
            if (currentPtr->firstItem == NULL)
            {
                printf("Item cannot be deleted as the list is empty.");
                return;
            }
            puts("Enter the name of the item to delete:");
            fflush(stdin);
            fgets(itemName, 100, stdin); //get name of item
            itemName[strlen(itemName) - 1] = '\0'; //remove trailing newline
            deleteItem(sPtr, listName, itemName);
        }

        if (choice == 4) //return to menu
        {
            return;
        }

        printf("\nOptions for list '%s'", listName);
        printf("\n1. Edit an item\n2. Add a new item\n3. Delete an item\n4. Return to main menu\n");
        printf("Enter your option:");
        scanf("%d", &choice);
    }
}

void addItem(ListPtr *sPtr, char listName[], char itemName[]) //add item to list
{
    ItemPtr newPtr = (Item *)malloc(sizeof(Item));

    if (newPtr != NULL) //checks if space is available
    {
        strcpy(newPtr->itemName, itemName); //places item name in node
        newPtr->nextPtr = NULL; //next node is null

        ListPtr currentPtr = *sPtr;

        //loop to find the correct list
        while (currentPtr->nextPtr != NULL && strcmp(currentPtr->listName, listName) != 0) {
                currentPtr = currentPtr->nextPtr; //walk to next node
        }

        ItemPtr currentItem = currentPtr->firstItem;

        if (currentItem == NULL)
        {
            currentItem = newPtr;
            currentPtr->firstItem = currentItem;
        }

        else
        {
            //walk to end of items
            while (currentItem->nextPtr != NULL)
            {
                currentItem = currentItem->nextPtr;
            }

            //add to end of list
            currentItem->nextPtr = newPtr;
        }


        displayBoard(*sPtr);
    }

    else
    {
        printf("Item not inserted. No memory available.");
    }
}

void deleteItem(ListPtr *sPtr, char listName[], char itemName[])
{
    ListPtr currentPtr = *sPtr;

    //find correct list
    while (currentPtr->nextPtr != NULL && strcmp(currentPtr->listName, listName) != 0) {
        currentPtr = currentPtr->nextPtr; //walk to next node
    }

    ItemPtr prevItem = currentPtr->firstItem;
    ItemPtr currentItem = prevItem->nextPtr;

    //delete if first item is the correct one
    if (strcmp(prevItem->itemName, itemName) == 0)
    {
        ItemPtr temp = prevItem;
        prevItem = prevItem->nextPtr;
        currentPtr->firstItem = prevItem;
        free(temp);
    }
    else {
        //find correct item
        while (currentItem != NULL && strcmp(currentItem->itemName, itemName) != 0) {
            prevItem = currentItem;
            currentItem = currentItem->nextPtr;
        }

        if (currentItem != NULL) {
            ItemPtr tempPtr = currentItem;
            prevItem->nextPtr = currentItem->nextPtr;
            free(tempPtr);
        }

        else
        {
            printf("\nItem not found\n");
        }
    }

    displayBoard(*sPtr);
}

void editItem(ListPtr *sPtr, char listName[], char itemName[])
{
    char newItemName[100];
    ListPtr currentPtr = *sPtr;

    //find correct list
    while (currentPtr->nextPtr != NULL && strcmp(currentPtr->listName, listName) != 0) {
        currentPtr = currentPtr->nextPtr; //walk to next node
    }

    ItemPtr currentItem = currentPtr->firstItem;

    //find correct item
    while (currentItem != NULL && strcmp(currentItem->itemName, itemName) != 0)
    {
        currentItem = currentItem->nextPtr;
    }

    //change name of item
    if (currentItem != NULL)
    {
        printf("Enter new name of item:");
        fgets(newItemName, 100, stdin);
        newItemName[strlen(newItemName) - 1] = '\0';

        strcpy(currentItem->itemName, newItemName);
    }

    else
    {
        printf("Item could not be found.\n");
    }

    displayBoard(*sPtr);
}

void editBoard(ListPtr *sPtr)
{
    int choice = 0;
    char listName[100];

    printf("\nOptions:\n1. Edit the name of a list\n2. Add a new list\n3. Delete a list\n4. Return to main menu\n");
    printf("Enter your option: ");
    scanf("%d", &choice);

    while (choice != 4)
    {

        if (choice == 1) //edit list name
        {
            printf("Enter name of list to edit: ");
            fflush(stdin);
            fgets(listName, 100, stdin);
            listName[strlen(listName) - 1] = '\0';
            editListName(sPtr, listName);
        }

        if (choice == 2) //add new list
        {
            printf("Enter name of new list: ");
            fflush(stdin);
            fgets(listName, 100, stdin);
            listName[strlen(listName) - 1] = '\0';
            addList(sPtr, listName);
        }

        if (choice == 3) //delete list
        {
            printf("Enter name of list to delete: ");
            fflush(stdin);
            fgets(listName, 100, stdin);
            listName[strlen(listName) - 1] = '\0';
            deleteList(sPtr, listName);
        }

        if (choice == 4) //return to main menu
        {
            return;
        }

        printf("\nOptions:\n1. Edit the name of a list\n2. Add a new list\n3. Delete a list\n4. Return to main menu\n");
        printf("Enter your option: ");
        scanf("%d", &choice);
    }
}

void addList(ListPtr *sPtr, char listName[])
{
    ListPtr newPtr = (List *)malloc(sizeof(List));

    if (newPtr != NULL) //if space is available
    {
        //create new pointer for new list
        strcpy(newPtr->listName, listName);
        newPtr->nextPtr = NULL;
        newPtr->firstItem = NULL;

        ListPtr currentPtr = *sPtr;

        //walk to end of board
        while (currentPtr->nextPtr != NULL)
        {
            currentPtr = currentPtr->nextPtr;
        }

        //last list points to new list
        currentPtr->nextPtr = newPtr;
    }

    else
    {
        printf("List not inserted. No memory available.\n");
    }

    displayBoard(*sPtr);
}

void deleteList(ListPtr *sPtr, char listName[])
{
    ListPtr prevPtr = *sPtr;
    ListPtr currentPtr = prevPtr->nextPtr;

    //delete if first list is a match
    if (strcmp((*sPtr)->listName, listName) == 0) {
        ListPtr temp = *sPtr;
        *sPtr = (*sPtr)->nextPtr;
        free(temp);
    }

    else {
        //find correct list
        while (currentPtr != NULL && strcmp(currentPtr->listName, listName) != 0) {
            prevPtr = currentPtr;
            currentPtr = currentPtr->nextPtr; //walk to next node
        }

        //delete list
        if(currentPtr != NULL)
        {
            ListPtr temp = currentPtr;
            prevPtr->nextPtr = currentPtr->nextPtr;
            free(temp);
        }
    }

    displayBoard(*sPtr);
}

void editListName(ListPtr *sPtr, char listName[])
{
    char newName[100];
    ListPtr currentPtr = *sPtr;

    //find correct list
    while (currentPtr->nextPtr != NULL && strcmp(currentPtr->listName, listName) != 0) {
        currentPtr = currentPtr->nextPtr; //walk to next node
    }

    //change name of list
    if (currentPtr != NULL)
    {
        printf("Enter new name of list:");
        fgets(newName, 100, stdin);
        newName[strlen(newName) - 1] = '\0';

        strcpy(currentPtr->listName, newName);
    }

    else
    {
        printf("\nList could not be found.\n");
    }

    displayBoard(*sPtr);
}

/*
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠘⣶⢤⣤⣤⠤⠤⢤⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣠⣤⣖⣋⠉⠉⢉⣉⢁⣠⠼⠶⠶⠦⢤⣄⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⡠⠞⠉⠀⢀⠩⠉⣃⡴⠞⠋⠁⠀⠀⠀⠀⠀⠈⠑⣦⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣠⡞⢁⠞⠛⠉⢛⠋⣽⠚⠉⢁⣀⣄⡀⠀⠀⠀⠀⠀⠀⠈⠹⡄⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⣠⡎⢹⣧⡏⠀⡴⢊⠏⢠⣿⣧⣀⠀⠀⠀⠈⠳⢦⣤⣀⣀⣀⡀⠀⣹⣤⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠈⠀⠀⡾⢸⡇⡈⠁⡏⠀⠈⢹⡏⠪⡙⠲⠤⡀⠀⠈⢻⣌⠉⢉⡽⡾⢉⣾⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣼⠗⣻⠀⠀⠰⢻⠀⢀⡾⠘⢀⣼⣷⣷⠦⡀⠀⢈⣇⡔⢁⡞⠁⣾⢻⡇⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠴⣎⣡⠠⡟⠀⠀⡀⣸⣧⢟⣤⣶⣿⣿⣿⣿⠁⣿⡆⣼⠛⢦⡾⠀⣼⢃⣼⢣⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⠞⢳⣾⣽⣾⣿⣗⡀⠀⠁⠃⠈⠟⠋⠀⡿⣿⣿⠦⡀⠱⣴⠃⢸⢛⣄⣳⣀⠀⠀⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣴⠷⠞⠛⠉⣿⣿⣹⡟⢻⡄⠀⠀⠀⠀⠀⣰⣇⣭⣿⡄⠹⣦⣹⣤⣯⡞⠁⠉⠋⠀⠀⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢰⣏⣿⣏⠁⢈⣇⡀⠀⠀⠀⠉⠉⢀⣾⠇⡇⢸⣿⣿⣿⠟⠟⠻⢶⣤⡀⠀⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣠⠞⢸⣿⢹⢧⡀⠀⣡⠤⠶⠆⠀⣠⣾⢃⠜⠁⢀⣿⡟⢿⡄⠀⢳⡀⠣⡙⣦⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⢀⡠⠖⠛⣻⠟⢁⣴⣽⠿⠋⠁⠉⠳⢄⣐⢃⣠⣴⠵⠛⢁⣠⣶⣿⡾⠦⣬⣧⡀⠀⣧⠀⠈⢸⣧⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⢀⡰⠟⠋⠉⠙⠻⣶⠟⠉⠀⠀⠀⠀⠀⣀⣴⠿⠟⣓⡿⠷⠶⣭⣿⣿⣛⡛⠒⠦⣬⣭⠳⣾⣄⣀⣾⠋⢧⠀⠀⠀⠀⠀
⣀⡤⢴⣄⡀⠀⠈⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢪⡿⣷⠿⠋⣁⠤⠖⠀⠀⠀⠈⠳⣍⠑⠊⣓⣉⣷⣿⣿⠾⣿⣇⠀⠀⠀⠀⠀⠀
⣥⣀⠈⣿⡙⢦⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⠴⠉⣸⡧⣶⠞⠀⠀⠀⠀⠀⠀⠀⠀⣿⡆⣾⣹⣇⣍⣙⠳⣦⡏⢹⡷⢤⡀⠀⠀⠀
⡣⠋⡀⠘⣧⡀⢳⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣰⡿⠊⠁⠀⠀⢀⠄⠀⠀⠀⠀⡰⢹⣿⠘⣿⠁⠸⣏⠓⢦⣹⡿⣆⠀⢹⡀⠀⠀
⣁⢜⡇⠀⠸⣧⠀⢳⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣰⠋⠀⠀⠀⠀⢐⡟⠀⠀⠀⠀⠸⡁⠈⢿⡅⠘⣧⡄⢹⡄⠀⢻⣄⢻⡆⠘⣷⡀⠀
⠋⢁⣿⡀⠀⠙⣧⡀⢳⡀⠀⠀⠀⠀⠀⠀⠀⠀⣰⡏⠀⠀⠀⣠⠴⠊⠀⠀⠀⠀⠀⣤⡇⠀⡿⣧⢀⢿⣿⣤⣿⣂⣈⣿⣦⣿⣄⠸⠙⢦
⣠⣾⠋⢷⡀⠀⠈⢷⡄⠱⣄⠀⠀⠀⠀⠀⠀⢠⡿⠀⡠⢔⣋⡠⣖⣧⠀⠀⠀⠀⠀⠇⠀⢰⠇⣿⢾⡸⣿⡿⡝⢷⠤⠦⠶⠽⢿⡇⠀⠖
⣿⠃⠀⠈⢳⡀⠀⠀⠙⢦⡘⢷⣄⠀⠀⠀⣠⣿⣴⣿⣭⣭⣷⣍⣩⠒⢮⡀⠀⠀⠀⠠⢸⡟⣿⠋⢸⡇⣞⢷⡷⢾⡷⠶⣶⣤⠺⡄⣴⠟
⣧⠀⠀⠀⠀⠻⣦⡀⠀⠈⠳⣆⡙⢷⣄⣴⢋⣥⠞⠋⢀⡀⠀⠀⠈⠙⢦⡪⢣⡀⣸⠀⢸⣿⠃⠀⣸⡇⠹⡈⣿⡌⢧⠀⠀⢈⠀⢿⡇⠀
⠋⣇⠀⠠⣀⠀⠙⢿⣄⠀⠀⠈⠳⣦⡙⢿⣿⣷⠤⠤⡀⠉⠳⣄⠀⠀⠈⣿⣿⡷⠏⠀⣾⠃⠀⢰⠃⠃⠀⣇⠸⣷⡘⣇⠀⠸⡷⡈⢷⠀
⡄⢹⡄⠂⠌⢱⣶⡾⠛⢀⣤⣄⠀⠈⠛⣦⣈⠛⢤⡀⠀⠀⠀⠘⢦⠀⢱⠘⣿⡿⣄⠀⣿⠀⢠⠃⠀⠀⠀⢄⣼⣿⣧⠹⡄⠀⢧⡘⠘⣇
⣋⡴⠃⣤⡄⠘⣿⣆⣀⣸⣿⣻⣷⠒⠋⠙⣿⠟⠲⠿⣳⡄⠀⠀⢘⣗⣡⣷⡿⣷⡘⣶⡟⠀⢁⠔⠁⠀⣠⣮⡾⠀⣿⡦⠿⢶⣄⢳⣧⠹
⠉⠀⠀⣿⣿⡄⠹⡿⡅⠀⠙⠛⠋⠀⠀⢠⡟⠀⢀⣠⡿⠀⠀⡠⠊⢈⣾⡟⠁⢺⣿⣿⠃⠀⠁⠀⢀⣴⡽⠁⣇⢀⣿⡿⡄⠘⣯⠈⣯⡆
⠀⠀⠀⣻⠻⣹⡀⢻⣿⣶⣾⡆⠀⠀⣰⡟⠀⠀⣸⡿⠁⠀⠈⣀⣴⢋⣬⣤⣴⠿⡗⠁⡠⠊⠀⣠⣿⠋⠀⠀⢙⣾⠇⢿⣷⠀⢸⣆⡼⣡
⠀⠀⢠⡿⡀⣸⠃⠀⣿⡿⠋⠀⠀⣰⣟⠀⢠⣶⣿⠀⢀⣴⠞⠋⠉⠉⠛⠉⢀⣸⠷⠊⠀⣠⣾⠛⠁⠀⠀⢀⣾⠏⠀⠘⣿⣧⠀⢿⣰⡟
⠀⣠⠞⢸⢡⠏⢀⣼⡿⠁⠀⠀⣼⠏⠀⢀⣤⣿⣽⠿⠋⠁⠁⠀⣀⣠⣴⠾⠛⢉⣠⣴⡾⠋⠀⠀⠤⢤⣶⢻⡇⠀⠀⠀⢹⣿⡆⢸⣿⠀
⡀⠚⠛⠉⡁⢠⣾⡿⠁⠀⢀⣾⡿⠂⢀⣸⣿⡏⢆⠀⠀⠈⡛⢹⢁⣾⣧⣶⡿⠛⠋⠉⠀⠀⣠⣤⡿⠛⣡⢿⡀⢀⣀⡀⣞⠙⣿⡋⢹⡀
⠀⠀⠀⢀⣉⣿⠈⠀⠀⣢⣾⡙⠀⢄⣼⠏⣀⣿⣿⣒⣶⣶⠶⡟⠛⠉⠉⠀⠀⣀⣠⡴⠷⡛⣁⣠⡴⠛⠁⣠⢟⣽⣿⣻⡟⣖⣾⣿⠚⠓
 */