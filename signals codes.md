## Write a C program to catch and handle the SIGINT signal.
```c
#include<stdio.h>
#include<signal.h>
#include<unistd.h>
void sigint_handler(int signum)
{
        printf("caught SIGINT (ctrl+c).signal number:%d\n",signum);
}
int main()
{
        signal(SIGINT,sigint_handler);
        while(1)
        {
                printf("running....press ctrl+c to trigger SIGINT \n");
                sleep(1);
        }
        return 0;
}
```
## Implement a C program to send a custom signal to another process.
```c
sender:

#include<stdio.h>
#include<signal.h>
#include<unistd.h>
int main(int c,char *v[])
{
        if(c==2)kill(atoi(v[1]),SIGUSR1);
        return 0;
}


receiver:
#include<stdio.h>
#include<unistd.h>
#include<signal.h>
void h(int s)
{
        printf("gpt SIGUR1:%d\n",s);
}
int main()
{
        signal(SIGUSR1,h);
        printf("PID:%d\n",getpid());
        while(1)pause();
}

```
## Create a C program to ignore the SIGCHLD signal temporarily.
```c
#include<signal.h>
#include<sys/wait.h>
#include<unistd.h>
int main()
{
        signal(SIGCHLD,SIG_IGN);
        if(fork()==0)_exit(0);
        sleep(1);
        signal(SIGCHLD,SIG_DFL);
        if(fork()==0)_exit(0);
        wait(NULL);
        return 0;
}


```
## Write a program to block the SIGTERM signal using sigprocmask().
```c
#include<stdio.h>
#include<signal.h>
#include<unistd.h>
int main()
{
        sigset_t set;
        sigemptyset(&set);
        sigaddset(&set,SIGTERM);
        sigprocmask(SIG_BLOCK,&set,NULL);
        printf("SIGTERM blocked.PID:%d\n",getpid());
        while(1)pause();
}

```

## Implement a C program to handle the SIGALRM signal using sigaction().
```c
#include<stdio.h>
#include<signal.h>
#include<unistd.h>
void handler(int s)
{
        printf("SIGALRM received\n");
}
int main()
{
        struct sigaction sa={.sa_handler=handler};
        sigaction(SIGALRM,&sa,NULL);
        alarm(2);
        while(1) pause();
}

```

## Write a C program to install a custom signal handler for SIGTERM?
```c
#include<stdio.h>
#include<signal.h>
#include<unistd.h>
void handler(int s)
{
        printf("caught signal:%d\n",s);
}
int main()
{
        signal(SIGTERM,handler);
        printf("PID:%d\n",getpid());
        while(1)pause();
}

```

## Implement a program to handle the SIGSEGV signal (segmentation fault).
```c
#include<stdio.h>
#include<signal.h>
#include<stdlib.h>
void handler(int s)
{
        printf("caught SIGSEGV:%d\n",s);
        exit(1);
}
int main()
{
        signal(SIGSEGV,handler);
        int *p=NULL;
        *p=43;
        return 0;
}

```

## Create a program to handle the SIGILL signal (illegal instruction).
```c
#include<stdlib.h>
#include<stdio.h>
#include<signal.h>
void handler(int s)
{
        printf("caught SIGILL:%d\n",s);
        exit(0);
}
int main()
{
        signal(SIGILL,handler);
        raise(SIGILL);
        return 0;
}
```



## Write a program to handle the SIGABRT signal (abort).
```c
#include<stdio.h>
#include<stdlib.h>
#include<signal.h>
void handler(int s)
{
        printf("caught SIGABRT:%d\n",s);
        exit(0);
}
int main()
{
        signal(SIGABRT,handler);
        abort();
        return 0;
}
```


