#ifndef STUDENT_H
#define STUDENT_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/time.h>

#define BUFLEN 1024 
#define PORT 6666
#define LISTNUM 20
socklen_t len;
unsigned int port;
char buf[BUFLEN];
fd_set rfds;
struct timeval tv;
int retval, maxfd;
#endif
