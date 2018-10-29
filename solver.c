/*
 * Source file for the functions that search the maze,
 * build the queue, and mark the solution path.
 */

#include "mopsolver.h"

int isValid( int row, int col, char maze[Rows][Cols] ){
   if(((row >= 0) && (row < Rows)) && ((col >= 0) && (col < Cols)))
      return ( maze[row][col] == '0' );
   return 0;
}

void markSolutionPoints( node *n, char maze[Rows][Cols] ){
   node *curr = n;
   while( curr != NULL ){
      int row = curr->loc->row;
      int col = curr->loc->col;
      maze[row][col] = '3';
      curr = curr->prev;
   }
}

int solver( char maze[Rows][Cols], struct point* src, struct point* dst ){
   if( maze[0][0] == '1' )
      return -1;

   node *root = malloc(sizeof(node));
   root->loc = src;
   root->distance = 0;
   root->next = malloc(sizeof(node));
   root->next->prev = root;
   root->prev = NULL;

   queue *q = malloc(sizeof(queue));
   q->root = root;
   q->first = root;
   q->last = root;

   int rownum[4] = {1, -1, 0, 0};
   int colnum[4] = {0, 0, 1, -1};

   while( !isEmpty( q ) ){
      node *curr = q->first;

      if(curr->loc->row == dst->row && curr->loc->col == dst->col){
         markSolutionPoints( curr, maze );
         return curr->distance + 1;
      }

      pop( q );

      for( int i = 0; i < 4; i++){
         int row = curr->loc->row + rownum[i];
         int col = curr->loc->col + colnum[i];
         point *p = malloc(sizeof(point));
         p->row = row;
         p->col = col;
         if( isValid(row, col, maze) && !visited( q, p ) )
            enqueue( q, makeNode( p, curr ) );

      }

   }
   return -1;
}
