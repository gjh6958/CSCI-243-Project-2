/*
 * Author - Grayson Hassell
 * CSCI-243 Project 2
 * "Escape From GNU York"
 * Maze solving program
 */

#include "mopsolver.h"

typedef struct point{
   int row;
   int col;
}point;

typedef struct queueNode{
   struct point *loc;
   int distance;
   struct queueNode *next;
   struct queueNode *prev;
   int solution;
}node;

typedef struct queue{
   node *root;
   node *first;
   node *last;
}queue;

struct queueNode pop( queue* q ){
   node first = *q->first;
   if( q->first == q->last )
      q->last = q->first->next;
   q->first = q->first->next;
   return first;
}

int enqueue( queue* q, node *n ){
   *q->last = *n;
   q->last->next->prev = q->last;
   q->last = q->last->next;
   return 0;
}

int isEmpty( queue* q ){
   return q->first->next == NULL;
}


int isValid( int row, int col, char maze[Rows][Cols] ){
   if(((row >= 0) && (row < Rows)) && ((col >= 0) && (col < Cols)))
      return ( maze[row][col] == '0' );
   return 0;
}

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
}

/// Tis fucntion reads the maze from a given file
int read_maze( FILE *fp, int dims[], char maze[Rows][Cols] ){

   char c;
   int colcount = 0;
   int rowcount = 0;

   for( rowcount; rowcount < Rows; rowcount++ ){
      for( colcount; colcount < Cols; colcount++ ){
         c = fgetc( fp );
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

/// This function writes the maze to a given file
int write_maze( FILE *fp ){

}

/// prints an optimal path
void option_p( FILE *fp, char maze[Rows][Cols] ){
   option_d( maze, fp );
}

/// Prints shortest solution steps
void option_s( FILE *out, int i ){
   if( i == -1 )
      fprintf( out, "No solution.\n" );
   else
      fprintf( out, "Solution in %d steps.\n", i );
}

node* makeNode( point *p, node* n ){
   node *newNode = malloc(sizeof(node));
   newNode->loc = p;
   newNode->distance = n->distance + 1;
   newNode->next = malloc(sizeof(node));
   //newNode->next->prev = newNode;
   newNode->prev = n;

   return newNode;
}

int visited( queue *q, point *p ){
   node * curr = q->root;
   if( p->row == 0 && p->col == 0 )
      return 1;
   while(curr->loc){
      if(curr->loc->col == p->col && curr->loc->row == p->row)
        return 1;
      else
        curr = curr->next;
   }
   return 0;
}

void markSolutionPoints( node *n, char maze[Rows][Cols] ){
   node *curr = n;
   while( curr != NULL ){
      int row = curr->loc->row;
      int col = curr->loc->col;
      maze[row][col] = '3';
      curr = curr->prev;
   }
}

int solver( char maze[Rows][Cols], struct point* src, struct point* dst ){
   if( maze[0][0] == '1' )
      return -1;

   node *root = malloc(sizeof(node));
   root->loc = src;
   root->distance = 0;
   root->next = malloc(sizeof(node));
   root->next->prev = root;
   root->prev = NULL;

   queue *q = malloc(sizeof(queue));
   q->root = root;
   q->first = root;
   q->last = root;

   int rownum[4] = {1, -1, 0, 0};
   int colnum[4] = {0, 0, 1, -1};

   while( !isEmpty( q ) ){
      node *curr = q->first;

      if(curr->loc->row == dst->row && curr->loc->col == dst->col){
         markSolutionPoints( curr, maze );
         return curr->distance + 1;
      }

      pop( q );

      for( int i = 0; i < 4; i++){
         int row = curr->loc->row + rownum[i];
         int col = curr->loc->col + colnum[i];
         point *p = malloc(sizeof(point));
         p->row = row;
         p->col = col;
         if( isValid(row, col, maze) && !visited( q, p ) )
            enqueue( q, makeNode( p, curr ) );

      }

   }
   return -1;
}

void pptopbot( FILE *out ){
   fprintf(out, "|");
   for( int i = 0; i < Cols * 2 + 1; i++)
      fprintf(out, "-");
   fprintf(out, "|\n");

}

/// Pretty prints the maze after reading
void option_d( char maze[Rows][Cols], FILE *out ){
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
   fprintf(outfile, "     -s      Print shortest solution steps.        	     (Default: off)\n");
   fprintf(outfile, "     -p      Print an optimal path.                	     (Default: off)\n");
   fprintf(outfile, "     -i INFILE       Read maze from INFILE.        	     (Default: stdin)\n");
   fprintf(outfile, "     -o OUTFILE      Write all output to OUTFILE.  	     (Default: stdout)\n");

}

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

   if(outfile != NULL)
      fop = fopen( outfile, "w" );
   if(infile != NULL)
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
      option_d( maze, fop );

   point *src = malloc(sizeof(point));
   src->row = 0;
   src->col = 0;
   point *dest = malloc(sizeof(point));
   dest->row = Rows - 1;
   dest->col = Cols - 1;
   int solution = solver( maze, src, dest );

   if( s )
      option_s( fop, solution );
   if( p )
      option_p( fop, maze );

   return 0;

}
