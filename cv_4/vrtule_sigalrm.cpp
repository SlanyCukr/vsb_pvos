#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <errno.h>
#include <sys/time.h>

char PRINTABLE_CHARS[] = {'-', '/', '|', '\\'};
int CHAR_INDEX = 0;
int TIME_PERIOD = 100;

void writer(int t_signnal)
{
    if(CHAR_INDEX == 4)
    {
        CHAR_INDEX = 0;
    }

    fflush(stdout); 
    printf("\r%c", PRINTABLE_CHARS[CHAR_INDEX]);

    CHAR_INDEX++;
}

// initialize and start SIGALRM
void gt_sig_start( void )
{
    struct sigaction l_sig_act;
    memset( &l_sig_act, 0, sizeof( l_sig_act ) );
    l_sig_act.sa_handler = writer;

    sigaction( SIGALRM, &l_sig_act, NULL );

    struct itimerval l_tv_alarm = { { 0, TIME_PERIOD * 1000 }, { 0, TIME_PERIOD * 1000 } };
    setitimer( ITIMER_REAL, & l_tv_alarm, NULL );
}

int main(int argc, char* argv[])
{
    char buf[1];
    while(1)
    {
        //alarm(1);
        gt_sig_start();
        int ret = read(0, buf, sizeof(buf));
    }

    return 0;
}