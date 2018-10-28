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
   int visited;
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

int enqueue( queue* q, node* n ){
   if( q->last == q->first &&  q->root == q->last ){
      *q->last = *n;
      return 0;
   }
   *n->prev = *q->last;
   *q->last = *n;
   return 0;
}

int isEmpty( queue* q ){
   return q->first == NULL;
}


int isValid( int row, int col, char maze[Rows][Cols] ){
   if(((row >= 0) && (row < Rows)) && ((col >= 0) && (col < Cols)))
      return ( ((char (*)[4])maze)[row][col] != '1' );
   return 0;
}

void getdims( FILE *fp, int dims[] ){
   int N = 0; // rows
   int M = 0; // cols
   char c;

   while( c = fgetc( fp ) ){
      if( c == '\n' )
         N++;
      else if( c == EOF )
         break;
      else
         M++;
   }

   M = (M/N);

   printf("Rows: %d, Cols: %d\n", N, M);

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
         if( c == '\n' )
            c = fgetc( fp );
         if( c == EOF )
            return 0;
         maze[rowcount][colcount] = c;
         printf("%c", maze[rowcount][colcount]);
      }
      colcount = 0;
      printf("\n");
   }
}

/// This function writes the maze to a given file
int write_maze( FILE *fp ){

}

/// prints an optimal path
void option_p( int i ){

}

/// Prints shortest solution steps
void option_s( FILE *out, int i){
   fprintf( out, "Solution in %d steps.\n", i );
}

node* makeNode( point *p, node* n ){
   node *newNode = malloc(sizeof(node));
   newNode->loc = p;
   newNode->distance = n->distance + 1;
   newNode->solution = 0;
   newNode->next = malloc(sizeof(node));
   newNode->prev = malloc(sizeof(node));;

   return newNode;
}

int visited( queue *q, point *p ){
   node * curr = q->root;
   if( p->row == 0 && p->col == 0 )
      return 1;
   while(curr->loc){
      if(curr->loc->col == p->col && curr->loc->row == p->row)
        return curr->loc->visited;
      else
        curr = curr->next;
   }
   return 0;
}

int solver( char maze[Rows][Cols], struct point* src, struct point* dst ){
   if( maze[0][0] == '1' )
      return 0;

   node *root = malloc(sizeof(node));
   root->loc = src;
   root->distance = 0;
   root->solution = 1;
   root->next = malloc(sizeof(node));
   root->prev = NULL;

   queue *q = malloc(sizeof(queue));
   q->root = root;
   q->first = root;
   q->last = root;

   int rownum[4] = {-1, 0, 0, 1};
   int colnum[4] = {0, -1, 1, 0};

   while( !isEmpty( q ) ){
      node curr = pop( q );

      if(curr.loc->row == dst->row && curr.loc->col == dst->col){
         return curr.distance;
      }

      for( int i = 0; i < 4; i++){
         int row = curr.loc->row + rownum[i];
         int col = curr.loc->col + colnum[i];
         point *p = malloc(sizeof(point));
         p->row = row;
         p->col = col;
         if( isValid(row, col, maze) && !visited( q, p ) ){
            p->visited = 1;
            curr.next = makeNode(p, &curr);
            enqueue( q, makeNode(p, curr.next));
         }

      }

   }


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
      fprintf(out, "| ");
      for( int colcount = 0; colcount < Cols; colcount++ ){
         if( maze[rowcount][colcount] == '0' )
            fprintf(out, ". ");
         else if( maze[rowcount][colcount] == '1' )
            fprintf(out, "# ");
      }
      fprintf(out, "|\n");
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


   printf("\nFlags set, p: %d s: %d d: %d h: %d", p, s, d, h);
   printf("\nInfile: %s", infile);
   printf("\nOutfile: %s\n", outfile);
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

   point *src = malloc(sizeof(point));
   src->row = 0;
   src->col = 0;
   src->visited = 1;
   point *dest = malloc(sizeof(point));
   dest->row = Rows - 1;
   dest->col = Cols - 1;
   dest->visited = 0;
   int solution = solver( maze, src, dest );

   if( d )
      option_d( maze, fop );
   if( s )
      option_s( fop, solution );
   if( p )
      option_p( p );

   return 0;

}
