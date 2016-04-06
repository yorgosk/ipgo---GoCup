/* File: minimax.c */
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>	//for INT_MIN and INT_MAX
#include "header.h"

float minimax(int depth, int **b, int dim, int col, int *best_row, int *best_col,float alpha ,float beta, int computer,
	int **lib, int jap, int **marked, float komi, int superko, int ***unb, int move,int **board,int **ml,int **mlothers){
	int i,j,k,g, fakeb[dim+2][dim+2];                     //fakeboard for minimax algorithm
	float rep;

	if (depth == 0 || isterminal(b, dim, col, lib, marked, superko, unb, move)){
             	float  heuristic = final_score(dim, board, lib, jap, marked, komi);
                return heuristic;
        }
	float val = computer==1 ? alpha : beta;

	for (i=1; i<=dim; i++)
	{
                for (j=1; j<=dim; j++)
		{
                        if (board[i][j] == '.' && ml[i][j]==0 && mlothers[i][j]==0 && b[i][j]=='.')
			{
				for(k=1;k<=dim;k++) for(g=1;g<=dim;g++)  fakeb[k][g]=board[k][g];
				board[i][j] = col;

				countlib(dim, board, lib,marked);                   //allazoume ton pinaka liberties
			        clear(dim,board,lib,'O'+'X'-col);                        //NA KATHARISOUN OSA EXOUN LIB==0 KAI EXOUN ALLO XRWMA
        			countlib(dim, board, lib,marked);

				if(computer == 0 ) rep = minimax(depth-1, b, dim, 'X' + 'O' - col,best_row, best_col,alpha,beta,1, lib, jap, marked, komi, superko, unb, move,board,ml,mlothers);
				if(computer == 1 ) rep = minimax(depth-1, b, dim, 'X' + 'O' - col,best_row, best_col,alpha,beta,0, lib, jap, marked, komi, superko, unb, move,board,ml,mlothers);

				for(k=1;k<=dim;k++) for(g=1;g<=dim;g++) board[k][g]=fakeb[k][g];     //go back to the previous board

				if ( (computer==1  && (rep>val) ) || (computer==0 && (rep<val)) )
				{
					val = rep;
					if ( computer== 1 ) alpha = val;
                                        else  beta = val;
					*best_row = i;
				        *best_col = j;
					if ( alpha >= beta ) return val;
				}
			}
		}
	 }
	 return val;
}
