#include "header.h"

int checkboard(int** b,int dim){
	int k,g;
	for(k=1;k<=dim;k++)                  //CHECK IF BOARD IS  EMPTY
               for(g=1;g<=dim;g++)
                      if(b[k][g]!='.')				/* the appearance of just one stone is enough to categorize a board as NOT EMPTY */
		      {
			  printf("? board not empty\n\n");
                          fflush(stdout);		/* optimazation, especially when playing with referee (generally we avoid silly bugs that way) */
			  read();                       //clear the rest of input, so that we will not be confused
			  return 0;							/* so we don't have to check the whole board (0 for board NOT being EMPTY) */
		      }
	return 1;						/* 1 for board being EMPTY */
}
