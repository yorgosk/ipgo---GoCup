/* File: clear.c */
#include "header.h"

void clear(int dim, int **b, int **lib,int col){
	int i, j;
	for(i=1;i<dim+1;i++) for(j=1;j<dim+1;j++) if(lib[i-1][j-1]==0  &&  b[i][j]==col) b[i][j]='.';  /*"clearing" a certain color's dead pieces (their liberties == 0)*/
}
