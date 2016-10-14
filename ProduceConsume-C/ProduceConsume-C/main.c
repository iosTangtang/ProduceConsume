//
//  main.c
//  ProduceConsume-C
//
//  Created by Tangtang on 2016/10/14.
//  Copyright © 2016年 Tangtang. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

#define MAXBUFFSIZE 10
#define PRODUCE_SEM_NAME "PRODUCE_SEM_NAME"
#define CONSUME_SEM_NAME "CONSUME_SEM_NAME"

typedef struct PRC_Queue {
    int buffer[MAXBUFFSIZE];
    int front;
    int rear;
}PRC_Queue;

//initilize queue
PRC_Queue queue = {{0}, 0, 0};

sem_t   *empty;
sem_t   *full;
pthread_mutex_t mutex;

// Queue Operation
void EnterQueue(int produce);
void DelQueue();

// Produce and Consume
void *producer();
void *consumer();

// Print Method
void printBuff();

int main(int argc, const char * argv[]) {
    int resultMutex, resultProducePthread, resultConsumePthread;
    pthread_t produce, consume;
    
    //initilize
    empty = sem_open(PRODUCE_SEM_NAME, O_CREAT, 0644, MAXBUFFSIZE);
    full = sem_open(CONSUME_SEM_NAME, O_CREAT, 0644, 0);
    
    if (empty == SEM_FAILED || full == SEM_FAILED) {
        printf("sem init error\n");
        exit(1);
    }
    
    resultMutex = pthread_mutex_init(&mutex, NULL);
    
    if (resultMutex != 0) {
        printf("mutex init error\n");
        exit(1);
    }
    
    resultProducePthread = pthread_create(&produce, NULL, producer, NULL);
    resultConsumePthread = pthread_create(&consume, NULL, consumer, NULL);
    
    if (resultConsumePthread != 0 || resultProducePthread != 0) {
        printf("pthread init error\n");
        exit(1);
    }
    
    pthread_join(produce, NULL);
    pthread_join(consume, NULL);
    
    return 0;
}

#pragma mark - Queue Operation
void EnterQueue(int produce) {
    queue.buffer[queue.front] = produce;
    queue.front = (queue.front + 1) % MAXBUFFSIZE;
    printf("-------------buff[%d]----------------\n", queue.front);
}

void DelQueue() {
    queue.buffer[queue.rear] = 0;
    queue.rear = (queue.rear + 1) % MAXBUFFSIZE;
    printf("-------------buff[%d]----------------\n", queue.rear);
}

#pragma mark - Produce and Consume
void *producer() {
    
    while (1) {
        sleep(1);
        sem_wait(empty);
        pthread_mutex_lock(&mutex);
        
        EnterQueue(1);
        printBuff();
        
        pthread_mutex_unlock(&mutex);
        sem_post(full);
    }
    
}

void *consumer() {
    
    while (1) {
        sleep(1);
        sem_wait(full);
        pthread_mutex_lock(&mutex);
        
        DelQueue();
        printBuff();
        
        pthread_mutex_unlock(&mutex);
        sem_post(empty);
    }
    
}

#pragma mark - Print Method
void printBuff() {
    int index;
    
    for (index = 0; index < MAXBUFFSIZE; index++) {
        printf("%d ", queue.buffer[index]);
    }
    
    printf("\n");
}
