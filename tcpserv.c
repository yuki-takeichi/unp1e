#include "unp.h"
#include "netutil.h"

#include "inet.h"

int main(
    int argc,
    char *argv[]
)
{
  int sockfd, newsockfd, clilen, childpid;
  struct sockaddr_in cli_addr, serv_addr;

  pname = argv[0];

  if ( (sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
    err_dump("server: can't open stream socket");
  }

  bzero((char *)&serv_addr, sizeof(serv_addr)); /* macro bzero calls memset */
  serv_addr.sin_family = AF_INET;
  serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
  serv_addr.sin_port = htons(SERV_TCP_PORT);

  if (bind(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
    err_dump("server: can't bind local address");
  }

  listen(sockfd, 5);

  for (;;) {
    clilen = sizeof(cli_addr);
    newsockfd = accept(sockfd, (struct sockaddr *)&cli_addr, (socklen_t *)&clilen);

    if (newsockfd < 0) {
      err_dump("server: accept error");
    }

    if ( (childpid = fork()) < 0) {
      err_dump("server: fork error");
    } else if (childpid == 0) {
      close(sockfd);
      str_echo(newsockfd);
      exit(0);
    } else {
      close(newsockfd);
    }
  }

  return 0;
}
