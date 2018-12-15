#include<stdio.h>
#include<string.h>
#include<stdlib.h>

int search(char line[])
{
	int i;
	int n = strlen(line);int count=1;
	for(i=0;i<n;i++)
	{
		if(line[i]==' ')
			count++;
	}
	return count;
}
int main()
{
FILE *fp1,*fp2,*fp3,*fp4,*fp5;
char line[30],addr[30],buff[30],symbol[30],endr[30],label[30],opcode[30],operand[30],loc[30],w[30],c;
int num,len,actual_len,add,i,flag=0,p,l,t=0,j,cr=0,ct=0,rmdr,len1,adc;
char mnemonic[15][15]={"LDA","STA","LDCH","STCH"};
char code[15][15]={"33","44","53","57"};

fp1 = fopen("intermediate.txt","r");
fp2 = fopen("intermediate.txt","r");
fp3 = fopen("optab.txt","r");
fp4 = fopen("symtab.txt","r");
fp5 = fopen("object.txt","w");



//header record

fscanf(fp1,"%s",addr);
//printf("%s\n",addr);

rewind(fp1);
fprintf(fp5,"H^%s^",addr);

fscanf(fp1,"%[^\n]\n",line);


	fscanf(fp1,"%s",addr);
	strcpy(endr,addr);
	//printf("%s\n",addr);
	for(i=0;i<6-strlen(addr);i++)
		fprintf(fp5,"0");
	fprintf(fp5,"%s^",addr);
	while(fscanf(fp1,"%[^\n]\n",line)!=EOF)
	{
		fscanf(fp1,"%s",addr);
		ct++;
	}
	//printf("%s\n",addr);
	for(i=0;i<6-strlen(addr);i++)
		fprintf(fp5,"0");
		
	fprintf(fp5,"%s\n",addr);
	//strcpy(endr,addr);
	//fscanf(fp2,"%s%s%s",label,opcode,operand);
	
	
	
	
	rewind(fp1);
	while(fscanf(fp1,"%s",line)!=EOF)
	{
		if((strcmp(line,"RESW")==0)||(strcmp(line,"RESB")==0))
			cr++;
	}
	rewind(fp1);
	fscanf(fp1,"%[^\n]\n",line);
	fscanf(fp2,"%s%s%s",label,opcode,operand);
	fprintf(fp5,"\nT^");
	//
	printf("------------##############%d",cr);
	j=ct-cr-1;
	j=j*6;
	if(j<69)
	{
		fprintf(fp5,"%x^",j+3);
	}
	else
	{
		fprintf(fp5,"%x^",69);
		rmdr = j/69; //rmdr contains no of text records to be made 
	}	printf("-----------------%d===============",j);
	//j=j+3*rmdr;
	
	adc=3;
	//fscanf(fp1,"%[^\n]\n",line);
	//printf("%s",line);
	while(1)
	{
		if(adc%69==0)
		{
			printf("-----------------%d===============",j);
			fprintf(fp5,"\n");
			j=j-66;
			if(j>69)
			{
				fprintf(fp5,"\nT^");
				fprintf(fp5,"%x^",69);
				adc=adc+3;
			
			}
			else
			{
				fprintf(fp5,"\nT^");
				fprintf(fp5,"%x^",j+3);
			
				adc=adc+3;
			
			
			}
			
		}
		rewind(fp3);
		if((fscanf(fp1,"%[^\n]\n",line)==EOF))
		{
			t=1;	
		}
		//printf("%d",search(line));
		

		l =search(line);
		printf("line _space =%d\n",l);


		if(l==4)// label - opcode - operand
		{
		printf("a\n");
			//printf("line space=%d",search(line));
			fscanf(fp2,"%s%s%s%s",loc,label,opcode,operand);
			printf("%s\t%s\t%s\t%s\t\n",loc,label,opcode,operand);
			if(strcmp(opcode,"END")==0)//||strcmp(label,"END")==0||strcmp(operand,"END")==0)
				break;
				
			if(strcmp(opcode,"BYTE")==0)
   			{
   				printf("1");
			 	len=strlen(operand);
			 	if((strcmp(operand,"C'EOF'")==0)||(strcmp(operand,"c'eof'")==0))
			 	{	fprintf(fp5,"454F46^");
			 		adc=adc+6;
			 	}
			 	else
			 	{
			 		for(i=0;i<6-len+3;i++)
			 			fprintf(fp5,"0");
			 			
			 		len=atoi(operand);//put the number
			 		printf("\n \t\t number = %d \t %s \n" ,len,operand); 
			 		
			 		for(i=2;i<strlen(operand)-1;i++)
			 		fprintf(fp5,"%c",operand[i]);
			 		adc=adc+6;
			 	fprintf(fp5,"^");
			   	}

			}
  			
  			else if(strcmp(opcode,"WORD")==0)
  			{
  				printf("2");
  				len=atoi(operand);
    				//itoa(atoi(operand),buff,10);
    				fprintf(fp5,"00000%x^",len);
    				adc=adc+6;
    			}//
    			else if((strcmp(opcode,"RESB")==0)||(strcmp(opcode,"RESW")==0))
    			{
    				//NO opcode for these two
    				printf("no opcode");
    			}
    			else
    			{	printf("\n\t3\t\n");
    				
				while(fscanf(fp3,"%s%s",buff,loc)!=EOF)
				{
					if(strcmp(opcode,buff)==0)
					{
						printf("4");
						break; 
					}
				}
				rewind(fp4);
				fscanf(fp4,"%s%s",symbol,addr);
				while(strcmp(operand,symbol)!=0)
				{
					if(fscanf(fp4,"%s%s",symbol,addr)==EOF)		
						break;
					if(strcmp(operand,symbol)==0)
					{
						flag=1;
					}
				}
				if(flag==1)
				{
				
									
					//fprintf(fp5,"%s00%s^",loc,addr);
					fprintf(fp5,"%s",loc);
					len1=strlen(addr)+2;
					for(i=0;i<6-len1;i++)
					{
						printf("--------------iter-------------");
						fprintf(fp5,"0");
					}len1=0;
						fprintf(fp5,"%s^",addr);
					flag=0;
					adc=adc+6;
				}
				
				rewind(fp3);
				

		

			}
			
		}
	
		if(l==3) //opcode - operand 
		{
			printf("b\n");
			rewind(fp3);
			//printf("line space=%d",search(line));
			fscanf(fp2,"%s%s%s",loc,opcode,operand);
			//printf("%s\t%s\t%s\t\n",loc,opcode,operand);
			while(fscanf(fp3,"%s%s",buff,loc)!=EOF)
			{
				if(strcmp(opcode,buff)==0)	
				{	
					break;
				}
							
				fscanf(fp4,"%s%s",symbol,addr);
			}
			rewind(fp4);
			while(strcmp(operand,symbol)!=0)
			{
				if(fscanf(fp4,"%s%s",symbol,addr)==EOF)
					break;
			}
			//fprintf(fp5,"%s00%s^",loc,addr);
			fprintf(fp5,"%s",loc);
					len1=strlen(addr)+2;
					for(i=0;i<6-len1;i++)
					{
						printf("--------------iter-------------");
						fprintf(fp5,"0");
					}len1=0;
			fprintf(fp5,"%s^",addr);
			adc=adc+6;
			
		}
		
		if(l==2)
		{
			printf("c\n");
			fscanf(fp2,"%s%s",buff,opcode);
			rewind(fp3);
			while(fscanf(fp3,"%s%s",buff,loc)!=EOF)
			{
				if(strcmp(opcode,buff)==0)	
					break;
			}
			fprintf(fp5,"%s0000^",loc);
			adc=adc+6;
		}
	
	if(t==1)
		break;		
		
	}
	
	//end record	
t=strlen(endr);
fprintf(fp5,"\nE^");
	for(i=0;i<6-t;i++)
	{	
		fprintf(fp5,"0");
		
	}
	fprintf(fp5,"%s",endr);

	fclose(fp5);	
	fclose(fp1);
	
return 0;
}
	


