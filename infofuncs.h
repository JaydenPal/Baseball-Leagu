#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include "playernode.h"
#include "constants.h"
#ifndef infofuncs
#define infofuncs

char buffer[BUFFER_SIZE];
void clean_stdin()
{
    int c;
    do {
        c = getchar();                  //Flushes input buffer by getting characters remaining in buffer
    } while (c != '\n' && c != EOF);    //Flushes until new line is reached, flushing the \n char as well, 
}   

void clearBuffer(){
   memset(buffer, 0, sizeof(buffer));
}

int checkString(char buffer[], int MAX_LEN){
   if(strlen(buffer) > MAX_LEN){
            printf("That name is too long! Please enter a name no longer than %d characters.\n", MAX_LEN);
            clean_stdin(); // prevents error if user inputs string > MAXlength WITH spaces when asking for input again
            return strlen(buffer) - MAX_LEN;
         } else if(strlen(buffer) == 0){
               clean_stdin();
               printf("Value cannot be empty. Please try again.\n");
               return -1;
            } else {
            clean_stdin();
            return 0;
         }
         return -1;
}

char getChoice(char *value, char prompt[]){
   bool isDataValid;
      do{
      printf("\n%s", prompt);
      scanf(" %c", value);
      clean_stdin();
      //validate choice
      if(*value == 'n' || *value == 'y'){
         isDataValid =true;
      }  else {
         printf("\nPlease enter \'y\' for yes and \'n\' for no.");
         isDataValid = false;
         continue;
      }
      }while(isDataValid == false);
      return *value;
}

void getName(Player* p, int MAX_LEN, char prompt[], int nameType){
    bool isDataValid;
   do{
         // retrieve name
         printf("%s", prompt);
         clearBuffer();             //clear buffer before asking for input each time function is called
         scanf("%[^\n]s", buffer);
         //validate name
         int temp = checkString(buffer, MAX_LEN);
         if(temp == 0){
            isDataValid = true;
         } else{
            isDataValid = false;
         }
      } while(isDataValid == false);
      switch(nameType){
         case 0:
            p->firstName = (char*)malloc(sizeof(char)*strlen(buffer));
            strcpy(p->firstName, buffer);
            p->firstNameLen = strlen(buffer);
            break;
         case 1: 
            p->lastName = (char*)malloc(sizeof(char)*strlen(buffer));
            strcpy(p->lastName, buffer);
            p->lastNameLen = strlen(buffer);
            break;
         case 2:
            p->city = (char*)malloc(sizeof(char)*strlen(buffer));
            strcpy(p->city, buffer);
            p->cityLen = strlen(buffer);
            break;
         case 3:
            p->parentFirstName = (char*)malloc(sizeof(char)*strlen(buffer));
            strcpy(p->parentFirstName, buffer);
            p->parentFirstNameLen = strlen(buffer);
            break;
         case 4: 
            p->parentLastName = (char*)malloc(sizeof(char)*strlen(buffer));
            strcpy(p->parentLastName, buffer);
            p->parentLastNameLen = strlen(buffer);
            break;
         case 5:
            p->streetName = (char*)malloc(sizeof(char)*strlen(buffer));
            strcpy(p->streetName, buffer);
            p->streetNameLen = strlen(buffer);
            break;
      }

}


void retrieveShort(Player* p, int min, int max, char prompt[], int shortType){
   bool isDataValid;
   unsigned short value;
   do{
         //retrieve value(month day or year)
         int temp;
         printf("%s", prompt);
         temp = scanf("%hu", &value);
         clean_stdin();
         //validate value
         if(temp == 1 && value <=max && value >= min){
            isDataValid = true;
         } else {
            printf("You have entered invalid data! Please enter a value between %d-%d.\n", min, max);
            isDataValid = false;
            continue;
         }
      }while(isDataValid == false);
      (shortType == 0) ? (p->birthYear = value) : (p->streetNum = value);
}

void getPhoneNumber(Player* p){
   unsigned int* phoneNum;
   phoneNum = &p->phoneNumber;
   bool isDataValid;
   do{
      printf("Please enter parent/guardian phone number(only digits): ");
      int temp = scanf("%10u", phoneNum); // first 10 only bc phone numbers are 10 digits
      clean_stdin(); //clean fucntion prevents infinite loop when invalid data is entered by clearing input stream 
      //validate
      if(temp == 1 && *phoneNum >= 1000000000) { //validates data type entered (only chars 0-9) if less than 1, no fields converted meaing no int was entered
         isDataValid = true; 
         }else{
            printf("You have entered invalid data or not enough digits to be a valid number(10)! Please enter a phone number that only contains the digits 0-9.\n"); 
            isDataValid = false;
            continue; 
         }
}while(isDataValid == false);
}

void getRelationship(Player* p){
   //retrieve parent/guardian relationship
   bool valid;
   int temp = 0;
   do{
      printf("\nWhat is your relationship to the child?\nEnter (1) for mother; (2) for father; (3) for grandmother; (4) for grandfather; (5) for other: ");
      scanf("%d", &temp);
      if(temp > 0 && temp <= 5){
         p->relationship = temp;
         valid = true;
      } else {
         printf("\nPlease enter a number between 1-5.\n");
         clean_stdin();
         valid = false;
         continue;
      }
   }while(valid != true);
   valid = false;
}
void getPhoneType(Player* p){
   //retrieve parent/guardian relationship
   bool valid;
   int temp = 0;
   do{
      printf("\nWhat type of phone number was entered?\nEnter (1) for home; (2) for work; (3) for cell: ");
      scanf("%d", &temp);
      if(temp > 0 && temp <= 3){
         p->phoneType = temp;
         valid = true;
      } else {
         printf("\nPlease enter a number between 1-3.");
         clean_stdin();
         valid = false;
         continue;
      }
   }while(valid != true);
   valid = false;
}
#endif
