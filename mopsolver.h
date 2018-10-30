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
/// last node in a given queue.
/// @param q The queue structure that to insert the node into
/// @param n A node structure that contains the data to place at the end of the queue
void enqueue( queue* q, node *n );

/// Checks to make sure that the given queue still has
/// active nodes linked within it.
/// @param q The queue structure that is being checked for active nodes
/// @return Returns a 1 if queue is empty and a 0 if not.
int isEmpty( queue* q );

/// Increments the q's first pointer
/// to its next value.
/// @param q Queue to increment the first pointer
/// @return The node that was contained at the queues previous first pointer
node pop( queue* q );

/// Creates and returns a new node with the given point
/// structure and back links it to its parent within the maze.
/// @param p A pointer to a point structure containing location values
/// @param n A pointer to the node that should be the left neighbor of the newly created node
/// @return A node pointer to the newly created node.
node* makeNode( point *p, node *n );

/// This function is responsible for freeing all of the
/// dynamically allocated memory contained in the queue.
/// @param q The queue to free held memory nodes
void destroyQueue( queue *q );

/// This function returns a boolean in the form of an
/// integer to check if the given row and column are
/// passable within the maze and within the scope of
/// the maze dimensions.
/// @param row The row of the location to check validity
/// @param col The col of the location to check validity
/// @param maze The read in maze data
/// @return A 0 if the location is not valid and a 1 if it is valid
int isValid( int row, int col, char maze[Rows][Cols] );

/// Traverses the queue to determine if the given location
/// has already been enqueued.
/// @param q A pointer to the current queue of maze nodes
/// @param p A point pointer that contains the maze location to check
/// @return A 1 if the point has been visited and a 0 if not
int visited( queue *q, point *p );

/// Takes the completed queue with the travered nodes
/// and backtracks the left neighbors to get their
/// location and change their char value within the maze.
/// @param n A pointer to the node that contains the exit location
/// @param maze The maze data
void markSolutionPoints( node *n, char maze[Rows][Cols] );

/// Maze traversal function that preforms the BFS on the
/// given maze, creates and enqueues the location nodes,
/// and returns the length of the optimal solution.
/// @param maze The maze data to traverse
/// @return The number of steps in the optimal solution, a -1 if none was found
int solver( char maze[Rows][Cols] );

/// Function responsible for getting the dimensions of the
/// provided maze.
/// @param fp The file pointer of the file containing raw maze data.
/// @param dims An integer array to contain the dimensions of the maze
void getdims( FILE *fp );

/// This function reades the plain text maze from a given file.
/// @param fp A file pointer to the file containing raw maze data
/// @param maze The empty 2D character array to be populated with read in maze data
void read_maze( FILE *fp, char maze[Rows][Cols] );

/// Pretty prints the top and bottom borders of the maze.
/// @param out The file pointer to write output to.
void pptopbot( FILE *out );

/// Pretty prints the optimal path
/// @param fp The file pointer to write output to.
/// @param maze The maze data to print
void print_maze( FILE *fp, char maze[Rows][Cols] );

/// Prints the number of steps to the optimal solution.
/// @param fp The file pointer to write output to
/// @param i The number of optimal solution steps
void option_s( FILE *fp, int i);

/// Prints helpful mesaage to stdout and exit.
/// @param out The file pointer to write output to
void option_h( FILE* out );

/// Function that runs the other functions in sequence
/// to control the parsing of the flags and maze as well
/// as the solving of maze and acting on flags.
/// @param argc Number ot command line arguments
/// @param argv An array of char* contining the command line arguments
int main( int argc, char *argv[] );


#endif
