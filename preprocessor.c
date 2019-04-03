#include <stdio.h>
#include <string.h> 
#include <unistd.h>
#include <stdlib.h> // For exit() 
char inc[8]="include", output[30];
int main() 
{       
	int t=1,check=1;
	FILE *fptr1, *fptr2, *fptr3; 
	char filename[50],c,h,inc2[8];

	printf("Enter the filename to open for reading \n"); 
	scanf("%s", filename); 

	// Open one file for reading 
	fptr1 = fopen(filename,"r"); 
	char ttt[3]={'.','i','\0'};
	if (fptr1 == NULL) 
	{ 
		printf("Cannot open file %s \n", filename); 
		exit(0); 
	} 
    int temp=0;
    while(filename[temp]!='.' && filename[temp+1]!='c'){
    	output[temp]=filename[temp];
    	printf("%c\n",output[temp] );
    	temp++;
    	output[temp]='\0';
    	if(filename[temp]=='.' && filename[temp+1]=='c')
    	{
    		strcat(output,ttt);
    	}
    }
    
    
    
	//Open another file for writing 
	fptr2 = fopen(output, "w"); 
	if (fptr2 == NULL) 
	{       
                 
		printf("Cannot open file %s \n",output); 
		exit(0); 
	} 

	// Read contents from file 	
        c = fgetc(fptr1); 
	while (c != EOF) 
	{ 
        if(c=='#'){
	        memset(inc2,0,8);
	        for(int i=0;i<=6;i++){
	              c=getc(fptr1); 
	              inc2[i]=c;
	               
	           }
	           inc2[7]='\0';
	        int s = strcmp(inc,inc2);
	        if(s==0)
	        {
	         while (t)
	         {
	           int f=0,x=0;
	           c=fgetc(fptr1);
	           if(c=='<' || c=='"'){
	           	
	              c=fgetc(fptr1);
	              while(c!='>' && c!='"'){
                      x++;
	                  c=fgetc(fptr1);
	                  
			        }
                     fseek(fptr1,-(x+1),SEEK_CUR);
			         c=fgetc(fptr1);
			         char lib[x+1]; 
				         for(int i=0;i<sizeof(lib)-2;i++){
                            if(c!='>'){
                            	lib[i]=c;
                            	c=fgetc(fptr1);
                                 }
                             }
                        char tt[2]={'h','\0'};
                        strcat(lib,tt);
				        c=fgetc(fptr1);
				        f++;check++;
				        
			        
			        t=0;
			        c='\0';
	             char path[]="/usr/include/";
	             fptr3 = fopen(strcat(path,lib),"r");
	             if(!fptr3){
                     
		             fptr3 = fopen(lib,"r");
	             }
	             h = fgetc(fptr3);
	             while(h!=EOF){
                   fputc(h,fptr2);
                   h = fgetc(fptr3);
	            }
               }
	          }
	          t=1;
	        }
	        else{
	          fseek(fptr1,-7,SEEK_CUR);
	          fputc('#',fptr2);
	          c=getc(fptr1);
	        }	
        }
        else if(c=='/'){
        	c=fgetc(fptr1);
        	if(c=='/'){
        		while(c!='\n'){
        			c=fgetc(fptr1);
        		}
        	}
        	else if(c=='*')
        	{
        		c=fgetc(fptr1);
        		while(t)
        		   {
        			if(c=='*'){
        			c=fgetc(fptr1);
        			if(c=='/')
        			{
                     t=0;
        			}
        		}
                c=fgetc(fptr1); 
        	}
        	}
        }
        else{
        	fputc(c, fptr2); 		
            c = fgetc(fptr1); 
        }
	} 

	printf("\nContents copied to %s", output); 
	fclose(fptr1); 
	fclose(fptr2); 
	return 0; 
}
