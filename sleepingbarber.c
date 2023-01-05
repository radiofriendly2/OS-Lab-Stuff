#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

sem_t mutex;
sem_t students_waiting;

void IdleProf()
{
    while (1)
    {
        sem_wait(&mutex);
        if (sem_trywait(&students_waiting) == 0)
        {
            sem_post(&mutex);
            printf("Professor is answering a student's question\n");
        }
        else
        {
            sem_post(&mutex);
            printf("Professor is sleeping\n");
            sem_wait(&students_waiting);
        }
    }
}

void ArrivingStudent()
{
    sem_wait(&mutex);
    if (sem_trywait(&students_waiting) == -1)
    {
        printf("Student woke up the professor\n");
        sem_post(&students_waiting);
    }
    sem_post(&mutex);
    printf("Student is asking a question\n");
}

int main()
{
    sem_init(&mutex, 0, 1);
    sem_init(&students_waiting, 0, 0);

    pthread_t professor_thread;
    pthread_create(&professor_thread, NULL, (void *)IdleProf, NULL);

    ArrivingStudent();
    ArrivingStudent();
    ArrivingStudent();

    pthread_exit(NULL);
}