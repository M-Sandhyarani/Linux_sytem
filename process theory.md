### Explain the concept of process creation in operating systems.
```c
Processes are created in UNIX-like systems using the fork() system call.
fork() creates a new child process by duplicating the address space, file descriptors, and code of the parent.
After creation, both the parent and child continue executing independently.
The OS assigns a unique process ID (PID) to each process.

```
### What is the purpose of the wait() system call in process management?
```c
wait() is used by a parent process to wait for the termination of its child.
It prevents zombie processes by allowing the parent to collect the child's exit status.
It blocks the parent until a child finishes
```

## Describe the role of the exec() family of functions in process management
 ```c
The exec() family (execl, execv, execvp, execve, etc.) replaces the current process image with a new program.
Used after fork() to run a different program in the child.
It does not return if successful — the current program is completely replaced.
```

 ## Differentiate between the fork() and exec() system calls.
```c
 `fork()`                             `exec()`                                  
 -----------------------------------  ----------------------------------------- 
 Creates a **new process** (child)    **Replaces** current process image        
 Returns twice (to parent and child)  Never returns if successful               
 Often followed by `exec()`           Used after `fork()` to load a new program 
```

## How does the vfork() system call differ from fork()?
```c
vfork() vs fork()
vfork() is like fork() but:
child shares the same address space as parent until it calls exec() or exit().
Parent is suspended until the child finishes.
Faster than fork(), but dangerous: child must not modify shared memory.
```

## Discuss the significance of the getpid() and getppid() system calls.
```c
getpid() returns the process ID of the calling process.
getppid() returns the parent's process ID.
Useful for process tracking and debugging.

```
## Explain the concept of process termination in UNIX-like operating systems.
```c
A process terminates by:
            Calling exit()
            Returning from main()
            Being terminated by a signal
            Termination results in:
            Resource cleanup
Exit status returned to the parent (waitable)
```

##Describe the process hierarchy in UNIX-like operating systems.
```c
UNIX processes form a tree:
Root is typically init (PID 1 or systemd)
Child processes are spawned by parents using fork()
Hierarchy affects resource control, signal propagation, and job control
```

## What is the purpose of the exit() function in C programming?
```c
exit(status) terminates a process and returns the status to the parent.

Performs:
         Cleanup of I/O buffers
         Closing of file descriptors
         Invokes atexit() handlers

```

## Explain how the execve() system call works and provide a code example.
```c
execve(const char *path, char *const argv[], char *const envp[]):
Loads and executes a new program.
Replaces the current process image.
Requires full path and environment.

#include <unistd.h>
int main() {
    char *args[] = {"/bin/ls", "-l", NULL};
    execve("/bin/ls", args, NULL);
    return 0; // won't reach here if execve is successful
}

```

## Discuss the role of the fork() system call in implementing multitasking
```c
Enables multitasking by allowing a process to spawn another process.
Both run concurrently — essential for parallelism.
Used in shells, servers, and background task execution.

```
## How does the exec() system call replace the current process image with a new one?
```c
When exec() is called:
The entire memory image of the process is replaced.
Only file descriptors and PID are retained.
The new program starts executing from main() as if it's a fresh process.
```

## Explain the concept of process scheduling in operating systems.
```c
Determines which process runs next on the CPU.
Based on scheduling policies like:
First-Come First-Served (FCFS)
Round Robin
Priority Scheduling
Multilevel Queue
Goals: maximize CPU utilization, minimize waiting time, ensure fairness.
```

## Describe the role of the clone() system call in process management
```c
Used to create threads or custom processes.
Allows fine-grained control over what is shared (e.g., memory, file descriptors, etc.).
Used internally by libraries like pthread_create().

Example:

#include <sched.h>
int clone(int (*fn)(void *), void *stack, int flags, void *arg);

Common flags: CLONE_VM, CLONE_FS, CLONE_FILES, CLONE_SIGHAND
```

## Discuss the significance of the setuid() and setgid() system calls in process man
```c
setuid(uid) sets the user ID of the process.
setgid(gid) sets the group ID.
Used for privilege management (e.g., a root-owned process drops privileges for safety).
```

