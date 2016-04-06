/* File: countlib.c */
#include "header.h"

void countlib(int dim,int** b,int** lib,int** marked)
{
 int i, j,k,g,color;
 for(i=1;i<dim+1;i++)				//iterate through the board
 {
	for(j=1;j<dim+1;j++)
	{	if(b[i][j]!='.')
		{
			for (k = 0; k < dim; k++) for (g =0 ; g < dim; g++) marked[k][g] = 1;		/* initialize marked[] array */
			color=b[i][j];																/* store current piece's color */
			lib[i-1][j-1]=count(i, j, color, dim, b, marked);				/* call the function that is going to do all the heavy work and count the liberties */
		}
		else lib[i-1][j-1]=0;                    //empty
	}  /* end countlib */
 }
}
