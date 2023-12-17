#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define PORT 8080

int main() {
    int server_fd, new_socket;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);
    char buffer[1024] = {0};
    char *message = "TCP 서버로부터 안녕하세요";

    // 소켓 생성
    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt));

    // 주소 정보 설정
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    // 포트에 소켓 바인드
    bind(server_fd, (struct sockaddr *)&address, sizeof(address));

    // 연결 대기
    listen(server_fd, 3);
    printf("TCP 서버가 %d 포트에서 연결을 기다립니다...\n", PORT);

    // 클라이언트 연결 수락
    new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen);
    read(new_socket, buffer, 1024);
    printf("클라이언트: %s\n", buffer);

    // 클라이언트에게 응답 보내기
    send(new_socket, message, strlen(message), 0);
    printf("클라이언트에게 응답을 보냈습니다.\n");

    // 소켓 닫기
    close(new_socket);
    close(server_fd);
    return 0;
}