## Explain the concept of process groups and their significance in UNIX-like operating systems
```c
A collection of related processes with the same group ID.
Helps with signal management (e.g., Ctrl+C sends SIGINT to a whole group).
Used in job control and shell environments.

```
## Discuss the role of the execle() function in the exec() family of calls.
```c
Part of the exec() family.
      Executes a new program with a custom environment.
syntax:
    int execle(const char *path, const char *arg0, ..., NULL, char *const envp[]);

```
## Describe the purpose of the nice() system call in process scheduling.
```c
Adjusts the priority of a process (on a scale from -20 to 19).
Lower value = higher priority.
Syntax: nice(int increment);

```
## Explain the role of the getpid() and getppid() functions in process management.
```c
getpid() → current process's ID.
getppid() → parent process's ID.
Used for process tracking, logging, or forking relationships.

```
## Discuss the difference between the fork() and clone() system calls
```c
   `fork()`                  `clone()`                                 
 ------------------------  ----------------------------------------- 
 Creates a new process      Creates threads or processes              
 Shares nothing (default)   Can selectively share memory, files, etc. 
 Simpler                    More control (used for threads)           
```

## Explain the concept of process states in UNIX-like operating systems.
```c
Typical process states:
RUNNING – actively using CPU
SLEEPING – waiting for I/O
STOPPED – paused via signal
ZOMBIE – finished, waiting for parent to collect status
```

## Describe the purpose of the chroot() system call and provide an example.agement.
```c
Changes the root directory (/) for the current process.
Often used for sandboxing or jails.
ex:
chroot("/newroot");
chdir("/");
```

## Discuss the role of the execv() function in the exec() family of call
```c
Executes a program with an argument vector.
Syntax:
      int execv(const char *path, char *const argv[]);

```
## Explain the significance of process identifiers (PIDs) in process management.
```c
Unique ID assigned by OS to every process.
Used for:
      Signal sending (kill(pid, SIGINT))
      Process control
      Parent-child tracking

```
## Discuss the concept of orphan processes and how they are handled in UNIX-like 
operating systems.
```c
A process whose parent has terminated.
Automatically adopted by init (PID 1).
Ensures proper resource cleanup.
```

## Describe the concept of process priority and how it is managed in operating systems.
```c
Determines the order in which processes are scheduled.
Higher-priority processes are chosen first.
Managed using nice() (user space) and setpriority() (system call).
Priority range:
      Nice value: -20 (high) to +19 (low).
Real-time priorities (in SCHED_FIFO, etc.): 
         numeric, strict order.
```


## Explain the purpose of the fork() system call in creating copy-on-write (COW)
processes.
```c
fork() uses COW to optimize memory use:
Parent and child share the same memory pages initially (read-only).
Pages are copied only when written to, reducing overhead.

```
## Discuss the role of the execvp() function in searching for executable files.
```c
Replaces current process image with a new executable.
Searches the executable in the PATH environment variable.
v → takes vector of arguments
p → searches PATH
char *args[] = {"ls", "-l", NULL};
execvp("ls", args);
```

## Explain the concept of process context switching and its impact on system 
performance.
```c
Switching CPU from one process to another.
Involves saving and loading registers, program counters, etc.
Adds overhead; frequent switches reduce performance.
Necessary for multitasking and responsiveness.
```


## Discuss the role of the clone() system call in creating threads in Linux
```c
clone() can create threads by sharing memory (CLONE_VM), file descriptors, etc.
Basis for pthread_create() in Linux.
Offers fine-grained control over what is shared between threads.
```

## Explain the difference between process creation using fork() and pthread_create().
```c
 `fork()`                   `pthread_create()`         
 -------------------------  -------------------------- 
 Creates a new **process**  Creates a new **thread**   
 Has separate memory        Shares memory              
 Slower                     Faster                     
 Safer (isolation)          Efficient (shared context) 

```

## Discuss the significance of the execvp() function in searching for executables in the PATH environment variable
```c
Searches for an executable using PATH, unlike execv() which requires full path.
Allows calling common shell commands like ls, grep without absolute paths.
````

## Describe the role of the fork() system call in implementing the shell's job control.
```c
Shell uses fork() to create child processes for commands.
Can assign process groups, background/foreground execution.
Enables job control with &, fg, bg, kill, etc.

