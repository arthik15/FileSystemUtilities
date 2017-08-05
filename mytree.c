#include<stdio.h>
#include<stdlib.h>
#include<dirent.h>
#include<errno.h>
#include<unistd.h>
#include<string.h>
#include<sys/stat.h>
#include<pwd.h>

int linespace = 0;
int drawHierarchy(char* folder);

int main(int argc, char **argv)
  {

    char* folder;
    char statout[PATH_MAX + 1];

    if(argc==2) //when invoked with 1 argument from cmdline 
    folder= argv[1]; //taking that as the root
    else        //when invoked without arguments
    folder = getcwd(statout, PATH_MAX +1);  //to choose the current working directory
    //to print the directory name which is selected
    printf("\t%s \n", folder );
                             //to pass filename to the tree function
  int t_var = drawHierarchy(folder);
  }

int drawHierarchy(char* folder)
  { 
   struct dirent *st_directory; //readdir returns
   DIR *pointer;   //directory pointer
   pointer = opendir(folder); 
   //if file is opened succesfully
   if(pointer)
   {
   st_directory = readdir(pointer);
   while(st_directory)
    {	
     if(strcmp(st_directory->d_name,"..")!=0 && strcmp(st_directory->d_name,".")!=0)
      {
      struct stat statout;
      //stat variable to access stat functionality
    char * c_var = (char *) malloc(strlen(st_directory->d_name)+ strlen(folder)+2 );
    strcpy(c_var, folder);

   strcat(c_var,"/");

     strcat(c_var, st_directory->d_name);

     //to check stat success
    if(stat(c_var,&statout)==0)
     {
      int i =0;
      int d_flag=0;

    if(statout.st_mode & S_IFDIR)
    d_flag = 1;  //if it is a directory 

    while(i<linespace)
    {
      printf("      \t");
      i=i+1;
    }
    if(d_flag)
     { //to print corresponding directory and filenames
     printf("\t|______%s \n",st_directory->d_name);
     linespace=linespace+1;
     int t_var = drawHierarchy(c_var); //to call drawHierarchy recursively
     linespace=linespace-1;
     //spacing to print as per the format
     }
     else
     printf("\t|______%s \n",st_directory->d_name);
    }
     else
    printf("call to STAT failed");
   }
    st_directory = readdir(pointer);
  }
   return;	//return on file open failure
  }
   return;  //return on on function call fail
}