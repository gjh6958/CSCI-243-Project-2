/*
 * Source file for the functions that are responsible
 * for parsing the in file for characters and building
 * the array representation of the maze.
 */

#include "mopsolver.h"

void getdims( FILE *fp, int dims[] ){
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

   dims[0] = N;
   dims[1] = M;

   Rows = N;
   Cols = M;
   fclose( fp );
}

/// Tis fucntion reads the maze from a given file
int read_maze( FILE *fp, int dims[], char maze[Rows][Cols] ){

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
            return 0;
         maze[rowcount][colcount] = c;
      }
      colcount = 0;
   }
}

