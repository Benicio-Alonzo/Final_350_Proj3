#include "types.h"
#include "stat.h"
#include "user.h"

//#define STUB_FUNCS
#ifndef STUB_FUNCS
//int mask(int m){};
#endif

int
main(int argc, char *argv[])
{
  if(argc != 2) {
    printf(1,"Please provide a signal mask\n");
    exit();
  }

  int sig_mask = atoi(argv[1]); 
  
  mask(sig_mask);
 
  for(;;){ 
  }

  exit();
}
