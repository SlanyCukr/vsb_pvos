#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <sys/syscall.h>

void* thread_function(void* ptr)
{
    sleep(100);
}

int main(int argc, char* argv[])
{
    for(int i = 0; i < 999999999999999; i++)
    {
        // this is not TID
        pthread_t pth1;

        // create threads
        int ret_value = pthread_create(&pth1, nullptr, thread_function, nullptr);

        if(ret_value != 0)
        {
            printf("Number of threads: %d\n", i);
            break;
        }

        // wait for thread to end
        //pthread_join(pth1, nullptr);
    }

    getchar();

    return 0;    
}
