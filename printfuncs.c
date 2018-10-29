/*
 * Author - Grayson Hassell
 * Defines the functionality of the
 * functions that print to the out file
 */

#include "mopsolver.h"

void pptopbot( FILE *out ){
   fprintf(out, "|");
   for( int i = 0; i < Cols * 2 + 1; i++)
      fprintf(out, "-");
   fprintf(out, "|\n");

}

/// Pretty prints the maze after reading
void print_maze( FILE *out, char maze[Rows][Cols] ){
   pptopbot( out );
   for( int rowcount = 0; rowcount < Rows; rowcount++ ){
      if(rowcount != 0)
         fprintf(out, "| ");
      else
         fprintf(out, "  ");
      for( int colcount = 0; colcount < Cols; colcount++ ){
         if( maze[rowcount][colcount] == '0' )
            fprintf(out, ". ");
         else if( maze[rowcount][colcount] == '1' )
            fprintf(out, "# ");
         else if( maze[rowcount][colcount] == '3' )
            fprintf(out, "+ ");
      }
      if(rowcount != Rows-1)
         fprintf(out, "|\n");
      else
         fprintf(out, " \n");
   }
   pptopbot( out );
}

/// Prints helpful mesaage to stdout and exit
void option_h( int i, FILE* outfile ){
   fprintf(outfile, "USAGE:\n");
   fprintf(outfile, "mopsolver [-hdsp] [-i INFILE] [-o OUTFILE]\n\n");
   fprintf(outfile, "Options:\n");
   fprintf(outfile, "     -h      Print this helpful message to stdout and exit.\n");
   fprintf(outfile, "     -d      Pretty print (display) the maze after reading.  (Default: off)\n");
   fprintf(outfile, "     -s      Print shortest solution steps.                     (Default: off)\n");
   fprintf(outfile, "     -p      Print an optimal path.                             (Default: off)\n");
   fprintf(outfile, "     -i INFILE       Read maze from INFILE.                     (Default: stdin)\n");
   fprintf(outfile, "     -o OUTFILE      Write all output to OUTFILE.               (Default: stdout)\n");

}

/// Prints shortest solution steps
void option_s( FILE *out, int i ){
   if( i == -1 )
      fprintf( out, "No solution.\n" );
   else
      fprintf( out, "Solution in %d steps.\n", i );
}

