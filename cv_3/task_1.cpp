#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char* argv[])
{
    for(int i = 0; i < 999999999999999;i ++)
    {
        int fork_ret_value = fork();
        if(fork_ret_value == 0)
        {
            sleep(1000);
            exit(0);
        }
        if(fork_ret_value == -1)
        {
            printf("%d processes created.\n", i);
            exit(0);
        }
        usleep(1);
    }

    wait(nullptr);

    return 0;    
}
