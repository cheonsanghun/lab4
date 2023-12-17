#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <sys/wait.h>
#include <unistd.h>

#define MYPORT 3490 // 포트 번호
#define BACKLOG 10 // 대기중인 연결의 최대 수

int main() {
    int sockfd, new_fd; // listen을 위한 sockfd, 새 연결을 위한 new_fd
    struct sockaddr_in my_addr; // 서버의 주소 정보
    struct sockaddr_in their_addr; // 클라이언트의 주소 정보
    int sin_size;

    // 소켓 생성
    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        perror("socket");
        exit(1);
    }

    my_addr.sin_family = AF_INET;
    my_addr.sin_port = htons(MYPORT);
    my_addr.sin_addr.s_addr = INADDR_ANY; // 자동으로 내 IP 사용
    memset(&(my_addr.sin_zero), 0, 8); // 나머지 구조체를 0으로 초기화

    // 소켓에 주소 바인드
    if (bind(sockfd, (struct sockaddr *)&my_addr, sizeof(struct sockaddr)) == -1) {
        perror("bind");
        exit(1);
    }

    // 연결 대기
    if (listen(sockfd, BACKLOG) == -1) {
        perror("listen");
        exit(1);
    }

    while(1) { // 주 연결 accept 루프
        sin_size = sizeof(struct sockaddr_in);
        if ((new_fd = accept(sockfd, (struct sockaddr *)&their_addr, &sin_size)) == -1) {
            perror("accept");
            continue;
        }

        printf("서버: %s로부터의 연결을 받았습니다.\n", inet_ntoa(their_addr.sin_addr));

        if (!fork()) { // 자식 프로세스
            if (send(new_fd, "안녕하세요, 세계!\n", 18, 0) == -1)
                perror("send");
            close(new_fd);
            exit(0);
        }

        close(new_fd);  // 부모 프로세스는 이 소켓을 사용하지 않음
        while(waitpid(-1, NULL, WNOHANG) > 0); // 자식 프로세스 정리
    }

    return 0;
}

