#ifndef __STRING_INCLUDED__
#define __STRING_INCLUDED__

#include <stdio.h>

typedef struct STRING STRING;

extern STRING *newString(char *);
extern char *getSTRING(STRING *);
extern char *setSTRING(STRING *, char *);
extern void displaySTRING(void *, FILE *);
extern int compareSTRING(void *, void *);
extern int compareSTRINGdecr(void *, void *);
extern void freeSTRING(void *);

#endif
