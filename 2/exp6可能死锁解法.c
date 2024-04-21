#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include <unistd.h>

//规定奇数哲学家先拿左边筷子再拿右边筷子，偶数哲学家先拿右边筷子再拿左边筷子
pthread_mutex_t chopstick[5];
void *func(void*);// 线程函数
void init();
int Random(void) {
        int a = time(NULL);
        srand(a);
        return (rand() % 400 + 100);
}//每种状态维持的随机时间

int main(){
        init();
        pthread_t p1,p2,p3,p4,p5; // 定义哲学家
        pthread_create(&p1,NULL,func,"0");
        pthread_create(&p2,NULL,func,"1");
        pthread_create(&p3,NULL,func,"2");
        pthread_create(&p4,NULL,func,"3");
        pthread_create(&p5,NULL,func,"4");        
pthread_join(p1,NULL);
        pthread_join(p2,NULL);
        pthread_join(p3,NULL);
        pthread_join(p4,NULL);
        pthread_join(p5,NULL);
        return 0;
}

void init(){
        int i = 0;
        for(;i < 5; i++){
                chopstick[i] = (pthread_mutex_t)PTHREAD_MUTEX_INITIALIZER;
        }
}

void *func(void *arg){
int i = 0;
        int num = atoi((char *)arg);
        do{
                //思考
                int time =Random();
                printf("哲学家%d开始思考，将思考%dms\n",num + 1,time);                usleep(time*1000);

                //吃饭
                if(num % 2 == 0){ //偶数哲学家
                        pthread_mutex_lock(&chopstick[(num + 1) % 5]);
                        pthread_mutex_lock(&chopstick[num]);
                        time=Random();
                        printf("哲学家%d开始吃饭，将吃饭%dms\n",num + 1,time);
                        usleep(time*1000);
                } else{ //奇数哲学家 
                        pthread_mutex_lock(&chopstick[num]);
                        pthread_mutex_lock(&chopstick[(num + 1) % 5]);
                        time=Random();
                        printf("哲学家%d开始吃饭，将吃饭%dms\n",num + 1,time);
                        usleep(time*1000);
                     }

                i++;
        } while(i < 30);
}
