/* File: isterminal.c */
#include "header.h"

int isterminal(int **b, int dim, int col, int **lib, int **marked, int superko, int ***unb, int move){
	int i, j;
	for(i=1; i<=dim; i++)
		for(j=1; j<=dim; j++)
			if(valid(i, j, col, dim, b, lib, marked, move, unb, superko))		//if at least one position is valid
				return 0;
	return 1;	//we only need to return 0 or 1, to know whether the node is terminal or not (1 -> terminal, 0 -> not_terminal)
}
