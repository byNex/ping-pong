# ping-pong
## Server Side Code (server.c)
단계 (해당 함수 혹은 구조체 명) 

소켓을 연다 (socket) 
    > 서버에 주소를 할당한다(sturct sockaddr_in)
       > 서버를 연다 (bind)
           > 연결을 기다린다.(listen)
               > 연결이 오면 허가한다.(accept)
                   > 데이터를 주고 받는다.(read/write)
> 연결을 종료한다. (close)

## Client Side Code (client.c)
소켓을 연다 (socket) 
    > 서버 주소를 삽입한다(sturct sockaddr_in)
       > 서버에게 요청한다. (connect)
           > 데이터를 주고 받는다.(read/write)
> 연결을 종료한다. (close)

### 추가 해야 하는 부분
1. 연결, 해제시 알림
2. -eb 옵션시 브로드 케스트
