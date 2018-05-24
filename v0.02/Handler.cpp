#include "lib/Handler.h"

Handler::Handler(){
  // Empty constructor
}

void Handler::config(const char *name, int inp[2], int outp[2]){
  _pid = 0;
  _configured = true;
  pipe(inp);
  pipe(outp);
  _pid = fork();
  if(_pid == 0)
  {
      /*create and define the sigaction struct
      struct sigaction sa;
      sa.sa_handler = Handler::sig_handler;
      sigemptyset(&sa.sa_mask);
      sa.sa_flags = SA_RESTART;
      //handle the signal
      if(sigaction(SIGSEGV, &sa, NULL) == -1)
        printf("Can't handle segfault\n");*/
      dup2(outp[0], STDIN_FILENO);
      dup2(inp[1], STDOUT_FILENO);
      dup2(inp[1], STDERR_FILENO);
      //deliver SIGTERM in case the parent dies
      prctl(PR_SET_PDEATHSIG, SIGTERM);
      execl(name, name, (char*)NULL);
      //in case execl fails
      exit(1);
  }
  close(inp[1]);
  close(outp[0]);
  _pipe.in = inp[0];
  _pipe.out = outp[1];
}

Handler::Handler(const char *name, int inp[2], int outp[2]){
  _pid = 0;
  _configured = true;
  pipe(inp);
  pipe(outp);
  _pid = fork();
  if(_pid == 0)
  {
      /*create and define the sigaction struct
      struct sigaction sa;
      sa.sa_handler = Handler::sig_handler;
      sigemptyset(&sa.sa_mask);
      sa.sa_flags = SA_RESTART;
      //handle the signal
      if(sigaction(SIGSEGV, &sa, NULL) == -1)
        printf("Can't handle segfault\n");*/
      dup2(outp[0], STDIN_FILENO);
      dup2(inp[1], STDOUT_FILENO);
      dup2(inp[1], STDERR_FILENO);
      //deliver SIGTERM in case the parent dies
      prctl(PR_SET_PDEATHSIG, SIGTERM);
      execl(name, name, (char*)NULL);
      //in case execl fails
      exit(1);
  }
  close(inp[1]);
  close(outp[0]);
  _pipe.in = inp[0];
  _pipe.out = outp[1];
}

void Handler::stopConnection(){
  kill(_pid, SIGKILL); //send SIGKILL signal to the child process
  waitpid(_pid, &_status, 0);
}

PIPE Handler::getPipe(){
  return _pipe;
}

/*
* Alpha *
Returns 0 is all went correct
*/
int Handler::recv(char *dest, size_t n){
  read(_pipe.in, dest, n);
}


void Handler::send(const void *data, size_t n){
  write(_pipe.out, data, n);
}


void Handler::_readForever(){
  char buffer[500];
  while(1){
    memset(buffer, 0, sizeof(buffer));
    recv(buffer, sizeof(buffer));
    if (*buffer != '\x00'){
      printf("%s\n", buffer);
      printf("$ ");
      fflush(stdout);
    }
  }
}

/*
This function interacts forever
*/
void Handler::interact(void){
  char buffer[500];
  std::thread readThread (&Handler::_readForever, this);
  printf("$ ");
  fflush(stdout);
  while (1){
    memset(buffer, 0, sizeof(buffer));
    read(0, buffer, sizeof(buffer));
    send(buffer, sizeof(buffer));
  }
}
void Handler::sig_handler(int signo) {
  if (signo == SIGSEGV){
    //terminate the child process
    kill(_pid, SIGTERM);
    child_Died();
  }
}
void Handler::child_Died() {
  char flag[5] = {'D', 'B', 'E', 'E', 'F'};
  printf("Child got SEGFAULT!\n");
  exit(0);
  //handle the segfault from here.
}
pid_t Handler::getPid(){ return _pid;}
