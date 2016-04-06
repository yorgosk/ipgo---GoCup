/* File: main.c */
#include "header.h"

int main(int argc, char* argv[]){
	char c[20], winr, kc[20],f[200];
	unsigned int seed;

	int i, j, **b, k, dim, pass=0, **lib, **marked, num, known=0,g,move=0,***unb,flag=0, japfl=0, *pas,boardflag=0,superko=0;
	float score, komi=0;
        char *comm[]={"protocol_version","name","version","known_command","list_commands","quit","boardsize",
                        "clear_board","komi","play","genmove","showboard", "final_score", "undo","fixed_handicap","place_free_handicap","set_free_handicap"};

 	if(argc>=3) if(!strcmp(argv[1], "-seed")){
		if(atoi(argv[2]) < 0){			//seed is unsigned, so it can't be less than zero (<0)
			printf("? invalid seed\n\n");
			return -1;
		}
		seed=atoi(argv[2]);		//take seed for random number generator from command line arguments
	}
        if(argc < 3){						//check if seed is has been given (when seed is given we definitely have argc==3)
                printf("? invalid seed\n\n");
                return -1;							//if seed is not valid the game can't be continued
        }
	if(argc>=3 && (!strcmp(argv[2],"-jap") || !strcmp(argv[2],"-superko"))){ //prevent careless mistakes at command line (like forgetting seed number)
		printf("? invalid seed\n\n");
                return -1;                                                      //if seed is not valid the game can't be continued
        }
        if(argc==4)
	{
		if(!strcmp(argv[3],"-jap")) japfl=1;			//check if we are requested for japanese score and mark that into a flag
		else if(!strcmp(argv[3],"-superko")) superko=1;
	}
	if(argc==5 && !strcmp(argv[4],"-superko")) superko=1;

        do{				//our main loop, where we respond to the user's primary command (e.g. play..... , play is our primary command
		flag=0;
		scanf("%s", c);		//scan for command
		/* the following block of code fixes a very serious bug in the playing sequence (playing or interacting with the board when it's not made)
		   but it seems to be causing trouble with the referee so we commended it */
		/*      if(strcmp(c,comm[6])!=0 && boardflag==0)               //ERROR : THE FIRST COMMAND IS NOT BOARDSIZE
                {
                        flag=0;
                        for(k=0; k<=16; k++)
                                 if(!strcmp(c,comm[k]))               //if it is an known command  but not boardsize
                                 {
                                         printf("? board not made\n\n");
                                         flag=1;
                                 }
                        if(flag==0) printf("? unknown command\n\n");    //if it is an unknown command  but not boardsize
                        read();                             //clear the rest of input, so that we will not be confused
                        continue;                           //read the next command
                }else if(!strcmp(c,comm[6]) && boardflag==0) boardflag=1;            //THE FIRST COMMAND IS NOT BOARDSIZE
	        */

		for(i=0; i<=16; i++){	//search for command
	                if(!strcmp(c,comm[i])){
        	                if(i==0){
                	                printf("= 2\n\n");	//protocol version
					fflush(stdout);
                        	        break;
                       		}else if(i==1){
                                	printf("= GNU Go\n\n");	//name
					fflush(stdout);
                                	break;
                        	}else if(i==2){
                                	printf("= 1.0\n\n");	//version
					fflush(stdout);
                                	break;
                        	}else if(i==3){
					scanf("%s", kc);	//name of command to be searched if it's known
					known=0;
					for(k=0; k<=16; k++) if(!strcmp(kc,comm[k])) known=1; //check if command is known
					printf("= %s\n\n", ((known==1) ? "true" : "false"));	//print result of search
					fflush(stdout);						//performance optimization
                                	break;
                        	}else if(i==4){
					printf("= ");
                                	for(j=0; j<=16; j++){                   //print list of commands
						printf("%s\n", comm[j]);
					}
					printf("\n\n");			//GTP requirement
					fflush(stdout);			//performance optimization
                                	break;
                        	}else if(i==5){
                                	printf("= \n\n");
					fflush(stdout);
                                	return 1;			//quit
                        	}else if(i==6){
                                	scanf("%d", &dim);			//get requested size of board
					if(dim>25 || dim<=1){			//chack if size is valid according to GTP specifications
						printf("? unacceptable size\n\n");
						read();                 //clear the rest of input, so that we will not be confused
						break;				//if not, go no further in this block of code
					}else printf("= \n\n");
					if((unb=malloc(1*sizeof(int**)))==NULL){                  //pinakas pou krata thn kathe kinhsh
						//printf("Memory allocation problem.\n");      //we have erased those messages because they might cause referee-trouble
                                                return -1;
                                        }
					for(k=0;k<=1;k++)
				        {
						if((unb[k]=malloc((dim+2)*sizeof(int*)))==NULL){		//dynamic memory allocation for 3d board
							//printf("Memory allocation problem.\n");      //we have erased those messages because they might cause referee-trouble
                                                	return -1;
                                        	}
						for(g=0;g<=dim+1;g++) if((unb[k][g]=malloc((dim+2)*sizeof(int)))==NULL){
									//printf("Memory allocation problem.\n");      //we have erased those messages because they might cause referee-trouble
                                                			return -1;
                                        			      }
					}
					if((lib=malloc((dim) * sizeof(int*)))==NULL){       /*dynamikh desmeush pinaka*/
						//printf("Memory allocation problem.\n");      //we have erased those messages because they might cause referee-trouble
						return -1;
					}
                                        for(k=0;k<=dim-1;k++) if((lib[k]=malloc((dim) * sizeof(int)))==NULL){	//lib is a 2d board parallel to b[][] where we store..
								//printf("Memory allocation problem.\n");	//..the current number of liberties after each move
							      	return -1;
							      }
					if((marked=malloc((dim) * sizeof(int*)))==NULL){       /*dynamikh desmeush pinaka*/
						//printf("Memory allocation problem.\n");
						return -1;					//marked[][] is a multipurpose board parallel to b[][] and lib[][]...
					}							//where, in an algorithm with "checking" element we will store...
                                        for(k=0;k<=dim-1;k++) if((marked[k]=malloc((dim) * sizeof(int)))==NULL){     //if we have checked one piece with that algorithm
								//printf("Memory allocation problem.\n");
								return -1;
							      }
					if((b=malloc((dim+2) * sizeof(int*)))==NULL){       /*dynamikh desmeush pinaka*/
						//printf("Memory allocation problem.\n");
						return -1;				//b[][] is our GO board, where the stones are really placed
					}
 					for(k=0;k<=dim+1;k++) if((b[k]=malloc((dim+2) * sizeof(int)))==NULL){
								//printf("Memory allocation problem.\n");
								return -1;
							      }
                                        if((pas=malloc(dim*sizeof(int))) == NULL){       //array tha shows  someone has played pass
                                        	//printf("Memory allocation problem.\n");
                                                return -1;
                                        }
                                        for(i=0;i<=move;i++) pas[i]=0;       //clear pas array
                                        move=0;
					boardsize(dim,b);		//create the board of the requested size
					for(k=0;k<=dim+1;k++) for(g=0;g<=dim+1;g++) unb[0][k][g]=b[k][g];	//set initial state for undo board unb[][][]
					break;
                        	}else if(i==7){
                                	printf("= \n\n");
					fflush(stdout);
					for(i=0;i<=move;i++) pas[i]=0;
					move=0;
					boardsize(dim,b);	//clear_board is basically a request for board reset, so we boardsize() again
                                	break;
                       		}else if(i==8){					//take komi's value
                                	scanf("%f",&komi);			//printf("\nkomi == %f\n\n",komi);
					printf("= \n\n");
					fflush(stdout);				//performance optimization
					break;
                        	}
				else if(i==9){
					int p=play(dim,b,lib,marked);	//call main-playing function
                                        if(p==1){                    //EDWSE PASS
						if((pas=realloc(pas,(move*dim+1)*sizeof(int)))==NULL){
							//printf("Memory allocation problem.\n");  //we have erased those messages because they might cause referee trouble
                                                        return -1;
                                                }
                                                pas[move]++;
                                                pass++;                 //remember the current number of passes from both players
                                                break;
                                        }else if(p==0){        // EKANE  KINHSH
						pass=0;
                                                move++;                          //egine kinhsh  opote shmeiwse thn
                                                if(ko(move,b,unb,dim,lib,marked,superko)==0)		// we have zero (0) when ko
                                                {
                                                        move--;				//not really a move
                                                        printf("? illegal move\n\n");	//error motification according to GTP
                                                        break;				//don't create undo board state
                                                }
						printf("= \n\n");         //if we dont have KO OR SUPERKO
						if((unb=realloc(unb,(move+10)*sizeof(int**)))==NULL){
							//printf("Memory allocation problem.\n");  //we have erased those messages because they might cause referee-trouble
                                                	return -1;
                                        	}
                                                if((unb[move]=malloc((dim+2)*sizeof(int*)))==NULL){     //create space to add new board state to list of boards in undo
                                                	//printf("Memory allocation problem.\n");      //we have erased those messages because they might cause referee-trouble
                                                	return -1;
                                        	}
						for(g=0; g<=dim+1; g++) if((unb[move][g]=malloc((dim+2)*sizeof(int)))==NULL){
										//printf("Memory allocation problem.\n");      //we have erased those messages because they might cause referee-trouble
                                                				return -1;
                                        				}
						for(k=0;k<=dim+1;k++) for(g=0;g<=dim+1;g++) unb[move][k][g]=b[k][g];       //dimhourgia unb
						if((pas=realloc(pas,(move*dim+1)*sizeof(int)))==NULL){
							//printf("Memory allocation problem.\n");  //we have erased those messages because they might cause referee trouble
                                                        return -1;
                                                }
                                                pas[move]=0;                    //efoson paixthke kinhsh
						break;
					}else if(p==-1) break;                   //FOR INVALID COLOR OR INVALID COORDINATE
                        	}else if(i==10){
					move++;
					if((pas=realloc(pas,(move*dim+1)*sizeof(int)))==NULL){
                                                 //printf("Memory allocation problem.\n");  //we have erased those messages because they might cause referee trouble
                                                 return -1;
                                        }
                                        if(genmove(dim,b, lib, marked, move,unb,seed,superko,japfl,komi,pass))		//call genmove function
                                        {
						move--;
						pas[move]++;
                                                pass++;			//if we are here, we have pass
                                                break;
                                        }
					else
					{
						pas[move]=0;
						pass=0;			//if one move is not pass, pass-sequence is equal to 0 (zero)
						if((unb=realloc(unb,(move+10000)*sizeof(int**)))==NULL){               //create space for new undo-board-state
                                        		//printf("Memory allocation problem.\n");      //we have erased those messages because they might cause referee-trouble
                                                	return -1;
                                        	}
						if((unb[move]=malloc((dim+2)*sizeof(int*)))==NULL){
							//printf("Memory allocation problem.\n");      //we have erased those messages because they might cause referee-trouble
                                                	return -1;
                                        	}
                                        	for(g=0;g<=dim+1;g++) if((unb[move][g]=malloc((dim+2)*sizeof(int)))==NULL){
									//printf("Memory allocation problem.\n");      //we have erased those messages because they might cause referee-trouble
                                                			return -1;
                                        			      }
						for(k=0;k<=dim+1;k++) for(g=0;g<=dim+1;g++)  unb[move][k][g]=b[k][g];	//store board-state
					}
					break;
                        	}else if(i==11){
                                	printf("= \n");
					fflush(stdout);
					showboard(dim, b);		//GTP valid printing of the GO board
					printf("\n\n");
                                	break;
                        	}else if(i==12){
					if(japfl){			//if we want japanese score, give japanese score
						final_score(dim,b,lib,japfl,marked,komi);	 //work with the japanese score to determine the winner
						break;	      //'break's are generally used to track i values differiantion and be able to respond at unknown commands
					}else{
						score=final_score(dim, b, lib, japfl,marked,komi);	//find the final score
						if(score<0){			//determine winner or if it's tie
                                                	winr='W';
							score *= -1.0;
                                        	}else if(score>0){
                                                	winr='B';
                                                	score *= 1.0;
                                        	}else winr=' ';			//tie
						printf("= %c%+4.1f\n\n", winr, score);	//print result with final score
						fflush(stdout);					//performance optimization
						break;
					}
				}else if(i==13){                        //for undo command
                                        if(move==0)
                                        {
                                                if(pas[move]>0)
                                                {
                                                        printf("= \n\n");
                                                        pas[move]--;
                                                        break;
                                                }
                                                printf("? cannot undo\n\n");    //if no move (start of the game), cannot undo
                                                break;
                                        }
                                        else if(pas[move]>0)                //exoun ginei pass
                                        {
                                                printf("= \n\n");
                                                        pas[move]--;       //meiwse ta
                                                        break;

                                        }
                                        else
                                        {
                                                move--;
                                                undo(b,unb,move,dim);           //change board-state (go to previous board-state)
                                                printf("= \n\n");
                                                fflush(stdout);                 //performance optimization trick
                                                countlib( dim, b, lib, marked); //re-count liberties
                                                break;
                                        }
                                }
				else if(i==14){                      //FIXED_HANDICAP
					scanf("%d", &num);
                                        if(checkboard(b,dim)==0)break;      //NOT EMPTY BOARD
                                        if(num < 0 || num > 9 || dim < 7 || (dim%2==0 && num > 4)  || (dim==7 && num > 4) )        //OXI handicap se boardsize < 7
                                        {
                                                printf("? invalid number of stones\n\n");
                                                read();                 //clear the rest of input, so that we will not be confused
                                        }
                                        else
                                        {
                                                printf("=");
                                                fixedhandicap(dim, b, lib, num);       //BALE TIS PETRES STON BOARD
                                                for(k=1;k<=dim;k++)for(g=1;g<=dim;g++)
                                                {
                                                         if(b[k][g]=='X') printf(" %c%d",(k<9)? (k+'A'-1) :(k+'A'),dim-g+1);           // ektypesh tesewn handicap
                                                         unb[0][k][g]=b[k][g];          //to telaiuteo nomimo undo tha kataligei ston pinaka me ta handicap
                                                }printf("\n\n");
                                        }
                                        fflush(stdout);                 //the known by now performance optimization trick
                                        break;
                                }else if(i==15){                      //PLACE_FREE_HANDICAP
                                        scanf("%d", &num);              //number of handicap stones to be generated
                                        if(checkboard(b,dim)==0) break;      //NOT EMPTY BOARD
                                        else
                                        {
                                                placefreehandicap(dim, b, lib, num, seed);       //BALE TIS PETRES STON$
                                                for(k=0;k<=dim+1;k++) for(g=0;g<=dim+1;g++) unb[0][k][g]=b[k][g];
                                        }
                                        fflush(stdout);
                                        break;
                                }
                                else if(i==16){
                                        if(checkboard(b,dim)==0)break;     //NOT EMPTY BOARD
                                        if(setfreehandicap(b,dim)==1)          //lathos
                                        {
                                                boardsize(dim,b);   //CLEAR_BOARD
                                                printf("? bad vertex list\n\n");
                                                fflush(stdout);
                                                read();                 //clear the rest of input, so that we will not be confused
                                        }
                                        else
                                        {
                                                printf("= \n\n");
                                                fflush(stdout);
                                                for(k=0;k<=dim+1;k++) for(g=0;g<=dim+1;g++) unb[0][k][g]=b[k][g];
                                        }
                                        break;
                                }
                	}
        	}
	//	printf("pass == %d \n\n",pass);
        	if(i>16){
			printf("? unknown command\n\n");
			read();
		}
		fflush(stdout);					//performance optimization
	}while(1);

	for(k=0; k<=dim-1; k++) free(lib[k]);                     //free any memory we have dynamically allocated so far
	free(lib);
	for(k=0; k<=dim-1; k++) free(marked[k]);
	free(marked);
	for(k=0; k<=dim+1; k++) free(b[k]);
	free(b);
	for(i=0;i<move;i++)
	{
        	for(j=0;j<dim+1;j++)
        	{
                	free(unb[i][j]);
        	}
        	free(unb[i]);
    	}
    	free(unb);
	free(pas);

	return 0;
}
/* We added  fflush(stdout);  and the  read();  because we observed that, without them, the program wasn't co-operating well with the referees
and wasn't responding well in invalid commands, so the stdin and stdout, respectively, needed a cleaning. */
