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
#include <iostream>
#include <cstdint> // include this header for size_t

struct PIPE {
    int out;
    int in;
};

class Handler {
    public:
        Handler(const char *name, int inp[2], int outp[2]);
        int recv(char *dest, size_t n);
        void send(const void *data, size_t n);
        void stopConnection();
        PIPE getPipe();
    private:
        pid_t _pid;
        int _status;
        PIPE _pipe;
};


#endif
