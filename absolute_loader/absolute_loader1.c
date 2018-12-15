
#include<stdio.h>

#include<string.h>
char input[10],label[10],ch1,ch2;
int addr, w=0, start, ptaddr, l, length=0, end, count=0, k, taddr, address, i=0;
FILE *fp1,*fp2,*fp3;
void check();
void main()
{ 
  fp1=fopen("INPUT1.txt","r");
  fp2=fopen("OUTPUT.txt","w");
  fp3=fopen("input.txt","w");
 
 char ch;	
 while((ch=getc(fp1))!=EOF)
 {
	if(ch=='^')
		fprintf(fp3," ");
	else
		fprintf(fp3,"%c",ch);
 }
	fclose(fp1);
	fclose(fp3);
	fp1=fopen("input.txt","r");	
	


  fscanf(fp1,"%s",input);

  while(strcmp(input,"E")!=0)
  {
   if(strcmp(input,"H")==0)
   {
    fscanf(fp1,"%s %x %x %s",label,&start,&end,input);
    address=start;
   }
   else if(strcmp(input,"T")==0)
   {
    l=length;
    ptaddr=addr;//previous tddr
    fscanf(fp1,"%x %x %s",&taddr,&length,input);
    addr=taddr;
    if(w==0)
    {
     ptaddr=address;
     w=1;
    }
    for(k=0;k<(taddr-(ptaddr+l));k++)  //current addr - previous addr + len 
    {
     address=address+1;
     fprintf(fp2,"xx");
     count++;
     if(count==4)
     {
      fprintf(fp2,"  ");
      i++;
      if(i==4)
      {
       fprintf(fp2,"\n\n%x\t\t",address);
       i=0;
      }
      count=0;
     }
    }
    if(taddr==start)
     fprintf(fp2,"\n\n%x\t\t",taddr);
    fprintf(fp2,"%c%c",input[0],input[1]);
    check();
    fprintf(fp2,"%c%c",input[2],input[3]);
    check();
    fprintf(fp2,"%c%c",input[4],input[5]);
    check();
    fscanf(fp1,"%s",input);
   }
   else
   {
    fprintf(fp2,"%c%c",input[0],input[1]);
    check();
    fprintf(fp2,"%c%c",input[2],input[3]);
    check();
    fprintf(fp2,"%c%c",input[4],input[5]);
    check();
    fscanf(fp1,"%s",input);
   }
  }
  fprintf(fp2,"\n-+\n");
 fclose(fp1);
  fclose(fp2);
  printf("\n\n The contents of output file:\n\n");
  fp2=fopen("OUTPUT.txt","r");
  ch2=fgetc(fp2);
  while(ch2!=EOF)
  {
   printf("%c",ch2);
   ch2=fgetc(fp2);
  }
  fclose(fp1);
  fclose(fp2);

}
void check()
{
  count++;
  address++;
  taddr=taddr+1;
  if(count==4)
  {
   fprintf(fp2,"  ");
   i++;
   if(i==4)
   {
    fprintf(fp2,"\n\n%x\t\t",taddr);
    i=0;
   }
   count=0;
  }
}