```

## Explain the purpose of the execlp() function and provide an example.
```c
Executes a program with list of arguments and searches PATH.

#include <unistd.h>
int main() {
    execlp("ls", "ls", "-l", NULL);
    return 0;
}

```
## Discuss the significance of the setpgid() system call in managing process groups.
```c
Sets the process group ID of a process.
Helps manage job control, signal handling (e.g., SIGINT to a whole group).
Syntax: setpgid(pid, pgid);

```
## Explain the concept of process priority inheritance and its importance in real-time systems.
```c
Prevents priority inversion (low-priority process blocking a high-priority one).
Temporarily raises the priority of the blocking process.
Important in real-time systems and handled via mutex protocols like PTHREAD_PRIO_INHERIT.

```
## Describe the role of the fork() system call in copy-on-write (COW) mechanism and its benefits
```c
Reduces memory usage during fork() — child shares memory until it writes.
Improves performance in cases where the child immediately calls exec().
```

## Explain the concept of process scheduling policies such as FIFO, Round Robin, and Priority scheduling.
```c
FIFO (SCHED_FIFO):
       Real-time, first-come-first-run, non-preemptive.
Round Robin (SCHED_RR):
        Time-sliced, preemptive, fair to all.
Priority Scheduling:
       Highest priority runs first; can be preemptive or not.
Risk of starvation if not managed.
```

## Discuss the significance of the execve() function in process creation and execution.
```c
execve() is the core function in the exec family.
It replaces the current process image with a new executable.
Used after fork() to run a different program in the child process.
Key Roles:
     Loads a new binary into memory.
     Passes command-line arguments and environment.
     Retains file descriptors (unless marked FD_CLOEXEC).
syntax:
   int execve(const char *pathname, char *const argv[], char *const envp[]);


```
## Explain the concept of process swapping and its role in memory management.
```c
Swapping is the act of moving an entire process out of main memory (RAM) to disk (swap space) and back.
Done when RAM is full and the system needs memory for active processes.
Helps manage limited physical memory, though it's slower.
Effects:
    Makes room for other processes.
    Causes delay (high swap = poor performance).
     Modern systems use paging more than full process swapping.
```


## Discuss the difference between the fork() and pthread_create() functions in terms of process/thread creation.
```c
 Aspect         `fork()`                   `pthread_create()`   
 -------------  -------------------------  -------------------- 
 Creates        A new **process**          A new **thread**     
 Memory         **Separate** memory space  **Shared** memory    
 Scheduling     OS-scheduled process       OS-scheduled thread  
 Overhead       Higher                     Lower                
 Communication  Via IPC (pipes, shm)       Via shared variables 

```

## Describe the purpose of the prctl() system call in process management
```c
prctl() allows you to control specific characteristics of a process.
Common Uses:
      Set process name (PR_SET_NAME)
      Set child subreaper (PR_SET_CHILD_SUBREAPER)
      Disable core dumps
      Set secure bits
Example:
#include <sys/prctl.h>
prctl(PR_SET_NAME, "myprocess");
```

## Explain the concept of process preemption and its impact on system responsiveness
```c
Preemption allows the OS to interrupt a running process to switch to another (usually higher-priority) process.
Ensures fair CPU usage and improves responsiveness.
Impact:
     Allows fast reaction to user inputs or real-time events.
     Prevents one process from hogging the CPU.
     Used in preemptive multitasking operating systems like Linux.

```

##discuss the role of the exec functions in handling file descriptors during process execution.
```c
By default, open file descriptors remain open after an exec() call.
If marked with the FD_CLOEXEC flag, they will be closed automatically during exec().
Example:
fcntl(fd, F_SETFD, FD_CLOEXEC);  // Will close fd on exec

Why it matters:
Ensures security and resource isolation.
Prevents leaking file descriptors across exec’ed programs.

