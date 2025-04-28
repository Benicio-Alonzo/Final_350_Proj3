#include "types.h"
#include "x86.h"
#include "defs.h"
#include "date.h"
#include "param.h"
#include "memlayout.h"
#include "mmu.h"
#include "proc.h"

int sys_pstat(void){
  int pid;

  if(argint(0, &pid) < 0){
    return -1;
  }
  return p_stat(pid);
}

int
sys_fork(void)
{
  return fork();
}

int
sys_exit(void)
{
  exit();
  return 0;  
}

int
sys_wait(void)
{
  return wait();
}

int
sys_kill(void)
{
  int pid;

  if(argint(0, &pid) < 0)
    return -1;
  return kill(pid);
}

int
sys_getpid(void)
{
  return myproc()->pid;
}

int
sys_sbrk(void)
{
  int addr;
  int n;

  if(argint(0, &n) < 0)
    return -1;
  addr = myproc()->sz;
  if(growproc(n) < 0)
    return -1;
  return addr;
}

int
sys_sleep(void)
{
  int n;
  uint ticks0;

  if(argint(0, &n) < 0)
    return -1;
  acquire(&tickslock);
  ticks0 = ticks;
  while(ticks - ticks0 < n){
    if(myproc()->killed){
      release(&tickslock);
      return -1;
    }
    sleep(&ticks, &tickslock);
  }
  release(&tickslock);
  return 0;
}


int
sys_uptime(void)
{
  uint xticks;

  acquire(&tickslock);
  xticks = ticks;
  release(&tickslock);
  return xticks;
}

int sys_shutdown(void)
{
  
  outw(0xB004, 0x0|0x2000); 
  outw(0x604, 0x0|0x2000); 
  
  return 0;
}

int
sys_cps(void)
{
  return cps();
}

int
sys_chpr(void)
{
  int pid, pr;
  if(argint(0, &pid) < 0)
    return -1;
  if(argint(1, &pr) < 0)
    return -1;

  return chpr(pid, pr);
}


int
sys_term(void)
{
  int pid;
  if(argint(0, &pid) < 0)
    return -1;
  return sigterm(pid);
}
int
sys_mask(void)
{
  int m;
  if (argint(0, &m) < 0)
    return -1;

  myproc()->sig_mask = m;
  return 0;
}
int sys_stop(void) {
  int pid;
  if(argint(0, &pid) < 0)
    return -1;
  return sigstop(pid);
}

int sys_cont(void) {
  int pid;
  if(argint(0, &pid) < 0)
    return -1;
  return sigcont(pid);
}
int
sys_interrupt(void)
{
  int pid;
  if(argint(0, &pid) < 0)
    return -1;
  return sigint(pid);  
}

int
sys_fgproc(void)
{
  return fgproc();
}






