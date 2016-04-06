/* File: undo.c */
#include "header.h"

void undo(int **b , int*** unb,int move ,int dim ){
	int g, k;

	for(k=0;k<=dim+1;k++) for(g=0;g<=dim+1;g++) b[k][g]=unb[move][k][g];   /* when undo, we basically go to the previous board-stuation */

	for(k=0; k<=dim+1; k++) free(unb[move+1][k]);		/* we also free the dynamically allocated memory of the former board-situation */
    	free(unb[move+1]);
}
