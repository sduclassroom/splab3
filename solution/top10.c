#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include <stdlib.h>

int main() {
    int A[2]; // pipe A
    pipe(A);
    pid_t pid1 = fork(); // cut
    if (!pid1) {
        dup2(A[1], 1);
        close(A[0]);
        close(A[1]);
        execlp("cut","cut", "-f11", "-d ", "log.txt", NULL);
        exit(EXIT_FAILURE);
    }
    
    int B[2]; // pipe B
    pipe(B);
    pid_t pid2 = fork();
    if (!pid2) { // grep
        dup2(A[0], 0);
        close(A[0]);
        close(A[1]);
        
        dup2(B[1], 1);
        close(B[0]);
        close(B[1]);
        
        execlp("grep","grep", "-v", "-", NULL);
        exit(EXIT_FAILURE);
    }
    
    close(A[0]);
    close(A[1]);
    
    int C[2]; // pipe C
    pipe(C);
    
    pid_t pid3 = fork();
    if (!pid3) { // sort
        dup2(B[0], 0);
        close(B[0]);
        close(B[1]);
        
        dup2(C[1], 1);
        close(C[0]);
        close(C[1]);
        
        execlp("sort","sort", NULL);
        exit(EXIT_FAILURE);
    }
    
    close(B[0]);
    close(B[1]);
    
    
    int D[2]; // pipe D
    pipe(D);
    
    pid_t pid4 = fork();
    if (!pid4) { // uniq
        dup2(C[0], 0);
        close(C[0]);
        close(C[1]);
        
        dup2(D[1], 1);
        close(D[0]);
        close(D[1]);
        
        execlp("uniq","uniq", "-c", NULL);
        exit(EXIT_FAILURE);
    }
    
    close(C[0]);
    close(C[1]);
    
    int E[2]; // pipe E
    pipe(E);
    
    pid_t pid5 = fork();
    if (!pid5) { // sort
        dup2(D[0], 0);
        close(D[0]);
        close(D[1]);
        
        dup2(E[1], 1);
        close(E[0]);
        close(E[1]);
        
        execlp("sort","sort", "-rn", NULL);
        exit(EXIT_FAILURE);
    }
    
    close(D[0]);
    close(D[1]);
    
    int F[2]; // pipe F
    pipe(F);
    
    pid_t pid6 = fork();
    if (!pid6) { // cat
        dup2(E[0], 0);
        close(E[0]);
        close(E[1]);
        
        dup2(F[1], 1);
        close(F[0]);
        close(F[1]);
        
        execlp("cat","cat", "-n", NULL);
        exit(EXIT_FAILURE);
    }
    
    close(E[0]);
    close(E[1]);
    
    int G[2]; // pipe G
    pipe(G);
    
    pid_t pid7 = fork();
    if (!pid7) { // awk
        dup2(F[0], 0);
        close(F[0]);
        close(F[1]);
        
        dup2(G[1], 1);
        close(G[0]);
        close(G[1]);
        
        execlp("awk", "awk", " { print $1 \". \" $3 \" - \" $2 \" - \" int($2/1120*100) \"%\" } ", NULL);
        exit(EXIT_FAILURE);
    }
    
    close(F[0]);
    close(F[1]);
    
	pid_t pid8 = fork();
    if (!pid8) { // head
        dup2(G[0], 0);
        close(G[0]);
        close(G[1]);
        execlp("head", "head", "-n", "10", NULL);
        exit(EXIT_FAILURE);
    }
	
   
    close(G[0]);
    close(G[1]);
    waitpid(pid8, 0, 0);
}
