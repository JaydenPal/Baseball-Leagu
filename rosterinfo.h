#include <ctype.h>
#include <stdio.h>
#include <stdbool.h>
#ifndef rosterinfo
#define rosterinfo

struct __ROSTER_INFO {
    char* rosterName;
    size_t rosterNameLen;
    bool loadedRoster;
} typedef rosterInfo;

#endif