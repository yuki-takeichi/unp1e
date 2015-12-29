#pragma once

#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>

void str_echo(
    int sockfd
);

void str_cli(
    register FILE *fp,
    register int sockfd
);

void dg_echo(
    int sockfd,
    struct sockaddr *pcli_addr,
    int maxclilen
);
