#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>

#include "unp.h"
#include "ioutil.h"

#define MAXMESG 2048

void str_echo(
    int sockfd
)
{
  int n;
  char line[MAXLINE];

  for (;;) {
    n = readline(sockfd, line, MAXLINE);
    if (n == 0) {
      return ;
    } else if (n < 0) {
      err_dump("str_echo: readline error");
    }

    if (writen(sockfd, line, n) != n) {
      err_dump("str_echo: writen error");
    }
  }
}

void str_cli(
    register FILE *fp,
    register int sockfd
)
{
  int n;
  char sendline[MAXLINE], recvline[MAXLINE + 1];

  while (fgets(sendline, MAXLINE, fp) != NULL) {
    n = strlen(sendline);
    if (writen(sockfd, sendline, n) != n) {
      err_sys("str_cli: writen error on socket");
    }

    n = readline(sockfd, recvline, MAXLINE);
    if (n < 0) {
      err_dump("str_cli: readline error");
    }
    recvline[n] = 0;
    fputs(recvline, stdout);
  }

  if (ferror(fp)) {
    err_sys("str_cli: error reading file");
  }
}

void dg_echo(
    int sockfd,
    struct sockaddr *pcli_addr,
    int maxclilen
)
{
  int n, clilen;
  char mesg[MAXMESG];

  for (;;) {
    clilen = maxclilen;
    n = recvfrom(sockfd, mesg, MAXMESG, 0, pcli_addr, (socklen_t *)&clilen);
    if (n < 0) {
      err_dump("dg_echo: recvfrom error");
    }
    if (sendto(sockfd, mesg, n, 0, pcli_addr, clilen) != n) {
      err_dump("dg_echo: sendto error");
    }
  }
}

void dg_cli(
    FILE *fp,
    int sockfd,
    struct sockaddr *pserv_addr,
    int servlen
)
{
  int n;
  char sendline[MAXLINE], recvline[MAXLINE + 1];

  while (fgets(sendline, MAXLINE, fp) != NULL) {
    n = strlen(sendline);
    if (sendto(sockfd, sendline, n, 0, pserv_addr, servlen) != n) {
      err_dump("dg_cli: sendto error on socket");
    }

    n = recvfrom(sockfd, recvline, MAXLINE, 0, (struct sockaddr *)0, (socklen_t *)0);
    if (n < 0) {
      err_dump("dg_cli: recvfrom error");
    }
    recvline[n] = 0;
    fputs(recvline, stdout);
  }

  if (ferror(fp)) {
    err_dump("dg_cli: error reading file");
  }
}
