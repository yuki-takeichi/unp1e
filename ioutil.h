#pragma once

int readn(
    register int fd,
    register char *ptr,
    register int nbytes
);

int writen(
    register int fd,
    register char *ptr,
    register int nbytes
);

int readline(
    register int fd,
    register char *ptr,
    register int maxlen
);
