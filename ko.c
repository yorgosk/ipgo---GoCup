int ko(int move,int **b,int ***unb,int dim,int **lib,int **marked,int superko) {
	int k,g,flag=0;

	if(move>2){			//to check for ko, at least 2 move need to have happened
       		 for(k=0;k<=dim+1;k++){
                        for(g=0;g<=dim+1;g++){
                               if(unb[move-2][k][g]!=b[k][g]){ //if even a part of the current board-state is not the same as 2 board-states before...
                                     flag=1;			//...(previous play of the current player)
                                     break;			//mark it and...
                               }
                        }
                        if(flag==1) break;			//...stop searching
                 }
         	 if(flag==0)				//AN EXOUME KO
          	 {
         		for(k=0;k<=dim+1;k++) for(g=0;g<=dim+1;g++) b[k][g]=unb[move-1][k][g];	//return board to previous state
         		countlib(dim, b, lib, marked);				//refresh liberties' board
			return 0;
                 }
        }else return 1;			//return 1 so we know where the problem is (less than 2 moves)

	if(superko==1)
	{
        	int i;
        	for(i=0; i<move; i++)			//iterate undo-board and check previous board-states
        	{
        		flag=0;
                	for(k=1;k<=dim+1;k++)
                	{
                        	for(g=1;g<=dim+1;g++)
                        	{
                                	if(unb[i][k][g] != b[k][g]){ //if even a part of the current board-state is not the same as 2 board-states before...
						flag=1;			//...(previous play of the current player)
						break;			//mark it and...
					}
                        	}
                        	if(flag==1) break;			//...stop searching
                	}
        		if(flag==0)			//AN EXOUME SUPERKO
        		{
	                	for(k=0;k<=dim+1;k++) for(g=0;g<=dim+1;g++) b[k][g]=unb[move-1][k][g];  //return board to previous state
                        	countlib(dim, b, lib, marked);                          //refresh liberties' board
                		return 0;
	        	}
		}
	}

        return flag;
}
