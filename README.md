# CSCI-243-Project-2
A maze solving program developed and submitted for "The Mechanics of Programming" Project 2.
Takes in a maze file containing zeros and ones representing passable and non-passable maze spaces respectivly.
Then parses this file, creates a 2D array structure representing the maze and preforms a BFS on the structure to
find the shortest possible path and prints data based on user-set flags.

USAGE:
mopsolver [-hdsp] [-i INFILE] [-o OUTFILE]

Options:
        -h      Print this helpful message to stdout and exit.
        -d      Pretty print (display) the maze after reading.  (Default: off)
        -s      Print shortest solution steps.        		(Default: off)
        -p      Print an optimal path.                		(Default: off)
        -i INFILE       Read maze from INFILE.        		(Default: stdin)
        -o OUTFILE      Write all output to OUTFILE.  		(Default: stdout)
        
Example maze file provided: maze.in
