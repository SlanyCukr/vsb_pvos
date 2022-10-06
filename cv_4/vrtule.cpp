#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char* argv[])
{
    char printable_chars[] = {'-', '/', '|', '\\'};
    int char_index = 0;

    // while(1)
    // {
    //     if(char_index == 4)
    //         char_index = 0;

    //     fflush(stdout); 
    //     printf("\r%c", printable_chars[char_index]);

    //     char_index++;

    //     usleep(100000);
    // }

    // char small_buf[1];
    // char big_buf[100];
    // setvbuf(stdout, big_buf, _IONBF, 100 * sizeof(char));
    // //setbuffer(stdout, small_buf, 1 * sizeof(char));

    // while(1)
    // {
    //     if(char_index == 4)
    //         char_index = 0;

    //     printf("\r%c", printable_chars[char_index]);

    //     char_index++;

    //     usleep(100000);
    // }



    return 0;    
}