## Implement a C program to handle the SIGQUIT signal.
```c
#include<stdio.h>
#include<unistd.h>
#include<signal.h>
void handler(int s)
{
        printf("caught SIGQUIT:%d\n",s);
}
int main()
{
        signal(SIGQUIT,handler);
        while(1)pause();
}


```
## Write a program to handle the SIGTERM signal (termination request).
```c
#include<stdio.h>
#include<signal.h>
#include<unistd.h>
void handler(int s)
{
        printf("caught SIGTERM:%d\n",s);
}
int main()
{
        signal(SIGTERM,handler);
        printf("PID :%d\n",getpid());
        while(1)pause();
}

```
### Write a program to handle the SIGTSTP signal (terminal stop).
```c
#include<stdio.h>
#include<signal.h>
#include<stdlib.h>
void handler(int s)
{
        printf("caught SIGTSTP:%d\n",s);
}
int main()
{
        signal(SIGTSTP,handler);
        while(1)pause();
}
```

## Write a program to handle the SIGVTALRM signal (virtual timer expired).
```c
#include<stdio.h>
#include<unistd.h>
#include<signal.h>
#include<sys/time.h>
void handler(int s)
{
        printf("SIGVTALRM fired\n");
}
int main()
{
        signal(SIGVTALRM,handler);
        struct itimerval timer={.it_interval={0,500000},.it_value={1,0}};
        setitimer(ITIMER_VIRTUAL,&timer,NULL);
        while(1);
}

```

### Write a program to handle the SIGWINCH signal (window size change).
```c

#include<stdio.h>
#include<signal.h>
#include<stdlib.h>
void handler(int s)
{
        printf("window size changed(SIGWINCH)\n");
}
int main()
{
        signal(SIGWINCH,handler);
        while(1)pause();
}


```
### Implement a C program to handle the SIGXFSZ signal (file size limit exceeded).
```c
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<signal.h>
#include<fcntl.h>
void handler(int s)
{
        printf("caught SIGXFSZ(file size limited exceeded\n");
        exit(1);
}
int main()
{
        signal(SIGXFSZ,handler);
        int fd=open("big file.txt",O_WRONLY,0644);
        while(1)write(fd,"1234567890",10);
}
```


### Create a program to handle the SIGPWR signal (power failure restart).
```c
#include<stdio.h>
#include<stdlib.h>
#include<signal.h>
void handler(int s)
{
        printf("caught SIGPWR(power failure)\n");
}
int main()
{
        signal(SIGPWR,handler);
        raise(SIGPWR);
        return 0;
}
```

### Write a program to handle the SIGSYS signal (bad system call).
```c
#include<stdio.h>
#include<stdlib.h>
#include<signal.h>
void handler(int s)
{
        printf("caught SIGSYS(bad system call)\n");
        exit(1);
}
int main()
{
        signal(SIGSYS,handler);
        raise(SIGSYS);
        return 0;
}

```
### Write a C program to handle the SIGIO signal (I/O is possible on a descriptor).
```c
#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>
#include<signal.h>
void handler(int s)
{
        printf("SIGIO:input available\n");
}
int main()
{
        signal(SIGIO,handler);
        fcntl(STDIN_FILENO,F_SETOWN,getpid());
        fcntl(STDIN_FILENO,F_SETFL,O_ASYNC);
        while(1)pause();
}

```
### Implement a C program to handle the SIGINFO signal (status request from keyboard).
```c
#include<stdio.h>
#include<stdlib.h>
#include<signal.h>
void handler(int s)
{
        printf("caught SIGINFO(status request)\n");
        exit(1);
}
int main()
{
#ifdef SIGINFO
        signal(SIGSYS,handler);
#endif
        while(1)pause();
}
```


