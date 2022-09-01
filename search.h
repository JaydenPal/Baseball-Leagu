#include "playernode.h"
#include <string.h>
#include <stdlib.h>
#ifndef search
#define search

Player* findMiddleNode(Player* firstNode, Player* lastNode){       //had to tweak function for binary search to be able to find the middle between any two nodes in list. if whole list pass NULL ptr to lastNode
   //establish runners to find mid of list
   Player* slowRunner = firstNode;
   Player* fastRunner = firstNode->next;  //top->next so when list size is 1 -> node is returned
   if(slowRunner->next == fastRunner){  //if first/last are contiguous return slow or loop will segfault going beyond scope of list
      return slowRunner;
   }
   //find mid of list w runners (when fast is at end of list-> slow will be in middle)
   while(fastRunner != lastNode && fastRunner->next != lastNode){ // 
      slowRunner = slowRunner->next;
      fastRunner = fastRunner->next->next; 
   }
   return slowRunner;
}
int compareBirthYear(unsigned short y1, unsigned short y2){
   if(y1 > y2){
      return -1;
   } else if(y1 < y2){
      return 1;
   }
   return 0; //years are equal
}
int compareIndex(int i1, int i2){
   if(i1 < i2){    //comparisons are opposite of birth years to get least to greatest
      return -1;
   } else if(i1 > i2){
      return 1;
   }
   return 0; //indices are equal
}
Player* merge(Player* head1, Player* head2, int cmptType){
   Player* newHead = (Player*)malloc(sizeof(Player));  //doesnt work without malloc not sure why ASK PROF next class!!!
   Player* cur = (Player*)malloc(sizeof(Player));
   cur = newHead;
   while(head1 != NULL && head2 != NULL){
      int cmpResult;
      switch(cmptType){
         case 0: 
                  cmpResult = strcasecmp((head1->lastName), head2->lastName);
                  break;
         case 1: 
                  cmpResult = compareBirthYear(head1->birthYear, head2->birthYear);
                  break;
         case 2: 
                  cmpResult = compareIndex(head1->index, head2->index);
                  break;
      }
      if(cmpResult < 0 || cmpResult == 0){ //if they are equal just take left
         cur->next = head1;
         head1 = head1->next;
         cur = cur->next;
      } else {
        cur->next = head2;
        head2 = head2->next;
        cur = cur->next;
      }
   }
   //add remaining nodes from either left or right (whichever isnt NULL)
   while(head1 != NULL) {
        cur->next = head1;
        head1 = head1->next;
        cur = cur->next;
    }
    while(head2 != NULL) {
        cur->next = head2;
        head2 = head2->next;
        cur = cur->next;
    }
   return newHead->next;
}
Player* mergeSort(Player* head, int cmptType){
   //break if top of list is only node or is NULL
   if(head->next == NULL){ 
      return head;
   }
   Player* head2 = (Player*)malloc(sizeof(Player)); //doesnt work without malloc not sure why ASK PROF next class!!!
   Player* mid = (Player*)malloc(sizeof(Player));
   mid = findMiddleNode(head, NULL);
   head2 = mid->next;
   mid->next = NULL;
   Player* headToReturn = merge(mergeSort(head, cmptType), mergeSort(head2, cmptType), cmptType);
   return headToReturn;
}
Player* searchByLastName(Player* head, char* name){ //binary search
   if(strcasecmp(head->lastName, name) == 0){ //if head is result return without binary search (best case)
         return head;
   }
   Player* firstNode = head;
   Player* lastNode = NULL;
   Player* mid = findMiddleNode(firstNode, lastNode);
   while(lastNode == NULL || lastNode != firstNode){
      int cmpResult = strcasecmp(mid->lastName, name);  //only cmp strings once instead of three seprate times
      if(cmpResult == 0){
         return mid;
      }
      if(cmpResult > 0){
         if(mid == firstNode) break;
         lastNode = mid;
         mid = findMiddleNode(firstNode, lastNode); //finds middle of lefthalf
      } else {
         if(!mid->next) break;   //PREVENTS SEG FAULT IF VALUE NOT IN LIST (when only one value left)
         firstNode = mid->next; //mid has already been checked
         mid = findMiddleNode(firstNode, lastNode); //finds middle of right half
      }
   }
   return NULL; //name not found in list
}
#endif