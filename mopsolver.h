/*
 * Header file for the mopsolver file
 * defines functions and describes their functionality
 * includes other libraries
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef MOPSOLVER
#define MOPSOLVER
#include "structures.h"

/// Links together a newly created node and the existing
/// last node.
int enqueue( queue* q, node *n );

/// Checks to make sure that the given queue still has
/// active nodes linked within it.
int isEmpty( queue* q );

/// Increments the q first pointer
/// to itsnext value.
node pop( queue* q );

/// Creates and returns a  new node with the given point
/// structure and back links it to its parent within the maze.
node* makeNode( point *p, node *n );

/// This function is responsible for freeing all of the
/// dynamically allocated memory contained in the queue.
void destroyQueue( queue *q );

/// This function returns a boolean in the form of an
/// integer to check if the given row and column are
/// passable within the maze and within the scope of
/// the maze dimensions.
int isValid( int row, int col, char maze[Rows][Cols] );

/// Traverses the queue to determine if the given location
/// has already been enqueued.
int visited( queue *q, point *p );

/// Takes the completed queue with the travered nodes
/// and backtracks the left neighbors to get their
/// location and change their char value within the
/// maze.
void markSolutionPoints( node *n, char maze[Rows][Cols] );

/// Maze traversal function that preforms the BFS on the
/// given maze, creates and enqueues the location nodes,
/// and returns the length of the optimal solution.
int solver( char maze[Rows][Cols] );

/// Function responsible for getting the dimensions of the
/// provided maze.
void getdims( FILE *fp, int dims[] );

/// This function reades the plain text maze from a given file.
int read_maze( FILE *fp, int dims[], char maze[Rows][Cols] );

/// Pretty prints the top and bottom borders of the maze.
void pptopbot( FILE *out );

/// Pretty prints the optimal path
void print_maze( FILE *fp, char maze[Rows][Cols] );

/// Prints the number of steps to the optimal solution.
void option_s( FILE *fp, int i);

/// Prints helpful mesaage to stdout and exit.
void option_h( int i, FILE* out );

/// Function that runs the other functions in sequence
/// to control the parsing of the flags and maze as well
/// as the solving of maze and acting on flags.
int main( int argc, char *argv[] );


#endif
