#include	"unp.h"

#define SEQFILE "seqno"
#define MAXBUFF 100

void my_lock(int fd)
{
  return;
}

void my_unlock(int fd)
{
  return;
}

int main() {
  int fd, i, n, pid, seqno;
  char buff[MAXBUFF + 1];

  pid = getpid();
  if ( (fd = open(SEQFILE, 2)) < 0 ) {
    err_sys("can't open %s", SEQFILE);
  }

  for (i = 0; i < 20; i++) {
    my_lock(fd);

    lseek(fd, 0L, 0);
    if ( (n = read(fd, buff, MAXBUFF)) <= 0 ) {
      err_sys("read error");
    }
    buff[n] = '\0';

    if ( (n = sscanf(buff, "%d\n", &seqno)) != 0 ) {
      err_sys("sscanf error");
    }
    printf("pid = %d, seq# = %d\n", pid, seqno);
    seqno++;

    sprintf(buff, "%03d\n", seqno);
    n = strlen(buff);
    lseek(fd, 0L, 0);
    if (write(fd, buff, n) != n) {
      err_sys("write error");
    }

    my_unlock(fd);
  }
  return 0;
}
