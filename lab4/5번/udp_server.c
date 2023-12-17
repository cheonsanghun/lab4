#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define PORT 8080
#define BUFFER_SIZE 1024

int main() {
    int sockfd;
    char buffer[BUFFER_SIZE];
    struct sockaddr_in servaddr, cliaddr;

    // 소켓 생성
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);

    // 서버 주소 정보 초기화
    memset(&servaddr, 0, sizeof(servaddr));
    memset(&cliaddr, 0, sizeof(cliaddr));

    // 서버 주소 정보 설정
    servaddr.sin_family = AF_INET; // IPv4
    servaddr.sin_addr.s_addr = INADDR_ANY;
    servaddr.sin_port = htons(PORT);

    // 주소에 소켓 바인딩
    bind(sockfd, (const struct sockaddr *)&servaddr, sizeof(servaddr));
    printf("UDP 서버가 %d 포트에서 실행 중입니다...\n", PORT);

    int len, n;
    len = sizeof(cliaddr);

    // 클라이언트로부터 데이터 수신
    n = recvfrom(sockfd, (char *)buffer, BUFFER_SIZE, MSG_WAITALL, (struct sockaddr *)&cliaddr, &len);
    buffer[n] = '\0';
    printf("클라이언트: %s\n", buffer);

    // 클라이언트에 응답 보내기
    char *message = "UDP 서버로부터 안녕하세요";
    sendto(sockfd, message, strlen(message), MSG_CONFIRM, (const struct sockaddr *)&cliaddr, len);
    printf("클라이언트에게 응답을 보냈습니다.\n");

    close(sockfd);
    return 0;
}

