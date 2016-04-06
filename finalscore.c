/* File: finalscore.c */
#include "header.h"

float final_score(int dim, int** b, int** lib, int jap, int **marked, float komi){
	int temp[dim+2][dim+2], i, j, k, l;

	if(!jap){					//if requested for CHINESE score

		int flag;
		float blackcount=0, score;
		for(i=0; i<=dim+1; i++) for(j=0; j<=dim+1; j++) temp[i][j]=b[i][j];	//create temp[][], a 2d array parallel to GO board b[][]
								//where we will store the temporary changes that we make into the board to help ourselves when counting
		for(i=1; i<=dim; i++) for(j=1; j<=dim; j++)  //clean dead stones
 			if(lib[i-1][j-1]==1)
			{
				temp[i][j]='.';
				lib[i-1][j-1]=0;
			}

		for(i=1; i<=dim; i++){				//we iterate though th b[][] (GO board)
			for(j=1; j<=dim; j++){
				flag=0;
				if(temp[i][j]=='.'){		//and for every free playing space we search if it's in the black's territory
					for(k=i; k>=1; k--){
						if(temp[k][j]=='O') flag=1;		//even one black is enough
						if(temp[k][j]=='X') break;		//stop immediatelly when you encounter white
					}
					for(k=i; k<=dim; k++){
						if(temp[k][j]=='O') flag=1;             //even one black is enough
						if(temp[k][j]=='X') break;              //stop immediatelly when you encounter white
					}
					for(l=j; l>=1; l--){
						if(temp[i][l]=='O') flag=1;             //even one black is enough
						if(temp[i][l]=='X') break;              //stop immediatelly when you encounter white
					}
					for(l=j; l<=dim; l++){
						if(temp[i][l]=='O') flag=1;             //even one black is enough
						if(temp[i][l]=='X') break;              //stop immediatelly when you encounter white
					}
					if(!flag) temp[i][j]='X';	//if it's under black's territory of influence then we make it black,
				}					//because it's gonna anyway be counted as black
			}
		}

		for(i=1; i<=dim; i++) for(j=1; j<=dim; j++) if(temp[i][j]=='X') blackcount++;	//count the black player's territory

		score = 2*(blackcount-(dim*dim)/2.0-komi/2.0);		//calculate score, with also using komi (if it exists)
		return score;		//return the score

	}else{					//if requested for JAPANESE score

		int blafl, whifl, inblafl, inwhifl, f;	//f is a marker flag for when we reach the end of the GO board without changing color
		float whites=0, blacks=0, score;		//also: blafl:blackflag, whifl:whiteflag, inblafl:initialblackflag, inwhifl:initialwhiteflag

		for(i=0; i<=dim+1; i++) for(j=0; j<=dim+1; j++) temp[i][j]=b[i][j];	//create temp[][], a 2d array parallel to GO board b[][]
                                                              //where we will store the temporary changes that we make into the board to help ourselves when counting
        	//kill but also face seki situations
		for(i=1; i<=dim; i++) for(j=1; j<=dim; j++){    //iterate through the GO board b[][]
			blafl=0;                                //initiate counter for influential black pieces
                        whifl=0;                                //initiate counter for influential white pieces
			if(lib[i-1][j-1]==1){               //if we find a piece that may be killed
				for(k=i; k>=1; k++){
					inblafl=blafl;
					inwhifl=whifl;
					f=0;
					if(b[k][j]!=b[i][j] && b[k][j]!='.'){
						if(b[k][j]=='X') blafl++;
						if(b[k][j]=='O') whifl++;
						f=1;
						break;
					}
					if(k==1 && (inblafl==blafl && inwhifl==whifl)){
						if(inwhifl==whifl) whifl++;
						if(inblafl==blafl) blafl++;
					}
				}
				for(k=i; k<=dim; k++){
                                        inblafl=blafl;
                                        inwhifl=whifl;
                                        f=0;
					if(b[k][j]!=b[i][j] && b[k][j]!='.'){
                                                if(b[k][j]=='X') blafl++;
                                                if(b[k][j]=='O') whifl++;
                                                f=1;
						break;
                                        }
					if(k==dim && (inblafl==blafl && inwhifl==whifl)){
                                                if(inwhifl==whifl) whifl++;
                                                if(inblafl==blafl) blafl++;
                                        }
                                }
				for(l=j; l>=1; l++){
					inblafl=blafl;
                                        inwhifl=whifl;
                                        f=0;
                                        if(b[i][l]!=b[i][j] && b[i][l]!='.'){
                                                if(b[i][l]=='X') blafl++;
                                                if(b[i][l]=='O') whifl++;
						f=1;
                                                break;
                                        }
					if(l==1 && (inblafl==blafl && inwhifl==whifl)){
                                                if(inwhifl==whifl) whifl++;
                                                if(inblafl==blafl) blafl++;
                                        }
                                }
				for(l=j; l<=dim; l++){
					inblafl=blafl;
                                        inwhifl=whifl;
                                        f=0;
                                        if(b[i][l]!=b[i][j] && b[i][l]!='.'){
                                                if(b[i][l]=='X') blafl++;
                                                if(b[i][l]=='O') whifl++;
                                                f=1;
						break;
                                        }
					if(l==dim && (inblafl==blafl && inwhifl==whifl)){
                                                if(inwhifl==whifl) whifl++;
                                                if(inblafl==blafl) blafl++;
                                        }
                                }
                        }
			if(whifl!=blafl){	//one counter being zero is enough for that piece to be considered dead
				temp[i][j]='.';
                                lib[i-1][j-1]=0;
			}				//otherwise it's not dead, so nothing happens
                }

		for(i=1; i<=dim; i++) for(j=1; j<=dim; j++){	//iterate through the GO board b[][]
                	blafl=0;				//initiate counter for influential black pieces
			whifl=0;				//initiate counter for influential white pieces
                	if(b[i][j]=='.'){		//if we find a free (clear) playing-place
                        	for(k=i; k>=1; k--){		//check up
					if(temp[k][j]=='X'){	//if directly up is a black
						blafl++;	//count it
						break;		//stop iterating upwards
					}
					else if(temp[k][j]=='O'){ //if directly up is a white
                                                whifl++;	//count it
                                                break;		//stop iterating upwards
                                        }
                        	}
                        	for(k=i; k<=dim; k++){		//check down
					 if(temp[k][j]=='X'){	//if directly down is a black
                                                blafl++;	//count it
                                                break;		//stop iterating downwards
                                        }
                                        else if(temp[k][j]=='O'){ //if directly down is a white
                                                whifl++;	 //count it
                                                break;		//stop iterating downwards
                                        }
                        	}
                        	for(l=j; l>=1; l--){		//check left
					 if(temp[i][l]=='X'){ //if directly left is a black
                                                blafl++;	//count it
                                                break;		//stop iterating leftwards
                                        }
                                        else if(temp[i][l]=='O'){ //if directly left is a white
                                                whifl++;	//count it
                                                break;		//stop iterating leftwards
                                        }
                        	}
                        	for(l=j; l<=dim; l++){		//check right
					 if(temp[i][l]=='X'){ //if directly right is a black
                                                blafl++;	//count it
                                                break;		//stop iterating rightwards
                                        }
                                        else if(temp[i][l]=='O'){ //if directly right is a white
                                                whifl++;	//count it
                                                break;		//stop iteratign rightwards
                                        }
				}
				if(blafl!=0 && whifl==0) temp[i][j]='B';
				else if(blafl==0 && whifl!=0) temp[i][j]='W';
                	}
        	}

        	for(i=1; i<=dim; i++){				//count black and white stones while iterating, in order to determine the winner
                	for(j=1; j<=dim; j++){
                        	if(temp[i][j]=='B') blacks++;		//count free places under black territory
                	        else if(temp[i][j]=='W') whites++;	//count free places under white territory
                	}
        	}
		whites += komi;						//add komi to the whites
		score=blacks-whites;					//calculate score

       		if(score>0) printf("= B%+4.1f\n\n", score);			//print the results of the counting
        	else if(score<0) printf("= W%+4.1f\n\n", score*(-1));		//we actually want the absolute value of the "score" variable
        	else printf("= Tie\n\n");

	}

}
/* NOTE: Japanese score may still be pretty buggy, especially in seki situations, but we will change that in future versions :-) */
