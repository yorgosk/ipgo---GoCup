/* File: showboard.c */
#include <stdio.h>
#include "header.h"

void showboard(int dim, int **b){
        int i,j;

        for(i=0; i<=dim+1;i++)
        {
                for(j=0;j<=dim+1;j++)
                {
                        if((j==0 || j==dim+1) && (i!=0 && i!=dim+1)){
                                if(j==0) printf("%2d ", b[i][j]);		/* in order to print beautifully  */
                                else printf("%-2d", b[i][j]);			/* in order to print beautifully the double-digit numbers of the right column of */
                        }
                        else{
                                putchar(b[i][j]);
                                if(isspace(b[i][j])) printf(" ");            /*beautification, nicelly looking spaces between playing-spaces */
                                printf(" ");								/* result to a better-looking board */
                        }
                }
               if(i!=dim+1) printf("\n");				/* change output's line when a board's line is over */
        }
	fflush(stdout);		/* cleaning stdout results to performance optimazation, especially when playing with referee and also helps avoiding some output bugs */
}