### Create a C program to handle the SIGRTMIN signal (minimum real-time signal).
```c
#include <signal.h>
#include <stdio.h>
#include <unistd.h>

void handler(int s) { printf("Caught SIGRTMIN: %d\n", s); }

int main() {
    signal(SIGRTMIN, handler);
    raise(SIGRTMIN);
    return 0;
}


```
### Implement a program to handle the SIGRTMAX signal (maximum real-time signal).
```c
#include<stdio.h>
#include<unistd.h>
#include<signal.h>
void handler(int s)
{
        printf("caught SIGRTMAX:%d\n",s);
        exit(1);
}
int main()
{
        signal(SIGRTMAX,handler);
        raise(SIGRTMIN);
        return 0;
}


```
## Create a C program to handle the SIGSEGV_SIGBUS signal (segmentation fault or bus error).
```c
#include<stdio.h>
#include<signal.h>
#include<stdlib.h>
void handler(int s)
{
        if(s==SIGSEGV)printf("caught SIGSEGV \n");
        if(s==SIGBUS)printf("caught SIGBUS\n");
        exit(1);
}
int main()
{
        signal(SIGSEGV,handler);
        signal(SIGBUS,handler);
        int *p=NULL;
        *p=1;
}
```

### Implement a program to handle the SIGUSR1_SIGUSR2 signal (user-defined signal).
```c
#include<stdio.h>
#include<signal.h>
#include<stdlib.h>
void handler(int s)
{
        if(s==SIGUSR1)printf("caught SIGUSR1 \n");
        if(s==SIGUSR2)printf("caught SIGUSR2\n");
        exit(1);
}
int main()
{
        signal(SIGUSR1,handler);
        signal(SIGUSR2,handler);
        printf("PID:%d\n",getpid());
        while(1)pause();
}


```
### Create a C program to handle the SIGCONT_SIGSTOP signal (continue or stop executing).
```c
#include<stdio.h>
#include<signal.h>
#include<stdlib.h>
void handler(int s)
{
        if(s==SIGCONT)printf("caught SIGCONT(resumed) \n");
}
int main()
{
        signal(SIGCONT,handler);
        printf("PID:%d(TRY SIGSTOP THEN SIGCONT)\n",getpid());
        while(1)pause();
}


```
## Write a program to implement a timer using signals.
```c
#include<stdio.h>
#include<signal.h>
#include<unistd.h>
void handler(int s)
{
        printf("timer expired!(SIGALRM)\n");
}
int main()
{
        signal(SIGALRM,handler);
        alarm(3);
        pause();
}
```


## Write a program to handle a real-time signal using sigqueue().
```c

#include<stdio.h>
#include<stdlib.h>
#include<signal.h>
#include<unistd.h>
void handler(int sig,siginfo_t *info,void *ucontext)
{
        printf("received signal %d with data=%d\n",sig,info->si_value.sival_int);
}
int main()
{
        struct sigaction sa;
        sa.sa_sigaction=handler;
        sa.sa_flags=SA_SIGINFO;
        sigemptyset(&sa.sa_mask);
        sigaction(SIGRTMIN,&sa,NULL);
        pid_t pid=getpid();
        printf("sending real-time signal to process %d..\n",pid);
        union sigval val;
        sigqueue(pid,SIGRTMIN,val);
        sleep(1);
        return 0;
}



```
## Why we use raise system call explain it programmatically
```c
The raise() system call is used to send a signal to the calling process itself.
Purpose of raise():
      To intentionally send a signal to your own process.
Used for:
    Triggering signal handlers manually (e.g., SIGINT, SIGUSR1)
    Testing signal handling code
    Graceful shutdown
    Simulating interrupts/errors
syntax:
     #include <signal.h>
     int raise(int sig);
sig: Signal number (e.g., SIGINT, SIGTERM)
Returns 0 on success, non-zero on failure.


#include<stdio.h>
#include<signal.h>
void handler(int sig)
{
        printf("caught signal:%d\n",sig);
}
int main()
{
        signal(SIGUSR1,handler);
        printf("sending SIGUSR1 using raise()\n");
        raise(SIGUSR1);
        printf("signalhandler,program continues...\n");
        return 0;
}

```

## Write a program to handle SIGALRM (alarm clock) signal for implementing a
timeout mechanism in system programming.
```c

#include<stdio.h>
#include<signal.h>
#include<unistd.h>
void handler(int s)
{
        printf("\ntimeout!\n");_exit;
}
int main()
{
        signal(SIGALRM,handler);
        alarm(5);
        char buf[100];
        printf("enter input of 5 sec:");
        if(fgets(buf,sizeof(buf),stdin))
        {
                alarm(0);
                printf("you entered :%s",buf);
        }
        return 0;
}


```