```
##Explain the significance of process priorities and how they affect scheduling 
decisions.
```c
Determines which process gets CPU time first.
High-priority processes run before low-priority ones.
Affects system responsiveness, real-time performance, and fairness.
Adjusted via:
    nice() / renice() (user-level)
    setpriority() (system-level)
    Real-time scheduling classes (SCHED_FIFO, SCHED_RR)
```


## Describe the process of process termination and the various ways it can occur.
```c
A process can terminate in the following ways:
Normal termination: via exit() or return from main().
Abnormal termination: due to errors (e.g., segmentation fault).
Killed by a signal: e.g., SIGKILL, SIGTERM.
Terminated by parent: using kill(pid, sig).
Orphaned and reaped by init (when parent dies).
After termination, the process becomes a zombie until the parent reads its status with wait().

```
### Discuss the role of the exit status in process termination and how it can be retrieved by the parent process
```c
The exit status is an integer returned by exit(status) or return n; in main().
The parent process retrieves it using wait() or waitpid().
Example:
int status;
wait(&status);
if (WIFEXITED(status))
    printf("Child exited with %d\n", WEXITSTATUS(status));
Exit status helps the parent know if the child succeeded or failed.
```


## Explain the concept of process suspension and resumption using signals.
```c
A process can be suspended using:
SIGSTOP (cannot be caught/ignored)
SIGTSTP (Ctrl+Z)
It can be resumed using:
SIGCONT
Use Cases:
   Job control in shells
   Temporarily pausing background tasks

```

## Discuss the role of process scheduling algorithms in determining the order of 
execution among processes.
```c
Scheduling algorithms decide which process runs next. Key types:
FCFS (First Come First Serve)
Round Robin – time-slicing, fair and preemptive
Priority Scheduling
Multilevel Feedback Queues
Real-time Policies: SCHED_FIFO, SCHED_RR
Each has trade-offs between:
Fairness
Throughput
Response time
Real-time guarantees

```

## Explain the concept of process migration and its relevance in distributed systems.
```c
Moving a process from one node to another.
Used for load balancing, fault tolerance, or resource optimization.
Types:
  Preemptive: process paused and moved
  Non-preemptive: newly created processes are migrated
Requires:
    Transparent state transfer
    Synchronization and resource mapping
```


## Describe the role of process identifiers (PIDs) in process management and their 
uniqueness within the system
```c
A Process Identifier (PID) is a unique number assigned to each running process.
Used for:
    Signaling (kill(pid, SIGTERM))
    Parent-child tracking (getppid())
    Debugging
    PIDs are reused after termination and cleanup.
```


## Explain the concept of process tracing and its importance in debugging and 
monitoring.
```c
Tracing allows one process (e.g., debugger) to monitor another.
Tools:
   ptrace() system call
   strace, gdb, ltrace (user-space tools)
Use Cases:
  Inspecting registers and memory
  Catching syscalls
  Debugging crashes or unusual behavior
```

## Discuss the role of the fork() system call in creating copy-on-write (COW) processes and its impact on memory usage.
```c
fork() creates a child process with a copy of the parent's memory.
To optimize memory, pages are shared and marked read-only.
When a process writes, the OS copies only that page.
Reduces memory usage and speeds up fork() especially when immediately followed by exec().

```
## Describe the concept of process control blocks (PCBs) and their role in process 
management.
```c
The PCB is a data structure the OS uses to manage a process.
Contains:
    PID, state, priority
    Program counter, registers
    Memory info (code, stack, heap)
    Open file descriptors
    Stored in kernel space. Every process has one.
```


## Explain the concept of process scheduling classes and their significance in real-time operating systems.
```c
Define how processes are prioritized and scheduled.
Common classes in Linux:
SCHED_OTHER: normal processes
SCHED_FIFO: real-time, no timeslice
SCHED_RR: real-time, round-robin
SCHED_DEADLINE: strict deadline-driven tasks
Used in robotics, multimedia, and systems where timing is critical.

```
## Discuss the role of the vfork() system call in process creation and its differences from fork().
```c
vfork() is similar to fork() but is optimized for cases where the child calls exec() immediately.

 Feature          `fork()`                    `vfork()`                                        
 ---------------  --------------------------  ------------------------------------------------ 
 Memory           Copies address space (COW)  Shares parent’s memory (no copy)                 
 Parent behavior  Continues independently     Suspended until child calls `exec()` or `exit()` 
 Use case         General child creation      Efficient `exec()` after fork                    
 Risk             Safe and isolated           Dangerous if child modifies memory               

