#include <windows.h>  
#include <stdio.h>  
#include <stdlib.h>  
#include <time.h>  

#define BUFFER_SIZE 10  
#define PRODUCER_COUNT 2  
#define CONSUMER_COUNT 3  

int buffer[BUFFER_SIZE] = { 0 };
int in = 0, out = 0;
CRITICAL_SECTION cs;
HANDLE semEmpty, semFull;

DWORD WINAPI Producer(LPVOID id) {
    int producerId = (int)id;
    while (TRUE) {
        WaitForSingleObject(semEmpty, INFINITE);
        EnterCriticalSection(&cs);

        int value = (producerId == 1) ? (rand() % 1000 + 1000) : (rand() % 1000 + 2000);
        buffer[in] = value;
        printf("Producer %d produced %d\n", producerId, value);
        in = (in + 1) % BUFFER_SIZE;

        LeaveCriticalSection(&cs);
        ReleaseSemaphore(semFull, 1, NULL);

        Sleep(rand() % 900 + 100); // Random delay between 100ms and 1s  
    }
    return 0;
}

DWORD WINAPI Consumer(LPVOID id) {
    while (TRUE) {
        WaitForSingleObject(semFull, INFINITE);
        EnterCriticalSection(&cs);

        int value = buffer[out];
        printf("Consumer %d consumed %d\n", (int)id, value);
        out = (out + 1) % BUFFER_SIZE;

        LeaveCriticalSection(&cs);
        ReleaseSemaphore(semEmpty, 1, NULL);

        Sleep(rand() % 900 + 100); // Random delay between 100ms and 1s  
    }
    return 0;
}

int main() {
    InitializeCriticalSection(&cs);
    semEmpty = CreateSemaphore(NULL, BUFFER_SIZE, BUFFER_SIZE, NULL);
    semFull = CreateSemaphore(NULL, 0, BUFFER_SIZE, NULL);

    HANDLE producerThreads[PRODUCER_COUNT];
    for (int i = 0; i < PRODUCER_COUNT; i++) {
        producerThreads[i] = CreateThread(NULL, 0, Producer, (void*)i, 0, NULL);
    }

    HANDLE consumerThreads[CONSUMER_COUNT];
    for (int i = 0; i < CONSUMER_COUNT; i++) {
        consumerThreads[i] = CreateThread(NULL, 0, Consumer, (void*)i, 0, NULL);
    }

    WaitForMultipleObjects(PRODUCER_COUNT, producerThreads, TRUE, INFINITE);
    WaitForMultipleObjects(CONSUMER_COUNT, consumerThreads, TRUE, INFINITE);
}
