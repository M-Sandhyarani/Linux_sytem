#### Discuss the significance of the getpid() and getppid() system calls.

#include<stdio.h>
#include<unistd.h>
int main()
{
        printf("My PID:%d\n",getpid());
        printf("My parent's PID:%d\n",getppid());
        return 0;
}



####  Write a C program to demonstrate the use of fork() system call. 

#include<stdio.h>
#include<unistd.h>
int main()
{
        int pid;
        pid=fork();
        if(pid==0)
        {
                printf("child process.\n");
        }
        else
        {
                printf("parent process.\n");
        }
        return 0;
}




###  Write a C program to illustrate the use of the execvp() function

#include<stdio.h>
#include<unistd.h>
int main()
{
        char *args[]={"ls","-l",NULL};
        printf("before execvp()\n");
        execvp("ls",args);
        printf("execvp failed\n");
        return 0;
}




### Write a program in C to create a child process using fork() and print its PID.

#include<stdio.h>
#include<unistd.h>
int main()
{
        pid_t pid=fork();
        if(pid==0)
        {
                printf("\n[child]\n");
                printf("PID=%d\n",getpid());
                printf("PPID=%d\n",getppid());
        }
        else
        {
                printf("\n[parent]\n");
                printf("PID=%d\n",getpid());
                printf("PPID=%d\n",getppid());
        }
        return 0;
}




#### Write a C program to create multiple child processes using fork() and display their PIDs.

#include <stdio.h>
#include <unistd.h>
int main() {
int i;
for (i = 0; i < 3; i++) {
 if (fork() == 0) {
            // Child process
printf("Child %d: PID = %d\n", i + 1, getpid());

/*for ppid -> printf(“Child %d: PID = %d\n”, i+1, getpid(), getppid());*/

            return 0; // Important: child exits after printing
        }
    }

    return 0; // Parent exits after creating all children
}




### Write a C program to demonstrate the use of the waitpid() function for process synchronization


#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/wait.h>
int main()
{
        pid_t pid=fork();
        if(pid<0)
        {
                perror("failed\n");
                exit(1);
        }
        if(pid==0)
        {
                printf("child:pid=%d\n",getpid);
                sleep(2);
        }
        else
        {
                printf("parent:waiting to childprocess finish\n");
                waitpid(pid,NULL,0);
                printf("parent:childprocess finished..\n");
        }
        return 0;
}





### Write a program in C to create a daemon process

#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
int main()
{
        pid_t pid=fork();
        if(pid<0)
        {
                perror("failed\n");
                exit(1);
        }
        if(pid>0)
        {
                printf("parent exist.daemon PID:%d\n",pid);
                exit(0);
        }
        while(1)
        {
                printf("daemon process running \n");
                sleep(3);
        }
        return 0;
}



### Write a C program to demonstrate the use of the system() function for executing shell commands.

#include<stdio.h>
#include<unistd.h>
int main()
{
        printf("listed file in cd:\n");
        system("ls-l");
        printf("\ncreating files\n");
        system("touch demo.txt");
        printf("\ndisplay files\n");
        system("date");
        printf("\nremoving files\n");
        system("rm demo.txt");
        return 0;
}


###  Write a C program to create a process using fork() and pass arguments to the child process.

#include<stdio.h>
#include<unistd.h>
#include<sys/wait.h>
#include<stdlib.h>
int main()
{
        pid_t pid;
        pid=fork();
        if(pid<0)
        {
                perror("failed\n");
                exit(1);
        }
        else if(pid==0)
        {
                printf("child process(PID:%d)\n",getpid());
                char *args[]={"ls","-l","/tmp",NULL};
                execvp("ls",args);
                perror("execvp failed");
                exit(1);
        }
        else
        {
                printf("parent process(PID:%d),waiting for child\n",getpid());
                wait(NULL);
                printf("child finished.\n");
        }
        return 0;
}





### Write a program in C to demonstrate process synchronization using semaphore

#include<stdio.h>
#include<unistd.h>
#include<semaphore.h>
#include<pthread.h>
sem_t semaphores;
void *thread_function(void *args)
{
        sem_wait(&semaphores);
        printf("inside critical section(thread:%ld\n",pthread_self());
        sleep(1);
        printf("leaving critical section(thread:%ld)\n",pthread_self());
        sem_post(&semaphores);
        return NULL;
}
int main()
{
        pthread_t t1,t2;
        sem_init(&semaphores,0,1);
        pthread_create(&t1,NULL,thread function,NULL);
        pthread_create(&t2,NULL,thread function,NULL);
        pthread_join(t1,NULL);
        pthread_join(t2,NULL);
        sem_destroy(&semaphores);
        return 0;
}




