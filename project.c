#include "rosterinfo.h"
#include "infofuncs.h"
#include "mainmenu.h"
#include "playernode.h"
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <stdbool.h>

Player* top;
rosterInfo* roster;
int count = 0;
bool changesMade;

int main(){
    top = (Player*)malloc(sizeof(Player));
    top->prev = NULL;
    top->next = NULL;
    roster = (rosterInfo*)malloc(sizeof(rosterInfo));
    Player* cur;
    cur = top;
    
    char choice = 'y';
    do{
    printf("\n\n(0) Close program");
    if(roster->loadedRoster != true && count == 0) printf("\n(1) Load Team");
    if(count != MAX_PLAYERS) printf("\n(2) Add Players");
    printf("\n(3) Display Teams"); 
    if(count > 0) printf("\n(4) Display Players");
    if(count > 0) printf("\n(5) Search Team");
    if(changesMade == true) printf("\n(6) Save Team");   
    printf("\nEnter selection: ");

    unsigned short menuSelection;
    scanf("%hu", &menuSelection);
    

    switch(menuSelection){
        // getc(stdin); //flush leftover new line char
        case 0:
            //close prgrm
            choice = 'n';
            break;
        case 1: 
            //load team
            count = loadTeamOption(cur, roster);
            while(cur->next != NULL){
                cur = cur->next;
            }
            break;
        case 2: 
            //Add players
            if(count == MAX_PLAYERS){
                printf("\nYou can not add any more players. This team already contains the max number of players for a roster.\n");
                break;
            }
            if(cur != NULL && cur != top){
                cur->next = (Player*)malloc(sizeof(Player));
                cur = cur->next;
            }
            count = addPlayers(cur, count);
            if(count == MAX_PLAYERS){
                sleep(2);
                printToFile(top, stdout, count);
            }
            changesMade = true;
            break;
        case 3:
            //display team names
            displayTeams();
            break;
        case 4:
            //display players
            if(count == 0){
                printf("\nNo players to display. Please add players or load a team.\n");
                break;
            }
            displayPlayers(top, count);
            break;
        case 5: 
            //search team
            if(count == 0){
                printf("\nNo team to search. Please add players or load a team.\n");
                break;
            }
            searchPlayers(top);
            break;
        case 6: 
            // Save team
            if(changesMade != true){
                printf("\nNo changes to save. Please add players and try again.\n");
                break;
            }
            saveTeam(top, roster, count);
            changesMade = false;
            break;
        default: 
            printf("\nYou have entered invalid data! Please enter a number from 0-5: ");
            continue;
    };
}while(choice != 'n');
//destroy roster
cur = top;
Player* temp;
while(cur != NULL){
    temp = cur;
    cur = cur->next;
    free(temp->city);
    free(temp->firstName);
    free(temp->lastName);
    free(temp->parentFirstName);
    free(temp->parentLastName);
    free(temp->streetName);
    free(temp);
}
temp = NULL;
cur = NULL;
top = NULL;
free(roster);
roster = NULL;
}