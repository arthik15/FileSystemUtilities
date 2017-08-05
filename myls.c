#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<time.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<pwd.h>
#include<dirent.h>
#include<errno.h>
#include<time.h>

void display(char* input_dir,int lflag)
{
 DIR *pointer;  //directory pointer
 struct dirent *st_directory;  
 // readdir() returns a structure
 pointer = opendir(input_dir);
	if(pointer)
	{
	st_directory = readdir(pointer);
	 while(st_directory!=NULL)
	  {
	char* present_dir = st_directory->d_name;
	if(strcmp(present_dir,".")!=0 && strcmp(present_dir,"..")!=0)
	{
	 if(lflag)
	 { //to append directory and filename
	   char * dir_name = (char *) malloc(strlen(present_dir)+2 + strlen(input_dir));
	   strcpy(dir_name, input_dir);
	   strcat(dir_name,"/");
	   strcat(dir_name, present_dir);
		
		struct stat statout;		
	if(stat(dir_name,&statout)==0) //to check succesful call to stat
	{			
	if(statout.st_mode&S_IFDIR) printf("d");
	else if(statout.st_mode&S_IFLNK) printf("l");
    else printf("-");
	//file permissions
	if(statout.st_mode&S_IRUSR) printf("r");
    else printf("-");
 
    if(statout.st_mode&S_IWUSR) printf("w");
    else printf("-");	
	
	if(statout.st_mode&S_IXUSR) printf("x");
    else printf("-");	
	
	if(statout.st_mode&S_IRGRP) printf("r");
    else printf("-");
	
	if(statout.st_mode&S_IWGRP) printf("w");
    else printf("-");	
	
	if(statout.st_mode&S_IXGRP) printf("x");
    else printf("-");	
	
	if(statout.st_mode&S_IROTH) printf("r");
    else printf("-");	
	
	if(statout.st_mode&S_IWOTH) printf("w");
    else printf("-");	
	
	if(statout.st_mode&S_IXOTH) printf("x.");
    else printf("-");
    
	printf(" %d",statout.st_nlink); //reference link
	printf(" %s", getpwuid(statout.st_uid)->pw_name);
	printf(" %s", getpwuid(statout.st_gid)->pw_name); 
	printf("  %lld",statout.st_size); //to display file size
	//to print the timestamp
	char* test = ctime(&(statout.st_mtim.tv_sec));
	test = &test[4];
	char* time_var = (char*)malloc(12);
	strncpy(time_var,test,12);
	strcpy(&time_var[12]," ");
	//strcat(time_var," ");
	printf(" %s",time_var);
	printf("%s \n",st_directory->d_name);	
	}
	else
	printf("\n STAT failed"); //if call to stat fails

	free(dir_name); //to free allocated memory
	}
	else
		printf("%s   ",st_directory->d_name);	 //to display directory name
	}
	st_directory = readdir(pointer);
   }
  }
    else
    printf("\n myls: cannot access");		
}

void main(int argc, char **argv)
{ 
   int lflag=0;
   char* input_dir;
   char cwd_buffer[PATH_MAX + 1];
   int blocks=0;
	
	if(argc==3)  //when it takes 3 arguments from cmd line myls -l directory
	 {
	   if(strcmp(argv[1],"-l") == 0)
	   {lflag=1;
	   input_dir=argv[2];}
	   else if(strcmp(argv[2],"-l") == 0)
	   {
		  lflag=1;
		  input_dir=argv[1];
	   }
		//printf("\n reached 3::cwd_buffer::%s lflag %d",input_dir,lflag);
	 }
	 
	 else if(argc==2)   //when it takes 2 arguments from cmd line myls -l 
	 {
		if(strcmp(argv[1],"-l") == 0)
		{  lflag=1;
		//input_dir is current input_dir
		input_dir = getcwd( cwd_buffer, PATH_MAX + 1 );
		//printf("\n reached 2::cwd_buffer::%s lflag %d",input_dir,lflag);
		}	
		  else
		  {input_dir=argv[1]; }
		 //printf("\n reached 2 else::cwd_buffer::%s lflag %d",input_dir,lflag);}
	}
		
	 else if(argc==1)   //when there is only 1 argument given
	 {
		 //input input_dir is current input_dir
		 input_dir = getcwd( cwd_buffer, PATH_MAX + 1 );
		 //printf("\n reached 1::cwd_buffer::%s lflag %d",input_dir,lflag);	 
	 }	
	 	 if(lflag)    //when -l is encountered  
	 {
	 DIR *pointer;
 struct dirent *st_directory;
 
 pointer = opendir(input_dir);
	if(pointer)
	{
	st_directory = readdir(pointer);
	 while(st_directory!=NULL)
	  {
	char* present_dir = st_directory->d_name;
	if(strcmp(present_dir,".")!=0 && strcmp(present_dir,"..")!=0)
	{
		 char * dir_name = (char *) malloc(strlen(present_dir)+2 + strlen(input_dir));
	   strcpy(dir_name, input_dir);
	   strcat(dir_name,"/");
	   strcat(dir_name, present_dir);
		
		struct stat statout;		
	if(stat(dir_name,&statout)==0) //to check if stat is successfully called
	{		
		blocks=blocks+statout.st_blocks;
	}
	}st_directory = readdir(pointer);
	  }
	  printf("total=%d\n",blocks/2); //to print 'total' in output as in ls 
	}
	 }
	 display(input_dir,lflag);
	
}