Use vfork() only when you're immediately calling exec() to save memory and time.

```

## Describe the purpose of the sigaction() system call in handling signals in processes.
```c
The sigaction() system call is used for advanced signal handling.
Benefits over signal():
   Reliable delivery (no reset needed)
   Can block signals during handler execution
   Can retrieve extra signal info (via siginfo_t)
Structure:

 struct sigaction {
    void (*sa_handler)(int);
    sigset_t sa_mask;
    int sa_flags;
};

Example:

struct sigaction act;
act.sa_handler = handler;
sigemptyset(&act.sa_mask);
act.sa_flags = 0;
sigaction(SIGINT, &act, NULL);


```
## Explain the concept of process migration and its implications in distributed computing environment
```c
Process migration is moving a process from one machine to another at runtime.
 Goals:
    Load balancing
    Fault tolerance
    Efficient resource use
 Challenges:
       Maintaining process state (memory, files, sockets)
       Consistency and synchronization
       Communication and dependencies
       Common in grid, cluster, and cloud environments.
```

## Discuss the role of the sigprocmask() system call in managing signal masks for 
processes.
```c
sigprocmask() is used to block, unblock, or check signals in a process.
syntax:
  int sigprocmask(int how, const sigset_t *set, sigset_t *oldset);
 Actions:
    SIG_BLOCK: add to blocked signals
    SIG_UNBLOCK: remove from blocked
    SIG_SETMASK: replace entire signal mask
Useful for atomic signal blocking during critical sections.
```


## Describe the purpose of the setrlimit() system call in setting resource limits for processes.
```c
setrlimit() sets resource usage limits per process.
Common resources:
   RLIMIT_CPU – CPU time
   RLIMIT_NOFILE – open file descriptors
   RLIMIT_AS – virtual memory size
Example:

struct rlimit rl = {1024, 2048}; // soft, hard
setrlimit(RLIMIT_NOFILE, &rl);
Prevents resource exhaustion and enforces fairness.

```

## Discuss the concept of process groups and their importance in job control and signal propagation
```c
A process group is a collection of related processes with the same PGID.
Why they matter:
  Shells use them to manage foreground/background jobs.
  Signals like SIGINT, SIGTSTP can be sent to the entire group.
Example:
setpgid(pid, pgid);  // Set process group
kill(-pgid, SIGTERM); // Send signal to whole group
Essential for job control, terminal input/output control, and clean signal handling.

```

## Explain the role of the prlimit() system call in setting resource limits for processes.
```c
prlimit() combines getrlimit() and setrlimit() in a single syscall.
Syntax:
  int prlimit(pid_t pid, int resource, const struct rlimit *new_limit, struct rlimit *old_limit);
Use:
  Can set limits of another process
  Used in resource monitoring, sandboxing

```
## Discuss the concept of process scheduling policies in multi-core systems and their implications.
```c
process scheduling decides how CPU time is divided across cores.
Common Policies:
    SCHED_OTHER – default (time-shared)
    SCHED_FIFO – real-time, run until done
    SCHED_RR – real-time with time slices
    SCHED_DEADLINE – deadline-based scheduling (Linux)
Implications:
  Multicore systems benefit from load balancing and CPU affinity.
  Real-time tasks need low-latency, deterministic behavior.
  sched_setaffinity() can bind a process to specific cores.

```

## Describe the role of the setpriority() system call in adjusting process priorities
```c
setpriority() — Adjusting Process Priority
setpriority() sets the nice value of a process (affects scheduling priority).
Lower value = higher priority.
Syntax: int setpriority(int which, int who, int prio);
Only privileged users can set negative (higher) priorities

```

##Explain the concept of process scheduling latency and its impact on system 
responsiveness
```c
Scheduling latency is the time between when a process becomes ready and when it actually gets CPU time.
High latency ➝ poor responsiveness, especially in real-time systems.
Linux tries to minimize this using CFS (Completely Fair Scheduler) and real-time policies.

