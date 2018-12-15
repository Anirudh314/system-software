#include<stdio.h>
#include<stdlib.h>
#include<string.h>


int check1(char word1[])
{
	char op[40],buff[40];
	FILE *fp = fopen("optab.txt", "r");

do{	
	fscanf(fp, "%s" ,op);
	if(strcmp(op,word1)==0)
	{
		return 1;
	}
	//fscanf(fp,"%[^\n]\n",buff);	
	if(strcmp(op,"END")==0)
		return 0;
}while(1);

}	

int check2(char word1[],char word2[])
{
	int d=atoi(word2);
	if(strcmp(word1,"RESB")==0)
	{
		return d;
	}
	else if(strcmp(word1,"RESW")==0)
	{
		return 3*d;
	}
	else if(strcmp(word1,"BYTE")==0)
	{
		return strlen(word2)-3;
	}
	else if(strcmp(word1,"WORD")==0)
	{
		return 3;
	}
	else
		return 0;
}


int  main()
{
	
	char line[40],word1[40],word2[40],word3[40],label[40],opcode[40],operand[40];	
	int start ,space=0,locctr=0,i,c,length,adr;


	FILE *fp1,*fp2,*fp3,*fp4,*fp5;
			
	fp1 = fopen("input.asm","r");
	fp5=fopen("input.asm","r");
	fp2=fopen("symtab.txt","w");
	fp3=fopen("out.txt","w");
	fp4=fopen("optab.dat","r");

	
	fscanf(fp1,"%[^\n]\n",line);
	
	for(i=0;i<strlen(line);i++)
	{
		if(line[i]==' ')
			space++;
	}

	space =space+1;

	if(space ==3)
	{	
		fscanf(fp5,"%s%s%x",label,opcode,&adr);
		if(strcmp(opcode,"START")==0)
		{
				start = adr;
				locctr=start;
				printf("-------%x--------",adr);
		}		
	}	
	
	fprintf(fp3,"%s\t%s\t%x\n",label,opcode,adr);
	int cou=0;
while(strcmp(opcode,"END")!=0)
{
cou++;
	space=0;
	fscanf(fp1,"%[^\n]\n",line);
	for(i=0;i<strlen(line);i++)
	{
		if(line[i]==' ')
		{
			space++;
		}
	}
	printf("%s",line);
	space+=1;
	printf("%d\n",space);	
	if(space == 3)
	{
		fscanf(fp5,"%s%s%s",label,opcode,operand);
		c=check1(opcode);	
		//printf("%d\n",c);			
		if(c==1)
		{
			
				fprintf(fp3,"%x\t%s\t%s\t%s\n",locctr,label,opcode,operand);	
			
			
			
			
			fprintf(fp2,"%s\t%x\n",label,locctr);
			locctr+=3;
		}
		else if(c==0)
		{
			c = check2(opcode,operand);
			

		
				fprintf(fp3,"%x\t%s\t%s\t%s\n",locctr,label,opcode,operand);	
			
			


			//fprintf(fp3,"%x\t%s\t%s\t%s\n",locctr,label,opcode,operand);
			fprintf(fp2,"%s\t%x\n",label,locctr);
			locctr=locctr+c;
		}
	}	
	
	if(space == 2)
	{
		fscanf(fp5,"%s%s ",word1 ,word2 );
		c= check1(word1);	
		//printf("%s%s\n",word1,word2);
		
		if(c==1)
		{
			
			fprintf(fp3,"%x\t %s \t %s \n ",locctr,word1,word2);
			locctr=locctr+3;
		}
		else if(c==0)
		{
			c = check2(word1,word2);
			if(c!=0)
			{
				
				fprintf(fp3,"%x \t %s \t %s \n",locctr,word1,word2);		
				locctr=locctr+c;	
			}
			else
			{
				
				fprintf(fp2,"%s\t%x\n",word1,locctr);
				fprintf(fp3,"%x \t %s \t%s\n",locctr,word1,word2);
				locctr=locctr+3;
			}
		}
	}
	if(space ==1)
	{
		
		fscanf(fp5,"%s",word1);		
		fprintf(fp3,"%x \t %s\n",locctr,word1);	
		printf("%s",word1);	
		locctr = locctr+3;
	}

		
			
}
length=locctr-start;

fclose(fp1);
fclose(fp2);
fclose(fp3);
fclose(fp4);
fclose(fp5);
	

return 0;
}
