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
  int bal;
  // int lefth;
  // int righth;
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
  new->bal     = 0;
  // new->lefth       = -1;
  // new->righth      = -1;
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
// extern void  setLeftHeight(BSTNODE *temp, int lh);
// extern int   getLeftHeight(AVAL *temp);
// extern void  setRightHeight(BSTNODE *temp, int rh);
// extern int   getRightHeigth(AVAL *temp);
extern int   getAVALbalance(AVAL *temp);
extern int   getBalance(BSTNODE *temp);
extern int   getMax(int a, int b);
extern void  setHeight(BSTNODE *temp);
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
extern int      checkLinearLeft(BSTNODE *child, BSTNODE *parent, BSTNODE *gparent);
extern int      checkLinearRight(BSTNODE *child, BSTNODE *parent, BSTNODE *gparent);
extern int      checkLinear(BSTNODE *child, BSTNODE *parent, BSTNODE *gparent);
extern void     rotateRight(AVL *a, BSTNODE *y);
extern void     rotateLeft(AVL *a, BSTNODE *y);
extern void     rotate(AVL *a, BSTNODE *y);
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


// extern void setLeftHeight(BSTNODE *temp, int lh)
// {
//   AVAL *temp2 = getBSTNODEvalue(temp);
//   temp2->lefth = lh;
//   return;
// }


// extern int getLeftHeight(AVAL *temp)
// {
//   return temp->lefth;
// }


// extern void setRightHeight(BSTNODE *temp, int rh)
// {
//   AVAL *temp2 = getBSTNODEvalue(temp);
//   temp2->righth = rh;
//   return;
// }


// extern int getRightHeigth(AVAL *temp)
// {
//   return temp->righth;
// }


