#include<stdio.h>
#include<stdlib.h>

int main(int argc, char *argv[]){
	//Test to see if there was an argument provided.
	if(argc != 2){
		printf("Expecting one arguement for the number of child processes to create.\n");
	//If there was, call the CreateChild function with the corresponding number of processes.
	}else{
		int numOfProcesses = atoi(argv[1]);
		CreateChild(numOfProcesses);
	}
	return 0;
}

int CreateChild(int numOfProcesses){
	//If all the child processes have been created, exit to allow ancestors to finish.
	if(numOfProcesses == 0){
		return 0;
	}
	int pid = fork();
	//Child creation failed.
	if(pid < 0){ 
		printf("Child creation failed!\n");
	//Child process block.
	}else if(pid == 0){
		printf("Hello from child %d whose parent is %d\n", getpid(), getppid());
		//Decrement the numberOfProcesses to create and call CreateChild with the new value.
		int x = numOfProcesses - 1;
		CreateChild(x);
		exit(0);
	//Parent process block.	
	}else{			
		wait(NULL);
	}
	return 0;
}
