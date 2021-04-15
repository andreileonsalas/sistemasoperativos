#include <stdio.h>
#include  <string.h>
#include  <sys/types.h>

int main()
{
    pid_t  pid;
    int i = 0;
        for (i=0; i < 4; i++) {
            pid = fork();
        if (pid = 0) fork();
            printf("Hola \n");
}

}
