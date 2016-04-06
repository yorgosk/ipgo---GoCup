/* File: boardsize.c */
#include "header.h"

void boardsize(int dim, int **b)
{
	int i, j;
        /* (Generally) Initiate board */
        for(i=0; i<=dim+1; i++){
                for(j=0; j<=dim+1; j++){
                        if((i==0 && j==0) || (i==0 && j==dim+1) || (i==dim+1 && j==0) || (i==dim+1 && j==dim+1)) b[i][j]=' ';	/* spaces at the board's edges */
                        else if((i==0 || i==dim+1) && (j!=0 && j!=dim+1)){
				if('A'-1+j>='I') b[i][j]='A'+j;				/* avoid 'I' appearance at board's co-ordinating system */
				else b[i][j]='A'-1+j;						/* print the correct letters */
                        }
			else if((j==0 || j==dim+1) && (i!=0 && i!=dim+1)) b[i][j]=dim-i+1;  /*print the numbers in reverse (greater---(going lower)---smaller) order*/
                        else b[i][j]='.';						/* dot '.' at any playable position (playing spaces) */
                }
        }
}
