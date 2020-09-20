//
//  find.c
//  CS4352_Project_2
//
//  Created by Dylan Buchheim on 5/7/20.
//  Copyright © 2020 Dylan Buchheim. All rights reserved.
//

/*----------------- DIRECTIVES ------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <string.h>
#include <time.h>

/*----------------- GLOBAL VARIABLES ------------------*/
char * full_path;

/*----------------- Read_Dir Function ------------------*/
void Read_Dir(char* subDirectory, char *name, char *mmin, unsigned long long inum, int deleteFlag){
	DIR *subDirectoryPtr = opendir(subDirectory);
	struct dirent *subDirPtr;

	if(subDirectoryPtr != NULL){
		while((subDirPtr = readdir(subDirectoryPtr)) != NULL){
			//print the name of each item in the sub directory
			//printf("%s\n",subDirPtr -> d_name);
			//setup comparison variables 
			char *temp = subDirPtr -> d_name;
			char temp1[] = ".";
			char temp2[] = "..";
			//if the current item is not the hidden file "." or ".."
			if(strcmp(temp,temp1)!=0 && strcmp(temp,temp2)!=0){
				//put a "/" in front of the current item.
				char temp3[] = "/";
				char *tempSub = temp3;
				tempSub = strcat(tempSub, temp);
				//retrieve the path of the current directory.
				char * tempFullPath = malloc(sizeof(char)*2000);
				tempFullPath = strcpy(tempFullPath, subDirectory);
				//concatenate the current subdirectory onto the current directory to get a new path.
				strcat(tempFullPath,tempSub);
				DIR * subSubDirectoryPtr = opendir(tempFullPath);
				//check to see if tempFullPath is a sub-directory
				if(subSubDirectoryPtr != NULL){
					//if tempFullPath is a sub-directory call Read_Dir with the sub directory
					closedir(subSubDirectoryPtr);
					Read_Dir(tempFullPath,name,mmin,inum,deleteFlag);
				}
				//otherwise check if the file fits the name criteria
				else if(name != NULL){
					if(strcmp(name,temp) == 0){
						if(deleteFlag == 1){
							//delete the file
							remove(tempFullPath);
							printf("Removed file: %s\n", tempFullPath);
						}else{
							printf("%s\n",tempFullPath);
						}
					}
					
				}
				//otherwise check if the file fits the minutes criteria
				else if(mmin != NULL){
					//getting the time elapsed since the last modification
					struct stat buf;
					stat(tempFullPath,&buf);
					time_t modTime = buf.st_mtime;
					int timeElapsed = (int)difftime(time(NULL),modTime)/60;
					//looking for files with more than x time elapsed 
					if(mmin[0] == '+'){
						char * subStr = &mmin[1];
						int timeCheck = atoi(subStr);
						if(deleteFlag == 1 && timeElapsed > timeCheck){
							//delete the file
							remove(tempFullPath);
							printf("Removed file: %s\n", tempFullPath);
						}else if(timeElapsed > timeCheck){
							printf("%s\n",tempFullPath);
						}
					}
					//looking for files with less than x time elapsed
					else if(mmin[0] == '-'){
						char * subStr = &mmin[1];
						int timeCheck = atoi(subStr);
						if(deleteFlag == 1 && timeElapsed < timeCheck){
							//delete the file
							remove(tempFullPath);
							printf("Removed file: %s\n", tempFullPath);
						}else if(timeElapsed < timeCheck){
							printf("%s\n",tempFullPath);
						}
					}
					//looking for files with exactly x time elapsed
					else{
						int timeCheck = atoi(mmin);
						if(deleteFlag == 1 && timeElapsed == timeCheck){
							//delete the file
							remove(tempFullPath);
							printf("Removed file: %s\n", tempFullPath);
						}else if(timeElapsed == timeCheck){
							printf("%s\n",tempFullPath);
						}
					}
				}
				//otherwise check if the file fits the i-node criteria
				else if(inum != -1){
					//getting the i-node of the current file
					struct stat buf;
					stat(tempFullPath,&buf);
					ino_t iNode = buf.st_ino;
					//if the i-node number matches inum
					if(iNode == inum){
						if(deleteFlag == 1){
							//delete the file
							remove(tempFullPath);
							printf("Removed file: %s\n", tempFullPath);
						}else{
							printf("%s\n",tempFullPath);
						}
					}
				}
				//otherwise just print the file path because this is a default find
				else{
					printf("%s\n",tempFullPath);
				}
			}
		}
		closedir(subDirectoryPtr);
	}else{
		printf("cannot open directory");
		exit(2);
	}
}

/*----------------- MAIN ------------------*/
int main(int argc, char **argv)
{
    //Local Variables
    char * dir = ".";
    char * name = NULL;
    char * mmin = NULL;
    unsigned long long inum = -1;
    int deleteFlag = 0;
    //Interpret the command line arguments.
    int count  = 1;
    while(argc > count){
    	if(strcmp(argv[count],"-name") == 0){
    		name = argv[count+1];
    		count += 2;
    	}else if(strcmp(argv[count],"-mmin") == 0){
    		mmin = argv[count+1];
    		count += 2;
    	}else if(strcmp(argv[count],"-inum") == 0){
    		inum = atol(argv[count+1]);
    		count += 2;
    	}else if(strcmp(argv[count],"-delete") == 0){
    		deleteFlag = 1;
    		count ++;
    	}else{
    		dir = argv[count];
    		count ++;
    	}
    }
    //Report the entered command line arguments.
    printf("Where-To-Look = %s, Name = %s, MMin = %s, iNum = %llu, DeleteFlag = %d\n", dir, name, mmin, inum, deleteFlag);

    Read_Dir(dir,name,mmin,inum,deleteFlag);
}
