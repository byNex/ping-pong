#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>

enum{CMD, PORT};

int main(int argc, char * argv[])
{
    int sock, sock_clinet;
    int sock_client_len;
    struct sockaddr_in sock_addr, sock_clinet_addr;
    char buf[1024];

    if(argc != 2){
        printf("Usage %s <PORT>\n",argv[CMD]);
        exit(1);
    }

// 소켓을 {{
    sock=socket(AF_INET,SOCK_STREAM,0);
    if(sock < 0){
        perror("socket ");
        exit(1);
    }
// }} 여는 부분

// 서버의 주소를{{ 
    memset(&sock_addr,0x00,sizeof(sock_addr));
    sock_addr.sin_family = AF_INET;
    sock_addr.sin_addr.s_addr = htons(INADDR_ANY);    //INADDR_ANY는 실행 중인 컴퓨터에 IP 주소를 의미한다.
    sock_addr.sin_port=htons(atoi(argv[PORT]));
// }} 설정하는 부분

// 설정된 주소로 {{
    if(bind(sock,(struct sockaddr *)&sock_addr, sizeof(sock_addr)) < 0){
        perror("bind ");
        exit(1);
    }
// }} 서버를 여는 부분

// 연결을 {{
    if(listen(sock,5) < 0){
        perror("listen ");
        exit(1);
    }
// }} 기다리는 부분

// 클라이언트의 연결을 {{
    sock_client_len = sizeof(sock_clinet_addr);
    sock_clinet = accept(sock,(struct sockaddr *)&sock_clinet_addr, &sock_client_len);
    if(sock_clinet < 0){
        perror("accept ");
        exit(1);
    }
// 받는 부분

// 데이터를 {{
    while(1){
        if(read(sock_clinet,buf,sizeof(buf)) < 1){
            perror("read ");
            exit(1);
        }

        printf("====Ping data====\n%s\n====================\n", buf);

        if(write(sock_clinet,buf,sizeof(buf))<0){
            perror("write ");
            exit(1);
        }
    }
// }} 주고 받는 부분

    close(sock_clinet);
    close(sock);
    return 0;
}
