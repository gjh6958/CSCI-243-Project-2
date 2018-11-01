/*
 * Author - Grayson Hassell
 * Source file for the functions that are responsible
 * for parsing the in file for characters and building
 * the array representation of the maze.
 */

#include "mopsolver.h"

// Gets the dimensions of the maze
// data and sets global variable
char* getdims( FILE *fp ){
   int N = 0; // rows
   int M = 0; // cols
   char c;
   char *buffer = malloc( 100 * sizeof(char));
   int index = 0;
   int currSize = 100;
   int colCount = 0;
   int rowCount = 0;

   while( c = fgetc( fp ) ){
      while( c == ' ' ){
         c = fgetc( fp );
      }
      if( c == '\n' ){
         N++;
      }
      else{
         if( index > currSize - 1 ){
            buffer = realloc( buffer, (100+currSize)*sizeof(char));
            currSize = currSize + 100;
         }
	 if( c == EOF ){
            buffer[index] = c;
            break;
         }
         else{
            buffer[index] = c;
            index++;
            M++;
         }
      }
   }

   M = (M/N);
   Rows = N;
   Cols = M;
   fclose( fp );

   return buffer;
}

/// This function reads the maze from a given file
void read_maze( char* buffer, char maze[Rows][Cols] ){
   char c;
   int colcount = 0;
   int rowcount = 0;
   int index = 0;

   for( rowcount; rowcount < Rows; rowcount++ ){
      for( colcount; colcount < Cols; colcount++ ){
         c = buffer[index];
         if( c == EOF )
            return;
         maze[rowcount][colcount] = c;
         index++;
      }
      colcount = 0;
   }
}

