#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <pthread.h>
sem_t empty, full;
pthread_mutex_t wr, mutex;
int buffer[5];
int count = 0, i, j, k, l, choice, a = 10, readcount = 0;

void *producer(void *arg)
{
    long int num = (long int)arg;

    sem_wait(&empty);
    pthread_mutex_lock(&mutex);
    buffer[count] = rand() % 10;
    printf("\nProducer : %ld produced : %d ", num + 1, buffer[count]);
    count++;
    sleep(1);
    pthread_mutex_unlock(&mutex);
    sem_post(&full);
}

void *consumer(void *arg)
{
    long int num = (long int)arg;

    sem_wait(&full);
    pthread_mutex_lock(&mutex);
    count--;
    printf("\nConsumer : %ld consumed : %d ", num + 1, buffer[count]);
    sleep(1);
    pthread_mutex_unlock(&mutex);
    sem_post(&empty);
}

void producer_consumer()
{
    int np, nc;
    pthread_t p[10], c[10];
    printf("\nEnter no. of producers and no. of consumers ");
    scanf("%d %d", &np, &nc);

    sem_init(&empty, 0, 5);
    sem_init(&full, 0, 0);
    pthread_mutex_init(&mutex, NULL);

    for (i = 0; i < np; i++)
    {
        pthread_create(&p[i], NULL, producer, (void *)i);
    }
    for (j = 0; j < nc; j++)
    {
        pthread_create(&c[j], NULL, consumer, (void *)j);
    }
    for (k = 0; k < np; k++)
    {
        pthread_join(p[k], NULL);
    }
    for (l = 0; l < nc; l++)
    {
        pthread_join(c[l], NULL);
    }
}

void *writer(void *arg)
{

    long int num = (long int)arg;

    pthread_mutex_lock(&wr);
    printf("\n Writer %ld is in critical section ",num);
    printf("\n Writer %ld have written data as %d", num, ++a);
    sleep(1);
    pthread_mutex_unlock(&wr);
    printf("\n Writer %ld leaving the critical section ",num);
}

void *reader(void *arg)
{
    long int num = (long int)arg;

    pthread_mutex_lock(&mutex);
    readcount++;
    pthread_mutex_unlock(&mutex);
    if (readcount == 1)
    {
        pthread_mutex_lock(&wr);
    }
    printf("\n Reader %ld is in critical section ",num);
    printf("\n Reader %ld is reading data %d", num, 1);
    sleep(1);
    pthread_mutex_lock(&mutex);
    readcount--;
    pthread_mutex_unlock(&mutex);
    if (readcount == 0)
    {
        pthread_mutex_unlock(&wr);
    }
    printf("\n Reader %ld leaving the critical section ",num);
}

void reader_writer()
{
    pthread_t r[10], w[10];
    int i, j, nor, now;
    pthread_mutex_init(&wr,NULL);
    pthread_mutex_init(&mutex,NULL);

    printf("Enter the no. of Readers and no. of Writers ");
    scanf("%d %d", &nor, &now);

    for (i = 0; i < nor; i++)
    {
        pthread_create(&r[i], NULL, reader, (void *)i);
    }
    for (j = 0; j < now; j++)
    {
        pthread_create(&w[j], NULL, writer, (void *)j);
    }
    for (i = 0; i < nor; i++)
    {
        pthread_join(r[i], NULL);
    }
    for (j = 0; j < now; j++)
    {
        pthread_join(w[j], NULL);
    }
}


void menu()
{
    printf("\n\n\n\n**************MENU****************");
    printf("\n1. Producer Consumer");
    printf("\n2. Reader Writer");
    printf("\n3. Exit");
    printf("\nEnter Your Choice:");
    scanf("%d", &choice);
}

int main()
{
    while (1)
    {
        menu();
        switch (choice)
        {
        case 1:
            producer_consumer();
            break;
        case 2:
            reader_writer();
            break;
        case 3:
            exit(0);
            break;
        }
    }
}