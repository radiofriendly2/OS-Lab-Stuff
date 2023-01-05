#include<stdio.h>
#include<signal.h>
#include<unistd.h>
#include<pthread.h>
int sigint=0;
int sigquit=0;
void fun()
{
    printf("Thread Running\n");
}
void sig_handler(int signo)
{
    pthread_t arr[20];
    if (signo == SIGINT)
    {
        sigint++;
        printf("\nreceived SIGINT\n");
        printf("SIGINT= %d SIGQUIT=%d\n",sigint,sigquit);
    }
    else if (signo == SIGQUIT)
     {   
         sigquit++;
         printf("\nreceived SIGQUIT\n");
        printf("SIGINT= %d SIGQUIT=%d\n",sigint,sigquit);
     }
     for(int i=0;i<sigint+sigquit;i++)
     {
        pthread_create(&arr[i],NULL,&fun,NULL);
     }
     printf("%d Threads Created",sigint+sigquit);
    for(int i=0;i<sigint+sigquit;i++)
     {
        pthread_join(arr[i],NULL);
     }

}

int main(void)
{
    signal(SIGQUIT,sig_handler);
    signal(SIGINT,sig_handler);
    while(1);
   
	return 0;
}