##### Write a C program to demonstrate the use of the execvpe() function

#define _GNU_SOURCE
#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>
int main()
{
        char *args={"ls","-l","/",NULL};
        char *env[]={"MYVAR=helloworld",NULL};
        printf("before execvpe()\n");
        if(execvpe("ls",args,env)==1)
        {
                perror("execvpe failed\n");
                exit(1);
        }
        printf("after execvpe()\n");
        return 0;
}






### Write a C program to create a process group and change its process group ID (PGID)

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
int main()
{
        pid_t pid=fork();
        if(pid<0)
        {
                perror("failed\n");
                exit(1);
        }
        else if(pid==0)
        {
                printf("child PID:%d\n",getpid());
                printf("before:child PGID:%d\n",getpgrp());
                setpgid(0,0);
                printf("after:child PGID:%d\n",getpgrp());
                sleep(5);
        }
        else
        {
                printf("parent PID:%d\n",getppid());
                printf("parent PGID:%d\n",getpgrp());
                wait(NULL);
         }
return 0;
}





####Write a C program to create a child process using vfork() and demonstrate its usage

#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>
int main()
{
        int var=10;
        pid_t pid=vfork();
        if(pid<0)
        {
                printf("vfork failed\n");
                exit(1);
        }
        else if(pid==0)
        {
                printf("child:var=%d\n",var);
                var+=5;
                printf("child:updated var=%d\n",var);
                exit(0);
        }
        else
        {
                printf("parent:var=%d\n",var);
        }
        return 0;
}





###  Write a C program to create a pipeline between two processes using the pipe() system call.

#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
int main()
{
        int fd[2];
        pid_t pid;
        char buffer[100];
        if(pipe(fd)==-1)
        {
                perror("failed\n");
                exit(1);
        }
        pid=fork();
        if(pid<0)
        {
                perror("failed fork");
                exit(1);
        }
        else if(pid==0)
        {
                close(fd[1]);
                read(fd[0],buffer,sizeof(buffer));
                printf("child received:%s\n",buffer);
                close(fd[0]);
        }
        else
        {
                close(fd[0]);
                char msg[]="hello world";
                write(fd[1],msg,sizeof(msg));
                close(fd[1]);
                wait(NULL);
        }
        return 0;
}





### Write a program in C to demonstrate the use of the nice() system call for adjusting process priority


#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/resource.h>
int main()
{
        int ret;
        printf("default value received:%d\n",getpriority(PRIO_PROCESS,0));
        ret=nice(5);
        if(ret==-1)
        {
                perror("nice failed");
        }
        printf("new value:%d\n",getpriority(PRIO_PROCESS,0));
        for(int i=0;i<5;i++)
        {
                printf("doing well...\n");
                sleep(1);
        }
        return 0;
}




#### Write a C program to create a child process using fork() and communicate between parent and child using pipes.


#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/wait.h>
int main()
{
        int fd[2];
        pid_t pid;
        char write_msg="hello world";
        char read_msg[100];
        if(pipe(fd)==-1)
        {
                perror("failed");
                exit(1);
        }
        pipe=fork();
        if(pid<0)
        {
                perror("failed");
                exit(1);
        }
        else if(pid==0)
        {
                close(fd[1]);
                read(fd[0],read_msg,sizeof(read_msg));
                printf("child :%d\n",read_msg);
                close(fd[0]);
                exit(0);
        }
        else
        {
                close(fd[0]);
                write(fd[1],write_msg,string(write_msg)+1);
                close(fd[1]);
                wait(NULL);
        }
        return 0;
}




####  Write a C program to demonstrate process synchronization using the 
fork() and wait() system calls.

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
int main()
{
        pid_t pid=fork();
        if(pid<0)
        {
                printf("failed");
                exit(1);
        }
        else if(pid==0)
        {
                printf("child :doing some work\n");
                sleep(2);
                printf("child successfulley work\n");
                exit(0);
        }
        else
        {
                printf("parent :waiting child completed work\n");
                wait(NULL);
                printf("parent:child work complete\n");
        }
        return 0;
}




### Write a C program to create a child process using fork() and demonstrate inter-process communication (IPC) using shared memory

