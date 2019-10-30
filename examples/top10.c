// example of running 'cat top10.c | grep if'
// to compile type 'gcc top10.c -o top10'
// to run type './top10'
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include <stdlib.h>

int main() {
	int fd[2], status;                                         
	// creating unnamed pipe
	pipe(fd);

	// cloning the parent
	pid_t pid1 = fork();                
		       
	if (!pid1) {
		// child this process is going to write to pipe
		// redirecting STDOUT (fd==1) to pipe
		dup2(fd[1], 1);
		// closing both ends of the pipe
		close(fd[0]);
		close(fd[1]);      
		// execute cat
		char* command[3] = {"/bin/cat", "top10.c", NULL};
		execv(command[0], command);
		exit(EXIT_FAILURE);
	} else if (pid1 == -1) {                                   
		// fork() returns -1 upon error
		fprintf(stderr, "Can't fork, exiting...\n");           
		exit(EXIT_FAILURE);
	}                                                          

	pid_t pid2 = fork();                                       
	if (!pid2) {
		// child process is going to read from pipe
		// redirecting STDIN (fd==0) to pipe                                               
		dup2(fd[0], 0);
		close(fd[0]);
		close(fd[1]); 
		// execute grep
		char* command[4] = {"/bin/grep", "--color=auto", "if", NULL};
		execv(command[0], command);
		exit(EXIT_FAILURE);                            
	} else if (pid2 == -1) {             
		fprintf(stderr, "Can't fork, exiting...\n");
		exit(EXIT_FAILURE);
	}
	close(fd[0]);
	close(fd[1]);
	// wait for child process to exit
	waitpid(pid1, NULL, 0);                                 
	waitpid(pid2, &status, 0);                       
	// exit with the exit status of grep
	exit(status);
}
