/*
 * Author - Grayson Hassell
 * Header file that defines the
 * global variables and structures
 * used throughout the program
 */

#ifndef STRUCTURES_H
#define STRUCTURES_H

/// Global variables the define the
/// dimensions of the maze.
extern int Rows;
extern int Cols;

/// Structure that holds the row and
/// column values of specific points
/// in the maze;
typedef struct point{
   int row;
   int col;
}point;

/// Structure that defines the nodes
/// for the queue to contain that also
/// link together to form the queue
/// and solution path.
typedef struct queueNode{
   point *loc;
   int distance;
   int solution;
   struct queueNode *next;
   struct queueNode *prev;
}node;

/// Queue structure that holds the
/// linked queuenodes and also holds
/// the pointers to the root, current
/// first, and current last nodes.
typedef struct queue{
   node *root;
   node *first;
   node *last;
}queue;

#endif
