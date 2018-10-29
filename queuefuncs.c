/*
 * Source file that contains the functions
 * responsible for manipulating the values
 * and pointers stored in a queue structure
 */

#include "mopsolver.h"
#include "structures.h"

node pop( queue* q ){
   node first = *q->first;
   if( q->first == q->last )
      q->last = q->first->next;
   q->first = q->first->next;
   return first;
}

int enqueue( queue* q, node *n ){
   *q->last = *n;
   q->last->next->prev = q->last;
   q->last = q->last->next;
   return 0;
}

int isEmpty( queue* q ){
   return q->first->next == NULL;
}

node* makeNode( point *p, node* n ){
   node *newNode = malloc(sizeof(node));
   newNode->loc = p;
   newNode->distance = n->distance + 1;
   newNode->next = malloc(sizeof(node));
   //newNode->next->prev = newNode;
   newNode->prev = n;

   return newNode;
}

int visited( queue *q, point *p ){
   node * curr = q->root;
   if( p->row == 0 && p->col == 0 )
      return 1;
   while(curr->loc){
      if(curr->loc->col == p->col && curr->loc->row == p->row)
        return 1;
      else
        curr = curr->next;
   }
   return 0;
}
