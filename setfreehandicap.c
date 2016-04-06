#include <stdio.h>
#include <string.h>
int setfreehandicap(int **b,int dim)
{	int i=0,flag=0,x,y,z,ch;
	char s[5];

	do{
		scanf("%s",s);
		i++;                         //METRHTHS GIA TA VERTICES
		if(strlen(s)>3 || i>(dim*dim)-1 || s[0]=='I' || s[0]=='i') return 1;
		if((s[0]>'I' && s[0]<'a') || s[0]>'i') s[0]--;

		if(s[0]>='A' && s[0]<='Z') x=s[0]-'A'+1;
                else if(s[0]>='a' && s[0]<='z') x=s[0]-'a'+1;
		if(strlen(s)==3)
		{
                        y=s[1]-'0';
                        z=s[2]-'0';
                        y=dim+1-(10*y+z);
                }
		else y=dim+1-(s[1]-'0');                    /*ascii code '1'=49*/

		if(y>=1 && y<=dim && x>=1 && x<=dim && b[y][x]=='.') b[y][x]='X';
		else return 1;
		do{
			ch=getc(stdin);
			if(ch=='\n')
			{
				flag=1;
				break;
			}
		}while(isspace(ch));                //oso to ch einai white space diabase to

		if(flag==0) ungetc(ch,stdin);                           //an teleiwsei kai exei kana gramma to ch prepei na to epistrepsei sto reyma eisodou

	}while(flag==0);

return 0;
}
//if the function return 1  means that something is wrong but if the function return 0 means that the stones are placed on the board