```

## Discuss the role of the prlimit64() system call in setting resource limits for processes with 64-bit address space.
```c
prlimit64() is like prlimit() but supports 64-bit resource limits.
Used for setting limits like:
Maximum memory
Max file descriptors
CPU time
Useful in modern systems with large address space.

```
## Describe the purpose of the sched_getaffinity() system call in querying the CPU 
affinity of a process.
```c
Retrieves which CPUs a process is allowed to run on.
Syntax:
     sched_getaffinity(pid, sizeof(cpu_set_t), &mask);
Helps in performance tuning, NUMA awareness, and CPU isolation.

```

## Discuss the concept of process checkpointing and its relevance in fault tolerance and process migration
```c
Saving a process’s state (memory, registers, file descriptors) so it can be resumed later.
Used in:
   Fault tolerance
   Process migration
   Long-running tasks
Example tools: CRIU, BLCR

```
## Explain the significance of the /proc filesystem in providing information about 
processes in Linux.
```c
A virtual filesystem that provides runtime information about processes and system.
Example paths:
     /proc/[pid]/status — process info
     /proc/cpuinfo — CPU details
    /proc/meminfo — memory usage
Widely used by tools like ps, top, htop.

```

## Describe the purpose of the sched_setaffinity() system call in setting CPU affinity for processes.
```c
Restricts a process to specific CPU cores.
Improves cache usage and reduces CPU migration.
Syntax:
   sched_setaffinity(pid, sizeof(cpu_set_t), &mask);

```
## Discuss the concept of process re-parenting and its implications in process 
management.
```c
When a parent process dies before the child, the child is re-parented to init (PID 1).
Ensures all processes have a valid parent.
Important for cleaning up zombie processes.

```
## what is process and what is the difference between process and program?
```c
Program: A passive file containing code (e.g., .out, .exe).
Process: A running instance of a program with its own memory, PID, etc.
One program can spawn multiple processes (e.g., browser tabs).

```
## what type of infomation pcb contains ?
```c
Process ID
State (ready, running, waiting)
Program counter
CPU registers
Memory pointers
I/O info
Scheduling info
Open file descriptors
Maintained by OS in kernel space.

```

## Explain about memory segements ?
```c
Memory layout of a process:
Text segment: Executable code
Data segment:
Initialized (int x = 5)
Uninitialized (BSS, e.g., static int a;)
Heap: Dynamic memory (malloc)
Stack: Function calls, local variables
```


## when fork invoked what are things will happen ?
```c
OS creates a new process:
    Copies parent’s PCB (with new PID)
    Shares memory (copy-on-write)
    Child gets its own stack, heap, file table
    Both parent and child run from the same point

```

## what is the difference between ps and top?
```c
 Tool    Description                                                            
 ------  ---------------------------------------  ----------------------------- 
 `ps`    Shows a **snapshot** of processes                                      
 `top`   Shows a **real-time view** of processes                                
 Output  Static                                   Dynamic, updates every second 
 Use     Scriptable                               Interactive                   
```


## what are the types of processes we have explain each process breifly?
```c
 Types of Processes
 Parent Process
   Creates one or more child processes using fork().
Child Process
   Created by a parent. May use exec() to load a new program.
Orphan Process
   Parent dies before child; child is re-parented to init (PID 1).
Zombie Process
  Child has terminated but parent hasn’t called wait(). Exists only in process table.
Daemon Process
  Background process, detached from terminal (e.g., cron, httpd).
  Foreground/Background Process
Controlled by terminal (foreground) or running independently (background using &).

```
## what is the ppid of orphan process?
```c
When a process becomes orphaned, it is re-parented to init, so:
PPID = 1
```

## what is the difference between exit vs return?
```c
 `return`                           `exit()`                                              
 ---------------------------------  ----------------------------------------------------- 
 Exits **from a function**          Exits the **entire process**                          
 Used in `main()` to return status  Terminates process from **anywhere**                  
 Calls destructors in C++           Doesn’t call destructors unless `atexit()` registered 
```


## In parent process can you access to the exit code of return value of child
```c
Use wait() or waitpid() in parent to:
         Block until child finishes
         Get child exit code
