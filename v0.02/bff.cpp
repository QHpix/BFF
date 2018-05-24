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

void sig_handler(int);

Handler hnd;

int main(int argc, char** argv)
{
  char name[50], rcv[50], buffer[50] = "TEST\n";
  int inp[2], outp[2];
  struct sigaction sa;
  strncpy(name, argv[1], sizeof(name));

  hnd = new Handler(name, inp, outp);
  sa.sa_handler = sig_handler;
  sigemptyset(&sa.sa_mask);
  sa.sa_flags = SA_RESTART;
  if(sigaction(SIGSEGV, &sa, NULL) == -1)
    printf("Can't handle segfault\n");
//  hnd.sig_handler(SIGSEGV);
  hnd.interact();
//  hnd.sig_handler(SIGSEGV);
  hnd.stopConnection();
}

void sig_handler(int signo)
{
    if(signo == SIGSEGV){
      kill(hnd.getPid(), SIGTERM);
      hnd.child_Died();
    }
}
