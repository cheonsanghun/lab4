#include <stdlib.h>
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

#define BUFFER_SIZE 20  // 버퍼의 크기를 정의
#define NUMITEMS 30     // 생성 및 소비할 아이템의 총 수

// 버퍼 구조체 정의
typedef struct {
    int item[BUFFER_SIZE]; // 버퍼 배열
    int totalitems;        // 현재 버퍼에 있는 아이템 수
    int in, out;           // 버퍼의 입력 및 출력 위치
    pthread_mutex_t mutex; // 상호 배제를 위한 뮤텍스
    pthread_cond_t full;   // 버퍼가 가득 찼을 때를 위한 조건 변수
    pthread_cond_t empty;  // 버퍼가 비었을 때를 위한 조건 변수
} buffer_t;

buffer_t bb = {{0}, 0, 0, 0, PTHREAD_MUTEX_INITIALIZER, PTHREAD_COND_INITIALIZER, PTHREAD_COND_INITIALIZER};

// 아이템 생성 함수
int produce_item() {
    int item = (int)(100.0 * rand() / (RAND_MAX + 1.0));
    sleep((unsigned long)(5.0 * rand() / (RAND_MAX + 1.0)));
    printf("produce_item: item = %d\n", item);
    return item;
}

// 버퍼에 아이템 삽입 함수
int insert_item(int item) {
    pthread_mutex_lock(&bb.mutex);

    while (bb.totalitems >= BUFFER_SIZE) {
        pthread_cond_wait(&bb.empty, &bb.mutex);
    }

    bb.item[bb.in] = item;
    bb.in = (bb.in + 1) % BUFFER_SIZE;
    bb.totalitems++;

    pthread_cond_signal(&bb.full);
    pthread_mutex_unlock(&bb.mutex);
    return 0;
}

// 아이템 소비 함수
int consume_item(int item) {
    sleep((unsigned long)(5.0 * rand() / (RAND_MAX + 1.0)));
    printf("\t\tconsume_item: item = %d\n", item);
    return 0;
}

// 버퍼에서 아이템 제거 함수
int remove_item(int *temp) {
    pthread_mutex_lock(&bb.mutex);

    while (bb.totalitems <= 0) {
        pthread_cond_wait(&bb.full, &bb.mutex);
    }

    *temp = bb.item[bb.out];
    bb.out = (bb.out + 1) % BUFFER_SIZE;
    bb.totalitems--;

    pthread_cond_signal(&bb.empty);
    pthread_mutex_unlock(&bb.mutex);
    return 0;
}

// 생산자 스레드 함수
void *producer(void *arg) {
    for (int i = 0; i < NUMITEMS; i++) {
        int item = produce_item();
        insert_item(item);
    }
    return NULL;
}

// 소비자 스레드 함수
void *consumer(void *arg) {
    for (int i = 0; i < NUMITEMS; i++) {
        int item;
        remove_item(&item);
        consume_item(item);
    }
    return NULL;
}

// 메인 함수
int main() {
    pthread_t producer_tid_1, consumer_tid_1, producer_tid_2, consumer_tid_2;

    pthread_create(&producer_tid_1, NULL, producer, NULL);
    pthread_create(&producer_tid_2, NULL, producer, NULL);
    pthread_create(&consumer_tid_1, NULL, consumer, NULL);
    pthread_create(&consumer_tid_2, NULL, consumer, NULL);

    pthread_join(producer_tid_1, NULL);
    pthread_join(producer_tid_2, NULL);
    pthread_join(consumer_tid_1, NULL);
    pthread_join(consumer_tid_2, NULL);

    return 0;
}

