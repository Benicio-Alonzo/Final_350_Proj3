#include "types.h"
#include "stat.h"
#include "user.h"

//#define STUB_FUNCS
#ifndef STUB_FUNCS
//int mask(int m){}
//int term(int pid){}
//int stop(int pid){}
//int cont(int pid){}
//int interrupt(int pid){}
#endif

void
printstat(int stat, int pid, int expected){
  char* statstring;
  
  switch(stat){
    case 2: 
      statstring = "BLOCKED";
      break;
    case 1:
      statstring = "RUNNABLE";
      break;
    case 3: 
      statstring = "TERMINATED";
      break;
    case 4:
      statstring = "CREATION";
      break;
    case 5:
      statstring = "BLOCKED"; 
      break;
    default:
      statstring = "ERROR -- IMPOSSIBLE STATE REACHED";
  } 

  printf(1, "PID %d is in state %s\n", pid, statstring);
  if(stat == expected){
    printf(1, "Test Passed\n");
  } else {
    printf(1, "Test Failed\n");
  }

  return 0;
}

void
test_header(int test_n, char* text){
  printf(1, "######################################\n");
  printf(1, "sig_test: Starting test %d\n", test_n);
  printf(1, "Test %d: %s\n", test_n, text);
  printf(1, "######################################\n\n\n");
}
void
test_footer(){
  printf(1,"\n\n\n");
}

void
test_1(void){
  //Testcase 1
  int pid, stat;
  test_header(1, "Termination signal with mask 0 -- child should terminate");

  pid = fork();
  if(pid == 0){
    char *args[] = {"mask", "0", 0};
    exec("mask", args); 
    exit();
  }

  sleep(100);
  term(pid);
  sleep(100);

  stat = pstat(pid);
  printstat(stat, pid, 3);
  kill(pid);
  test_footer();
}

void
test_2(void){
  //Testcase 1
  int pid, stat;
  test_header(2, "termination signal with mask 1 -- child should not terminate");
  
  pid = fork();
  if(pid == 0){
    char *args[] = {"mask", "1", 0};
    exec("mask", args); 
    exit();
  }

  sleep(100);
  term(pid);
  sleep(100);

  stat = pstat(pid);
  printstat(stat, pid, 1);
  kill(pid);
  test_footer();
}

void test_3(void) {
  //Testcase 3
  int pid, stat;

  test_header(3, "termination signal with mask 95 -- child should terminate");

  pid = fork();
  if(pid == 0){
    char *args[] = {"mask", "96", 0};
    exec("mask", args); 
    exit();
  }

  sleep(100);
  term(pid);
  sleep(100);

  stat = pstat(pid);
  printstat(stat, pid, 3);
  kill(pid);
  test_footer();
}

void test_4(void){
  //Testcase 4
  int pid, stat;
  test_header(4, "termination signal with mask 5 -- child should not terminate");

  pid = fork();
  if(pid == 0){
    char *args[] = {"mask", "3", 0};
    exec("mask", args); 
    exit();
  }

  sleep(100);
  term(pid);
  sleep(100);

  stat = pstat(pid);
  printstat(stat, pid, 1);
  kill(pid);
  test_footer();
}

void test_5(void){
  int pid, stat;

  test_header(5, "stop and cont signals with mask 0 -- child should stop \n");

  pid = fork();
  if(pid == 0){
    char *args[] = {"mask", "0", 0};
    exec("mask", args); 
    exit();
  }

  sleep(100);
  stop(pid);
  sleep(100);

  stat = pstat(pid);
  printf(1, "%d\n", stat);
  printstat(stat, pid, 5);
  
  sleep(100);
  cont(pid);
  sleep(100);

  stat = pstat(pid);
  printf(1, "%d\n", stat);
  printstat(stat, pid, 1);
 
  kill(pid);
  test_footer();
}

void test_6(void){
  int pid, stat;
  test_header(6, "stop and cont signals with mask 7 -- child should not stop\n");

  pid = fork();
  if(pid == 0){
    char *args[] = {"mask", "7", 0};
    exec("mask", args); 
    exit();
  }

  sleep(100);
  stop(pid);
  sleep(100);

  stat = pstat(pid);
  printstat(stat, pid, 1);
  
  sleep(100);
  cont(pid);
  sleep(100);

  stat = pstat(pid);
  printstat(stat, pid, 1);
 
  kill(pid);
  test_footer();
}

void test_7(void){
  int pid, stat;
  test_header(7, "cont signal before stop with mask 0 -- child should ignore cont \n");

  pid = fork();
  if(pid == 0){
    char *args[] = {"mask", "0", 0};
    exec("mask", args); 
    exit();
  }

  sleep(100);
  cont(pid);
  sleep(100);

  stat = pstat(pid);
  printstat(stat, pid, 1);
  
  sleep(100);
  stop(pid);
  sleep(100);

  stat = pstat(pid);
  printstat(stat, pid, 5);
 
  kill(pid);
  test_footer();
}

void test_8(void){
  int pid, stat;
  test_header(8, "2x stop and cont with mask 5 -- child should stop then continue \n");

  pid = fork();
  if(pid == 0){
    char *args[] = {"mask", "5", 0};
    exec("mask", args); 
    exit();
  }

  sleep(100);
  stop(pid);
  sleep(100);

  stat = pstat(pid);
  printstat(stat, pid, 5);
  
  sleep(100);
  stop(pid);
  sleep(100);

  stat = pstat(pid);
  printstat(stat, pid, 5);

  sleep(100);
  cont(pid);
  sleep(100);

  stat = pstat(pid);
  printstat(stat, pid, 1);

  kill(pid);
  test_footer();
}

void
test_9(void){
  //Testcase 1
  int pid, stat;

  test_header(9, "interrupt signal with mask 0 -- child should terminate\n");

  pid = fork();
  if(pid == 0){
    char *args[] = {"mask", "0", 0};
    exec("mask", args); 
    exit();
  }

  sleep(100);
  interrupt(pid);
  sleep(100);

  stat = pstat(pid);
  printstat(stat, pid, 3);
  kill(pid);
  test_footer();
}

void
test_10(void){
  //Testcase 1
  int pid, stat;

  test_header(10,"interrupt signal with mask 4 -- child should not terminate\n");


  pid = fork();
  if(pid == 0){
    char *args[] = {"mask", "4", 0};
    exec("mask", args); 
    exit();
  }

  sleep(100);
  interrupt(pid);
  sleep(100);

  stat = pstat(pid);
  printstat(stat, pid, 1);
  kill(pid);
  test_footer();
}


void
sig_test(void)
{
  test_1();
  test_2();
  test_3();
  test_4();
  test_5();
  test_6();
  test_7();
  test_8();
  test_9();
  test_10();
}

int
main(void)
{
  sig_test();
  exit();
}
