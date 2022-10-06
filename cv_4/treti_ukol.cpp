#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>

#define INTERVAL 10

int CHILDS_CREATED = 0;
int CHILDS_EXITED_WAITPID = 0;
int CHILDS_EXITED_SIGNAL = 0;

void child_stopped_or_terminated(int t_signal)
{
    CHILDS_EXITED_SIGNAL++;

    int pid, stat;
    while ( (pid = waitpid(-1, &stat, WNOHANG)) > 0) {
        CHILDS_EXITED_WAITPID++;
    }
}

int main(void)
{
    struct sigaction l_sa;
    l_sa.sa_handler = child_stopped_or_terminated;
    l_sa.sa_flags = 0;
    sigemptyset(&l_sa.sa_mask);
    sigaction(SIGCHLD, &l_sa, nullptr);

    while(1 == 1)
    {
        if(fork() == 0)
        { 
            // initialize random generator based on pid value and generate random number
            srand(getpid());
            int random_number = rand() % (INTERVAL + 1);

            sleep(random_number);
            return 0;
        }

        CHILDS_CREATED++;

        usleep(10000);

        printf("\x12");
        printf("Childs created:\t%d\nChilds exited SIGCHLD:\t%d\nChilds exited WAITPID:\t%d\n\n", CHILDS_CREATED, CHILDS_EXITED_SIGNAL, CHILDS_EXITED_WAITPID);
    }

    return 0;
}