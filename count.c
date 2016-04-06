/* File: count.c */
#include "header.h"

int count(int i, int j, int col, int dim, int** b, int** marked)
{   int r=0;
	//check upper neighbor
	if(i>1){
		if(b[i-1][j]=='.' && marked[i-2][j-1] ){	/* if it's space and we haven't already checked */
			r++;									/* it's an extra liberty */
			marked[i-2][j-1]=0;						/* now it's checked */
		}else if(b[i-1][j]==col && marked[i-2][j-1]){	/* if it's the same color's and we haven't already checked */
			marked[i-2][j-1]=0;						/* now it's checked */
			r+=count(i-1, j, col, dim, b,marked);  //function recursively calls itself
		}
	}
	//check lower neighbor
	if(i<dim){
		if(b[i+1][j]=='.' && marked[i][j-1]){		/* if it's space and we haven't already checked */
			r++;									/* it's an extra liberty */
			marked[i][j-1]=0;						/* now it's checked */
		}else if(b[i+1][j]==col && marked[i][j-1]){		/* if it's the same color's and we haven't already checked */
			marked[i][j-1]=0;						/* now it's checked */
			r+=count(i+1, j, col, dim, b,marked); //function recursively calls itself
		}

	}
	//check left neighbor
	if(j>1){
		if(b[i][j-1]=='.' && marked[i-1][j-2]){			/* if it's space and we haven't already checked */
			r++;										/* it's an extra liberty */
			marked[i-1][j-2]=0;							/* now it's checked */
		}else if(b[i][j-1]==col && marked[i-1][j-2]){	/* if it's the same color's and we haven't already checked */
			marked[i-1][j-2]=0;							/* now it's checked */
			r+=count(i, j-1, col, dim, b,marked); //function recursively calls itself
		}
	}
	//check right neighbor
	if(j<dim){
		if(b[i][j+1]=='.' && marked[i-1][j]){		/* if it's space and we haven't already checked */
			r++;									/* it's an extra liberty */
			marked[i-1][j]=0;						/* now it's checked */
		}else if(b[i][j+1]==col && marked[i-1][j]){	/* if it's the same color's and we haven't already checked */
			marked[i-1][j]=0;						/* now it's checked */
			r+= count(i, j+1, col, dim, b,marked); // function recursively calls itself
		}
	}
        return r;							//return number of liberties
}