extern int
getAVALbalance(AVAL *temp)
{
  return temp->bal;
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


extern void
setHeight(BSTNODE *temp)
{
  if (!temp) return;
  BSTNODE *left = getBSTNODEleft(temp);
  BSTNODE *right = getBSTNODEright(temp);
  AVAL *temp2 = getBSTNODEvalue(temp);
  if (!left && !right) temp2->height = 0;
  else if (!left) temp2->height = getHeight(right)+1;
  else if (!right) temp2->height = getHeight(left)+1;
  else temp2->height = getMax(getHeight(left), getHeight(right))+1;
  return;
}


extern void
setBalance(BSTNODE *temp)
{
  BSTNODE *left = getBSTNODEleft(temp);
  BSTNODE *right = getBSTNODEright(temp);
  if (left) setHeight(left);
  if (right) setHeight(right);
  int l = getHeight(left);
  int r = getHeight(right);
  AVAL *temp2 = getBSTNODEvalue(temp);
  temp2->bal = l - r;
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
    if (temp == getBSTNODEleft(parent)) {
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
  // setBalance(temp);
  if (!temp) {
    return NULL;
  }
  else if (getBalance(temp) < 0) {
    return getBSTNODEright(temp);
  }
  else if (getBalance(temp) > 0) {
    return getBSTNODEleft(temp);
  }
  else {
    return NULL;
  }
}


extern int
checkLinearLeft(BSTNODE *child, BSTNODE *parent, BSTNODE *gparent)
{
  return (getBSTNODEleft(gparent) == parent) && (getBSTNODEleft(parent) == child);
}


extern int
checkLinearRight(BSTNODE *child, BSTNODE *parent, BSTNODE *gparent)
{
  return (getBSTNODEright(gparent) == parent) && (getBSTNODEright(parent) == child);
}


extern int checkLinear(BSTNODE *child, BSTNODE *parent, BSTNODE *gparent)
{
  int l = checkLinearLeft(child, parent, gparent);
  int r = checkLinearRight(child, parent, gparent);
  return l || r;
}


extern void rotateRight(AVL *a, BSTNODE *y)
{
  BSTNODE *x = getBSTNODEparent(y);
  BSTNODE *yright = getBSTNODEright(y);
  BSTNODE *xparent = getBSTNODEparent(x);
  setBSTNODEleft(x, yright);
  if (yright) {
    setBSTNODEparent(yright, x);
  }
  setBSTNODEparent(y, xparent);
  if (!xparent) {
    setBSTroot(a->tree, y);
  }
  else if (x == getBSTNODEright(xparent)) {
    setBSTNODEright(xparent, y);
  }
  else {
    setBSTNODEleft(xparent, y);
  }
  setBSTNODEright(y, x);
  setBSTNODEparent(x, y);
  setHeight(x);
  setHeight(y);
  return;
}


extern void rotateLeft(AVL *a, BSTNODE *y)
{
  BSTNODE *x = getBSTNODEparent(y);
  BSTNODE *yleft = getBSTNODEleft(y);
  BSTNODE *xparent = getBSTNODEparent(x);
  setBSTNODEright(x, yleft);
  if (yleft) {
    setBSTNODEparent(yleft, x);
  }
  setBSTNODEparent(y, xparent);
  if (!xparent) {
    setBSTroot(a->tree, y);
  }
  else if (x == getBSTNODEleft(xparent)) {
    setBSTNODEleft(xparent, y);
  }
  else {
    setBSTNODEright(xparent, y);
  }
  setBSTNODEleft(y, x);
  setBSTNODEparent(x, y);
  setHeight(x);
  setHeight(y);
  return;
}


extern void rotate(AVL *a, BSTNODE *x)
{
  BSTNODE *left = getBSTNODEleft(getBSTNODEparent(x));
  if (left && left == x) rotateRight(a, x);
  else rotateLeft(a, x);
  return;
}


extern void insertionFixup(AVL *a, BSTNODE *curr)
{
  while (1) {
    // printf("-------------------------------\n");
    // displayAVL(a, stdout);
    // printf("^^^^^^^^^^BEGINNING OF WHILE^^^^^^^^^^\n");
    // printf("\n");
    BSTNODE *sibling = getSibling(curr);
    BSTNODE *parent = getBSTNODEparent(curr);
    // if (parent) {
    //   printf("PARENT BALANCE IS: %d\n", getBalance(parent));
    // }
    BSTNODE *fav = getFavoriteChild(parent);
    if (curr == getBSTroot(a->tree)) {
      // setHeight(curr);
      // setBalance(curr);
      // printf("^^^^^^^^REACHED ROOT^^^^^^^^\n\n\n\n");
      return;
    }
    else if (fav && sibling == fav) {
      // printf("^^^^^^^^^^^^^^^SIBLING IS FAVORITE CHILD^^^^^^^^^^^^^^\n");
      // if (!sibling) {
      //   printf("SIBLING IS NULL\n");
      // }
      // printf("\n\n\n");
      // setHeight(curr);
      setBalance(parent);
      return;
    }
    else if (!fav) {
      // printf("^^^^^^^^NO FAVORITE CHILD^^^^^^^^\n\n\n\n");
      // setHeight(curr);
      setBalance(parent);
      curr = getBSTNODEparent(curr);
    }
    else {
      BSTNODE *y = getFavoriteChild(curr);
      if (y && (checkLinear(y,curr,parent) == 0)) {
        // printf("^^^^^^^^DOUBLE ROTATION^^^^^^^^\n\n");
        rotate(a, y);
        // displayAVL(a, stdout);
        // printf("^^^^^^^^FIRST ROTATION COMPLETE^^^^^^^^\n\n");
        rotate(a, y);
        // displayAVL(a, stdout);
        // printf("^^^^^^^^SECOND ROTATION COMPLETE^^^^^^^^\n\n\n\n");
        // setHeight(curr);
        setBalance(curr);
        setBalance(parent);
        setBalance(y);
      }
      else {
        // printf("^^^^^^^^SINGLE ROTATION^^^^^^^^\n\n");
        rotate(a, curr);
        // displayAVL(a, stdout);
        // printf("^^^^^^^^SINGLE ROTAION COMPLETE^^^^^^^^\n\n\n\n");
        setBalance(parent);
        setBalance(curr);
      }
      return;
    }
  }
}


extern void deleteFixup(AVL *a, BSTNODE *curr)
{
  while (curr) {
    // printf("-------------------------------");
    // displayAVL(a, stdout);
    // // printf("-------------------------------");
    // printf("\n\n");
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
        rotate(a, y);
        rotate(a, y);
        setBalance(parent);
        setBalance(sibling);
        setBalance(y);
        curr = y;
      }
      else {
        rotate(a, sibling);
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
  // printf("\n\n");
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
    BSTNODE *temp2 = insertBST(a->tree, new);
    a->size++;
    insertionFixup(a, temp2);

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
