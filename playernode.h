#include <ctype.h>
#ifndef playernodes
#define playernodes
enum phoneTypes {HOME = 1, WORK = 2, CELL = 3};
enum relationships {MOTHER = 1, FATHER = 2, GRANDMOTHER = 3, GRANDFATHER = 4, OTHER = 5};

struct __Player_node {
    int index;
    char* firstName;
    size_t firstNameLen;
    char* lastName;
    size_t lastNameLen;
    unsigned short birthYear;
    unsigned short streetNum;
    char* streetName;
    size_t streetNameLen;
    char* city;
    size_t cityLen;
    char* parentFirstName;
    size_t parentFirstNameLen;
    char* parentLastName;
    size_t parentLastNameLen;
    unsigned int phoneNumber;
    enum phoneTypes phoneType;
    enum relationships relationship;
    struct __Player_node* next; 
    struct __Player_node* prev; 
} typedef Player;

#endif