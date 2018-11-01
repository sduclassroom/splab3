/*
does same thing as 'sum01'
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
		execlp("cut","cut","-f1","-f9", "-d ", "log.txt", NULL);
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

		execlp("awk","awk", "-F ", "$2~\"^3\"", NULL);
		exit(EXIT_FAILURE);                            
	}
	
	close(A[0]);
	close(A[1]);
	
    
	int C[2]; 
	pipe(C);
	pid_t pid3 = fork();  // uniq -cf1 | sort | tail -r -10
	if (!pid3) { // sed
		dup2(B[0], 0);
		close(B[0]);
		close(B[1]);
		
		dup2(C[1], 1);
		close(C[0]);
		close(C[1]);

		execlp("uniq","uniq", "-cf1", NULL); // sed -E 's/\[0*([0-9]*).*/\1/'
		exit(EXIT_FAILURE);                            
	}
	
	
	// closing pipe ends that are no more used
	close(B[0]);
	close(B[1]);

	int D[2]; 
	pipe(D);
	pid_t pid4 = fork();                                       
	if (!pid4) { // sed
		dup2(C[0], 0);
		close(C[0]);
		close(C[1]);
		
		dup2(D[1], 1);
		close(D[0]);
		close(D[1]);

		execlp("sort", "sort", NULL); // sed -E 's/\[0*([0-9]*).*/\1/'
		exit(EXIT_FAILURE);                            
	}
	
	
	// closing pipe ends that are no more used
	close(C[0]);
	close(C[1]);




	int E[2]; 
	pipe(E);
	
	pid_t pid5 = fork();                                       
	if (!pid5) {
		dup2(D[0], 0);
		close(D[0]);
		close(D[1]);
		
		dup2(E[1], 1);
		close(E[0]);
		close(E[1]);

		execlp("tail", "tail", "-r", "-10", NULL); 
		exit(EXIT_FAILURE);                            
	}
	
	close(D[0]);
	close(D[1]);

	int F[2];
	pipe(F);
	
	pid_t pid6 = fork();                                       
	if (!pid6) { // sed
		dup2(E[0], 0);
		close(E[0]);
		close(E[1]);
		execlp("awk", "awk", " {printf $2 \"\\n\"}", NULL);
		exit(EXIT_FAILURE);                            
	}
	
	
	close(E[0]);
	close(E[1]);

	waitpid(pid6, 0, 0);
	
}
