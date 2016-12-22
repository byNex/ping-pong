#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>

enum{CMD, IP, PORT};

int main(int argc, char * argv[])
{
    int sock;
    struct sockaddr_in sock_addr;
    char buf[1024];

    if(argc != 3){
        printf("Useage: %s <IP> <PORT>\n", argv[CMD]);
        exit(1);
    }

// 소켓을 {{
    sock=socket(AF_INET,SOCK_STREAM,0);
    if(sock < 0){
        perror("socket ");
        exit(1);
    }
// }} 여는 부분

// 주소를 {{
    memset(&sock_addr,0x00,sizeof(sock_addr));
    sock_addr.sin_family = AF_INET;
    sock_addr.sin_addr.s_addr = inet_addr(argv[IP]);
    sock_addr.sin_port=htons(atoi(argv[PORT]));
// }} 설정하는 부분

// 설정된 주소로 {{
    if(connect(sock,(struct sockaddr *)&sock_addr, sizeof(sock_addr)) < 0){
        perror("connect ");
        exit(1);
    }
// }} 연결하는 부분

// 데이터를 {{
    while(1){
        printf("Input string :");
        scanf("%s",buf);

        if(write(sock,buf,sizeof(buf))<0){
            perror("write ");
            exit(1);
        }

        if(read(sock,buf,sizeof(buf))<0){
            perror("read ");
            exit(1);
        }
        printf("====Pong data====\n%s\n====================\n", buf);
    }
// }} 주고 받는 부분

    close(sock);
    return 0;
}
