#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>

#define INTERVAL 10

int main(void){
    int childs_created = 0;
    int childs_exited = 0;

    while(1 == 1){
        if(fork() == 0){ 
            // initialize random generator based on pid value and generate random number
            srand(getpid());
            int random_number = rand() % (INTERVAL + 1);

            sleep(random_number);
            return 0;
            }

        childs_created++;

        sleep(1);

        system("clear");
        printf("Childs created:\t%d\nChilds exited:\t%d\n\n", childs_created, childs_exited);

        int pid, stat;
        while ( (pid = waitpid(-1, &stat, WNOHANG)) > 0) {
            printf("Child %d terminated\n", pid);
            childs_exited++;
        }
    }

    return 0;
}