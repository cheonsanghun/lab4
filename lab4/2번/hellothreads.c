#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define NUM_THREADS 3 // 생성할 스레드의 수 정의

// 스레드 함수 정의
void *hello_thread(void *arg) {
    printf("Thread %ld: Hello, World!\n", (long) arg); // 스레드에서 메시지 출력
    return arg; // 스레드 종료 시 반환값 전달
}

int main() {
    pthread_t tid[NUM_THREADS]; // 스레드 식별자 배열
    int i, status; // 반복문을 위한 변수 및 스레드 생성 상태

    // 스레드 생성
    for (i = 0; i < NUM_THREADS; i++) {
        status = pthread_create(&tid[i], NULL, hello_thread, (void *) (long) i);
        if (status != 0) {
            fprintf(stderr, "Create thread %d: %d\n", i, status); // 스레드 생성 실패 시 오류 메시지 출력
            exit(1); // 비정상 종료
        }
    }

    pthread_exit(NULL); // 메인 스레드 종료 대기
    // pthread_exit을 호출하여 메인 스레드가 종료되어도 다른 스레드가 계속 실행될 수 있도록 함
    return 0; // 정상 종료 (이 코드는 실제로 실행되지 않음)
}
