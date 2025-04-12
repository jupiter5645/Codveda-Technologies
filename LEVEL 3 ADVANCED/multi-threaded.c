#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define BUFFER_SIZE 5
#define NUM_ITEMS 20

int buffer[BUFFER_SIZE];
int count = 0; 
int in = 0;   
int out = 0; 

pthread_mutex_t mutex;
pthread_cond_t not_empty;
pthread_cond_t not_full;

void* producer(void* arg) {
    for (int i = 0; i < NUM_ITEMS; i++) {
  
        int item = rand() % 100;
        pthread_mutex_lock(&mutex);


        while (count == BUFFER_SIZE) {
            pthread_cond_wait(&not_full, &mutex);
        }


        buffer[in] = item;
        printf("Produced: %d\n", item);
        in = (in + 1) % BUFFER_SIZE;
        count++;

     
        pthread_cond_signal(&not_empty);
        pthread_mutex_unlock(&mutex);


        usleep(rand() % 100000);
    }
    return NULL;
}

void* consumer(void* arg) {
    for (int i = 0; i < NUM_ITEMS; i++) {
        pthread_mutex_lock(&mutex);


        while (count == 0) {
            pthread_cond_wait(&not_empty, &mutex);
        }

  
        int item = buffer[out];
        printf("Consumed: %d\n", item);
        out = (out + 1) % BUFFER_SIZE;
        count--;

     
        pthread_cond_signal(&not_full);
        pthread_mutex_unlock(&mutex);

  
        usleep(rand() % 100000);
    }
    return NULL;
}

int main() {
    pthread_t prod_thread, cons_thread;


    pthread_mutex_init(&mutex, NULL);
    pthread_cond_init(&not_empty, NULL);
    pthread_cond_init(&not_full, NULL);

   
    pthread_create(&prod_thread, NULL, producer, NULL);
    pthread_create(&cons_thread, NULL, consumer, NULL);

    
    pthread_join(prod_thread, NULL);
    pthread_join(cons_thread, NULL);


    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&not_empty);
    pthread_cond_destroy(&not_full);

    return 0;
}
