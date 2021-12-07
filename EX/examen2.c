
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <assert.h>
#include <sys/wait.h>

int main(int argc, char** argv)
{
int pipeA[2] = {-1, -1}, pipeB[2] = {-1, -1};
pid_t pidA = -1, pidB = -1, pidC = -1;

if (argc != 2)
{
dprintf(STDERR_FILENO, "Usage: %s <FILTER>\n", argv[0]);
return EXIT_FAILURE;
}

assert(pipe(pipeA) != -1);

pidA = fork();
assert(pidA != -1);

if (pidA == 0)
{
close(pipeA[0]);

dup2(pipeA[1], STDOUT_FILENO);
close(pipeA[1]);

execlp("ls", "ls", "-l", NULL, NULL);
assert(0);
}

assert(pipe(pipeB) != -1);
pidB = fork();
assert(pidB != -1);

if (pidB == 0)
{
close(pipeA[1]);
dup2(pipeA[0], STDIN_FILENO);
close(pipeA[0]);
close(pipeB[0]);

dup2(pipeB[1], STDOUT_FILENO);
close(pipeB[1]);

execlp("grep","grep", argv[1], NULL);
assert(0);
}

pidC = fork();
assert(pidC != -1);

if (pidC == 0)
{
close(pipeA[1]);
close(pipeA[0]);

close(pipeB[1]);

dup2(pipeB[0], STDIN_FILENO);
close(pipeB[0]);

execlp("sort","sort", NULL, NULL);
assert(0);
}

close(pipeA[0]);
close(pipeA[1]);
close(pipeB[0]);
close(pipeB[1]);

waitpid(pidC, NULL, 0);

return EXIT_SUCCESS;
}