#include "unp.h"
#include "netutil.h"

#include "inet.h"

int main(
    int argc,
    char *argv[]
)
{
  int sockfd;
  struct sockaddr_in serv_addr;

  pname = argv[0];

  bzero((char *)&serv_addr, sizeof(serv_addr));
  serv_addr.sin_family = AF_INET;
  serv_addr.sin_addr.s_addr = inet_addr(SERV_HOST_ADDR);
  serv_addr.sin_port = htons(SERV_TCP_PORT);

  if ( (sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
    err_sys("client: can't open stream socket");
  }

  if (connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
    err_sys("client: can't connect to server");
  }
  str_cli(stdin, sockfd);

  close(sockfd);
  
  return 0;
}
