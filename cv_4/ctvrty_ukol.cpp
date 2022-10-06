#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>


#define CHILD_COUNT 5

int main(void)
{
    pid_t child_pids[CHILD_COUNT];
    bool child_off[CHILD_COUNT];

    for(int i = 0; i < CHILD_COUNT; i++)
    {
        pid_t fork_ret_value = fork();
        
        // child code
        if(fork_ret_value == 0)
        {
            // redirect to different terminal
            int fid = open("/dev/pts/1", O_WRONLY);
            dup2(fid, STDOUT_FILENO);

            while(1)
            {
                printf("%d\n", i);

                sleep(1);
            }

            return 0;
        }

        child_pids[i] = fork_ret_value;
    }

    for(int i = 0; i < CHILD_COUNT - 1; i++)
    {
        kill(child_pids[i], SIGSTOP);
        child_off[i] = true;
    }

    while(1)
    {
        char c = getchar();
        int index = c - '0';

        if(child_off[index] == true)
        {
            child_off[index] = false;
            kill(child_pids[index], SIGCONT);
        }
        else
        {
            child_off[index] = true;
            kill(child_pids[index], SIGSTOP);
        }
    }
    return 0;
}