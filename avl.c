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
  int lefth;
  int righth;
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
  new->lefth       = -1;
  new->righth      = -1;
  new->display     = d;
  new->compare     = c;
  new->free        = f;
  return new;
}


/*---------public AVAL functions---------*/
extern void *getAVALvalue(AVAL *temp);
extern int   getAVALfrequency(AVAL *temp);
extern int   getAVALheight(AVAL *temp);
extern int   getHeight(BSTNODE *temp);
extern void  setAVALheight(AVAL *temp, int h);
extern void  setHeight(BSTNODE *temp, int h);
extern void  setLeftHeight(BSTNODE *temp, int lh);
extern int   getLeftHeight(AVAL *temp);
extern void  setRightHeight(BSTNODE *temp, int rh);
extern int   getRightHeigth(AVAL *temp);
extern int   getAVALbalance(AVAL *temp);
extern int   getBalance(BSTNODE *temp);
extern int   getMax(int a, int b);
extern void  setBalance(BSTNODE *temp);
extern void  incrAVALfrequency(AVAL *temp);
extern void  decrAVALfrequency(AVAL *temp);
extern void  displayAVAL(void *v, FILE *fp);
extern int   compareAVAL(void *v, void *w);
extern void  swapperAVAL(BSTNODE *a, BSTNODE *b);
extern void  freeAVAL(void *v);
extern void  freeAVALwhole(void *v);
/*---------------------------------------*/


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


/*---------public AVL functions---------*/
extern BSTNODE *getSibling(BSTNODE *temp);
extern BSTNODE *getFavoriteChild(BSTNODE *temp);
extern int      checkLinear(BSTNODE *child, BSTNODE *parent, BSTNODE *gparent);
extern void     rotateRight(AVL *a, BSTNODE *child, BSTNODE *parent);
extern void     rotateLeft(AVL *a, BSTNODE *child, BSTNODE *parent);
extern void     rotate(AVL *a, BSTNODE *child, BSTNODE *parent);
extern void     insertionFixup(AVL *a, BSTNODE *curr);
extern void     deleteFixup(AVL *a, BSTNODE *curr);
/*--------------------------------------*/


extern void *getAVALvalue(AVAL *temp)
{
  return temp->value;
}


extern int getAVALfrequency(AVAL *temp)
{
  return temp->freq;
}


extern int getAVALheight(AVAL *temp)
{
  if (!temp) return -1;
  else return temp->height;
}


extern int getHeight(BSTNODE *temp)
{
  if (!temp) return -1;
  else return getAVALheight(getBSTNODEvalue(temp));
}


extern void setAVALheight(AVAL *temp, int h)
{
  temp->height = h;
  return;
}


extern void setHeight(BSTNODE *temp, int h)
{
  return setAVALheight(getBSTNODEvalue(temp), h);
}


extern void setLeftHeight(BSTNODE *temp, int lh)
{
  AVAL *temp2 = getBSTNODEvalue(temp);
  temp2->lefth = lh;
  return;
}


extern int getLeftHeight(AVAL *temp)
{
  return temp->lefth;
}


extern void setRightHeight(BSTNODE *temp, int rh)
{
  AVAL *temp2 = getBSTNODEvalue(temp);
  temp2->righth = rh;
  return;
}


extern int getRightHeigth(AVAL *temp)
{
  return temp->righth;
}


extern int getAVALbalance(AVAL *temp)
{
  return getLeftHeight(temp) - getRightHeigth(temp);
}


extern int getBalance(BSTNODE *temp)
{
  return getAVALbalance(getBSTNODEvalue(temp));
}


extern int getMax(int a, int b)
{
  if (a > b) return a;
  else return b;
}


extern void setBalance(BSTNODE *temp)
{
  setLeftHeight(temp, getHeight(getBSTNODEleft(temp)));
  setRightHeight(temp, getHeight(getBSTNODEright(temp)));
  AVAL *temp2 = getBSTNODEvalue(temp);
  setHeight(temp, getMax(getLeftHeight(temp2), getRightHeigth(temp2))+1);
  return;
}


extern void incrAVALfrequency(AVAL *temp)
{
  temp->freq++;
  return;
}


extern void decrAVALfrequency(AVAL *temp)
{
  temp->freq--;
  return;
}


