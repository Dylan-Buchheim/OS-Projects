#include<stdio.h>
#include<stdlib.h>

int main(int argc, char *argv[]){
	//Test to see if there was an arguement provided.
	if(argc != 2){
		printf("Expecting one arguement for the number of child processes to create.\n");
	//If there was an arguement, create the corresponding number of child processes.
	}else{
		int numOfProcesses = atoi(argv[1]);
		int i;
		for(i=0;i<numOfProcesses;i++){
			int pid = fork();
			//If child process creation fails.
			if(pid < 0){
				printf("Child creation failed!\n");
			//Child process code block.
			}else if(pid == 0){
				printf("Hello from child %d whose parent is %d\n",getpid(),getppid());
				exit(0);
			//Parent process code block.	
			}else{
				wait(NULL);
			}
		}
		exit(0);
	}
}
