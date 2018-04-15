#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <ctype.h>
#include "bst.h"
#include "string.h"
#include "queue.h"
#include "gst.h"
#include "avl.h"
#include "scanner.h"


extern void avlRead(AVL *tree, int argc, char **argv);
extern void gstRead(GST *tree, int argc, char **argv);
char *cleaner(char *);


int
main(int argc, char **argv)
{
  // static int(*compare)(void *, void *);
  // static void (*display)(void *, FILE *);
  // static void (*release)(void *);


  int type = 0;

  switch (argv[1][1]) {
    case 'v':
      printf("MATHHEW RINNE\n");
      exit(-1);
      break;

    case 'g':
      type = 1;
      break;

    case 'r':
      type = 0;
      break;
  }

  if (type == 0) {
    AVL *atree = newAVL(displaySTRING, compareSTRING, freeSTRING);
    avlRead(atree, argc, argv);
  }
  else {
    GST *gtree = newGST(displaySTRING, compareSTRING, freeSTRING);
    gstRead(gtree, argc, argv);
  }

  return 0;
}


extern void
avlRead(AVL *tree, int argc, char **argv)
{
  FILE *fp = fopen(argv[argc-2], "r");
  int sot = stringPending(fp);
  char *temp;
  if (sot == 0) temp = readToken(fp);
  else temp = readString(fp);
  /*--------clean string--------*/
  temp = cleaner(temp);
  while (!feof(fp)) {
    STRING *temp2 = newSTRING(temp);
    insertAVL(tree, temp2);
    sot = stringPending(fp);
    if (sot == 0) temp = readToken(fp);
    else temp = readString(fp);
    /*--------clean string--------*/
    temp = cleaner(temp);
  }
  fclose(fp);

  FILE *fp2 = fopen(argv[argc-1], "r");
  temp = fgetc(fp2);
  while (!feof(fp2)) {
    switch (temp) {
      case 's':
        displayAVL(tree, stdout);
        break;

      case 'r':
        statisticsAVL(tree, stdout);
        break;

      case 'i':
        int sot = stringPending(fp2);
        if (sot == 0) temp = readToken(fp2);
        else temp = readString(fp2);
        /*--------clean string--------*/
        temp = cleaner(temp);
        STRING *temp3 = newSTRING(temp);
        insertAVL(tree, temp3);
        break;

      case 'd':
        int sot = stringPending(fp2);
        if (sot == 0) temp = readToken(fp2);
        else temp = readString(fp2);
        /*--------clean string--------*/
        temp = cleaner(temp);
        STRING *temp4 = newSTRING(temp);
        deleteAVL(tree, temp4);
        break;

      case 'f':
        int sot = stringPending(fp2);
        if (sot == 0) temp = readToken(fp2);
        else temp = readString(fp2);
        /*--------clean string--------*/
        temp = cleaner(temp);
        STRING *temp5 = newSTRING(temp);
        int freq = findAVLcount(tree,temp5);
        printf("Frequency of ");
        displaySTRING(temp5, stdout);
        printf(": %d\n", freq);
        break;
    }

    skipWhiteSpace(fp2);
    temp = fgetc(fp2);
  }
  fclose(fp2);
  return;
}


extern void
gstRead(GST *tree, int argc, char **argv)
{
  FILE *fp = fopen(argv[argc-2], "r");
  int sot = stringPending(fp);
  char *temp;
  if (sot == 0) temp = readToken(fp);
  else temp = readString(fp);
  /*--------clean string--------*/
  temp = cleaner(temp);
  while (!feof(fp)) {
    STRING *temp2 = newSTRING(temp);
    insertGST(tree, temp2);
    sot = stringPending(fp);
    if (sot == 0) temp = readToken(fp);
    else temp = readString(fp);
    /*--------clean string--------*/
    temp = cleaner(temp);
  }
  fclose(fp);

  FILE *fp2 = fopen(argv[argc-1], "r");
  temp = fgetc(fp2);
  while (!feof(fp2)) {
    switch (temp) {
      case 's':
        displayGST(tree, stdout);
        break;

      case 'r':
        statisticsGST(tree, stdout);
        break;

      case 'i':
        int sot = stringPending(fp2);
        if (sot == 0) temp = readToken(fp2);
        else temp = readString(fp2);
        /*--------clean string--------*/
        temp = cleaner(temp);
        STRING *temp3 = newSTRING(temp);
        insertGST(tree, temp3);
        break;

      case 'd':
        int sot = stringPending(fp2);
        if (sot == 0) temp = readToken(fp2);
        else temp = readString(fp2);
        /*--------clean string--------*/
        temp = cleaner(temp);
        STRING *temp4 = newSTRING(temp);
        deleteGST(tree, temp4);
        break;

      case 'f':
        int sot = stringPending(fp2);
        if (sot == 0) temp = readToken(fp2);
        else temp = readString(fp2);
        /*--------clean string--------*/
        temp = cleaner(temp);
        STRING *temp5 = newSTRING(temp);
        int freq = findGSTcount(tree,temp5);
        printf("Frequency of ");
        displaySTRING(temp5, stdout);
        printf(": %d\n", freq);
        break;
    }

    skipWhiteSpace(fp2);
    temp = fgetc(fp2);
  }
  fclose(fp2);
  return;
}


extern char *
cleaner(char *str)
{
  // int length = strlen(str);
  int source = 0;
  int dest = 0;
  int space = 0;
  while (str[source] != '\0') {
    if (islower(str[source])) {
      space = 0;
      str[dest] = str[source];
      ++dest;
    }
    else if (isalpha(str[source])) {
      space = 0;
      str[dest] = str[source]+32;
      ++dest;
    }
    else if (str[source] == ' ') {
      if (space == 0) {
        space = 1;
        str[dest] = str[source];
        ++dest;
      }
      else continue;
    }
    source++;
  }
  str[dest] = '\0';
  // dest++;
  // char *str2[dest];
  // for (int i=0; i<dest; i++) {
  //   str2[i] = str[i];
  // }
  return str;
}
