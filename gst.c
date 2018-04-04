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


extern void *
getGVALvalue(GVAL *temp)
{
    return temp->value;
}


extern int
getGVALfrequency(GVAL *temp)
{
  return temp->freq;
}

extern void
displayGVAL(void *v, FILE *fp)
{
  GVAL *temp = v;
  temp->display(getGVALvalue(temp), fp);
  if (getGVALfrequency(temp) > 1) {
    fprintf(fp, "[%d]", getGVALfrequency(temp));
  }
  return;
}


extern int
compareGVAL(void *v, void *w)
{
  GVAL *temp = v;
  GVAL *temp2 = w;
  return temp->compare(getGVALvalue(temp),getGVALvalue(temp2));
}

extern void
freeGVAL(void *v)
{
  free(v);
  return;
}


extern void
freeGVALwhole(void *v)
{
  GVAL *temp = v;
  if (temp->free) {
    temp->free(getGVALvalue(temp));
    freeGVAL(temp);
  }
  return;
}


extern void
incrGVALfrequency(GVAL *temp)
{
  temp->freq++;
  return;
}


extern void
decrGVALfrequency(GVAL *temp)
{
  temp->freq--;
  return;
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
  g->tree       = newBST(displayGVAL,compareGVAL,NULL,freeGVALwhole);
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
    incrGVALfrequency(temp2);
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
    int val = getGVALfrequency(temp2);
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
    void *val = getGVALvalue(temp2);
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
    if (getGVALfrequency(temp2) > 1) {
      decrGVALfrequency(temp2);
      g->size--;
      return NULL;
    }
    else if (getGVALfrequency(temp2) == 1) {
      BSTNODE *delete = swapToLeafBST(g->tree, find);
      pruneLeafBST(g->tree, delete);
      int s = sizeBST(g->tree);
      s--;
      setBSTsize(g->tree, s);
      temp2 = getBSTNODEvalue(delete);
      g->size--;
      return getGVALvalue(temp2);
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
