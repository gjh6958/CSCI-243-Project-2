/*
 * Author - Grayson Hassell
 * Source file for the functions that are responsible
 * for parsing the in file for characters and building
 * the array representation of the maze.
 */

#include "mopsolver.h"

// Gets the dimensions of the maze
// data and sets global variable
void getdims( FILE *fp ){
   int N = 0; // rows
   int M = 0; // cols
   char c;

   while( c = fgetc( fp ) ){
      while( c == ' ' ){
         c = fgetc( fp );
      }
      if( c == '\n' )
         N++;
      else if( c == EOF )
         break;
      else
         M++;
   }

   M = (M/N);

   Rows = N;
   Cols = M;
   fclose( fp );
}

/// This function reads the maze from a given file
void read_maze( FILE *fp, char maze[Rows][Cols] ){
   char c;
   int colcount = 0;
   int rowcount = 0;

   for( rowcount; rowcount < Rows; rowcount++ ){
      for( colcount; colcount < Cols; colcount++ ){
         c = getc( fp );
         while( c == '\n' || c == ' ' ){
            c = fgetc( fp );
         }
         if( c == EOF )
            return;
         maze[rowcount][colcount] = c;
      }
      colcount = 0;
   }
}