## Write a c program on pause system call
```c
#include<stdio.h>
#include<signal.h>
#include<unistd.h>
void handler(int s)
{
        printf("received signal %d,resuming pause()\n",s);
}
int main()
{
        signal(SIGINT,handler);
        printf("waiting for SIGINT (ctrl+c)...\n");
        pause();
        printf("program continues pause()\n");
        return 0;
}

```
## Create a C program to handle the SIGTRAP signal (trace/breakpoint trap).
```c
#include<stdio.h>
#include<stdlib.h>
#include<signal.h>
#include<unistd.h>
void handler(int s)
{
        printf("caught SIGTRAP:%d\n",s);
        exit(1);
}
int main()
{
        signal(SIGTRAP,handler);
        raise(SIGTRAP);
        return 0;
}

```

## Create a C program to handle the SIGWINCH_SIGINFO signal (window size change or status request from keyboard).
```c
#include<stdio.h>
#include<unistd.h>
#include<signal.h>
void handler(int s)
{
        if(s==SIGWINCH)printf("window size change (SIGWINCH)\n");
#ifdef SIGINFO
        else if(s==SIGINFO)printf("status request (SIGINFO)\n");#endif
}
int main()
{
        signal(SIGWINCH,handler);
#ifdef SIGINFO
        signal(SIGINFO,handler);
#endif
        while(1)pause();
}

```

## Implement a program to handle the SIGSYS_SIGPIPE signal (bad system call or
write on a pipe with no one to read it).

```c
#include<stdio.h>
#include<stdlib.h>
#include<signal.h>
#include<unistd.h>
void handler(int s)
{
        if(s==SIGSYS)printf("bad syscall (SIGSYS)\n");
        if(s==SIGPIPE)printf("write with no reader (SIGPIPE)\n");
        exit(1);
}
int main()
{
        signal(SIGSYS,handler);
        signal(SIGPIPE,handler);
        int fd[2];
        pipe(fd);
        close(fd[0]);
        write(fd[1],"test",4);
}

```

## Write a program to handle the SIGURG_SIGTSTP signal (urgent condition on socket or stop signal).

```c
#include<stdio.h>
#include<signal.h>
#include<unistd.h>
void handler(int s)
{
        if(s==SIGURG)printf("(urgent socket condition) caught SIGURG\n");
        if(s==SIGTSTP)printf("(ctrl+z) caught SIGTSTP\n");
}
int main()
{
        signal(SIGURG,handler);
        signal(SIGTSTP,handler);
        while(1)pause();
}


```
## Implement a program to handle the SIGTTIN_SIGTTOU signal (background read or
write attempted from control terminal).
```c

#include<stdio.h>
#include<signal.h>
#include<unistd.h>
void handler(int s)
{
        if(s==SIGTTIN)printf("(background read) caught SIGTTIN\n");
        if(s==SIGTTOU)printf("(background write) caught SIGTTOU\n");
}
int main()
{
        signal(SIGTTIN,handler);
        signal(SIGTTOU,handler);
        while(1)pause();
}


```
## Create a C program to handle the SIGXCPU_SIGXFSZ signal (CPU time limit
exceeded or file size limit exceeded).
```c

#include<stdio.h>
#include<signal.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/resource.h>
void handler(int s)
{
        if(s==SIGXCPU)printf("caught SIGXCPU:cpu time limit exceeded\n");
        if(s==SIGXFSZ)printf("caught SIGXFSZ:file size limit exceed\n");
        exit(1);
}
int main()
{
        signal(SIGXCPU,handler);
        signal(SIGXFSZ,handler);
        struct rlimit rl;
        rl.rlim_cur=1;
        rl.rlim_max=2;
        setrlimit(RLIMIT_CPU,&rl);
        rl.rlim_cur=1024;
        rl.rlim_max=2048;
        setrlimit(RLIMIT_FSIZE,&rl);
        while(1);
}

```

