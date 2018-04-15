#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include "bst.h"
#include "string.h"
#include "queue.h"
#include "gst.h"
#include "avl.h"
#include "scanner.h"


extern void avlRead(AVL *tree, int argc, char **argv);
extern void gstRead(GST *tree, int argc, char **argv);
char *readStringClean(FILE *fp);
char *readTokenClean(FILE *fp);


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
  if (sot == 0) temp = readTokenClean(fp);
  else temp = readStringClean(fp);
  while (!feof(fp)) {
    STRING *temp2 = newSTRING(temp);
    insertAVL(tree, temp2);
    sot = stringPending(fp);
    if (sot == 0) temp = readTokenClean(fp);
    else temp = readStringClean(fp);
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
        if (sot == 0) temp = readTokenClean(fp2);
        else temp = readStringClean(fp2);
        STRING *temp2 = newSTRING(temp);
        insertAVL(tree, temp2);
        break;

      case 'd':
        int sot = stringPending(fp2);
        if (sot == 0) temp = readTokenClean(fp2);
        else temp = readStringClean(fp2);
        STRING *temp2 = newSTRING(temp);
        deleteAVL(tree, temp2);
        break;

      case 'f':
        int sot = stringPending(fp2);
        if (sot == 0) temp = readTokenClean(fp2);
        else temp = readStringClean(fp2);
        STRING *temp2 = newSTRING(temp);
        int freq = findAVLcount(temp2);
        printf("Frequency of ");
        displaySTRING(temp2, stdout);
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
  if (sot == 0) temp = readTokenClean(fp);
  else temp = readStringClean(fp);
  while (!feof(fp)) {
    STRING *temp2 = newSTRING(temp);
    insertGST(tree, temp2);
    sot = stringPending(fp);
    if (sot == 0) temp = readTokenClean(fp);
    else temp = readStringClean(fp);
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
        if (sot == 0) temp = readTokenClean(fp2);
        else temp = readStringClean(fp2);
        STRING *temp2 = newSTRING(temp);
        insertGST(tree, temp2);
        break;

      case 'd':
        int sot = stringPending(fp2);
        if (sot == 0) temp = readTokenClean(fp2);
        else temp = readStringClean(fp2);
        STRING *temp2 = newSTRING(temp);
        deleteGST(tree, temp2);
        break;

      case 'f':
        int sot = stringPending(fp2);
        if (sot == 0) temp = readTokenClean(fp2);
        else temp = readStringClean(fp2);
        STRING *temp2 = newSTRING(temp);
        int freq = findGSTcount(temp2);
        printf("Frequency of ");
        displaySTRING(temp2, stdout);
        printf(": %d\n", freq);
        break;
    }

    skipWhiteSpace(fp2);
    temp = fgetc(fp2);
  }
  fclose(fp2);
  return;
}


char *
readStringClean(FILE *fp)
{
  int ch,index;
  char *buffer;
  int size = 512;

  /* advance to the double quote */

  skipWhiteSpace(fp);

  if (feof(fp)) return 0;

  ch = fgetc(fp);

  if (ch == EOF) return 0;

  /* allocate the buffer */

  buffer = allocateMsg(size,"readString");

  if (ch != '\"')
      {
      fprintf(stderr,"SCAN ERROR: attempt to read a string failed\n");
      fprintf(stderr,"first character was <%c>\n",ch);
      exit(4);
      }

  /* toss the double quote, skip to the next character */

  ch = fgetc(fp);

  /* initialize the buffer index */

  index = 0;

  /* collect characters until the closing double quote */

  while (ch != '\"') {
    int space = 0;
    if (ch == EOF) {
      fprintf(stderr,"SCAN ERROR: attempt to read a string failed\n");
      fprintf(stderr,"no closing double quote\n");
      exit(6);
    }
    if (index > size - 2) {
      ++size;
      buffer = reallocateMsg(buffer,size,"readString");
    }

    if (ch == '\\') {
      ch = fgetc(fp);
      if (ch == EOF) {
        fprintf(stderr,"SCAN ERROR: attempt to read a string failed\n");
        fprintf(stderr,"escaped character missing\n");
        exit(6);
      }
      buffer[index] = convertEscapedChar(ch);
      ++index;
      ch = fgetc(fp);
    }
    else {
      if ((ch >= 97 && ch <= 122) || ch == 32) {
        if (space == 1 && ch == 32) {
          ch = fgetc(fp);
        }
        else if (space == 0 && ch == 32) {
          space = 1;
          buffer[index] = ch;
          ++index;
          ch = fgetc(fp);
        }
        else {
          space = 0;
          buffer[index] = ch;
          ++index;
          ch = fgetc(fp);
        }
      }
      else if (ch >= 65 && ch <= 90) {
        ch = ch + 32;
        buffer[index] = ch;
        ++index;
        ch = fgetc(fp);
      }
      else {
        ch = fgetc(fp);
      }
    }
  }

  buffer[index] = '\0';

  return buffer;
}


char *
readTokenClean(FILE *fp)
{
  int ch,index;
  char *buffer;
  int size = 80;

  skipWhiteSpace(fp);

  ch = fgetc(fp);
  if (ch == EOF) return 0;

  buffer = allocateMsg(size,"readToken");

  index = 0;
  while (!isspace(ch)) {
    if (ch == EOF) break;
    if (index > size - 2) {
      ++size;
      buffer = reallocateMsg(buffer,size,"readToken");
    }
    if (ch >= 97 && ch <= 122) {
      buffer[index] = ch;
      ++index;
      ch = fgetc(fp);
    }
    else {
      ch = fgetc(fp);
    }
  }

  /* push back the character that got us out of this loop */

  ungetc(ch,fp);

  if (index > 0)              //there is something in the buffer
      clearerr(fp);           //so force the read to be good

  buffer[index] = '\0';

  return buffer;
}
