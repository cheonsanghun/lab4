#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

// 버퍼 크기 및 아이템 수 상수 정의
#define BUFFER_SIZE 20
#define NUMITEMS 30

// 공유 버퍼 구조체 정의
typedef struct {
    int item[BUFFER_SIZE];   // 아이템을 저장할 배열
    int totalitems;          // 현재 버퍼에 저장된 아이템의 수
    int in, out;             // 버퍼의 입력 및 출력 위치 인덱스
    pthread_mutex_t mutex;   // 상호 배제를 위한 뮤텍스
    pthread_cond_t full;     // 버퍼가 가득 찼을 때의 조건 변수
    pthread_cond_t empty;    // 버퍼가 비어있을 때의 조건 변수
} buffer_t;

// 전역 버퍼 인스턴스 및 초기화
buffer_t bb = {
    {0}, 0, 0, 0,
    PTHREAD_MUTEX_INITIALIZER,
    PTHREAD_COND_INITIALIZER,
    PTHREAD_COND_INITIALIZER
};

// 아이템을 생성하는 함수
int produce_item() {
    int item = (int)(100.0 * rand() / (RAND_MAX + 1.0));
    sleep((unsigned long)(5.0 * rand() / (RAND_MAX + 1.0)));
    printf("produce_item: item=%d\n", item);
    return item;
}

// 아이템을 버퍼에 삽입하는 함수
int insert_item(int item) {
    int status = pthread_mutex_lock(&bb.mutex);
    if (status != 0) return status;

    // 버퍼가 가득 찼다면 대기
    while (bb.totalitems >= BUFFER_SIZE) {
        status = pthread_cond_wait(&bb.empty, &bb.mutex);
        if (status != 0) {
            pthread_mutex_unlock(&bb.mutex);
            return status;
        }
    }

    // 아이템 삽입 및 인덱스 조정
    bb.item[bb.in] = item;
    bb.in = (bb.in + 1) % BUFFER_SIZE;
    bb.totalitems++;

    pthread_cond_signal(&bb.full);
    return pthread_mutex_unlock(&bb.mutex);
}

// 아이템을 소비하는 함수
void consume_item(int item) {
    sleep((unsigned long)(5.0 * rand() / (RAND_MAX + 1.0)));
    printf("\t\tconsume_item: item=%d\n", item);
}

// 아이템을 버퍼에서 제거하는 함수
int remove_item(int *temp) {
    int status = pthread_mutex_lock(&bb.mutex);
    if (status != 0) return status;

    // 버퍼가 비어있다면 대기
    while (bb.totalitems <= 0) {
        status = pthread_cond_wait(&bb.full, &bb.mutex);
        if (status != 0) {
            pthread_mutex_unlock(&bb.mutex);
            return status;
        }
    }

    // 아이템 제거 및 인덱스 조정
    *temp = bb.item[bb.out];
    bb.out = (bb.out + 1) % BUFFER_SIZE;
    bb.totalitems--;

    pthread_cond_signal(&bb.empty);
    return pthread_mutex_unlock(&bb.mutex);
}

// 생산자 스레드 함수
void *producer(void *arg) {
    int item;
    for (int i = 0; i < NUMITEMS; ++i) {
        item = produce_item();
        insert_item(item);
    }
    return NULL;
}

// 소비자 스레드 함수
void *consumer(void *arg) {
    int item;
    for (int i = 0; i < NUMITEMS; ++i) {
        remove_item(&item);
        consume_item(item);
    }
    return NULL;
}

// 메인 함수
int main() {
    srand(time(NULL)); // 난수 생성기 초기화

    pthread_t producer_tid, consumer_tid;

    // 생산자 스레드 생성
    if (pthread_create(&producer_tid, NULL, producer, NULL) != 0) {
        perror("Create producer thread");
    }

    // 소비자 스레드 생성
    if (pthread_create(&consumer_tid, NULL, consumer, NULL) != 0) {
        perror("Create consumer thread");
    }

    // 스레드가 종료될 때까지 대기
    pthread_join(producer_tid, NULL);
    pthread_join(consumer_tid, NULL);

    return 0;
}

