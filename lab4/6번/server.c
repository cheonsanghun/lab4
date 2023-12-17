#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<arpa/inet.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<pthread.h>
#include<time.h>

#define BUF_SIZE 100        // 버퍼 크기
#define MYPORT 3333         // 서버 포트 번호
#define MAX_CLNT 100        // 최대 클라이언트 수
#define MAX_IP 30

// 함수 선언
void *handle_clnt(void *arg); // 클라이언트 처리 스레드 함수
void send_msg(char *msg, int len); // 메시지 전송 함수
void error_handling(char *msg); // 에러 처리 함수
char *serverState(int count); // 서버 상태 확인 함수

int clnt_cnt=0; // 현재 클라이언트 수
int clnt_socks[MAX_CLNT]; // 클라이언트 소켓 배열
pthread_mutex_t mutx; // 뮤텍스

int main(int argc, char *argv[]){
    int serv_sock, clnt_sock; // 서버 및 클라이언트 소켓
    struct sockaddr_in serv_adr, clnt_adr; // 서버 및 클라이언트 주소 구조체
    int clnt_adr_sz;
    pthread_t t_id; // 스레드 ID

    pthread_mutex_init(&mutx, NULL); // 뮤텍스 초기화
    serv_sock=socket(PF_INET, SOCK_STREAM, 0); // 서버 소켓 생성
    
    // 서버 주소 설정
    memset(&serv_adr, 0, sizeof(serv_adr));
    serv_adr.sin_family=AF_INET;
    serv_adr.sin_addr.s_addr=htonl(INADDR_ANY);
    serv_adr.sin_port=htons(MYPORT);
 
    // 소켓 바인딩 및 리스닝
    if (bind(serv_sock, (struct sockaddr*)&serv_adr, sizeof(serv_adr))==-1)
        error_handling("bind() 실패");
    if (listen(serv_sock, 5)==-1)
        error_handling("listen() 실패");

    printf("서버 시작!!\n");
 
    while(1){
        clnt_adr_sz=sizeof(clnt_adr);
        clnt_sock=accept(serv_sock, (struct sockaddr*)&clnt_adr, &clnt_adr_sz); // 클라이언트 연결 수락
 
        pthread_mutex_lock(&mutx);
        clnt_socks[clnt_cnt++]=clnt_sock; // 클라이언트 소켓 저장
        pthread_mutex_unlock(&mutx);
 
        pthread_create(&t_id, NULL, handle_clnt, (void*)&clnt_sock); // 클라이언트 처리 스레드 생성
        pthread_detach(t_id); // 스레드 분리
        printf("연결된 클라이언트 IP : %s ", inet_ntoa(clnt_adr.sin_addr));
        printf("채팅 참가자 (%d/100)\n", clnt_cnt);
    }
    close(serv_sock); // 서버 소켓 닫기
    return 0;
}

void *handle_clnt(void *arg){
    int clnt_sock=*((int*)arg); // 클라이언트 소켓
    int str_len=0, i;
    char msg[BUF_SIZE];

    // 클라이언트로부터 메시지 수신
    while((str_len=read(clnt_sock, msg, sizeof(msg)))!=0)
        send_msg(msg, str_len); // 수신 메시지를 다른 클라이언트에게 전송

    pthread_mutex_lock(&mutx);
    for (i=0; i<clnt_cnt; i++) {
        if (clnt_sock==clnt_socks[i]) {
            while(i++<clnt_cnt-1)
                clnt_socks[i]=clnt_socks[i+1]; // 클라이언트 목록에서 제거
            break;
        }
    }
    clnt_cnt--; // 클라이언트 수 감소
    printf("클라이언트 연결 종료. 현재 채팅 참가자: (%d/100)\n", clnt_cnt);
    pthread_mutex_unlock(&mutx);
    close(clnt_sock); // 클라이언트 소켓 닫기
    return NULL;
}

void send_msg(char* msg, int len){
    int i;
    pthread_mutex_lock(&mutx);
    for (i=0; i<clnt_cnt; i++)
        write(clnt_socks[i], msg, len); // 모든 클라이언트에게 메시지 전송
    pthread_mutex_unlock(&mutx);
}

void error_handling(char *msg){
    fputs(msg, stderr); // 에러 메시지 출력
    fputc('\n', stderr);
    exit(1);
}

char* serverState(int count){
    char* stateMsg = malloc(sizeof(char) * 20);
    strcpy(stateMsg ,"None");
    
    if (count < 5)
        strcpy(stateMsg, "good");
    else
        strcpy(stateMsg, "bad");
    
    return stateMsg;
}

