#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <pthread.h>

void *hello_world(void *thread_id)
{
    long tid = (long)thread_id;
    printf("Hello World from thread %ld\n", tid);
    pthread_exit(NULL);
}

int main()
{
    printf("Start the alarm\n");

    for (int i = 1; i <= 5; i++)
    {
        alarm(i);
        pause();
        printf("Alarm %d received\n", i);

        int num_threads = 5;
        pthread_t threads[num_threads];
        int rc;
        long t;
        for (t = 0; t < num_threads; t++)
        {
            rc = pthread_create(&threads[t], NULL, hello_world, (void *)t);
            if (rc)
            {
                printf("Error creating thread\n");
                return -1;
            }
        }

        for (t = 0; t < num_threads; t++)
        {
            pthread_join(threads[t], NULL);
        }
    }

    return 0;
}