Example:
int status;
wait(&status);
if (WIFEXITED(status))
    printf("Exit code: %d\n", WEXITSTATUS(status));
process (or) in parent process how do you block to get the id of child?

```

## what is the difference between Zombie and Orphan process?
```c
 Zombie                                            Orphan                                 
 ------------------------------------------------  -------------------------------------- 
 Child terminated, parent didn't read exit status  Parent terminated, child still running 
 State: `Z` in `ps`                                Re-parented to `init`                  
 Wastes process table slot                         Continues running normally             


```
### what is the use of fork() 
```c
Creates a new child process, which is a copy of the parent.
Used in shells, multitasking, server-client models.

```
## define system call name some blocking system calls?
```c
System calls are requests by user-space programs to kernel services.
Blocking System Calls:
    read(), accept(), wait(), recv(), select()
These calls block the process until an event occurs.
```

### why do not we run program with in harddisk (or) why do we copy program to 
RAM for execution?
```c
HDD/SSD is too slow.
RAM is much faster, allows direct CPU access.
Code/data must be in RAM for the CPU to fetch instructions and operands.
```

## how do you copy data from RAM to CPU registers ?
```c
Done by load operations:
MOV AX, [memory_address]
Handled via CPU instructions, compiler, and system calls.
```


## how do you copy data from CPU registers to RAM ?
```c
Done by store operations:
MOV [memory_address], AX
Both directions involve load/store units in CPU and memory buses.

```
## explain about paging technique ?
```c
Divides memory into fixed-size pages (typically 4KB).
Logical memory ➜ Page number + offset
Physical memory ➜ Frame number + offset
Pages are mapped via page tables.
Benefits:
   Prevents fragmentation
   Enables virtual memory
   Supports memory isolation

```

## why the no of pages are not fixed ?
```c
Total number of pages = Total virtual address space / Page size
Changes based on:
   Architecture (32-bit vs 64-bit)
   Page size (4KB, 2MB, etc.)
   Process size
```

## explain about shared memory why we require shared memory?
```c
A type of Inter-Process Communication (IPC).
Multiple processes map the same memory segment into their address space.
Why needed?
   Fastest IPC (no copying)
   Useful in real-time, large data sharing
    Created using shmget(), shmat(), etc.

``

## How does multiple process can share data ?
```c
Methods:
   Shared memory
   Pipes / FIFOs
   Message queues
   Sockets
   Memory-mapped files
Shared memory is the fastest but requires synchronization (e.g., semaphores or mutexes).
```

### explain the scenario when pages of process-1 and pages of process-2 are 
 copied into same frames (or) explain the scenario where pages of multiple 
process are sharing the same physical frames(or) Can the page table of 
multiple process point to same  physical frames?

```c
Yes, multiple processes can map their virtual pages to the same physical frame, under specific scenarios:
Scenarios:
    Shared Libraries
    Read-only code like /lib/libc.so is mapped into all processes, but only one physical copy exists.
    Mapped as read-only, so all can safely share.
    Memory-Mapped Files (mmap)
    Shared memory (e.g., shared region using mmap() with MAP_SHARED).
    Pages are mapped to the same physical frames between processes.
     Copy-On-Write (COW)
     After fork(), child and parent share the same physical frames marked read-only.
     If one writes, a separate copy is made (hence "copy-on-write").
     Anonymous Shared Memory
     Using shmget() + shmat() or mmap() for shared memory region.
     Used for Inter-Process Communication (IPC). 
```

## How child process uses the memory segment of parent process?
```c
After fork(), the child process gets a copy of the parent’s page table,
 but the actual physical frames are shared using copy-on-write (COW).
Both processes point to the same physical memory until either modifies it.
COW improves performance because memory isn’t duplicated unless needed.

```
## how the parent process and child process keep track of which instruction 
 they are going to execute ?
```c
fork() creates a new process with:
    Same program counter (PC)
    Same stack, heap, registers
     Both start execution from the next instruction after fork().
But:
They each check the return value of fork():

pid_t pid = fork();
if (pid == 0) {
    // Child block
} else {
    // Parent block
}

This allows them to run different code paths after the same fork call.

```

