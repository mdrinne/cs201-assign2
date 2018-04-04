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
newAVL(void (*d)(void *,FILE *),int (*c)(void *,void *),void (*f)(void *), void *value)
{
  AVAL *new = malloc(sizeof(AVAL));
  assert(new != 0);
  new->value     = value;
  new->freq      = 1;
  new->height    = 0;
  new->display   = d;
  new->compare   = c;
  new->free      = f;
  return new;
}


extern void *
getAVALvalue(AVAL *temp)
{
  return temp->value;
}


extern int
getAVALfrequency(AVAL *temp)
{
  return temp->freq;
}


extern int
getAVALheight(AVAL *temp)
{
  return temp->height;
}


extern void
displayAVAL(void *v, FILE *fp)
{

}


extern int
compareAVAL(void *v, void *w)
{
  AVAL *temp  = v;
  AVAL *temp2 = w;
  return temp->compare(getAVALvalue(temp),getAVALvalue(temp2));
}


extern void
swapperAVAL(BSTNODE *a,BSTNODE *b)
{
  AVAL *ta = getBSTNODEvalue(a);
  AVAL *tb = getBSTNODEvalue(b);

  /* swap the values stored in the AVL value objects */
  void *vtemp = ta->value;
  ta->value = tb->value;
  tb->value = vtemp;

  /* swap the counts stored in the AVL value objects */
  int ctemp = ta->count;
  ta->count = tb->count;
  tb->count = ctemp;

  return;
}


extern void
freeAVAL(void *v)
{
  free(v);
  return;
}


extern void
freeAVALwhole(void *v)
{
  AVAL *temp = v;
  if (temp->free) {
    temp->free(getAVALvalue(temp));
    freeAVAL(temp);
  }
  return;
}


extern void
incrAVALfrequency(AVAL *temp)
{
  temp->freq++;
  return;
}


extern void
decrAVALfrequency(AVAL *temp)
{
  temp->freq--;
  return;
}


extern void
setAVALheight(AVAL *temp, int h)
{
  temp->height = h;
  return;
}


extern void
incrAVALheight(AVAL *temp)
{
  temp->height++;
  return;
}

extern void
decrAVALheight(AVAL *temp)
{
  temp->height--;
  return;
}


struct avl
{
  BST *tree;
  int size;
  void (*display)(void *, FILE *);
  void (*compare)(void *, void *);
  void (*free)(void *);
}


extern AVL *
newAVL(void (*d)(void *,FILE *),int (*c)(void *,void *),void (*f)(void *))
{
  AVL *a = malloc(sizeof(AVL));
  assert(a != 0);
  a->tree = newBST(displayAVAL,compareAVAL,swapperAVAL,freeAVALwhole);
  a->size = 0;
  a->display    = d;
  a->compare    = c;
  a->free       = f;
  return a;
}


extern void
insertAVL(AVL *,void *)
{
  AVAL
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
