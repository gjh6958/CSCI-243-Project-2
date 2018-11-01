/*
 * Author - Grayson Hassell
 * CSCI-243 Project 2
 * "Escape From GNU York"
 * Maze solving program
 */

#include "mopsolver.h"

// Declares global variables
// that hold maze dimensions
int Rows;
int Cols;

// Controls the execution of all other functions
// and parses command line arguments
int main( int argc, char* argv[] ){

   // base flag values
   int p = 0;
   int s = 0;
   int d = 0;
   int h = 0;
   char *infile = NULL;
   char *outfile = NULL;

   // default file pointers
   FILE *fip = stdin;
   FILE *fop = stdout;

   // parses the command line arguments
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

   // Changes file pointers if they
   // should be different from defaults
   if( outfile != NULL )
      fop = fopen( outfile, "w" );
   if( infile != NULL )
      fip = fopen( infile, "r" );

   // runs option_h if flag was set
   // and ends program execution
   if( h ){
      option_h( fop );
      return 0;
   }

   // Creates the maze value buffer and populates itwith value from the file
   char *buffer;
   buffer = getdims( fip );

   // Creates the maze and populates it
   char maze[Rows][Cols];
   read_maze( buffer, maze );

   free( buffer );

   if( d )
      print_maze( fop, maze );

   int solution = solver( maze );

   if( s )
      option_s( fop, solution );
   if( p )
      print_maze( fop, maze );

   fclose( fop );
   return 0;

}
