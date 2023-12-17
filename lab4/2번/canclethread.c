#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

// 취소 가능한 스레드의 함수
void *cancel_thread(void *arg) {
    int i, state;
    for (i = 0; ; i++) {
        // 스레드의 취소 가능성을 비활성화
        pthread_setcancelstate(PTHREAD_CANCEL_DISABLE, &state);
        printf("Thread: cancel state disabled\n");
        sleep(1);

        // 스레드의 취소 가능성을 이전 상태로 복원
        pthread_setcancelstate(state, &state);
        printf("Thread: cancel state restored\n");

        // 일정 시간마다 취소 요청을 검사
        if (i % 5 == 0)
            pthread_testcancel();
    }
    return arg;
}

int main(int argc, char *argv[]) {
    pthread_t tid; // 스레드 식별자
    int arg, status;
    void *result;

    // 인자 확인
    if (argc < 2) {
        fprintf(stderr, "Usage: cancelthreadtime(sec)\n");
        exit(1);
    }

    // 스레드 생성
    status = pthread_create(&tid, NULL, cancel_thread, NULL);
    if (status != 0) {
        fprintf(stderr, "Create thread: %d", status);
        exit(1);
    }

    // 메인 스레드가 지정된 시간 동안 기다림
    arg = atoi(argv[1]);
    sleep(arg);

    // 스레드 취소 요청
    status = pthread_cancel(tid);
    if (status != 0) {
        fprintf(stderr, "Cancel thread: %d", status);
        exit(1);
    }

    // 스레드의 종료를 기다림
    status = pthread_join(tid, &result);
    if (status != 0) {
        fprintf(stderr, "Join thread: %d", status);
        exit(1);
    }

    // 스레드의 반환값을 메인 함수의 반환값으로 사용
    return (intptr_t)result;
}
