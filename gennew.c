/* File: gennew.c */
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "header.h"

int genmove(int dim, int **b, int **lib, int **marked, int move, int ***unb, unsigned int seed, int superko, int jap, float komi, int pass)
{
        char movable[5];         /*this is where we store the color to try to generate (white->(5), black->(5), anything else invalid so 5 is the optimal required space)*/
        scanf("%s", movable);	//take color to generate

	int flag=1, col,alpha,beta,k,g,**board,**ml,**mlothers;
	int best_row=-1, best_col=-1;	//we initiate them negative, because minimax will never return negative

	if((board=malloc((dim+2) * sizeof(int*)))==NULL){       /*dynamikh desmeush pinaka*/
                  //printf("Memory allocation problem.\n");
                  return -1;                              //board[][] is our GO board, where the stones are really placed
        }
        for(k=0;k<=dim+1;k++) if((board[k]=malloc((dim+2) * sizeof(int)))==NULL){
                 //printf("Memory allocation problem.\n");
                 return -1;
        }
	for(k=0;k<=dim+1;k++)for(g=0;g<=dim+1;g++)board[k][g] = b[k][g];

        if(!strcmp(movable,"black") || !strcmp(movable, "b") || !strcmp(movable, "B")) col='X';
        else if(!strcmp(movable,"white") || !strcmp(movable, "w") || !strcmp(movable, "W")) col='O';

	if(pass==1){
                float score=final_score(dim, b, lib, jap,marked,komi);      //find half the final score
	        if(score > 0  &&  col=='X'){
                        printf("= PASS\n\n");
                        return 1;
                }
		else if(score < 0 && col=='O')
		{
			printf("= PASS\n\n");
                        return 1;
		}
        }

	if((ml=(int**)calloc((dim+2), sizeof(int*)))==NULL){       /*dynamikh desmeush pinaka*/
                  //printf("Memory allocation problem.\n");
                  return -1;
        }
        for(k=0;k<=dim+1;k++) if((ml[k]=(int*)calloc((dim+2), sizeof(int)))==NULL){
                 //printf("Memory allocation problem.\n");
                 return -1;
        }

	for(k=1;k<=dim;k++) for(g=1;g<=dim;g++) if(board[k][g]=='.' && valid(k,g,col,dim,board,lib,marked,move, unb, superko) == 0) ml[k][g]=1;     //we mark the illegal moves

	if((mlothers=(int**)calloc((dim+2), sizeof(int*)))==NULL){       /*dynamikh desmeush pinaka*/
                  //printf("Memory allocation problem.\n");
                  return -1;
        }
        for(k=0;k<=dim+1;k++) if((mlothers[k]=(int*)calloc((dim+2), sizeof(int)))==NULL){
                 //printf("Memory allocation problem.\n");
                 return -1;
        }
	for(k=1;k<=dim;k++) for(g=1;g<=dim;g++) if(board[k][g]=='.' && valid(k,g,'O'+'X'-col,dim,board,lib,marked,move, unb, superko) == 0) mlothers[k][g]=1;//we mark the illegal moves  of the enemy

	int computer=1;
	int depth=4;		// Our prefered search depth
	minimax(depth, b, dim, col, &best_row, &best_col, INT_MIN, INT_MAX, 1 ,lib, jap, marked,  komi, superko,unb,move,board,ml,mlothers);
	//printf("best_row == %d     best_col == %d\n\n",best_row,best_col);
	if(best_row == -1 || best_col == -1){
		printf("= PASS\n\n");
		return 1;
	}
	b[best_row][best_col]=col;
	countlib(dim, b, lib,marked);                   //allazoume ton pinaka liberties

        clear(dim,b,lib,'O'+'X'-col);                        //NA KATHARISOUN OSA EXOUN LIB==0 KAI EXOUN ALLO XRWMA
        countlib(dim, b, lib,marked);

	if(best_row >= 9) best_row++;    //for 'I' printing problem
        printf("= %c%d\n\n", best_col+'A'-1, dim+1-best_row);

	for(k=0; k<=dim+1; k++) free(board[k]);
        free(board);
        fflush(stdout);                                         /* general optimization, especially when referee-playing */

	for(k=0; k<=dim+1; k++) free(ml[k]);
        free(ml);

	for(k=0; k<=dim+1; k++) free(mlothers[k]);
        free(mlothers);

	return 0;
}
