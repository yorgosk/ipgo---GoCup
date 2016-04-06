/* File: pruning.c */
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>     //for INT_MIN and INT_MAX
#include "header.h"

float minimax(int depth, int **b, int dim, int col, int *best_row, int *best_col,int alpha ,int beta, int computer,
        int **lib, int jap, int **marked, float komi, int superko, int ***unb, int move){
        int i,j,k,g, **temp,fakeb[dim+2][dim+2];                     //temp board for minimax algorithm

	if (depth == 0 || isterminal(b, dim, col, lib, marked, superko, unb, move)){
                float  heuristic = final_score(dim, b, lib, jap, marked, komi);
                return heuristic;
        }

	if((temp=malloc((dim+2) * sizeof(int*)))==NULL){       /*dynamikh desmeush pinaka*/
                //printf("Memory allocation problem.\n");      //we have erased those messages because they might cause refe$
                return -1;
        }
        for(k=0;k<=dim+1;k++) if((temp[k]=malloc((dim+2) * sizeof(int)))==NULL){   //lib is a 2d board parallel to b[][] where $
                //printf("Memory allocation problem.\n");       //..the current number of liberties after ea$
                return -1;
        }

	float val = computer==1 ? alpha : beta;
	for(i=1; i<=dim; i++) for(j=1; j<=dim; j++) temp[i][j]=b[i][j];             //initiate temp

	for(i=1;i<=dim;i++){
		for(j=1;j<=dim;j++){
			if(temp[i][j] == '.'){
				if(!valid(i,j,col,dim,temp,lib,marked,move,unb,superko)){
					countlib(dim, temp, lib, marked);                   //allazoume ton pinaka liberties
					continue;
				}
				for(k=1; k<=dim; k++) for(g=1; g<=dim; g++) fakeb[k][g]=temp[k][g];             //initiate temp

				temp[i][j]=col;

				float rep=minimax(depth-1,temp,dim,'X'+'O'-col,best_row,best_col,alpha,beta,!computer,lib,jap,marked,komi,superko,unb,move);

				for(k=1; k<=dim; k++) for(g=1; g<=dim; g++) temp[k][g]=fakeb[k][g];             //initiate temp

				if ( (computer==1  && (rep>val) ) || (computer==0 && (rep<val)) )
				{
					val = rep;
					if ( computer== 1 ) alpha = val;
                                        else  beta = val;
					*best_row = i;
				        *best_col = j;
					if ( alpha >= beta ){
						for(k=0; k<=dim+1; k++) free(temp[k]);
        					free(temp);
						return val;
					}
				}
			}
		}
	}
	for(k=0; k<=dim+1; k++) free(temp[k]);
       	free(temp);
	return val;
}