### Implement a program to handle the SIGVTALRM_SIGWINCH signal (virtual timer expired or window size change).
```c
#include<stdio.h>
#include<signal.h>
#include<unistd.h>
#include<sys/time.h>
void handler(int s)
{
        if(s==SIGVTALRM)printf("caught SIGVTALRM:virtual timer expired\n");
        if(s==SIGWINCH)printf("caught SIGWINCH:windoe size change\n");
}
int main()
{
        signal(SIGVTALRM,handler);
        signal(SIGWINCH,handler);
        struct itimerval timer={.it_value={1,0},.it_interval={0,500000}};
        setitimer(ITIMER_VIRTUAL,&timer,NULL);
        while(1);
}
```

### Write a program to demonstrate how to handle and recover from a segmentation fault (SIGSEGV) in a system programming scenario.
```c
#include<stdio.h>
#include<signal.h>
#include<setjmp.h>
jmp_buf env;
void handler(int s)
{
        printf("SIGSEGV caught!\n");
        longjmp(env,1);
}
int main()
{
        signal(SIGSEGV,handler);
        if(!setjmp(env))
        {
                *(int*)0=1;
        }
        else
        {
                printf("recovered from fault.\n");
        }
        return 0;
}

```

## Write a program to demonstrate the use of sigaction() for handling signal

```c
#include<stdio.h>
#include<signal.h>
#include<unistd.h>
void handler_signal(int sig)
{
        printf("caught signal:%d\n",sig);
}
int main()
{
        struct sigaction sa;
        sa.sa_handler=handler_signal;
        sigemptyset(&sa.sa_mask);
        sa.sa_flags=0;
        sigaction(SIGINT,&sa,NULL);
        printf("press ctrl+c to trigger SIGINT...\n");
        while(1)
        {
                printf("running....\n");
                sleep(2);
        }
        return 0;
}

```

## Write a program to demonstrate signal handling in a multithreaded environment.
```c
#include<stdio.h>
#include<signal.h>
#include<unistd.h>
void handler(int sig)
{
        printf("got %s\n",sig==SIGUSR1?"SIGUSR1":"SIGUSR2");
}
int main()
{
        struct sigaction sa={.sa_handler=handler};
        sigaction(SIGUSR1,&sa,NULL);
        sigaction(SIGUSR2,&sa,NULL);
        printf("PID:%d\n",getpid());
        while(1)pause();
}

```

## Write a program to handle the SIGTSTP signal and suspend the process.
```c

#include<stdio.h>
#include<signal.h>
#include<unistd.h>
void handler(int sig)
{
        printf("SIGTSTP caught (ctrl+z)\n");
}
int main()
{
        signal(SIGTSTP,handler);
        while(1)
        {
                printf("running....press ctrl+z\n");
                sleep(2);
        }
        return 0;
}

```

## Write a program to demonstrate IPC using signals.

```c
#include<stdio.h>
#include<unistd.h>
#include<signal.h>
void handler(int sig)
{
        printf("child caught signal %d from parent :%d\n",sig);
}
int main()
{
        pid_t pid=fork();
        if(pid==0)
        {
                signal(SIGUSR1,handler);
                pause();
        }
        else
        {
                sleep(1);
                kill(pid,SIGUSR1);
                wait(NULL);
        }
        return 0;
}

```
## Write a program to demonstrate signal handling during fork() and exec().
```c
#include<stdio.h>
#include<signal.h>
#include<unistd.h>
#include<stdlib.h>
void handler(int sig)
{
        printf("signal %d caught in PID %d\n",sig,getpid());
}
int main()
{
        signal(SIGUSR1,handler);
        if(fork()==0)
        {
                printf("child PID:%d\n",getpid());
                kill(getpid(),SIGUSR1);
                execlp("ls", "ls",NULL);
                perror("exec failed");
                exit(1);
        }
        else
        {
                wait(NULL);
        }
        return 0;
}

```
## Write a program to demonstrate how to block and unblock signals using
sigprocmask() in a system programming context.

