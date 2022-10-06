#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <sys/syscall.h>
#include <vector>

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
    char* filename = (char*) ptr;

    FILE *fp;
    long lSize;
    char *buffer;

    fp = fopen ( filename , "rb" );
    if( !fp ) perror(filename),exit(1);

    fseek( fp , 0L , SEEK_END);
    lSize = ftell( fp );
    rewind( fp );

    /* allocate memory for entire content */
    buffer = (char*) calloc( 1, lSize+1 );
    if( !buffer ) fclose(fp),fputs("memory alloc fails",stderr),exit(1);

    /* copy the file into the buffer */
    if( 1!=fread( buffer , lSize, 1 , fp) )
    fclose(fp),free(buffer),fputs("entire read fails",stderr),exit(1);

    fclose(fp);

    return buffer;
}

int main(int argc, char* argv[])
{
    std::vector<pthread_t> threads;

    // start threads
    for(int i = 1; i < argc; i++)
    {
        pthread_t thread;

        pthread_create(&thread, nullptr, thread_function, (void*)argv[i]);

        threads.push_back(thread);
    }

    // collect threads
    void* ret;
    for(int i = 0; i < threads.size(); i++)
    {
        pthread_join(threads[i], &ret);

        printf("----------------------------------\nFILE: %s\n----------------------------------\n", argv[i]);
        printf("%s", ret);

        free(ret);
    }

}