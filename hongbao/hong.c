/*************************************************************************
	> File Name: hong.c
	> Author: 
	> Mail: 
	> Created Time: 2017年09月24日 星期日 17时39分41秒
 ************************************************************************/

#include<stdio.h>
#include<pthread.h>
#include<unistd.h>
#include<sys/time.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>

#define RAND(min,max)(rand()%((max) - (min) ) + min)
#define n 100

struct person
{
    int num;
    double sum;
}Person;


   pthread_mutex_t mutex=PTHREAD_MUTEX_INITIALIZER;
   
void creat_ret()//创建一个红包
{
    int num ;//红包个数
    double sum ;//红包总额
    printf("请输入红包的个数和金额：");
    scanf("%d %lf",&num,&sum);
    
    pthread_mutex_lock(&mutex);
    
    Person.num = num;
    Person.sum = sum *100;

    pthread_mutex_unlock(&mutex);
    usleep(1);
}

void *consumer(void *arg)
{
    int money =0;
    int i = * (int *) arg;
    pthread_mutex_lock(&mutex);
   
    if(Person.num < 1 )
    {
       // printf("红包被抢完了！ \n");
        pthread_mutex_unlock(&mutex);
        pthread_exit(NULL);

    }
    else if(Person.num == 1)
    {
        money =   Person.sum;  
    }
    else if(Person.sum/Person.num==1)
    {
        money ==1;
    }
    else
    {
        money =   Person.sum *RAND(1,200)/100/Person.num; 
    }
    Person.sum -= money;
    Person.num--;
    printf("%dth thread\tget %d.%d%d money\n",i,money/100,(money/10)%10,money%10);
    pthread_mutex_unlock(&mutex);

    return NULL;

}


int main()
{
    int ret;


    pthread_t  ctid[100];
    srand(time(NULL));

    creat_ret();
    int arr[n];
    int i;
    for(i = 0;i < n;i++)
    {
        arr[i] = i+1;
      if( ( ret = pthread_create(&ctid[i],NULL,consumer,&arr[i])) !=0)
        {
            printf("线程%d创建失败\n",i);
        }
        else
        {
          //  printf("线程%d\n",i);
        }
    }
    for(i =0;i<n;i++)
    {
        pthread_join(ctid[i],NULL);

    }
    pthread_mutex_destroy(&mutex);
    return 0;
    
}