#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/shm.h>
#include<sys/ipc.h>
#define SHM_KEY 1234
#define SHM_SIZE 1024
int main()
{
        int shmid;
        char *shared_memory;
        shmid=shmget(SHM_KEY,SHM_SIZE,IPC_CREAT|0666);
        if(shmid==-1)
        {
                perror("shmget failed");
                exit(1);
        }
        pid_t pid=fork();
        if(pid<0)
        {
                perror("fork failed");
                exit(1);
        }
        else if(pid==0)
        {
                sleep(1);
                shared_memory=(char *)shmat(shmid,NULL,0);
                if(shared_memory==(void *)-1)
                {
                        perror("shmat failed (child)");
                        exit(1);
                }
                printf("child reads from shared memory :%s\n",shared_memory);
                shmdt(shared_memory);
        }
               else
        {
                shared_memory=(char *)shmat(shmid,NULL,0);
                if(shared_memory==(void *)-1)
                {
                        perror("shmat failed (parent)");
                        exit(1);
                }
                strcpy(shared_memory,"hello from parent");
                printf("parent wrote to shared memory.\n");
                wait(NULL);
                shmdt(shared_memory);
                shmctl(shmid,IPC_RMID,NULL);
        }
        return 0;
}





### Write a C program to demonstrate the use of the prctl() system call to change process attributes.

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/prctl.h>
#define _GNU_SOURCE
int main()
{
        char name[20];
        if(prctl(PR_SET_NAME,"Myprocess",0,0,0)==-1)
        {
                printf("failed\n");
                exit(1);
        }
        printf("prefer name as'Myprocess'\n");
        if(prctl(PR_GET_NAME,name,0,0,0)==-1)
        {
                printf("failed\n");
                exit(1);
        }
        printf("prefer name:%s\n",name);
        sleep(5);
        return 0;
}





### Write a C program to create a child process using fork() and demonstrate process synchronization using semaphores.

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<semaphore.h>
#include<fcntl.h>
#include<sys/wait.h>
int main()
{
        sem_t *sem=sem_open("/mysem",O_CREAT,0644,1);
        if(sem==SEM_FAILED)
        {
                perror("failed\n");
                exit(1);
        }
        pid_t pid=fork();
        if(pid<0)
        {
                perror("failed\n");
                exit(1);
        }
        else if(pid==0)
        {
                sem_wait(sem);
                printf("child:entered\n");
                sleep(2);
                printf("child:leaving\n");
                sem_post(sem);
                exit(0);
        }
        else
        {
                sem_wait(sem);
                printf("parent:entered\n");
                sleep(2);
                printf("parent:leaving\n");
                sem_post(sem);
                wait(NULL);
                sem_close(sem);
                sem_unlink("/mysem");
        }
        return 0;
}





### Write a C program to create a child process using fork() and demonstrate process communication using named pipes (FIFOs)

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/wait.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<string.h>
int main()
{
        char *fifo="/tmp/mkfifo";
        mkfifo(fifo,0666);
        pid_t pid=fork();
        if(pid==0)
        {
                char buffer[100];
                int fd=open(fifo,O_RDONLY);
                read(fd,buffer,sizeof(buffer));
                printf("child received:%s\n",buffer);
                close(fd);
                unlink(fifo);
                exit(0);
        }
        else
        {
                int fd=open(fifo,O_WRONLY);
                char *msg="hello world";
                write(fd,msg,strlen(msg)+1);
                close(fd);
                wait(NULL);
        }
        return 0;
}





####Write a C program to create a child process using fork() and demonstrate process communication using shared memory and semaphore

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<semaphore.h>
#include<sys/mman.h>
#include<sys/wait.h>
typedef struct
{
        int value;
        sem_t sem;
}shared_data;
int main()
{
        shared_data *data=mmap(NULL,sizeof(shared_data),PROT_READ|PROT_WRITE,MAP_SHARED|MAP_ANONYMOUS,-1,0);
        sem_init(&data->sem,1,0);
        pid_t pid=fork();
        if(pid==0)
        {
                printf("child:setting value to 42\n");
                data->value=42;
                sem_post(&data->sem);
                exit(0);
        }
        else
        {
                printf("parent :waiting for child\n");
                sem_wait(&data->sem);
                printf("parent vallue:%d\n",data->value);
                wait(NULL);
        }
        sem_destroy(&data->sem);
        return 0;
}


