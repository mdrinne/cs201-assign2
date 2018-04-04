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
};


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


// extern int
// isLeaf(BSTNODE *temp)
// {
//   BSTNODE *l = getBSTNODEleft(temp);
//   BSTNODE *r = getBSTNODEright(temp);
//   if (!l && !r) {
//     return 1;
//   }
//   else {
//     return 0;
//   }
// }


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
  AVAL *atemp = getBSTNODEvalue(temp);
  if (getHeight(l) - getHeight(r) == 0) {
    clearAVALbalance(atemp);
    return;
  }
  if (getHeight(l) - getHeight(r) == 1) {
    atemp->balance = 1;
    return;
  }
  if (getHeight(l) - getHeight(r) == -1) {
    atemp->balance = -1;
    return;
  }
  return;
}


extern int
getAVALbalance(AVAL *temp)
{
  return temp->balance;
}


extern int
getBalance(BSTNODE *temp)
{
  AVAL *atemp = getBSTNODEvalue(temp);
  return getAVALbalance(atemp);
}


extern void
displayAVAL(void *v, FILE *fp)
{
  AVAL *temp = v;
  temp->display(getAVALvalue(temp), fp);
  if (getAVALfrequency(temp) > 1) {
    fprintf(fp, "[%d]", getAVALfrequency(temp));
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
  int ctemp = ta->freq;
  ta->freq = tb->freq;
  tb->freq = ctemp;

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
  int (*compare)(void *, void *);
  void (*free)(void *);
};


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


extern BSTNODE *
getFavoriteChild(BSTNODE *temp)
{
  if (getBalance(temp) == 1) {
    return getBSTNODEleft(temp);
  }
  else if (getBalance(temp) == -1){
    return getBSTNODEright(temp);
  }
  else {
    return NULL;
  }
}


extern int
checkLinear(BSTNODE *child, BSTNODE *parent, BSTNODE *gparent)
{
  /* check if linear left */
  if (getBSTNODEleft(parent) == child) {
    if (getBSTNODEleft(gparent) == parent) {
      return 1;
    }
    else {
      return 0;
    }
  }
  /*check if linear right */
  // else if (getBSTNODEright(parent) == child) {
  else {
    if (getBSTNODEright(gparent) == parent) {
      return 1;
    }
    else {
      return 0;
    }
  }
}


extern void
rotateRight(BSTNODE *child, BSTNODE *parent)
{
  BSTNODE *childr = getBSTNODEright(child);
  BSTNODE *gparent = getBSTNODEparent(parent);
  if (getBSTNODEleft(gparent) == parent) {
    setBSTNODEleft(gparent, child);
  }
  else {
    setBSTNODEright(gparent, child);
  }
  setBSTNODEparent(child, gparent);
  setBSTNODEright(child, parent);
  setBSTNODEparent(parent, child);
  setBSTNODEleft(parent, childr);
  setBSTNODEparent(childr, parent);
  return;
}


extern void
rotateLeft(BSTNODE *child, BSTNODE *parent)
{
  BSTNODE *childl = getBSTNODEleft(child);
  BSTNODE *gparent = getBSTNODEparent(parent);
  if (getBSTNODEleft(gparent) == parent) {
    setBSTNODEleft(gparent, child);
  }
  else {
    setBSTNODEright(gparent, child);
  }
  setBSTNODEparent(child, gparent);
  setBSTNODEleft(child, parent);
  setBSTNODEparent(parent, child);
  setBSTNODEright(parent, childl);
  setBSTNODEparent(childl, parent);
  return;

}


extern void
rotate(BSTNODE *child, BSTNODE *parent)
{
  if (getBSTNODEleft(parent) == child) {
    rotateRight(child, parent);
  }
  else {
    rotateLeft(child, parent);
  }
  return;
}



extern void
insertionFixup(AVL *a, BSTNODE *curr)
{
  while (1) {
    BSTNODE *sibling = getSibling(curr);
    BSTNODE *parent = getBSTNODEparent(curr);
    if (getBSTroot(a->tree) == curr) {
      return;
    }
    else if (getHeight(sibling) > getHeight(curr)) {
      setAVALbalance(parent);
      return;
    }
    else if (getBalance(parent) == 0) {
      setAVALbalance(parent);
      curr = parent;
    }
    else {
      BSTNODE *y = getFavoriteChild(curr);
      if (y && !checkLinear(y,curr,parent)) {
        rotate(y, curr);
        rotate(y, parent);
        determineAVALheight(curr);
        determineAVALheight(parent);
        determineAVALheight(y);
        setAVALbalance(curr);
        setAVALbalance(parent);
        setAVALbalance(y);
      }
      else {
        rotate(curr, parent);
        determineAVALheight(parent);
        determineAVALheight(curr);
        setAVALbalance(parent);
        setAVALbalance(curr);
      }
      return;
    }
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
    a->size++;
    return;
  }
  else {
    BSTNODE *temp3 = insertBST(a->tree, new);
    a->size++;
    BSTNODE *curr = getBSTNODEparent(temp3);
    while (curr != getBSTroot(a->tree)) {
      determineAVALheight(curr);
      curr = getBSTNODEparent(curr);
    }
    insertionFixup(a, temp3);
    return;
  }
}


extern int
findAVLcount(AVL *a,void *v)
{
  AVAL *temp = newAVAL(a->display, a->compare, a->free, v);
  BSTNODE *find = findBST(a->tree, temp);
  freeAVAL(temp);
  if (find) {
    AVAL *temp2 = getBSTNODEvalue(find);
    int val = getAVALfrequency(temp2);
    return val;
  }
  return 0;
}


extern void *
findAVL(AVL *a,void *v)
{
  AVAL *temp = newAVAL(a->display, a->compare, a->free, v);
  BSTNODE *find = findBST(a->tree, temp);
  freeAVAL(temp);
  if (find) {
    AVAL *temp2 = getBSTNODEvalue(find);
    void *val = getAVALvalue(temp2);
    return val;
  }
  return NULL;
}


extern void *
deleteAVL(AVL *a,void *v)
{

}


extern int
sizeAVL(AVL *a)
{
  return a->size;
}


extern int
duplicatesAVL(AVL *a)
{
  return sizeAVL(a) -sizeBST(a->tree);
}


extern void
statisticsAVL(AVL *a,FILE *fp)
{
  fprintf(fp, "Duplicates: %d\n", duplicatesAVL(a));
  statisticsBST(a->tree, fp);
  return;
}


extern void
displayAVL(AVL *a,FILE *fp)
{
  displayBSTdecorated(a->tree, fp);
  return;
}


extern void
displayAVLdebug(AVL *a,FILE *fp)
{
  displayBST(a->tree, fp);
  return;
}


extern void
freeAVL(AVL *a)
{
  freeBST(a->tree);
  free(a);
  return;
}
