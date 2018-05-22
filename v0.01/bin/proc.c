#include <stdio.h>

int main(){
  char buf[50];
  read(0, buf, sizeof(buf));
  printf("RECEIVED: %s", buf);
  return 0;
}
