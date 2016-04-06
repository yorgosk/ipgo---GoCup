/* File: placefreehandicap.c */
#include "header.h"

void placefreehandicap(int dim, int** b, int**lib, int num, unsigned int seed){
        int i=1, x,y;

	srand((unsigned int) seed);                    /* Seed for random number generator */

        if(num>(dim*dim)-1 || num<0) printf("? invalid number of stones\n\n");		/* error message based on GTP specifications */
	else{
		printf("=");										/* we have a valid command */
		do{
			do {
                		x=rand()%dim+1;				/* generate random x coordinate */
                		y=rand()%dim+1;				/* generate random y coordinate */
			}while(b[dim+1-y][x]!='.');				/* while the stone isn't going to an empty space */
			i++;
			b[dim+1-y][x]='X';
			if(x>=9) x++;    //for 'I' problem
	                printf(" %c%d", x+'A'-1, y);		/* print handicap stone position */
        	        fflush(stdout);						/* referee-related performance optimazation method */
        	}while(i<=num);      // gia na min bazei se theseis pou hdh yparxoun poulia
		printf("\n\n");				/* changing lines (GTP requirement) */
	}
}

