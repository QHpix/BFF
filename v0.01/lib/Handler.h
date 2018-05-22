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
class Handler {
    public:
        Handler(const char *name);
        int recv(char *dest, uint64_t n);
        void send(const char *data, uint64_t n);
    private:
        int _pid;
        struct PIPE {
            int out;
            int in;
        } _pipe;
};


#endif
