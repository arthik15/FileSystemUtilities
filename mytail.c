#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<time.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<pwd.h>
#include<dirent.h>
#include<fcntl.h>
#include<linux/types.h>
#include<linux/kdev_t.h>
#include<errno.h>

int main(int argc, char **argv)
{ 
  int nof_l, f_nline=1, f_cursor=1;
  char* f_name;
  
	 if(argc==3)  //when 3 arguments taken from cmdline mytail -n filename
	 {
	   char* cof_l = argv[1];
	   
	   nof_l = atoi(&cof_l[1]); //to convert the 'no. of lines' stored in a string format to actual number
	   f_name = argv[2];
	   
	   char a = *f_name;
	   if(a=='-')
	   {printf("mytail: option used in invalid context");
	   return 0;}
	 }
	 
	 else if(argc==2) f_name = argv[1];  //when you get 2 arguments
	 else 
	 {            //when no directory name is given, single argument
	   printf("\n You have to give a directory and filename");
	   return 0;
	 }
	 
	 struct stat statout; //stat variable to check stat success and access members
	  if(stat(f_name,&statout)==0) //stat success
	  {
	    if(S_ISDIR(statout.st_mode))
	     { printf("\n mytail: error reading: Is a directory"); //when only directory name is given without filename
           return 0; 
	     }
	  }
      else printf("\n STAT failure");	  
	  //to open file with certain permissions
	 int f_pointer = open(f_name,O_RDONLY,S_IROTH);
	 if(f_pointer<=0)
	   { //file opening error
		 printf("\n Cannot open file");
		 return 0;
	   }
	   
	 char f_read[1]; //to read character one-by-one
	 int f_var = read(f_pointer,f_read,1);
		
	while(f_var!=0)
	{ //when a newline character is encountered
	  if(f_read[0] == '\n')
	  {  f_nline++;  }
  
	  f_var = read(f_pointer,f_read,1);
	}
	//goes to the starting of the file
	off_t f_endp = lseek(f_pointer,0,SEEK_SET);
		
        int ln ;
		if(nof_l==0 || nof_l>f_nline)
			ln = 1;
		else
		ln = f_nline-nof_l+1;
		
		f_var = read(f_pointer,f_read,1);
		//to go to the line from where it has to be printed
		while(f_var!=0 && f_cursor!=ln)
		{
		  if(f_read[0] == '\n')
			f_cursor=f_cursor+1;
		
		  f_var = read(f_pointer,f_read,1);
		}
		
		while(f_var!=0)
		{   //to print the desired data
			printf("%c",f_read[0]);
			f_var = read(f_pointer,f_read,1);
		}
	
	if(close(f_pointer)!=0)  //file close error
	printf("\n Closing error");
}