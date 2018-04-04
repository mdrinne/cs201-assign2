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
  int balance;
  void (*display)(void *, FILE *);
  int (*compare)(void *, void *);
  void (*free)(void *);
}


extern AVAL *
newAVAL(void (*d)(void *,FILE *),int (*c)(void *,void *),void (*f)(void *), void *value)
{
  AVAL *new = malloc(sizeof(AVAL));
  assert(new != 0);
  new->value       = value;
  new->freq        = 1;
  new->height      = 0;
  new->balance     = 0;
  new->display     = d;
  new->compare     = c;
  new->free        = f;
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
  if (!temp) {
    return -1;
  }
  return temp->height;
}


extern void
setAVALheight(AVAL*temp, int h)
{
  temp->height = h;
  return;
}


extern int
getHeight(BSTNODE *temp)
{
  AVAL *temp2 = getBSTNODEvalue(temp);
  if (!temp2) {
    return -1;
  }
  return getAVALheight(temp2);
}


extern void
determineAVALheight(BSTNODE *temp)
{
  BSTNODE *left = getBSTNODEleft(temp);
  BSTNODE *right = getBSTNODEright(temp);
  if (!left && !right) {
    setAVALheight(getBSTNODEvalue(temp), 0);
    return;
  }
  else if (!right) {
    setAVALheight(getBSTNODEvalue(temp), getHeight(left)+1);
    return;
  }
  else if (!left) {
    setAVALheight(getBSTNODEvalue(temp), getHeight(right)+1);
    return;
  }
  else {
    int l = getHeight(left)+1;
    int r = getHeight(right)+1;
    if (r > l) {
      setAVALheight(getBSTNODEvalue(temp), r);
    }
    else {
      setAVALheight(getBSTNODEvalue(temp), l);
    }
  }
}


extern BSTNODE *
getSibling(BSTNODE *temp)
{
  BSTNODE *parent = getBSTNODEparent(temp);
  if (getBSTNODEleft(parent) == temp) {
    return getBSTNODEright(parent);
  }
  else {
    return getBSTNODEleft(parent);
  }
}


extern int
isLeaf(BSTNODE *temp)
{
  BSTNODE *l = getBSTNODEleft(temp);
  BSTNODE *r = getBSTNODEright(temp);
  if (!l && !r) {
    return 1;
  }
  else {
    return 0;
  }
}


extern void
clearAVALbalance(AVAL *temp)
{
  temp->balance = 0;
  return;
}


extern void
setAVALbalance(BSTNODE *temp)
{
  BSTNODE *l = getBSTNODEleft(temp);
  BSTNODE *r = getBSTNODEright(temp);
  // AVAL *al = getBSTNODEvalue(l);
  // AVAL *ar = getBSTNODEvalue(r);
  if ((getHeight(l) == getHeight(r)) {
    clearAVALbalance(temp);
    return;
  }
  if (getHeight(l) > getHeight(r)) {

  }
  // AVAL *atemp = getBSTNODEvalue(temp);
  // if (isLeaf(temp)) {
  //   atemp->balance = 0;
  //   return;
  // }
  // if (!sibling) {
  //   atemp->balance = 1;
  // }
  // AVAL *asib = getBSTNODEvalue(sibling);
  // if (getAVALheight(atemp) > getAVALheight(asib)) {
  //   atemp->balance = 1;
  //   return;
  // }
  // else if (getAVALheight(atemp) < getAVALheight(asib)) {
  //   atemp->balance = -1;
  //   return;
  // }
  // else {
  //   atemp->balance = 0;
  // }
}


extern int
getAVALbalance(BSTNODE *temp)
{
  AVAL *atemp = getBSTNODEvalue(temp);
  return atemp->balance;
}


extern void
displayAVAL(void *v, FILE *fp)
{
  AVAL *temp = v;
  temp->display(getAVALvalue(temp), fp);
  if (getGVALfrequency(temp) > 1) {
    fprintf(fp, "[%d]", getAVALfrequency(temp));
  }
  if (isLeaf(temp)) {
    return;
  }
  if (getAVALbalance(temp) == 1) {
    fprintf(fp, "+");
  }
  if (getAVALbalance(temp) == -1) {
    fprintf(fp, "-");
  }
  return;
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
insertionFixup(AVL *a, BSTNODE *curr)
{
  while (1) {
    BSTNODE *sibling = getSibling(curr);
    AVAL *sib = getBSTNODEvalue(sibling);
    if (getBSTroot(a->tree) == curr) {
      return;
    }
    else if (getAVALbalance(sib) == 1) {
      clearAVALbalance(sib);
      return;
    }
    else if (!sibling) {
      setAVALbalance(curr);
      curr = getBSTNODEparent(curr);
    }
    else
  }
}


extern void
insertAVL(AVL *a,void *value)
{
  AVAL *new = newAVAL(a->display, a->compare, a->free, value);
  assert(new != 0);
  if (sizeAVL(a) == 0) {
    insertBST(a->tree, new);
    a->size++;
    return;
  }

  BSTNODE *temp = findBST(a->tree, new);
  if (temp) {
    freeAVAL(new);
    AVAL *temp2 = getBSTNODEvalue(temp);
    incrAVALfrequency(temp2);
    g->size++;
    return;
  }
  else {
    BSTNODE *temp3 = insertBST(a->tree, new);
    g->size++;
    determineAVALheight(getbstnodep(temp3));
    insertionFixup(a, temp3);
    return;
  }
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
