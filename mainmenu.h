#ifndef mainmenu
#define mainmenu
#include "helpers.h"
#include "rosterinfo.h"
#include "constants.h"
#include <string.h>
#include "search.h"

int loadTeamOption(Player* top, rosterInfo* roster){
    Player* curPlayer = top;
    int result;
    do{
        clearBuffer();
        clean_stdin();
        printf("Enter your team name (spaces are okay): ");
        scanf("%[^\n]s", buffer);
        roster->rosterNameLen = strlen(buffer) + 4; // 4 is len of '.txt'
        roster->rosterName = (char*)malloc(sizeof(char)*(roster->rosterNameLen));
        strcpy(roster->rosterName, buffer);
        strcat(roster->rosterName, ".txt");
        int i;
        for(i = 0; i < roster->rosterNameLen ; i++){
            if(roster->rosterName[i] == 32){
                roster->rosterName[i] = '-';
            }
            roster->rosterName[i] = tolower(roster->rosterName[i]);
        }
        result = loadFile(curPlayer, roster->rosterName);
        if(result == -1) continue;
        printToFile(curPlayer, stdout, result);
        roster->loadedRoster = true;
        }while(roster->loadedRoster != true);
    return result;
}
int addPlayers(Player* playerIn, int count){
    clean_stdin(); // only have to use this function on fox idk why
    Player* curPlayer = playerIn;
    char* choice = (char*)malloc(sizeof(char));
    char* infoCorrect = (char*)malloc(sizeof(char));
    char prompt[255];
    do{
      count++;
      curPlayer->index = count - 1; //assign index
      //get child last and first name
      memset(prompt, 0, sizeof(prompt));
      strcpy(prompt, "Enter your first name: ");
      getName(curPlayer, MAX_NAME_LEN, prompt, FIRST_NAME); //see function declaration for memory allocation
      memset(prompt, 0, sizeof(prompt));
      strcpy(prompt, "Enter your last name: ");
      getName(curPlayer, MAX_NAME_LEN, prompt, LAST_NAME); //see function declaration for memory allocation
      //retrieve birthyear
      memset(prompt, 0, sizeof(prompt));
      strcpy(prompt, "Enter your birth year: ");
      retrieveShort(curPlayer, MIN_YEAR, MAX_YEAR, prompt, BIRTH_YEAR);
      //retrieve address info
      memset(prompt, 0, sizeof(prompt));
      strcpy(prompt, "Enter the name of the city you were born: ");
      getName(curPlayer, MAX_CITY_LEN, prompt, CITY_NAME);
      //street
      memset(prompt, 0, sizeof(prompt));
      strcpy(prompt, "Enter the name of your street: ");
      getName(curPlayer, MAX_CITY_LEN, prompt, STREET_NAME);
      //street num
      memset(prompt, 0, sizeof(prompt));
      strcpy(prompt, "Enter your street number: ");
      retrieveShort(curPlayer, 1, USHRT_MAX, prompt, STREET_NUM);
      //Parent info
      memset(prompt, 0, sizeof(prompt));
      strcpy(prompt, "Enter the first name of your parent/gaurdian: ");
      getName(curPlayer, MAX_NAME_LEN, prompt, PAR_FIRST_NAME);
      memset(prompt, 0, sizeof(prompt));
      strcpy(prompt, "Enter the last name of your parent/gaurdian: ");
      getName(curPlayer, MAX_NAME_LEN, prompt, PAR_LAST_NAME);
      //get phone #
      getPhoneNumber(curPlayer);
      //get reltionship and phone type
      getPhoneType(curPlayer);
      getRelationship(curPlayer);
      //check if user info is correct
      printToFile(curPlayer, stdout, count);
      strcpy(prompt, "Is this information correct?(y/n)");
      getChoice(infoCorrect, prompt);
      //if no allow user to re enter info
      if(*infoCorrect == 'n'){
         printf("\nPlease re-enter your information.\n");
         count--;
         continue;
      } else  printf("\nThe information is correct!\n");
      if(count == MAX_PLAYERS){
        printf("\nYou have reached the maximum number of players. Displaying your summary...\n");
        break;
      }
      if(count >= MIN_PLAYERS){
        strcpy(prompt, "Would you like to enter more information?(y/n)");
        getChoice(choice, prompt);
        if(*choice == 'n'){
            curPlayer->next = NULL;
            break;
        } 
      }
      curPlayer->next = (Player*)malloc(sizeof(Player)); 
      curPlayer->next->prev = curPlayer;
      curPlayer = curPlayer->next;
      curPlayer->next = NULL;
    }while(*choice != 'n' && count < MAX_PLAYERS);
    free(choice);
    free(infoCorrect);
    infoCorrect = NULL;
    choice = NULL;
    curPlayer = NULL;
    return count;
}
void saveTeam(Player* top, rosterInfo* roster, int count){
    int i;
    clearBuffer();
    bool validRosterName;
    if(roster->loadedRoster != true){
        do{
        clean_stdin();
        printf("Enter a roster name (spaces are okay): ");
        clearBuffer();
        scanf("%[^\n]s", buffer);
        strcat(buffer, ".txt");
        roster->rosterNameLen = strlen(buffer);
        roster->rosterName = (char*)malloc(sizeof(char)*roster->rosterNameLen);
        strcpy(roster->rosterName, buffer);
        for(i = 0; i < roster->rosterNameLen; i++){
            if(roster->rosterName[i] == 32){
                roster->rosterName[i] = '-';
            }
            roster->rosterName[i] = tolower(roster->rosterName[i]);
        }
        FILE* tempFile = fopen(roster->rosterName, "r");
        if(tempFile != NULL){
            printf("\nThere already exists a team with this name. Please enter a different name.\n");
            free(roster->rosterName);
            validRosterName = false;
            continue;
        } else {
            tempFile = NULL;
            validRosterName = true;
        }
        }while(validRosterName != true);
        int numOfChars = strlen(roster->rosterName) - 4; //4 is length of ".txt"
        FILE* teams = fopen("teams.txt", "r");
        if(teams == NULL){
            teams = fopen("teams.txt", "w");
            fprintf(teams, "teams:");
        }
        fclose(teams);
        teams = NULL;
        teams = fopen("teams.txt", "a+");
        // while(fgets(buffer, sizeof(buffer), teams) != NULL){
        // clearBuffer();
        // }
        fprintf(teams,"\n%.*s", numOfChars, roster->rosterName);
        fclose(teams);
        teams = NULL;
        }
        FILE* newRoster = fopen(roster->rosterName, "w");
        printToFile(top, newRoster, count);
        fclose(newRoster);
        printf("Your roster has been saved to \"%s\"",roster->rosterName);
        newRoster = NULL;
}
void displayPlayers(Player* top, int count){
    unsigned short displaySelection;
    bool validDisplay;
    printf("\nDisplay Original Order(1)");
    printf("\nDisplay Sorted by Last Name(2)");
    printf("\nDisplay Sorted by Age(3)");
    printf("\nEnter selection: ");
    do{
    scanf("%hu", &displaySelection);
    getc(stdin); //flush leftover new line char
    switch(displaySelection){
        case 1:
            printToFile(top, stdout, count);
            validDisplay = true;
            break;
        case 2:
            top = mergeSort(top, SORT_BY_LAST);
            printToFile(top, stdout, count);
            top = mergeSort(top, SORT_BY_INDEX);
            validDisplay = true;
            break;
        case 3:
            top = mergeSort(top, SORT_BY_AGE);
            printToFile(top, stdout, count);
            top = mergeSort(top, SORT_BY_INDEX);
            validDisplay = true;
            break;
        default:
            printf("\nYou have entered invalid data! Please enter a number from 0-3: ");
            break;
    }
    }while(validDisplay != true);
}
void searchPlayers(Player* top){
    clean_stdin();
    char prompt[255];
    Player* tempPlayer = (Player*)malloc(sizeof(Player));
    strcpy(prompt, "Enter player last name: ");
    getName(tempPlayer, MAX_NAME_LEN, prompt, 1);
    top = mergeSort(top, SORT_BY_LAST);
    Player* returnedNode = searchByLastName(top, tempPlayer->lastName);
    if(returnedNode == NULL){
        printf("\nPlayer not found! Please try again.");
    } else {
    Player* cur = returnedNode;
    printf("\n\nPlayer: %d\n", cur->index + 1);
    //display childs info
    printf("Name: %s %s\n", cur->firstName, cur->lastName);
    printf("City: %s\n", cur->city);
    printf("Date of Birth: %hu", cur->birthYear);
    while(cur->prev != NULL && strcasecmp(cur->prev->lastName, cur->lastName) == 0){
        cur = cur->prev;
        printf("\n\nPlayer: %d\n", cur->index + 1);
        printf("Name: %s %s\n", cur->firstName, cur->lastName);
        printf("City: %s\n", cur->city);
        printf("Date of Birth: %hu", cur->birthYear);
    }
     cur = returnedNode;
    while(cur->next != NULL && strcasecmp(cur->next->lastName, cur->lastName) == 0){
        cur = cur->next;
        printf("\n\nPlayer: %d\n", cur->index + 1);
        printf("Name: %s %s\n", cur->firstName, cur->lastName);
        printf("City: %s\n", cur->city);
        printf("Date of Birth: %hu", cur->birthYear);
    }
    }
    top = mergeSort(top, SORT_BY_INDEX); //revert to original order
    free(tempPlayer);
    tempPlayer = NULL;
    returnedNode = NULL;
};
void displayTeams(){
    FILE* teams;
    printf("\nTeams: \n");
    teams = fopen("teams.txt", "r");
    if(teams == NULL){
        printf("\nThere are no teams to display OR the \"teams.txt\" file has been deleted.");
        return;
    }
    fgets(buffer, sizeof(buffer), teams);
    clearBuffer();
    while(fgets(buffer, sizeof(buffer), teams) != NULL){
        printf("%s", buffer);
        clearBuffer();
    }
    printf("\n");
    fclose(teams);
    teams = NULL;
}
#endif