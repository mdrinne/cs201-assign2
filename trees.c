//  CS201 Assign2 trees.c
//  Matthew Rinne
//  This file reads in data and implements a gst or avl tree accordingly
//  April 2018

#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <ctype.h>
#include "bst.h"
#include "string.h"
#include "sll.h"
#include "queue.h"
#include "gst.h"
#include "avl.h"
#include "scanner.h"


extern void avlRead(AVL *tree, int argc, char **argv);
extern void gstRead(GST *tree, int argc, char **argv);
extern void cleanToken(char *);
extern void cleanString(char *);
static void skipWhiteSpace(FILE *fp);


int
main(int argc, char **argv)
{

  int type = 0;

  char c = argv[1][1];
  switch (c) {
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
  if (sot == 0) {
    temp = readToken(fp);
    if (temp) cleanToken(temp);
  }
  else {
    temp = readString(fp);
    if (temp) cleanString(temp);
  }
  while (!feof(fp)) {
    STRING *temp2 = newSTRING(temp);
    if (isalpha(temp[0])) insertAVL(tree, temp2);
    sot = stringPending(fp);
    if (sot == 0) {
      temp = readToken(fp);
      if (temp) cleanToken(temp);
    }
    else {
      temp = readString(fp);
      if (temp) cleanString(temp);
    }
  }
  fclose(fp);

  FILE *fp2 = fopen(argv[argc-1], "r");
  char c = fgetc(fp2);
  while (!feof(fp2)) {
    switch (c) {
      case 's':
        displayAVL(tree, stdout);
        break;

      case 'r':
        statisticsAVL(tree, stdout);
        break;

      case 'i':
        sot = stringPending(fp2);
        if (sot == 0) {
          temp = readToken(fp);
          if (temp) cleanToken(temp);
        }
        else {
          temp = readString(fp);
          if (temp) cleanString(temp);
        }
        STRING *temp3 = newSTRING(temp);
        if (isalpha(temp[0])) insertAVL(tree, temp3);
        break;

      case 'd':
        sot = stringPending(fp2);
        if (sot == 0) {
          temp = readToken(fp);
          if (temp) cleanToken(temp);
        }
        else {
          temp = readString(fp);
          if (temp) cleanString(temp);
        }
        STRING *temp4 = newSTRING(temp);
        void *del = findAVL(tree, temp4);
        if (del == NULL && isalpha(temp[0])) {
          printf("Value ");
          displaySTRING(temp4, stdout);
          printf(" not found.\n");
        }
        else if (isalpha(temp[0])) deleteAVL(tree, temp4);
        break;

      case 'f':
        sot = stringPending(fp2);
        if (sot == 0) {
          temp = readToken(fp);
          if (temp) cleanToken(temp);
        }
        else {
          temp = readString(fp);
          if (temp) cleanString(temp);
        }
        STRING *temp5 = newSTRING(temp);
        int freq = findAVLcount(tree,temp5);
        printf("Frequency of ");
        displaySTRING(temp5, stdout);
        printf(": %d\n", freq);
        break;
    }

    skipWhiteSpace(fp2);
    c = fgetc(fp2);
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
  if (sot == 0) {
    temp = readToken(fp);
    if (temp) cleanToken(temp);
  }
  else {
    temp = readString(fp);
    if (temp) cleanString(temp);
  }
  while (!feof(fp)) {
    STRING *temp2 = newSTRING(temp);
    if (isalpha(temp[0])) insertGST(tree, temp2);
    sot = stringPending(fp);
    if (sot == 0) {
      temp = readToken(fp);
      if (temp) cleanToken(temp);
    }
    else {
      temp = readString(fp);
      if (temp) cleanString(temp);
    }
  }
  fclose(fp);

  FILE *fp2 = fopen(argv[argc-1], "r");
  char c = fgetc(fp2);
  while (!feof(fp2)) {
    switch (c) {
      case 's':
        displayGST(tree, stdout);
        break;

      case 'r':
        statisticsGST(tree, stdout);
        break;

      case 'i':
        sot = stringPending(fp2);
        if (sot == 0) {
          temp = readToken(fp);
          if (temp) cleanToken(temp);
        }
        else {
          temp = readString(fp);
          if (temp) cleanString(temp);
        }
        STRING *temp3 = newSTRING(temp);
        if (isalpha(temp[0])) insertGST(tree, temp3);
        break;

      case 'd':
        sot = stringPending(fp2);
        if (sot == 0) {
          temp = readToken(fp);
          if (temp) cleanToken(temp);
        }
        else {
          temp = readString(fp);
          if (temp) cleanString(temp);
        }
        STRING *temp4 = newSTRING(temp);
        void *del = findGST(tree, temp4);
        if (del == NULL && isalpha(temp[0])) {
          printf("Value ");
          displaySTRING(temp4, stdout);
          printf(" not found.\n");
        }
        else if (isalpha(temp[0])) deleteGST(tree, temp4);
        break;

      case 'f':
        sot = stringPending(fp2);
        if (sot == 0) {
          temp = readToken(fp);
          if (temp) cleanToken(temp);
        }
        else {
          temp = readString(fp);
          if (temp) cleanString(temp);
        }
        STRING *temp5 = newSTRING(temp);
        // int freq'
        // if (isalpha(temp[0])) {
        int freq = findGSTcount(tree,temp5);
        // }
        printf("Frequency of ");
        displaySTRING(temp5, stdout);
        printf(": %d\n", freq);
        break;
    }

    skipWhiteSpace(fp2);
    c = fgetc(fp2);
  }
  fclose(fp2);
  return;
}


static void
skipWhiteSpace(FILE *fp)
{
  int ch;
  while ((ch = fgetc(fp)) != EOF && isspace(ch))
    continue;
  if (ch != EOF) ungetc(ch,fp);
}


void cleanToken(char *str) {
  int size = strlen(str);
  int pos = 0;
  for (int i=0; i<size; i++) {
    if (isalpha(str[i])) {
      if (isupper(str[i])) {
        str[pos] = str[i] + 32;
      }
      else {
        str[pos] = str[i];
      }
      pos ++;
    }
    else continue;
  }
  str[pos] = '\0';
  return;
}

void cleanString(char *str) {
  int size = strlen(str);
  int pos = 0;
  int space = 0;
  for (int i=0; i<size; i++) {
    if (str[i] == 32) {
      if (space != 0) {
        space = 0;
        str[pos] = str[i];
        pos ++;
      }
      else continue;
    }
    else if (isalpha(str[i])) {
      if (isupper(str[i])) {
        str[pos] = str[i] + 32;
      }
      else {
        str[pos] = str[i];
      }
      space = 1;
      pos ++;
    }
    else continue;
  }

  if (isspace(str[pos-1])) {
    str[pos-1] = '\0';
  }
  else {
    str[pos] = '\0';
  }
  return;
}


// extern void
// cleanToken(char *str)
// {
//   int size = strlen(str);
//   int dest = 0;
//   for (int i=0; i<size; i++) {
//     if (isalpha(str[i])) {
//       if (isupper(str[i])) {
//         str[dest] = str[i]+32;
//         ++dest;
//       }
//       else {
//         str[dest] = str[i];
//         ++dest;
//       }
//     }
//   }
//   str[dest] = '\0';
//   return;
// }
//
// extern void
// cleanString(char *str)
// {
//   int size = strlen(str);
//   int dest = 0;
//   int space = 0;
//   for (int i=0; i<size; i++) {
//     if (str[i] == 32) {
//       if (space == 0) {
//         space = 1;
//         str[dest] = str[i];
//         dest++;
//       }
//       else continue;
//     }
//     else if (isalpha(str[i])) {
//       if (isupper(str[i])) {
//         str[dest] = str[i] + 32;
//       }
//       else {
//         str[dest] = str[i];
//       }
//     }
//     else continue;
//   }
//
//   if (isspace(str[dest-1])) {
//     str[dest-1] = '\0';
//   }
//   else {
//     str[dest] = '\0';
//   }
//   return;
// }
