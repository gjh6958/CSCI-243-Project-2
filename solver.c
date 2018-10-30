/*
 * Author - Grayson Hassell
 * Source file for the functions that search the maze,
 * build the queue, and mark the solution path.
 */

#include "mopsolver.h"

// Checks to see if a given location
// in the maze is a valid move
int isValid( int row, int col, char maze[Rows][Cols] ){
   if(((row >= 0) && (row < Rows)) && ((col >= 0) && (col < Cols)))
      return ( maze[row][col] == '0' );
   return 0;
}

// Marks the points in the maze that
// are in the solution path
void markSolutionPoints( node *n, char maze[Rows][Cols] ){
   node *curr = n;
   while( curr != NULL ){
      int row = curr->loc->row;
      int col = curr->loc->col;
      maze[row][col] = '3';
      curr = curr->prev;
   }
}

// Algorithem responsible for finding the
// optimal solution to the maze
int solver( char maze[Rows][Cols] ){
   if( maze[0][0] == '1' )
      return -1;

   point src = { 0, 0 };
   point dst = { Rows - 1, Cols - 1 };

   node *root = malloc(sizeof(node));
   root->loc = malloc(sizeof(point));
   *root->loc = src;
   root->distance = 0;
   root->next = malloc(sizeof(node));
   root->next->loc = malloc(sizeof(point)); // Not freed
   root->next->loc->row = -1;
   root->next->loc->col = -1;
   root->next->prev = root;
   root->prev = NULL;

   queue qu = { root, root, root };
   queue *q = &qu;

   int rownum[4] = {1, -1, 0, 0};
   int colnum[4] = {0, 0, 1, -1};

   while( !isEmpty( q ) ){
      node *curr = q->first;

      if(curr->loc->row == dst.row && curr->loc->col == dst.col){
         markSolutionPoints( curr, maze );
         int solution = curr->distance + 1;
         destroyQueue( q );
         return solution;
      }

      pop( q );

      for( int i = 0; i < 4; i++){
         int row = curr->loc->row + rownum[i];
         int col = curr->loc->col + colnum[i];
         point loc = { row, col };
         point *p = &loc;
         if( isValid(row, col, maze) && !visited( q, p ) )
            enqueue( q, makeNode( p, curr ) );

      }

   }
   destroyQueue( q );
   return -1;
}
