#include "lib/Handler.h"

Handler::Handler(){

}
/*
* Alpha *
Returns 0 is all went correct
*/
int Handler::recv(char *dest, uint64_t n){
  read(_pipe.in, dest, n);
}


void Handler::send(const char *data, uint64_t n){
  write(_pipe.out, data, n);
}
