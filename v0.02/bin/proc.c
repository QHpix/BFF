#include <stdio.h>

int main(){
  char buf[50];
  gets(buf);
  printf("RECEIVED: %s", buf);
  return 0;
}
