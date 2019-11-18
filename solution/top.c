#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char* argv[]) {

	int A1[2]; // pipe A1
	pipe(A1);
	pid_t pid12 = fork(); // cut
	if (!pid12) {
		dup2(A1[1], 1);
		close(A1[0]);
		close(A1[1]);
		execlp("cut","cut", "-d", "\"", "-f4,5,6", argv[2], NULL); //cut -d '"' -f4,5,6 $2
		exit(EXIT_FAILURE);
	}
	int B1[2]; // pipe B1
	pipe(B1);
	pid_t pid13 = fork();                                       
	if (!pid13) { // cut
		dup2(A1[0], 0);
		close(A1[0]);
		close(A1[1]); 

		dup2(B1[1], 1);
		close(B1[0]);
		close(B1[1]);      

		execlp("grep","grep", "-v", "\\-\"", NULL); //grep -v '\-"'
		exit(EXIT_FAILURE);                            
	}

	close(A1[0]);
	close(A1[1]);

	int C1[2]; // pipe C1
	pipe(C1);
	pid_t pid14 = fork();                                       
	if (!pid14) { // sed
		dup2(B1[0], 0);
		close(B1[0]);
		close(B1[1]);

		dup2(C1[1], 1);
		close(C1[0]);
		close(C1[1]);

		execlp("cut","cut", "-d", "\"", "-f3", NULL); // cut -d '"' -f3
		exit(EXIT_FAILURE);                            
	}
	
	close(B1[0]);
	close(B1[1]);

	int D1[2]; // pipe D1
	pipe(D1);
	
	pid_t pid15 = fork();                                       
	if (!pid15) {
		dup2(C1[0], 0);
		close(C1[0]);
		close(C1[1]);

		dup2(D1[1], 1);
		close(D1[0]);
		close(D1[1]);

		execlp("cut","cut", "-d", "/", "-f1", NULL); // cut -d '/' -f1
		exit(EXIT_FAILURE);                            
	}
	
	close(C1[0]);
	close(C1[1]);

	int E1[2]; // pipe E1
	pipe(E1);
	
	pid_t pid16 = fork();                                       
	if (!pid16) {
		dup2(D1[0], 0);
		close(D1[0]);
		close(D1[1]);

		dup2(E1[1], 1);
		close(E1[0]);
		close(E1[1]);

		execlp("sort","sort", NULL); // sort
		exit(EXIT_FAILURE);                            
	}
	
	close(D1[0]);
	close(D1[1]);

	int F1[2]; // pipe F1
	pipe(F1);
	
	pid_t pid17 = fork();                                       
	if (!pid17) {
		dup2(E1[0], 0);
		close(E1[0]);
		close(E1[1]);

		dup2(F1[1], 1);
		close(F1[0]);
		close(F1[1]);

		execlp("uniq","uniq", "-c", NULL); // uniq -c
		exit(EXIT_FAILURE);                            
	}
	
	close(E1[0]);
	close(E1[1]);

	int G1[2]; // pipe G1
	pipe(G1);
	
	pid_t pid18 = fork();                                       
	if (!pid18) {
		dup2(F1[0], 0);
		close(F1[0]);
		close(F1[1]);

		dup2(G1[1], 1);
		close(G1[0]);
		close(G1[1]);

		execlp("sort","sort", "-n", "-r", NULL); // sort -n -r
		exit(EXIT_FAILURE);                            
	}
	
	close(F1[0]);
	close(F1[1]);

	int H1[2]; // pipe H1
	pipe(H1);
	
	pid_t pid19 = fork();                                       
	if (!pid19) {
		dup2(G1[0], 0);
		close(G1[0]);
		close(G1[1]);

		dup2(H1[1], 1);
		close(H1[0]);
		close(H1[1]);
		char str[10];
		strcpy(str, "-");
		strcat(str, argv[1]);
		execlp("head","head", str, NULL); // head -$1
		exit(EXIT_FAILURE);                            
	}
	
	close(G1[0]);
	close(G1[1]);

	int I1[2]; // pipe I1
	pipe(I1);
	
	pid_t pid20 = fork();                                       
	if (!pid20) {
		dup2(H1[0], 0);
		close(H1[0]);
		close(H1[1]);

		dup2(I1[1], 1);
		close(I1[0]);
		close(I1[1]);

		execlp("sed","sed", "-e", "s/^[[:space:]]*//", NULL); // sed -e 's/^[[:space:]]*//'
		exit(EXIT_FAILURE);                            
	}
	
	close(H1[0]);
	close(H1[1]);

	pid_t pid21 = fork();                                       
	if (!pid21) {
		dup2(I1[0], 0);
		close(I1[0]);
		close(I1[1]);
		execlp("awk","awk", "BEGIN{n=0}{sum+=$1; a[n]=$1; b[n]=$2; n++}END{for(i=0;i<n;i++) printf \"%d. %s - %.0f - %0.1f%%\\n\", i+1, b[i], a[i], a[i]/sum*100}", NULL);
		exit(EXIT_FAILURE);                            
	}
	

	close(I1[0]);
	close(I1[1]);

	waitpid(pid21, 0, 0);
}
