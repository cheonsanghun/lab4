#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <fcntl.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#define PORT 8942        // 서버 포트
#define QLEN 10          // 대기 큐의 길이
#define BUF_SIZE 1024    // 버퍼 크기

// 함수 선언
void handle_clnt(int client_sock); // 클라이언트 처리 함수
void send_err(int client_sock);    // 에러 응답 전송 함수
void send_msg(int client_sock);    // 메시지 전송 함수

int main(int argc, char *argv[])
{
    int sockfd, new_fd;  // 서버 소켓 및 클라이언트 소켓
    struct sockaddr_in server_addr; // 서버 주소 구조체
    struct sockaddr_in client_addr; // 클라이언트 주소 구조체
    socklen_t alen;
    fd_set readfds, activefds; // 파일 디스크립터 세트
    int i, maxfd = 0;

    sockfd = socket(AF_INET, SOCK_STREAM, 0); // 소켓 생성
    if (sockfd < 0) {
        perror("socket() failed");
        exit(1);
    }

    // 서버 주소 설정
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);

    // 소켓 바인딩 및 리스닝
    if (bind(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("bind() failed");
        exit(1);
    }

    if (listen(sockfd, QLEN) < 0) {
        perror("listen() failed");
        exit(1);
    }

    alen = sizeof(client_addr);
    FD_ZERO(&activefds); // 파일 디스크립터 세트 초기화
    FD_SET(sockfd, &activefds); // 서버 소켓 파일 디스크립터 추가
    maxfd = sockfd; // 최대 파일 디스크립터 설정

    printf("Server up and running.\n");

    while(1) {
        printf("SERVER: Waiting for contact..., %d\n", maxfd);
        readfds = activefds;

        // select()를 사용하여 입력 대기
        if (select(maxfd + 1, &readfds, NULL, NULL, NULL) < 0) {
            perror("select() error");
            exit(EXIT_FAILURE);
        }

        for (i = 0; i <= maxfd; i++) {
            if (FD_ISSET(i, &readfds)) {
                if (i == sockfd) {
                    // 클라이언트 연결 수락
                    new_fd = accept(sockfd, (struct sockaddr *)&client_addr, &alen);
                    if (new_fd < 0) {
                        perror("accept() failed");
                        exit(1);
                    }
                    FD_SET(new_fd, &activefds); // 새 클라이언트 추가
                    if (new_fd > maxfd) {
                        maxfd = new_fd;
                    }
                } else {
                    // 클라이언트 요청 처리
                    handle_clnt(i);
                    close(i); // 클라이언트 연결 종료
                    FD_CLR(i, &activefds); // 파일 디스크립터 세트에서 제거
                }
            }
        }
    }
    close(sockfd); // 서버 소켓 닫기
    return 0;
}

void handle_clnt(int client_sock)
{
    char msg[BUF_SIZE]; // 메시지 버퍼
    memset(msg, 0, BUF_SIZE); // 버퍼 초기화

    int str_len = read(client_sock, msg, BUF_SIZE - 1); // 클라이언트로부터 메시지 읽기
    if (str_len < 0) {
        perror("read() error");
        send_err(client_sock); // 에러 응답 전송
        return;
    }

    char method[10], path[BUF_SIZE]; // HTTP 메소드 및 경로
    sscanf(msg, "%s %s", method, path); // 메시지에서 메소드와 경로 추출
    if (strcmp(method, "GET") != 0) {
        send_err(client_sock); // GET 메소드가 아닐 경우 에러 응답 전송
    } else {
        send_msg(client_sock); // 메시지 전송
    }
}

void send_err(int client_sock)
{
    // HTTP 에러 응답 메시지 구성 및 전송
    char protocol[] = "HTTP/1.1 400 Bad Request\r\n";
    char server[] = "Server: CustomServer/1.0\r\n";
    char contenttype[] = "Content-Type: text/html\r\n";
    char html[] = "<html><head><title>Bad Request</title></head><body><h1>Bad Request</h1></body></html>\r\n";
    char end[] = "\r\n";

    write(client_sock, protocol, strlen(protocol));
    write(client_sock, server, strlen(server));
    write(client_sock, contenttype, strlen(contenttype));
    write(client_sock, end, strlen(end));
    write(client_sock, html, strlen(html));
    close(client_sock); // 클라이언트 소켓 닫기
}

void send_msg(int client_sock)
{
    // HTTP 정상 응답 메시지 구성 및 전송
    char protocol[] = "HTTP/1.1 200 OK\r\n";
    char server[] = "Server: CustomServer/1.0\r\n";
    char contenttype[] = "Content-Type: text/html\r\n";
    char html[] = "<html><body><h1>This is last homework!</h1></body></html>\r\n";
    char end[] = "\r\n";

    char contentlength[100];
    sprintf(contentlength, "Content-Length: %ld\r\n", strlen(html));

    write(client_sock, protocol, strlen(protocol));
    write(client_sock, server, strlen(server));
    write(client_sock, contentlength, strlen(contentlength));
    write(client_sock, contenttype, strlen(contenttype));
    write(client_sock, end, strlen(end));
    write(client_sock, html, strlen(html));
    close(client_sock); // 클라이언트 소켓 닫기
}

