#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char* argv[])
{
    int pipe_1[2];
    pipe(pipe_1);

    write(pipe_1[1], "a", 1);

    for(int i = 1; i < argc; i++)
    {
        if(fork() == 0)
        {
            FILE *fp;
            long lSize;
            char *buffer;

            fp = fopen ( argv[i] , "rb" );
            if( !fp ) perror(argv[i]),exit(1);

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

            // synchronize
            char byte;
            read(pipe_1[0], &byte, 1);

            if (byte != 0)
            {
                printf("----------------------------------\nFILE: %s\n----------------------------------\n", argv[i]);
                printf("%s", buffer);
                write(pipe_1[1], "a", 1);
            }
                
            free(buffer);

            exit(0);
        }
    }

    close(pipe_1[0]);
    close(pipe_1[1]);

    wait(nullptr);

    return 0;    
}
