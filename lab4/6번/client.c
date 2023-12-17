#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<arpa/inet.h>
#include<sys/socket.h>
#include<pthread.h>
#include<time.h>

#define BUF_SIZE 100        // 버퍼 크기 정의
#define NORMAL_SIZE 20      // 일반 텍스트 크기 정의
#define MYPORT 3333         // 사용할 포트 번호

void* send_msg(void* arg);  // 메시지 전송 함수
void* recv_msg(void* arg);  // 메시지 수신 함수
void error_handling(char* msg); // 에러 처리 함수

char name[NORMAL_SIZE]="[기본]";  // 사용자 이름
char msg[BUF_SIZE];               // 메시지 버퍼

int main(int argc, char *argv[]) {
    int sock;
    struct sockaddr_in serv_addr;
    pthread_t snd_thread, rcv_thread;
    void* thread_return;

    // 인자 개수 확인
    if (argc!=3) {
        printf("사용법: %s <IP> <이름>\n", argv[0]);
        exit(1);
    }

    // 사용자 이름 설정
    sprintf(name, "[%s]", argv[2]);
    sock = socket(PF_INET, SOCK_STREAM, 0); // 소켓 생성

    // 서버 주소 설정
    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = inet_addr(argv[1]);
    serv_addr.sin_port = htons(MYPORT);

    // 서버에 연결
    if (connect(sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) == -1)
        error_handling("연결 실패");

    printf("채팅 시작!\n");

    // 송수신 스레드 생성
    pthread_create(&snd_thread, NULL, send_msg, (void*)&sock);
    pthread_create(&rcv_thread, NULL, recv_msg, (void*)&sock);
    pthread_join(snd_thread, &thread_return);
    pthread_join(rcv_thread, &thread_return);
    close(sock); // 소켓 닫기
    return 0;
}

void* send_msg(void* arg) {
    int sock = *((int*)arg);
    char name_msg[NORMAL_SIZE + BUF_SIZE];

    while(1) {
        fgets(msg, BUF_SIZE, stdin); // 표준 입력으로부터 메시지 읽기
        if (!strcmp(msg, "q\n") || !strcmp(msg, "Q\n")) {
            close(sock);
            exit(0);
        }
        sprintf(name_msg, "%s %s", name, msg);
        write(sock, name_msg, strlen(name_msg)); // 메시지 전송
    }
    return NULL;
}

void* recv_msg(void* arg) {
    int sock = *((int*)arg);
    char name_msg[NORMAL_SIZE + BUF_SIZE];
    int str_len;

    while(1) {
        str_len = read(sock, name_msg, NORMAL_SIZE + BUF_SIZE - 1); // 메시지 수신
        if (str_len == -1)
            return (void*)-1;
        name_msg[str_len] = 0;
        fputs(name_msg, stdout); // 수신 메시지 출력
    }
    return NULL;
}

void error_handling(char* msg) {
    fputs(msg, stderr); // 에러 메시지 출력
    fputc('\n', stderr);
    exit(1);
}

