/*
 * Author - Grayson Hassell
 * Source file that contains the functions
 * responsible for manipulating the values
 * and pointers stored in a queue structure
 */

#include "mopsolver.h"
#include "structures.h"

// Iterates the queue first pointer
node pop( queue* q ){
   node first = *q->first;
   if( q->first == q->last )
      q->last = q->first->next;
   q->first = q->first->next;
   return first;
}

// Places the new node data at the end of the queue
void enqueue( queue* q, node *n ){
   *q->last = *n;
   q->last->next->prev = q->last;
   q->last = q->last->next;
   free( n );
   return;
}

// Checks to see if the queue is empty
int isEmpty( queue* q ){
   return q->first->next == NULL;
}

// Makes a new node and back links it to its parent
node* makeNode( point *p, node* n ){
   node *newNode = malloc(sizeof(node));
   newNode->loc = malloc(sizeof(point));
   newNode->loc->row = p->row;
   newNode->loc->col = p->col;
   newNode->distance = n->distance + 1;
   newNode->next = malloc(sizeof(node));
   newNode->next->loc = malloc(sizeof(point)); // Not freed
   newNode->next->loc->row = -1;
   newNode->next->loc->col = -1;
   newNode->prev = n;

   return newNode;
}

// Checks to see if the given point has been visited
int visited( queue *q, point *p ){
   node * curr = q->root;
   if( p->row == 0 && p->col == 0 )
      return 1;
   while( curr->loc->row != -1 ){
      if(curr->loc->col == p->col && curr->loc->row == p->row)
        return 1;
      else
        curr = curr->next;
   }
   return 0;
}

// Frees the data stored in the queue
void destroyQueue( queue *q ){
   node *curr = q->root;
   while( curr->next->loc->row != -1 ){
      free( curr->loc );
      node *next = curr->next;
      free( curr );
      curr = next;
   }
   free( curr->next->loc );
   free( curr->next );
   free( curr->loc );
   free( curr );
}
