#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define PORT 8080

int main() {
    struct sockaddr_in serv_addr;
    int sock = 0;
    char *hello = "클라이언트에서 보낸 안녕하세요";
    char buffer[1024] = {0};

    // 소켓 생성
    sock = socket(AF_INET, SOCK_STREAM, 0);

    // 서버 주소 설정
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);
    inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr);

    // 서버에 연결
    connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr));
    send(sock, hello, strlen(hello), 0);
    printf("서버에 메시지를 보냈습니다: %s\n", hello);

    // 서버로부터의 응답 받기
    read(sock, buffer, 1024);
    printf("서버의 응답: %s\n", buffer);

    // 소켓 닫기
    close(sock);
    return 0;
}

