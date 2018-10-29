/*
 * Author - Grayson Hassell
 * CSCI-243 Project 2
 * "Escape From GNU York"
 * Maze solving program
 */

#include "mopsolver.h"

int Rows;
int Cols;

int main( int argc, char* argv[] ){

   int p = 0;
   int s = 0;
   int d = 0;
   int h = 0;
   char *infile = NULL;
   char *outfile = NULL;
   FILE *fip = stdin;
   FILE *fop = stdout;

   for( int i = 1; i < argc; i++ ){
      for( unsigned int j = 0; j < strlen( argv[i] ); j++ ){
         if( argv[i][0] == '-' ){
            if( argv[i][j] == 'p' )
               p = 1;
            if( argv[i][j] == 's' )
               s = 1;
            if( argv[i][j] == 'd' )
               d = 1;
            if( argv[i][j] == 'h' )
               h = 1;
         }
         else if( strcmp( argv[i-1], "-i" ) ){
            outfile = argv[i];
         }
         else if( strcmp( argv[i-1], "-o" ) ){
            infile = argv[i];
         }
      }
   }

   if( outfile != NULL )
      fop = fopen( outfile, "w" );
   if( infile != NULL )
      fip = fopen( infile, "r" );

   if( h ){
      option_h( h, fop );
      return 0;
   }

   int dims[2];
   if( infile != NULL){
      int dims[2];
      getdims( fip, dims );
   }
   char maze[Rows][Cols];
   if( infile != NULL ){
      fip = fopen( infile, "r" );
      read_maze( fip, dims, maze );
   }
   if( d )
      print_maze( fop, maze );

   int solution = solver( maze );

   if( s )
      option_s( fop, solution );
   if( p )
      print_maze( fop, maze );

   return 0;

}
