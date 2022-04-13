#include "heap.h"
#include <stdlib.h>
#include <stdio.h>

heap heap_create(int k, int (*f)(const void *, const void *)) {
  heap h = malloc(sizeof(*h));
  h->nmax=k;
  h->f = f;
  h->n=0;
  h->array= malloc(sizeof(void*)*k);
  return h;
}

void heap_destroy(heap h) {
  free(h->array);
  free(h);
}

bool heap_empty(heap h) {
  return !h->n;
}

bool heap_add(heap h, void *object) {
  if(h->n+1>h->nmax) return true;
  h->n++;
  h->array[h->n]=object;
  // if(h->n==1) return true;
  int i = h->n;
  while (i>1 && h->f(h->array[i/2],h->array[i])>=0){
    void* tmp = h->array[i/2];
    h->array[i/2] = h->array[i];
    h->array[i] = tmp;
    i = i/2;
  }
  return false;
}

void *heap_top(heap h) {
  if(heap_empty(h)) return NULL;
  return h->array[1];
}

void *heap_pop(heap h) {
  if(heap_empty(h)) return NULL;
  void * save = h->array[1];
  h->array[1] = h->array[h->n];
  h->n--;
  int i = 1;
  while ((2*i<=(h->n) && h->f(h->array[i],h->array[2*i])>=0) || 
         (2*i+1<=(h->n) && h->f(h->array[i],h->array[2*i+1])>=0)){
    if(2*i+1<=(h->n) && h->f(h->array[2*i],h->array[2*i+1])>0 ){
      void* tmp = h->array[2*i+1];
      h->array[2*i+1] = h->array[i];
      h->array[i] = tmp;
      i = i*2+1;
    } else {
      void* tmp = h->array[2*i];
      h->array[2*i] = h->array[i];
      h->array[i] = tmp;
      i = i*2;
    }
  }
  
  return save;
}

