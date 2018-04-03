#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "bst.h"
#include "queue.h"
#include "avl.h"


struct aval
{
  void *value;
  int freq;
  int height;
  void (*display)(void *, FILE *);
  int (*compare)(void *, void *);
  void (*free)(void *);
}


extern AVL *
newAVL(void (*)(void *,FILE *),int (*)(void *,void *),void (*)(void *))
{

}


extern void
insertAVL(AVL *,void *)
{

}


extern int
findAVLcount(AVL *,void *)
{

}


extern void *
findAVL(AVL *,void *)
{

}


extern void *
deleteAVL(AVL *,void *)
{

}


extern int
sizeAVL(AVL *)
{

}


extern int
duplicatesAVL(AVL *)
{

}


extern void
statisticsAVL(AVL *,FILE *)
{

}


extern void
displayAVL(AVL *,FILE *)
{

}


extern void
displayAVLdebug(AVL *,FILE *)
{

}


extern void
freeAVL(AVL *)
{

}