```c
#include<stdio.h>
#include<signal.h>
#include<unistd.h>
void handler(int sig)
{
        printf("caught signal %d\n",sig);
}
int main()
{
        signal(SIGINT,handler);
        sigset_t set;
        sigemptyset(&set);
        sigaddset(&set,SIGINT);
        sigprocmask(SIG_BLOCK,&set,NULL);
        printf("SIGINT blocked for 5 seconds,try ctrl+c...\n");
        sleep(5);
        sigprocmask(SIG_UNBLOCK,&set,NULL);
        printf("SIGINT unblocked.try ctrl+c again.\n");
        while(1)pause();
}

```

## Write a program to demonstrate the usage of sigaction() for handling SIGUSR1 and SIGUSR2 signals in a system programming scenario
```c
#include<stdio.h>
#include<signal.h>
#include<unistd.h>
void handler(int sig)
{
        printf("got %s\n",sig==SIGUSR1?"SIGUSR1":"SIGUSR2");
}
int main()
{
        struct sigaction sa={.sa_handler=handler};
        sigaction(SIGUSR1,&sa,NULL);
        sigaction(SIGUSR2,&sa,NULL);
        printf("PID:%d\n",getpid());
        while(1)pause();
}

```

## Create a C program to handle the SIGCHLD_SIGCONT signal (child process
terminated or continue executing).
```c

#include<stdio.h>
#include<sys/wait.h>
#include<stdlib.h>
#include<signal.h>
#include<unistd.h>
void handler(int s)
{
        if(s==SIGCHLD)
        {
                wait(NULL);
                printf("SIGCHILD\n");
        }
        else if(s==SIGCONT)
                printf("SIGCONT");
}
int main()
{
        signal(SIGCHLD,handler);
        signal(SIGCONT,handler);
        if(fork()==0)
        {
                sleep(1);
                exit(0);
        }
        while(1)pause();
}
```

### Write a program to handle the SIGBUS_SIGCHLD signal (bus error or child process
terminated).

```c
#include<stdio.h>
#include<sys/wait.h>
#include<stdlib.h>
#include<signal.h>
#include<unistd.h>
void handler(int s)
{
        if(s==SIGBUS)printf("caught SIGBUS(bus error)\n");
        else if(s==SIGCHLD)
        {
                wait(NULL);
                printf("caught SIGCHLD(child excited)\n");
        }
        exit(1);
}
int main()
{
        signal(SIGCHLD,handler);
        signal(SIGBUS,handler);
        if(fork()==0)_exit(0);
        sleep(1);
        pause();
}

```

## Implement a program to handle the SIGPWR_SIGSYS signal (power fa*iilure restart or bad system call).
```c
#include<stdio.h>
#include<stdlib.h>
#include<signal.h>
#include<unistd.h>
void handler(int s)
{
        if(s==SIGPWR)printf("caught SIGPWR(power failure)\n");
        else if(s==SIGSYS)printf("caught SIGSYS(bad syscall)\n");
        exit(1);
}
int main()
{
        signal(SIGPWR,handler);
        signal(SIGSYS,handler);
        raise(SIGSYS);
        return 0;
}


```
## Write a program to handle the SIGPIPE_SIGQUIT signal (write on a pipe with no one to read it or quit signal).
```c

#include<stdio.h>
#include<stdlib.h>
#include<signal.h>
#include<unistd.h>
void handler(int s)
{
        if(s==SIGPIPE)printf("caught SIGPIPE( no reader)\n");
        else if(s==SIGQUIT)printf("caught SIGQUIT(ctrl+\\ pressed)\n");
        exit(1);
}
int main()
{
        signal(SIGSYS,handler);
        signal(SIGPIPE,handler);
        int fd[2];
        pipe(fd);
        close(fd[0]);
        write(fd[1],"data",4);
        while(1)pause();
}


```
