#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<linux/types.h>
#include<linux/kdev_t.h>
#include<pwd.h>

int main(int argc, char **argv)
{  
	struct stat statout;  //stat variable to access members
	
	if(stat(argv[1],&statout)==0) // stat() function returns 0 on success
	{
printf("\n  File: '%s'",argv[1]);
printf("\n  Size: %d",statout.st_size); //to display file size
printf("\t\t Blocks: %d",statout.st_blocks); //number of blocks
printf("\t\t IO Block: %d",statout.st_blksize);
//printf("\n Device: %uh/%ud",major(statout.st_dev),minor(statout.st_dev));
printf("\t\t FileInode: %ld",statout.st_ino);  //file inode
printf("\t\tlinks: %d",statout.st_nlink);      //reference(link) count
printf("\nFile permissions :");               
printf("\nAccess: (%lo/",statout.st_mode); 
	//file permissions
	if(S_ISDIR(statout.st_mode)) printf("(d");
    else printf("(-");
		
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
	
	if(statout.st_mode&S_IXOTH) printf("x)");
    else printf("-)");
    //to print owner
	printf("\tUid: (%d/ ",statout.st_uid); 
	printf("\t%s)", getpwuid(statout.st_uid)->pw_name);
	printf("\tGid: (%d/",statout.st_gid); 
	printf("\t%s)", getpwuid(statout.st_gid)->pw_name); 
	printf("\n");
}
    else   //when calling stat fails
	{	printf("\n mystat: missing operand");
        return 0;
	}
}