/* File: handicap.c */
#include "header.h"

void fixedhandicap(int dim, int** b, int**lib, int num){
	int i=3, j=3;
	if(dim>=13){			/* fixing the relevant positions where the pieces will start to be places*/
		i++;				/* based on the observation of the different initial positions between 5x5, 9x9 boards and 13x13, 19x19, 25x25 boards */
		j++;
	}

	switch(num){				//Our pride and beauty!!!
		case 1:					/* just 1 handicap stone cannot be placed */
			 break;
		case 9:							/* we work based on the observation that for every number of handicap stones asked to be placed */
		case 8:							/* some of them have fixed positions from the previous numbers */
			b[dim/2+1][j]='X';				/* left-central stone */
			b[dim/2+1][dim-j+1]='X';		/* right-central stone */
			lib[dim/2][j-1]=4;
			lib[dim/2][dim-j]=4;
		case 7:
		case 6:
			b[i][dim/2+1]='X';				/* upper-central stone*/
			b[dim-i+1][dim/2+1]='X';		/* lower-central stone */
			lib[i-1][dim/2]=4;
			lib[dim-i][dim/2]=4;
		case 5:
			if(num%2!=0){					/* we don't want this to appear for 6 or 8 */
				b[dim/2+1][dim/2+1]='X';	/* centre stone */
				lib[dim/2][dim/2]=4;
			}
		case 4:
            		b[dim-i+1][dim-j+1]='X';		/* inner-upper-left stone */
            		lib[dim-i][dim-j]=4;
		case 3:
			b[i][j]='X';					/* inner-lower-right stone */
        		    lib[i-1][j-1]=4;
		case 2:								/* Every time we gonna need this */
			b[dim-i+1][j]='X';				/* inner-lower-left stone */
			b[i][dim-j+1]='X';				/* inner-upper-right stone */
			lib[dim-i][j-1]=4;
			lib[i-1][dim-j]=4;
			break;
		default:
			break;
	}
}							/* when case is 9 we obviously want all of the upper to happen, except default */
