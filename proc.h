// Per-CPU state
struct cpu {
  uchar apicid;                
  struct context *scheduler;   
  struct taskstate ts;         
  struct segdesc gdt[NSEGS];   
  volatile uint started;       
  int ncli;                    
  int intena;                  
  struct proc *proc;           
};

extern struct cpu cpus[NCPU];
extern int ncpu;

//PAGEBREAK: 17
// Saved registers for kernel context switches.
// Don't need to save all the segment registers (%cs, etc),
// because they are constant across kernel contexts.
// Don't need to save %eax, %ecx, %edx, because the
// x86 convention is that the caller has saved them.
// Contexts are stored at the bottom of the stack they
// describe; the stack pointer is the address of the context.
// The layout of the context matches the layout of the stack in swtch.S
// at the "Switch stacks" comment. Switch doesn't save eip explicitly,
// but it is on the stack and allocproc() manipulates it.
struct context {
  uint edi;
  uint esi;
  uint ebx;
  uint ebp;
  uint eip;
};

enum procstate { UNUSED, EMBRYO, SLEEPING, RUNNABLE, RUNNING, ZOMBIE, BLOCKED };

// Per-process state
struct proc {
  uint sz;                     
  pde_t* pgdir;                
  char *kstack;                
  enum procstate state;        
  int pid;                     
  struct proc *parent;         
  struct trapframe *tf;        
  struct context *context;     
  void *chan;                  
  int killed;                  
  struct file *ofile[NOFILE];  
  struct inode *cwd;           
  char name[16];               

  int priority;
  
  int sig_mask;  

};



#define STRIDE_TOTAL_TICKETS 100

typedef enum _ENUM_SCHEDULER{
    SCHEDULER_DEFAULT = 0,
    SCHEDULER_STRIDE
} ENUM_SCHEDULER;

