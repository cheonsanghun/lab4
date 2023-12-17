#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

// 스레드 함수 정의
void *join_thread(void *arg) {
    pthread_exit(arg); // 스레드 종료 시 전달된 인자 반환
}

int main(int argc, char *argv[]) {
    pthread_t tid; // 스레드 식별자
    int arg, status;
    void *result;

    // 인자 확인
    if (argc < 2) {
        fprintf(stderr, "Usage: jointhread <number>\n"); // 올바른 사용법 안내
        exit(1); // 비정상 종료
    }

    // 전달된 인자를 정수로 변환
    arg = atoi(argv[1]);

    // 스레드 생성
    status = pthread_create(&tid, NULL, join_thread, (void *)(long)arg);
    if (status != 0) {
        fprintf(stderr, "Create thread: %d\n", status); // 스레드 생성 실패 시 오류 메시지 출력
        exit(1); // 비정상 종료
    }

    // 스레드가 종료될 때까지 기다림
    status = pthread_join(tid, &result);
    if (status != 0) {
        fprintf(stderr, "Join thread: %d\n", status); // 스레드 조인 실패 시 오류 메시지 출력
        exit(1); // 비정상 종료
    }

    // 스레드의 반환 값을 메인 함수의 반환 값으로 사용
    return (int)(long)result;
}