## how parent an child process executes different blocks of code after fork()
```c
This happens logically, not physically.
The OS duplicates the parent’s memory (using COW).
Both processes start at the same point (right after fork()).
The return value of fork() tells which block to run:

Example:
pid_t pid = fork();
if (pid == 0) {
    printf("I am child\n");
} else {
    printf("I am parent\n");
}

Parent sees pid > 0
Child sees pid == 0
This enables different control flows in each.

 Feature          Parent & Child Shared?                      Behavior 
 --------------- ------------------------------------------  -------- 
 Page Table       Initially copied (pointing to same frames)  Yes      
 Physical Frames  Shared until write (COW)                    Yes      
 Program Counter  Initially same                              Yes      
 Stack / Heap     Logically separate after `fork()`           Yes      
 Execution Flow   Controlled via `fork()` return value        Yes      
```


## explain write operation to pages shared to parent and child process?
```c
When a parent process calls fork():
    Both parent and child initially share the same physical pages.
    These pages are marked as read-only in their page tables.
    If either tries to write, a page fault occurs.
The OS then:
    Allocates a new physical page.
    Copies the old page’s contents.
    Updates that process’s page table to point to the new page.
    Grants write permission to the new page.
    This is called Copy-On-Write (COW) — efficient memory use until modification.

```

 ## explain about adress translation?
```c
Address translation is the process of converting virtual addresses (used by processes)
 into physical addresses (used by hardware).
Steps:
CPU generates a virtual address.
    OS uses page tables to map virtual pages ➝ physical frames.
    MMU (Memory Management Unit) handles this in hardware.
    If page is not in memory → page fault occurs.

```
## what adress cpu places an adress bus?
```c
The CPU always places the physical address on the address bus to access memory.
However, programs work with virtual addresses.
The MMU translates virtual ➝ physical before the address is sent to the bus.

```

## when virtual adress are generated ?
```c
Generated by the CPU:
   Every memory operation (load/store) uses a virtual address.
   Virtual addresses are used in user mode to isolate and protect processes.
```

## when physical adresss are generated from virtual adress ?
```c
Generated by the CPU:
     every memory operation (load/store) uses a virtual address.
      Virtual addresses are used in user mode to isolate and protect processes.
      Physical address is calculated during MMU address translation

```

### what is exec () family of calls and what is the need of exac() family of calls 
 and what are those?
```c
The exec() family of calls replaces the current process image with a new program.
Why we need exec()?
    After using fork(), you may want the child to run a completely different program.
     exec() does this without creating a new process.
Common exec() variants:

 Function    Description                              
 ----------  ---------------------------------------- 
 `execl()`   Takes arguments one by one               
 `execv()`   Takes `argv[]` array                     
 `execlp()`  Like `execl()`, but searches `$PATH`     
 `execvp()`  Like `execv()`, but searches `$PATH`     
 `execve()`  The underlying syscall with env and args 

```

### most of the system call why they return error?
```c
System calls interact with hardware and kernel resources, which can fail.
 Hence, they return:
   0 or positive on success
   -1 on error and set errno
Example reasons:
   Invalid parameters
    Permission denied
    Resource not available
    Memory or file limits exceeded
This is why error checking is critical after each system call.

```
### what is the difference between Execl() and Execv()?
```c
 Feature  `execl()`                              `execv()`                           
 -------  -------------------------------------  ----------------------------------- 
 Args     Passed one-by-one                      Passed as an array (`char *argv[]`) 
 Use      Fixed number of arguments              Dynamic argument list               
 Example  `execl("/bin/ls", "ls", "-l", NULL);`  `execv("/bin/ls", args);`           

```
### What is the difference between Execlp() and Execvp()
```c
 Feature           `execlp()`                                    `execvp()`                         
 ----------------  --------------------------------------------  ---------------------------------- 
  Searches `$PATH`                                                                            
  Argument format   List (`execlp(path, arg1, arg2, ..., NULL)`)  Array (`execvp(path, argv[])`)     
  Use case           Simpler calls with known args                 Script-style execution with `argv` 

```






