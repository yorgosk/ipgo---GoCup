/* File: genmove.c */
#include <stdio.h>
#include <stdlib.h>
#include "header.h"

int genmove(int dim, int **b, int **lib, int **marked, int move, int ***unb, unsigned int seed, int superko)
{
	char movable[5];	 /*this is where we store the color to try to generate (white->(5), black->(5), anything else invalid so 5 is the optimal required space)*/
	int x,y,flag=1,k,g;

	srand((unsigned int) seed);			// seed for random number generator
	scanf("%s", movable);

	do
	{
		x=rand()%dim+1;					// generate random x board coordinate
		y=rand()%dim+1;					// generate rendom y board coordinate
	}while(b[dim+1-y][x]!='.');      // giati na min bazei se theseis pou hdh yparxoun poulia

	if(!strcmp(movable,"black") || !strcmp(movable, "b") || !strcmp(movable, "B"))
	{
		 b[dim+1-y][x]='X';
	         countlib(dim, b, lib,marked);                   //allazoume ton pinaka liberties
                 clear(dim,b,lib,'O');                        //NA KATHARISOUN OSA EXOUN LIB==0 KAI EXOUN MAYRO XRWMA
                 countlib(dim, b, lib,marked);                   //allazoume ton pinaka liberties
                 if(lib[dim-y][x-1]==0)
                 {
		       flag=1;
                       b[dim+1-y][x]='.';                         //FORBIDEN POINT

                 }else{
			flag=0;
		 }
	}
	else if(!strcmp(movable,"white") || !strcmp(movable, "w") || !strcmp(movable, "W"))
        {
		 b[dim+1-y][x]='O';					/* try to put it there */
		 countlib(dim, b, lib,marked);                   //allazoume ton pinaka liberties
                 clear(dim,b,lib,'X');                        //NA KATHARISOUN OSA EXOUN LIB==0 KAI EXOUN MAYRO XRWMA
                 countlib(dim, b, lib,marked);                   //allazoume ton pinaka liberties
                 if(lib[dim-y][x-1]==0)				//forbiden point
                 {
		       flag=1;
                       b[dim+1-y][x]='.';			/*so we take it back to normal */

                 }else{
			flag=0;
		 }
	}
        if(ko(move,b,unb,dim,lib,marked,superko)==0)            // we have zero (0) when ko
        {
             printf("= PASS\n\n");						// well, it can't be invalid... so PASS :-)
             return 1;
        }
	if(flag==1)
	{
		printf("= PASS\n\n");             //AN EXOUME FORBIDEN H KO GINETAI PASS
		countlib(dim, b, lib, marked);    /* recount liberties and remove dead piecies */
	        return 1;
	}else
	{
		 if(x>=9) x++;    //for 'I' problem
                 printf("= %c%d\n\n", x+'A'-1, y);
	}
	countlib( dim, b, lib, marked);		/* recount liberties and remove dead piecies */
	fflush(stdout);						/* general optimazation, especially when referee-playing */
	return 0;
}

/* Our logic here works that way: Genmove is supposed to have a very basical intelligence. That is to not defy itself, by making invalid moves... So whenever
we are going to be led to an invalid move, we PASS. */

