/* File: valid.c */
#include <stdio.h>
#include <stdlib.h>
#include "header.h"

int valid(int i , int j, int col, int dim, int** b, int** lib, int** marked, int move, int*** unb, int superko){
	int **temp, k,g;

	if((temp=malloc((dim+2) * sizeof(int*)))==NULL){       /*dynamikh desmeush pinaka*/
                //printf("Memory allocation problem.\n");      //we have erased those messages because they might cause refe$
        	return -1;
        }
        for(k=0;k<=dim+1;k++) if((temp[k]=malloc((dim+2) * sizeof(int)))==NULL){   //lib is a 2d board parallel to b[][] where $
        	//printf("Memory allocation problem.\n");       //..the current number of liberties after ea$
                return -1;
        }

	for(k=0; k<=dim+1; k++) for(g=0; g<=dim+1; g++) temp[k][g]=b[k][g];		//initiate temp
	temp[i][j]=col;
	countlib(dim, temp, lib, marked);                   //allazoume ton pinaka liberties

        clear(dim,temp,lib, 'X'+'O'-col);                        //NA KATHARISOUN OSA EXOUN LIB==0 KAI EXOUN ALLO XRWMA
        countlib(dim, temp, lib, marked);                   //allazoume ton pinaka liberties

        if(lib[i-1][j-1] == 0)
        {
		for(k=0; k<=dim+1; k++) free(temp[k]);
		free(temp);
	     	return 0;
        }

	clear(dim,temp,lib, col);                        //NA KATHARISOUN OSA EXOUN LIB==0 KAI EXOUN ALLO XRWMA
        countlib(dim, temp, lib, marked);                   //allazoume ton pinaka liberties
	if(temp[i][j]=='.')
	 {
                for(k=0; k<=dim+1; k++) free(temp[k]);
                free(temp);
                return 0;
        }

	if(ko(move,temp,unb,dim,lib,marked,superko)==0){            // we have zero (0) when ko
        	for(k=0; k<=dim+1; k++) free(temp[k]);
        	free(temp);
		return 0;                   //illegal move
	}

	for(k=0; k<=dim+1; k++) free(temp[k]);
	free(temp);
	return 1;               //if everything is ok
}
