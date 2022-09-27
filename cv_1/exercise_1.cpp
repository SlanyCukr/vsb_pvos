#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MAX 2

int main(int argc, char* argv[]){
    // parse argument
    char* child_arg = argv[1];
    int child_count = atoi(child_arg);

    printf("Child count: %d.\n", child_count);

    for(int i = 0; i < child_count; i++)
    {
        int j = fork();
        // j == 0 indicates children process
        if(j == 0)
        {
            // initialize random generator based on pid value and generate random number
            srand(getpid());
            int random_number = rand() % (MAX + 1) + 1;

            // bad exit
            if(random_number == 1){
                int* test = nullptr;
                test[0] = 0;
            }
            // good exit
            if(random_number == 2){
                return 2;
            }
            // exec ls - existing path
            if(random_number == 3){
                char* argument_list[] = {"ls", "-l", NULL};
                execvp("ls", argument_list);
            }
            // exec ls - not existing path
            if(random_number >= 4){
                char* argument_list[] = {"ls", "-l", "/void/null/test", NULL};
                execvp("ls", argument_list);
            }
        }
    }

    int child_status;
    for (int i = 0; i < child_count; i++) {
        pid_t wpid = waitpid(-1, &child_status, 0);
        if (WIFEXITED(child_status))
            printf("Child %d returned %d\n", wpid, WEXITSTATUS(child_status));
        else
        {
            if(WIFSTOPPED(child_status)){
                printf("Child %d stopped by signal %s\n", wpid, strsignal(WSTOPSIG(child_status)));
            }
            if(WIFSIGNALED(child_status)){
                printf("Child %d killed by signal %s\n", wpid, strsignal(WTERMSIG(child_status)));
            }
        }
    }
    
    return 0;
}
