/*
does same thing as 'sum02'
shell logic is performed by the parent process
*/
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include <stdlib.h>

int main() {
	int A[2]; // pipe A
	pipe(A);
	pid_t pid1 = fork(); // cat
	if (!pid1) {
		dup2(A[1], 1);
		close(A[0]);
		close(A[1]);
		execlp("cat","cat", "log.txt", NULL);
		exit(EXIT_FAILURE);
	}
	
	int B[2]; // pipe B
	pipe(B);
	pid_t pid2 = fork();                                       
	if (!pid2) { // cut
		dup2(A[0], 0);
		close(A[0]);
		close(A[1]); 

		dup2(B[1], 1);
		close(B[0]);
		close(B[1]);      

		execlp("cut","cut", "-f4", "-d ", NULL);
		exit(EXIT_FAILURE);                            
	}

	close(A[0]);
	close(A[1]);
	
	int C[2]; // pipe C
	pipe(C);
	
	pid_t pid3 = fork();                                       
	if (!pid3) { // sed
		dup2(B[0], 0);
		close(B[0]);
		close(B[1]);

		dup2(C[1], 1);
		close(C[0]);
		close(C[1]);

		execlp("sed","sed", "-E", "s/\\[0*([0-9]*).*/\\1/", NULL); // sed -E 's/\[0*([0-9]*).*/\1/' 
		exit(EXIT_FAILURE);                            
	}
	
	close(B[0]);
	close(B[1]);

	pid_t pid4 = fork();                                       
	if (!pid4) { // awk
		dup2(C[0], 0);
		close(C[0]);
		close(C[1]);
		execlp("awk","awk", "{sum+=$1} END {print sum}", NULL); // awk '{sum+=$1} END {print sum}'
		exit(EXIT_FAILURE);                            
	}
	
	close(C[0]);
	close(C[1]);
	waitpid(pid4, 0, 0);
}