extern void  displayAVAL(void *v, FILE *fp)
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


extern int compareAVAL(void *v, void *w)
{
  AVAL *temp  = v;
  AVAL *temp2 = w;
  return temp->compare(getAVALvalue(temp),getAVALvalue(temp2));
}


extern void swapperAVAL(BSTNODE *a, BSTNODE *b)
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


extern void freeAVAL(void *v)
{
  free(v);
  return;
}


extern void freeAVALwhole(void *v)
{
  AVAL *temp = v;
  if (temp->free) temp->free(getAVALvalue(temp));
  freeAVAL(temp);
  return;
}


extern BSTNODE *getSibling(BSTNODE *temp)
{
  BSTNODE *parent = getBSTNODEparent(temp);
  if (parent) {
    if (getBSTNODEleft(parent) == temp) {
      return getBSTNODEright(parent);
    }
    else {
      return getBSTNODEleft(parent);
    }
  }
  else {
    return NULL;
  }
}


extern BSTNODE *getFavoriteChild(BSTNODE *temp)
{
  setBalance(temp);
  if (getBalance(temp) > 1) {
    return getBSTNODEleft(temp);
  }
  else if (getBalance(temp) < -1){
    return getBSTNODEright(temp);
  }
  else {
    return NULL;
  }
}


extern int checkLinear(BSTNODE *child, BSTNODE *parent, BSTNODE *gparent)
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
  else {
    if (getBSTNODEright(gparent) == parent) {
      return 1;
    }
    else {
      return 0;
    }
  }
}


extern void rotateRight(AVL *a, BSTNODE *child, BSTNODE *parent)
{
  setBSTNODEleft(parent, getBSTNODEright(child));
  if (getBSTNODEright(child)) {
    BSTNODE *temp = getBSTNODEright(child);
    setBSTNODEparent(temp, parent);
  }
  BSTNODE *gparent = getBSTNODEparent(parent);
  setBSTNODEparent(child, gparent);
  if (!getBSTNODEparent(parent)) {
    setBSTroot(a->tree, child);
  }
  else if (getBSTNODEleft(gparent) == parent) {
    setBSTNODEleft(gparent, child);
  }
  else {
    setBSTNODEright(gparent, child);
  }
  setBSTNODEright(child, parent);
  setBSTNODEparent(parent, child);
  return;
}


extern void rotateLeft(AVL *a, BSTNODE *child, BSTNODE *parent)
{
  setBSTNODEright(parent, getBSTNODEleft(child));
  if (getBSTNODEleft(child)) {
    BSTNODE *temp = getBSTNODEleft(child);
    setBSTNODEparent(temp, parent);
  }
  BSTNODE *gparent = getBSTNODEparent(parent);
  setBSTNODEparent(child, gparent);
  if (!getBSTNODEparent(parent)) {
    setBSTroot(a->tree, child);
  }
  else if (getBSTNODEleft(gparent) == parent) {
    setBSTNODEleft(gparent, child);
  }
  else {
    setBSTNODEright(gparent, child);
  }
  setBSTNODEleft(child, parent);
  setBSTNODEparent(parent, child);
  return;
}


extern void rotate(AVL *a, BSTNODE *child, BSTNODE *parent)
{
  if (getBSTNODEleft(parent) == child) rotateRight(a, child, parent);
  else rotateLeft(a, child, parent);
  return;
}


extern void insertionFixup(AVL *a, BSTNODE *curr)
{
  while (curr) {
    BSTNODE *sibling = getSibling(curr);
    BSTNODE *parent = getBSTNODEparent(curr);
    if (curr == getBSTroot(a->tree)) {
      // printf("AT ROOT\n");
      return;
    }
    else if (sibling == getFavoriteChild(parent)) {
      // printf("favors sibling\n");
      setBalance(parent);
      return;
    }
    else if (getFavoriteChild(parent) == NULL) {
      // printf("parent has no favorite\n");
      setBalance(parent);
      curr = getBSTNODEparent(curr);
    }
    else {
      // printf("else\n");
      BSTNODE *y = getFavoriteChild(curr);
      if (y && (checkLinear(y,curr,parent) == 0)) {
        rotate(a, y, curr);
        rotate(a, y, parent);
        setBalance(curr);
        setBalance(parent);
        setBalance(y);
      }
      else {
        rotate(a, curr, parent);
        setBalance(parent);
        setBalance(curr);
      }
      return;
    }
  }
}


