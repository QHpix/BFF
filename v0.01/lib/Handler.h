#ifndef HANDLER_H
#define HANDLER_H
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
struct PIPE{
  int in;
  int out;
};
class Handler{
public:
  Handler();
private:
};


#endif
