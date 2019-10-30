# splab3 - io system calls

###### \[deadline is week07 labtime, October 15-19, 2018 \]

### Aim
- To master basic i/o redirection system calls

### Task

In this lab you are to write a program in `C` that solves the same problem as in `splab1`. The program should use the same tools that you used in `splab1`, but the shell logic should be done by the C program itself. You should use system calls like `fork`, `exec*`, `wait`/`waitpid`, `open`, `close`, `pipe`, `dup2`, `exit`/`_exit`.

By shell logic we mean:
* forking processes and waiting results from them
* opening files and i/o redirection (using `pipe`)
* `if` statements and loops (e.g. `for`/`while`) of the shell

Also the calculation of sums, precentages etc can be done in `C`.

* See example 1, [C program](./example/top10.c)
* See example 2, [shell script with for loop](./examples/sum01), [C program using `fdopen` function](./examples/sum01.c)
* See example 3, [shell script with `awk`](./examples/sum02), [C program without `fdopen`](./examples/sum02.c)

### References
0. `man fdopen`
1. `man 2 fork`
2. `man 2 execve`
3. `man 2 waitpid`
4. `man 2 pipe`
4. `man 2 dup2`
5. [OSTEP Chapter 5](http://pages.cs.wisc.edu/~remzi/OSTEP/cpu-api.pdf)
6. Chapters 6, 24-28 of Linux Programming Interface by Micheal Kerrisk
7. Chapter 5 of Linux System Programming by Robert Love

##### Credits
* The task was adopted and adapted from http://vseloved.github.io/spos. All credits go to Vsevolod Dyomkin.
* Variants in Russian can be found [there](http://vseloved.github.io/pdf/var-sh-ru.pdf)
