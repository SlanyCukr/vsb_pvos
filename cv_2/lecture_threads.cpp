#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <sys/syscall.h>

// fork ---> pthread_create
// wait ---> pthread_join
// exit ---> pthread_exit

// pthread_detach => po ukonceni se neceka na navratovou hodnotu, rovnou se uvolni prostredky pouzite vlaknem
// pstree -p | less
// ps ax -T | less

// hlavni vlakno ma vzdy stejny PID jako SPID
// kazde vlakno ma vlastni identifikator TID (thread ID)

void* thread_function(void* ptr)
{
    char* jmeno = (char*) ptr;

    printf("Thread here %s %lx %d.\n", jmeno, pthread_self(), gettid());

    // stop the execution of process until it receives input from keyboard
    getchar();

    return jmeno;
}

int main(int argc, char* argv[])
{
    // this is not TID
    pthread_t pth1, pth2;

    // create threads
    pthread_create(&pth1, nullptr, thread_function, (void*)"test1");
    pthread_create(&pth2, nullptr, thread_function, (void*)"test2");

    printf("Main thread TID: %d.\n", gettid());

    void* ret;

    // wait for threads to end
    pthread_join(pth1, &ret);
    printf("Thread %s ended.\n", (char*) ret);
    pthread_join(pth2, &ret);
    printf("Thread %s ended.\n", (char*) ret);

    return 0;    
}