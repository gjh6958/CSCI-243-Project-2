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

int Rows = 0;
int Cols = 0;

/// Tis fucntion writes the maze that was parsed to a specific file
int write_maze( FILE *fp );

/// This function reades the maze from a given file
int read_maze( FILE *fp, int dims[], char maze[Rows][Cols] );

/// prints an optimal path
void option_p( int i );

/// Prints shortest solution steps
void option_s( int i);

/// Pretty prints the maze after reading
void option_d( char maze[Rows][Cols], FILE *out );

/// Prints helpful mesaage to stdout and exit
void option_h( int i, FILE* out );

int main( int argc, char *argv[] );


#endif
