#include<stdio.h>
#include<pthread.h>
#include<stdlib.h>
#include<unistd.h>

int i;
pthread_mutex_t mutex;

void* counter(void *arg){
    int x = 1;
    while (x <= i){
        pthread_mutex_lock(&mutex);
        printf("angka: %d\n", x);
        pthread_mutex_unlock(&mutex);
        x++;
        sleep(1); // Sleep for a short duration to switch to the other thread
    }
}

void* square(void *arg){
    int x = 1;
    while (x <= i){
        pthread_mutex_lock(&mutex);
        printf("pangkat: %d\n", x*x);
        pthread_mutex_unlock(&mutex);
        x++;
        sleep(1); // Sleep for a short duration to switch to the other thread
    }
}

int main (void) {
    int num;
    printf("Masukan angka: ");
    scanf("%d", &i);

    if (pthread_mutex_init(&mutex, NULL) != 0)
        printf("Mutex failed");

    pthread_t counter_id;
    pthread_t square_id;

    pthread_create(&square_id, NULL, square, NULL);
    pthread_create(&counter_id, NULL, counter, NULL);
    
    pthread_join(counter_id, NULL);
    pthread_join(square_id, NULL);

    pthread_mutex_destroy(&mutex); // Destroy the mutex

    return 0;
}