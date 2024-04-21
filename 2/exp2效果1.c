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
        }
      
        else if(id==0)
        {
        
                printf("我是子进程（进程号：%d）,父进程号：%d\n",getpid(),getppid());
                sleep(6);
        }

        else if(id>0)
        {
                printf(“我是父进程（进程号：%d），父进程号：%d\n”,getpid(),getppid());

                sleep(5);
                exit(0);
        }

        return 0;
}
