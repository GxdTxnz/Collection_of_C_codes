#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
int main(int argc,char* argv[], char* env[])
{
	pid_t pid;
	int pipefd[2];
	char* args[2] = {"/bin/sort", NULL}; //путь до sort
	if ( (-1) == pipe(pipefd) ) 
	{
		perror("pipe");
		return __LINE__;
	}
	if ( (-1) == (pid = fork())) 
	{
		perror("fork");
	} 
	else if ( pid == 0 ) 
	{
		close(pipefd[1]);
		close(0);
		dup2(pipefd[0],0);
		execve(args[0],args,env);
		perror("execve");
	} 
	else 
	{
		close(pipefd[0]);
		close(1);
		dup2(pipefd[1], 1);
		printf("Введите команду:\n");
		close(pipefd[1]);
	}
return 0;
} 
