/* File: play.c */
#include <stdio.h>
#include "header.h"

int play(int dim, int **b,int** lib,int** marked){
	char movable[5],f[200];			// buffers for color to be played
	int x, y, z, pass=0,i,j,k,g, lastcol='.';
	scanf("%s", movable);				//read color to be played
	if(!strcmp(movable, "black") || !strcmp(movable, "b") || !strcmp(movable, "B")){		//black color
		char black[5];					//string of black coordinates
   		scanf("%s",black);
		if(strlen(black)>3 && strcmp(black,"pass")!=0)
		{
			        printf("? invalid coordinate\n\n");
                                fflush(stdout);
                                read();			//clear the rest of input, so that we will not be confused
                                return -1;
		}
							//take coordinates
		if(black[0]=='I' || black[0]=='i')					//an I column doesn't exist in our board
		{
			printf("? invalid coordinate\n\n");
			fflush(stdout);
			read();			//clear the rest of input, so that we will not be confused

			return -1;
		}
		if(((black[0]>'I' && black[0]<'a') || black[0]>'i') && strcmp(black, "pass")) black[0]--;       //to fix coordination problem sourcing from lack of 'I'
                if(!strcmp(black,"pass")){		//respond to pass
			printf("= \n\n");
			return 1;			//return 1 when black passes, because we also don't need to go any further
                }else
                {
			if(black[0]>='A' && black[0]<='Z') x=black[0]-'A'+1;			//get black piece column
			else if(black[0]>='a' && black[0]<='z') x=black[0]-'a'+1;
                        if(strlen(black)==3){							//black piece line when it's double digited
                                y=black[1]-'0';
                                z=black[2]-'0';
                                y=dim+1-(10*y+z);
                        }else y=dim+1-(black[1]-'0');                     //black piece line when it's single digited
                        if(y>=1 && y<=dim && x>=1 && x<=dim && b[y][x]=='.'){
				b[y][x]='X';                                   //to topothetoume mesa ston pinaka
                                countlib(dim, b, lib,marked);                   //allazoume ton pinaka liberties
                                clear(dim,b,lib,'O');                        //NA KATHARISOUN OSA EXOUN LIB==0 KAI EXOUN MAYRO XRWMA
                                countlib(dim, b, lib,marked);                   //allazoume ton pinaka liberties
                                if(lib[y-1][x-1]==0)
                                {
					printf("? invalid coordinate\n\n");
                                        b[y][x]='.';				//it can't stay on the board
					return -1;
                                }
			}else{
				printf("? invalid coordinate\n\n");
				fflush(stdout);
				read();			//clear the rest of input, so that we will not be confused

				return -1;					//returns -1 when it encounters error
			}
                }
	}else if(!strcmp(movable,"white") || !strcmp(movable, "w") || !strcmp(movable, "W")){			//white color
		char white[5];					//string of white coordinates
		scanf("%s",white);				//take white coordinates

		if(strlen(white)>3 && strcmp(white,"pass")!=0)
                 {
                                printf("? invalid coordinate\n\n");
                                fflush(stdout);
                                read();			//clear the rest of input, so that we will not be confused
                                return -1;
                 }

		if(white[0]=='I' || white[0]=='i')		//there is no I column in our board
                {
                        printf("? invalid coordinate\n\n");
			fflush(stdout);
			read();			//clear the rest of input, so that we will not be confused
                        return -1;
                }
		if(((white[0]>'I' && white[0]<'a') || white[0]>'i') && strcmp(white, "pass")) white[0]--;        //giati alliws den elgxw pass swsta
		if(!strcmp(white, "pass")){			//respond to pass
			printf("= \n\n");
			fflush(stdout);
			return 1;				//return 1 when white passes, because we also don't need to go any further
                }else
                {
			if(white[0]>='A' && white[0]<='Z') x=white[0]-'A'+1;			//get white piece column
                        else if(white[0]>='a' && white[0]<='z') x=white[0]-'a'+1;
                        if(strlen(white)==3){						 //black piece line when it's double digited
                                y=white[1]-'0';
                                z=white[2]-'0';
                                y=dim+1-(10*y+z);
                        }else y=dim+1-(white[1]-'0');                     //black piece line when it's single digited
			if(y>=1 && y<=dim && x>=1 && x<=dim && b[y][x]=='.'){
				b[y][x]='O';                                   //to topothetoume mesa ston pinaka
                                countlib(dim, b, lib,marked);                   //allazoume ton pinaka liberties
                                clear(dim,b,lib,'X');                        //NA KATHARISOUN OSA EXOUN LIB==0 KAI EXOUN MAYRO XRWMA
                                countlib(dim, b, lib,marked);                   //allazoume ton pinaka liberties
                                if(lib[y-1][x-1]==0)
                                {
					printf("? invalid coordinate\n\n");
					b[y][x]='.';				 //it can't stay on the board
					read();			//clear the rest of input, so that we will not be confused
					return -1;
                                }
                        }else{
				printf("? invalid coordinate\n\n");
				fflush(stdout);
				read();			//clear the rest of input, so that we will not be confused
				return -1;				//returns -1 when it encounters error
			}
                }
	}else
	{
		 printf("? invalid color\n\n");			//if the color's name is not correct according to GTP
		 read();			//clear the rest of input, so that we will not be confused
		 fflush(stdout);				//performance optimization
		 return -1;
	}

        countlib(dim, b, lib,marked);                     //GIA REFRESH
	fflush(stdout);					 //performance optimization
	return pass;				//so main() function knows whether player passed or not
}
