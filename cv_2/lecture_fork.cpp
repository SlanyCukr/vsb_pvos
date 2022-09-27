#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

// tty - zobrazi cestu k soucasne konzoli, lze takto presmerovat napr stderr do jine konzole
// postup; pipe -> fork -> dup2 -> exec
// dale je nutne zavrit nepouzivane veci close(pipe1[...])
// pipefd[0] = read
// pipefd[1] = write

// v prikladu dole vrati potomek rodicovi vysledek sve prace
int main(int argc, char* argv[])
{
    int pipe1[2];
    pipe(pipe1);

    // cloned process 1
    if(fork() == 0)
    {
        // cloned process doesn't need read end of the pipe
        close(pipe1[0]);

        // when program tries to print anything to stding, it will get redirected through pipe to parent
        dup2(pipe1[1], STDOUT_FILENO);

        // the now duplicated pipe[1] isn't needed anymore
        close(pipe1[1]);

        execlp("ls", "ls", 0);

        printf("Shouldn't get here...\n");

        return 0;
    }

    // parent

    // parent doesn't need write end of the pipe
    close(pipe1[1]);

    // reading loop
    while(1)
    {
        char buf[128];

        int len = read(pipe1[0], buf, sizeof(buf));
        if(len <= 0) break;

        write(STDOUT_FILENO, buf, len);
    }

    // close now unused read end of the pipe, wait child to terminate
    close(pipe1[0]);
    wait(nullptr);

    return 0;    
}