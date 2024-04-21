#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>
#include<stdio.h>
#include<sys/types.h>
#include<sys/wait.h>

int main()
{
        pid_t id=fork();

        if(id<0)
        {
                printf("fork error!\n");
                return 1;   
        }

        if(id==0) 
        {
                printf("child\n");
                sleep(5);  
                exit(2);
        }
        if(id>0)
        {
                printf("father\n");
                wait(NULL);
                printf("子进程返回的参数为2\n");
        }

        return 0;
}
