#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "bst.h"
#include "queue.h"
#include "gst.h"


struct gval
{
  void *value;
  int freq;
  void (*display)(void *, FILE *);
  int (*compare)(void *, void *);
  void (*free)(void *);
};


extern GVAL *
newGVAL(void (*d)(void *,FILE *),int (*c)(void *,void *),void (*f)(void *),void *value)
{
  GVAL *new = malloc(sizeof(GVAL));
  assert(new != 0);
  new->value     = value;
  new->freq      = 1;
  new->display   = d;
  new->compare   = c;
  new->free      = f;
  return new;
}

extern void
displayGVAL(void *v, FILE *fp)
{
  GVAL *temp = v;
  temp->display(temp->value, fp);
  if (temp->freq > 1) {
    fprintf(fp, "[%d]", temp->freq);
  }
  return;
}


extern int
compareGVAL(void *v, void *w)
{
  GVAL *temp = v;
  GVAL *temp2 = w;
  return temp->compare(temp->value,temp2->value);
}


extern void
freeGVAL(void *v)
{
  GVAL *temp = v;
  if (temp->free) {
    temp->free(temp->value);
    free(temp);
  }
}


struct gst
{
  BST *tree;
  QUEUE *nodes;
  int size;
  void (*display)(void *, FILE *);
  int (*compare)(void *, void *);
  void (*free)(void *);
};


extern GST *
newGST(void (*d)(void *,FILE *),int (*c)(void *,void *),void (*f)(void *))
{
  GST *g = malloc(sizeof(GST));
  assert(g != 0);
  g->tree       = newBST(displayGVAL,compareGVAL,NULL,freeGVAL);
  // g->root       = 0;
  g->nodes      = newQUEUE(d,f);
  g->size       = 0;
  g->display    = d;
  g->compare    = c;
  g->free       = f;
  return g;
}


extern void
insertGST(GST *g,void *value)
{
  GVAL *new = newGVAL(g->display, g->compare, g->free, value);
  assert(new != 0);
  if (sizeGST(g) == 0) {
    insertBST(g->tree, new);
    g->size++;
    return;
  }

  BSTNODE *temp = findBST(g->tree, new);
  if (temp) {
    freeGVAL(new);
    GVAL *temp2 = getBSTNODEvalue(temp);
    temp2->freq++;
    g->size++;
    return;
  }
  else {
    insertBST(g->tree, new);
    g->size++;
    return;
  }
}


extern int
findGSTcount(GST *g,void *v)
{
  GVAL *temp = newGVAL(g->display, g->compare, g->free, v);
  BSTNODE *find = findBST(g->tree, temp);
  if (find) {
    GVAL *temp2 = getBSTNODEvalue(find);
    int val = temp2->freq;
    freeGVAL(temp);
    return val;
  }
  return 0;
}


extern void *
findGST(GST *g,void *v)

{
  GVAL *temp = newGVAL(g->display, g->compare, g->free, v);
  BSTNODE *find = findBST(g->tree, temp);
  freeGVAL(temp);
  if (find) {
    GVAL *temp2 = getBSTNODEvalue(find);
    void *val = temp2->value;
    return val;
  }
  return NULL;
}


extern void *
deleteGST(GST *g,void *v)
{
  GVAL *temp = newGVAL(g->display, g->compare, g->free, v);
  BSTNODE *find = findBST(g->tree, temp);
  // freeGVAL(temp);
  if (find) {
    GVAL *temp2 = getBSTNODEvalue(find);
    if (temp2->freq > 1) {
      temp2->freq--;
      g->size--;
      return NULL;
    }
    else if (temp2->freq == 1) {
      BSTNODE *delete = swapToLeafBST(g->tree, find);
      pruneLeafBST(g->tree, delete);
      int s = sizeBST(g->tree);
      s--;
      setBSTsize(g->tree, s);
      temp2 = getBSTNODEvalue(delete);
      g->size--;
      return temp2->value;
    }
  }
  return NULL;
}


extern int
sizeGST(GST *g)
{
  return g->size;
}


extern int
duplicates(GST *g)
{
  return sizeGST(g) - sizeBST(g->tree);
}


extern void
statisticsGST(GST *g,FILE *fp)
{
  fprintf(fp, "Duplicates: %d\n", duplicates(g));
  statisticsBST(g->tree, fp);
  return;
}


extern void
displayGST(GST *g,FILE *fp)
{
  displayBSTdecorated(g->tree, fp);
}


extern void
displayGSTdebug(GST *g,FILE *fp)
{
  displayBST(g->tree, fp);
  return;
}


extern void
freeGST(GST *g)
{
  // freeBST(g->tree);
  free(g);
  return;
}
