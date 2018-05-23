#include "lib/Handler.h"

Handler::Handler(const char *name, int inp[2], int outp[2]){
  _pid = 0;
  pipe(inp);
  pipe(outp);
  _pid = fork();
  if(_pid == 0)
  {
      //something child
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
