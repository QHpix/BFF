#include<unistd.h>
#include<sys/wait.h>
#include<sys/prctl.h>
#include<signal.h>
#include<stdlib.h>
#include<string.h>
#include<stdio.h>
#include <sys/ptrace.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/user.h>
#include <sys/reg.h>
#include "lib/Handler.h"

int main(int argc, char** argv)
{
  char name[50];
  char rcv[50];
  char buffer[50] = "TEST\n";
  int inp[2], outp[2];
  strncpy(name, argv[1], sizeof(name));
  
  Handler hnd(name, inp, outp);
  printf("[+] Sending %s", buffer);
  hnd.send(buffer, strlen(buffer));
  hnd.recv(rcv, sizeof(rcv));
  printf("[+] RECEVIED: %s", rcv);
  hnd.stopConnection();
}
