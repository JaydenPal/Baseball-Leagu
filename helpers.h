#include <unistd.h>
#include "constants.h"
#include "infofuncs.h"
#ifndef helpers
#define helpers

void printToFile(Player* top, FILE* pF, int count){
   Player* cur = top;
   fprintf(pF, "Little League Roster\n");
   fprintf(pF, "Number of players: %d", count);
   while(cur != NULL){
      fprintf(pF, "\n\nPlayer %d:\n", cur->index + 1);
      //display childs info
      fprintf(pF, "Name: %s %s\n", cur->firstName, cur->lastName);
      fprintf(pF, "Date of Birth: %hu\n", cur->birthYear);
      fprintf(pF, "City: %s\n", cur->city);
      fprintf(pF, "Street Name: %s\n", cur->streetName);
      fprintf(pF, "Street Number: %hu\n", cur->streetNum);
      fprintf(pF, "Parent/Guardian Name: %s %s\n", cur->parentFirstName, cur->parentLastName);
      fprintf(pF, "Phone Number: %u\n", cur->phoneNumber);
      switch(cur->phoneType){
         case HOME:
            fprintf(pF, "Phone Type: 1 HOME\n");
            break;
         case WORK:
            fprintf(pF, "Phone Type: 2 WORK\n");
            break;
         case CELL:
            fprintf(pF, "Phone Type: 3 CELL\n");
            break;
         default:
            fprintf(pF, "Phone Type: 4 NONE\n");
            break;
      };
      switch(cur->relationship){
         case MOTHER:
            fprintf(pF, "Relationship: 1 MOTHER");
            break;
         case FATHER:
            fprintf(pF, "Relationship: 2 FATHER");
            break;
         case GRANDMOTHER:
            fprintf(pF, "Relationship: 3 GRANDMOTHER");
            break;
         case GRANDFATHER:
            fprintf(pF, "Relationship: 4 GRANDFATHER");
            break;
         case OTHER:
            fprintf(pF, "Relationship: 5 OTHER");
            break;
         default:
            break;
      };
      cur = cur->next;
   }
   cur = NULL;
}
int loadFile(Player* top, char* rosterName){
   //every fseek call is based on nums of chars between datas
   int numberOfPlayers;
   char buf[255];
   FILE* pF = fopen(rosterName, "r");
   if(pF == NULL){
      printf("\nThe file '%s' does not exist!\nPlease enter new information or restart the program and try again!\n", rosterName);
      return -1;
   }
   //get file size
   fseek(pF, 0L, SEEK_END);
   size_t fileSize = ftell(pF);
   rewind(pF);
   // leave funct if size == 0
   if(fileSize == 0){
      printf("\nThis file does not contain any data!\nPlease enter new information or restart the program and try again!\n");
      return -1;
   }
   fseek(pF, 40, 0);
   int temp = fscanf(pF, "%d", &numberOfPlayers);
   if(temp == -1){
      printf("\nThe orignal format of this file has been altered or there are no players.\nPlease enter new information or restart the program and try again!\n");
      return -1;
   }
   fseek(pF, 12, SEEK_CUR);
   int i;
   Player* curPlayer = top;
   for(i = 0; i < numberOfPlayers; i++){
      if(i > 0){
      curPlayer->next = (Player*)malloc(sizeof(Player));
      curPlayer->next->prev = curPlayer;
      curPlayer = curPlayer->next;
      curPlayer->next = NULL;
      }
      curPlayer->index = i; //assign index
      //read first name
      memset(buf, 0, sizeof(buf));
      fseek(pF, 6, SEEK_CUR);
      fscanf(pF, "%s ", buf);
      curPlayer->firstName = (char*)malloc(sizeof(char)*strlen(buffer));
      strcpy(curPlayer->firstName, buf);
      // read last name 
      memset(buf, 0, sizeof(buf));
      fscanf(pF, "%s", buf);
      curPlayer->lastName = (char*)malloc(sizeof(char)*strlen(buffer));
      strcpy(curPlayer->lastName, buf);
      //read YOB
      unsigned short *yearPtr = &curPlayer->birthYear;
      fseek(pF, 15, SEEK_CUR);
      fscanf(pF, "%hu", yearPtr);
      curPlayer -> birthYear = *yearPtr;
      //read city
      memset(buf, 0, sizeof(buf));
      fseek(pF, 7, SEEK_CUR);
      fscanf(pF, "%[^\n]s", buf);
      curPlayer->city = (char*)malloc(sizeof(char)*strlen(buffer));
      strcpy(curPlayer->city, buf);
      //read streetname
      memset(buf, 0, sizeof(buf));
      fseek(pF, 13, SEEK_CUR);
      fscanf(pF, "%[^\n]s", buf);
      curPlayer->streetName = (char*)malloc(sizeof(char)*strlen(buffer));
      strcpy(curPlayer->streetName, buf);
      //read streetnum
      unsigned short *numberPointer = &curPlayer->streetNum;
      fseek(pF, 15, SEEK_CUR);
      fscanf(pF, "%hu", numberPointer);
      curPlayer -> streetNum = *numberPointer;
      //read par first name
      memset(buf, 0, sizeof(buf));
      fseek(pF, 23, SEEK_CUR);
      fscanf(pF, "%s ", buf);
      curPlayer->parentFirstName = (char*)malloc(sizeof(char)*strlen(buffer));
      strcpy(curPlayer->parentFirstName, buf);
      // read par last name 
      memset(buf, 0, sizeof(buf));
      fscanf(pF, "%s", buf);
      curPlayer->parentLastName = (char*)malloc(sizeof(char)*strlen(buffer));
      strcpy(curPlayer->parentLastName, buf);
      //read phone number
      fseek(pF, 15, SEEK_CUR);
      fscanf(pF, "%u", &curPlayer->phoneNumber);
      //read phonetype
      fseek(pF, 13, SEEK_CUR);
      fscanf(pF, "%d", &temp);
      curPlayer->phoneType = temp;
      //read relationship
      fseek(pF, 20, SEEK_CUR); // phone enum ALWAYS 4 chars
      fscanf(pF, "%d", &temp);
      curPlayer->relationship = temp;
      fgets(buffer, BUFFER_SIZE, pF); //go past reltionship string. fgets bc they are not all same # of chars
      //go to next player
      if(i >= 8){
         fseek(pF, 12, SEEK_CUR);
       } else {
         fseek(pF, 11, SEEK_CUR);
       }
   }
   printf("Roster successfully loaded! Displaying uploaded roster...\n");
   sleep(2);
   fclose(pF);
   curPlayer = NULL;
   pF = NULL;
   return numberOfPlayers;
}
#endif