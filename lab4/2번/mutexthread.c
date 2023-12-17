#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <stdint.h>  
#define NUM_THREADS 3

pthread_mutex_t mutex; // 공유 자원에 대한 접근을 제어하기 위한 뮤텍스
int sum; // 모든 쓰레드에 의해 공유되는 변수

void *mutex_thread(void *arg)
{
    pthread_mutex_lock(&mutex); // 뮤텍스 잠금
    sum += (intptr_t)arg; // 공유 자원인 sum에 값을 더함
    pthread_mutex_unlock(&mutex); // 뮤텍스 해제
    return arg;
}

int main(int argc, char *argv[])
{
    pthread_t tid[NUM_THREADS]; // 쓰레드 ID 배열
    intptr_t *arg[NUM_THREADS]; // 쓰레드 함수에 전달될 인자 배열
    int i;
    void *result;
    int status;

    if (argc < 4)
    {
        fprintf(stderr, "Usage: mutexthread number1 number2 number3\n");
        exit(1);
    }

    for (i = 0; i < NUM_THREADS; i++)
        arg[i] = (void *)(intptr_t)atoi(argv[i + 1]); // 문자열 인자를 정수로 변환

    pthread_mutex_init(&mutex, NULL); // 뮤텍스 초기화

    // 쓰레드 생성
    for (i = 0; i < NUM_THREADS; i++)
    {
        status = pthread_create(&tid[i], NULL, mutex_thread, arg[i]);
        if (status != 0)
        {
            fprintf(stderr, "Create thread %d: %d\n", i, status);
            exit(1);
        }
    }

    // 쓰레드가 종료될 때까지 대기
    for (i = 0; i < NUM_THREADS; i++)
    {
        status = pthread_join(tid[i], &result);
        if (status != 0)
        {
            fprintf(stderr, "Join thread %d: %d\n", i, status);
            exit(1);
        }
    }

    pthread_mutex_destroy(&mutex); // 뮤텍스 파괴

    printf("sum is %d\n", sum); // 최종 합계 출력

    pthread_exit(result); // 메인 쓰레드 종료
}

