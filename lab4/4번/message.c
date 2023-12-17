#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

#define MAX_CLIENTS 4  // 최대 클라이언트 수 정의

pthread_t tid[MAX_CLIENTS], server_tid; // 스레드 식별자 배열 및 서버 스레드 식별자
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER; // 뮤텍스 초기화
pthread_cond_t cond_client = PTHREAD_COND_INITIALIZER; // 클라이언트 조건 변수 초기화
pthread_cond_t cond_server = PTHREAD_COND_INITIALIZER; // 서버 조건 변수 초기화

// 서버 스레드 함수
void *server_thread(void *arg) {
    while (1) {
        pthread_mutex_lock(&mutex);
        pthread_cond_wait(&cond_server, &mutex); // 서버 조건 변수를 기다림

        printf("서버가 메시지를 전송합니다\n");
        pthread_cond_broadcast(&cond_client); // 모든 클라이언트에게 신호 전송

        pthread_mutex_unlock(&mutex);
    }
    return NULL;
}

// 클라이언트 스레드 함수
void *client_thread(void *arg) {
    int id = *((int*)arg); // 클라이언트 ID
    pthread_mutex_lock(&mutex);

    printf("클라이언트 %d가 전송을 기다립니다\n", id);
    pthread_cond_wait(&cond_client, &mutex); // 클라이언트 조건 변수를 기다림

    printf("클라이언트 %d가 메시지를 수신하였습니다\n", id);
    pthread_mutex_unlock(&mutex);
    return NULL;
}

// 메인 함수
int main() {
    int i, id[MAX_CLIENTS]; // 클라이언트 식별자 배열
    
    pthread_create(&server_tid, NULL, server_thread, NULL); // 서버 스레드 생성

    for(i = 0; i < MAX_CLIENTS; i++) {
        id[i] = i;
        pthread_create(&tid[i], NULL, client_thread, &id[i]); // 클라이언트 스레드 생성
        sleep(1); // 간단한 지연
    }

    sleep(2);
    pthread_cond_signal(&cond_server); // 서버 조건 변수에 신호 전송

    for(i = 0; i < MAX_CLIENTS; i++) {
        pthread_join(tid[i], NULL); // 클라이언트 스레드가 종료될 때까지 기다림
    }

    pthread_join(server_tid, NULL); // 서버 스레드가 종료될 때까지 기다림
    return 0;
}

