#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

// 스레드 함수 정의
void *hello_thread(void *arg) {
    printf("Thread: Hello, World!\n"); // 스레드에서 출력
    return arg; // 스레드 종료 시 반환값 전달
}

int main() {
    pthread_t tid; // 스레드 식별자
    int status;    // 스레드 생성 상태

    // 스레드 생성
    status = pthread_create(&tid, NULL, hello_thread, NULL);
    if (status != 0) {
        perror("Create thread"); // 스레드 생성 실패 시 오류 메시지 출력
        exit(1); // 비정상 종료
    }

    pthread_exit(NULL); // 메인 스레드 종료 대기
    // 메인 스레드가 종료되면 모든 스레드가 종료되므로, 
    // pthread_exit을 호출하여 메인 스레드를 종료하지 않고 대기
    return 0; // 정상 종료
}