extern void deleteFixup(AVL *a, BSTNODE *curr)
{
  setHeight(curr, 0);
  while (curr) {
    BSTNODE *parent = getBSTNODEparent(curr);
    if (curr == getBSTroot(a->tree)) {
      return;
    }
    else if (curr == getFavoriteChild(parent)) {
      setBalance(parent);
      curr = parent;
    }
    else if (getFavoriteChild(parent) == NULL) {
      setBalance(parent);
      return;
    }
    else {
      BSTNODE *sibling = getSibling(curr);
      BSTNODE *y = getFavoriteChild(sibling);
      if (y && (checkLinear(y, sibling, parent) == 0)) {
        rotate(a, y, sibling);
        rotate(a, y, parent);
        setBalance(parent);
        setBalance(sibling);
        setBalance(y);
        curr = y;
      }
      else {
        rotate(a, sibling, parent);
        setBalance(parent);
        setBalance(sibling);
        if (!y) {
          return;
        }
        curr = sibling;
      }
    }
  }
}

extern void insertAVL(AVL *a,void *value)
{
  AVAL *new = newAVAL(a->display, a->compare, a->free, value);
  // printf("inserting ");
  // a->display(value, stdout);
  // printf("\n");
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
    // printf("new node was inserted: ");
    // a->display(getAVALvalue(getBSTNODEvalue(temp3)), stdout);
    // printf("\n");
    insertionFixup(a, temp3);
    return;
  }
}


extern int findAVLcount(AVL *a,void *value)
{
  AVAL *temp = newAVAL(a->display, a->compare, a->free, value);
  BSTNODE *find = findBST(a->tree, temp);
  freeAVAL(temp);
  if (find) return getAVALfrequency(getBSTNODEvalue(find));
  else return 0;
}


extern void *findAVL(AVL *a,void *value)
{
  AVAL *temp = newAVAL(a->display, a->compare, a->free, value);
  BSTNODE *find = findBST(a->tree, temp);
  freeAVAL(temp);
  if (find) return value;
  else return NULL;
}


extern void *deleteAVL(AVL *a,void *value)
{
  AVAL *temp = newAVAL(a->display, a->compare, a->free, value);
  BSTNODE *find = findBST(a->tree, temp);
  freeAVAL(temp);
  if (find) {
    AVAL *temp2 = getBSTNODEvalue(find);
    if (getAVALfrequency(temp2) > 1) {
      decrAVALfrequency(temp2);
      a->size--;
      return NULL;
    }
    else if (getAVALfrequency(temp2) == 1) {
      BSTNODE *delete = swapToLeafBST(a->tree, find);
      // deleteFixup(a, delete);
      pruneLeafBST(a->tree, delete);
      int s = sizeBST(a->tree);
      s--;
      setBSTsize(a->tree, s);
      deleteFixup(a, delete);
      temp2 = getBSTNODEvalue(delete);
      void *val = getAVALvalue(temp2);
      freeBSTNODE(delete, a->free);
      a->size--;
      return val;
    }
  }
  else {
    fprintf(stdout, "Value ");
    a->display(value, stdout);
    fprintf(stdout, " not found.\n");
    return NULL;
  }
  return NULL;
}


extern int sizeAVL(AVL *a)
{
  return a->size;
}


extern int duplicatesAVL(AVL *a)
{
  return sizeAVL(a) - sizeBST(a->tree);
}


extern void statisticsAVL(AVL *a,FILE *fp)
{
  fprintf(fp, "Duplicates: %d\n", duplicatesAVL(a));
  statisticsBST(a->tree, fp);
  return;
}


extern void displayAVL(AVL *a,FILE *fp)
{
  if (sizeAVL(a) == 0) printf("EMPTY\n");
  else displayBSTdecorated(a->tree, fp);
  return;
}


extern void displayAVLdebug(AVL *a,FILE *fp)
{
  if (sizeAVL(a) == 0) printf("EMPTY\n");
  else displayBST(a->tree, fp);
  return;
}


extern void freeAVL(AVL *a)
{
  freeBST(a->tree);
  free(a);
  return;
}
