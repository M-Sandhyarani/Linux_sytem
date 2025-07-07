### Implement a program that uses pipes for communication between a parent and child process. Show how data can be passed between processes using pipes.
```c
#include<stdio.h>
#include<unistd.h>
#include<string.h>
int main()
{
        int fd[2];
        pipe(fd);
        pid_t pid=fork();
        if(pid==0)
        {
                close(fd[1]);
                char buffer[100];
                read(fd[0],buffer,sizeof(buffer));
                printf("child received:%s\n",buffer);
                close(fd[0]);
        }
        else
        {
                close(fd[0]);
                char msg[]="hello from parent";
                write(fd[1],msg,strlen(msg)+1);
                close(fd[1]);
        }
        return 0;
}

```
### Create a program where two processes communicate synchronously using pipes. Ensure that one process waits for the other to finish before proceeding.
```c
#include<stdio.h>
#include<unistd.h>
#include<string.h>
#include<sys/wait.h>
int main()
{
        int fd[2];
        pipe(fd);
        pid_t pid=fork();
        if(pid==0)
        {
                close(fd[1]);
                char buffer[100];
                read(fd[0],buffer,sizeof(buffer));
                printf("child read:%s\n",buffer);
                close(fd[0]);
        }
        else
        {
                close(fd[0]);
                char msg[]="synchronous communication";
                write(fd[1],msg,strlen(msg)+1);
                wait(NULL);
                close(fd[1]);
        }
        return 0;
}
```

#### Implement a program that uses Named pipes for communication between two processes.
```c
#include<stdio.h>
#include<stdlib.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<unistd.h>
int main()
{
        const char *fifo="myfifo";
        mkfifo(fifo,0666);
        if(fork()==0)
        {
                int fd=open(fifo,O_RDONLY);
                char buffer[100];
                read(fd,buffer,sizeof(buffer));
                printf("child read:%s\n",buffer);
                close(fd);
        }
        else
        {
                int fd=open(fifo,O_WRONLY);
                write(fd,"hello fifo",11);
                close(fd);
                wait(NULL);
        }
        return 0;
}

```


###  Write a C program to create a message queue using the msgget system call. Ensure that the program checks for errors during the creation process.
```c

#include<stdio.h>
#include<sys/ipc.h>
#include<sys/msg.h>
int main()
{
        key_t key=fork("progfile",64);
        int msgid=msgget(key,0666|IPC_CREAT);
        if(msgid==-1)
        {

                 perror("msgget failed");
                 return 1;
        }
        printf("message queue created with id:%d\n",msgid);
        return 0;
}


```

### Develop two separate C programs, one for sending messages and the other for receiving messages through a created message queue.

```c
#include<stdio.h>
#include<sys/ipc.h>
#include<string.h>
#include<sys/msg.h>
struct msg_buffer
{
        long msg_type;
        char msg_text[100];
};
int main()
{
        key_t key=ftok("progfile",65);
        int msgid=msgget(key,0666|IPC_CREAT);
        struct msg_buffer message={1,"helloo from sender"};
        msgsnd(msgid,&message,sizeof(message),0);
        printf("message sent.\n");
        return 0;
}


#include<stdio.h>
#include<sys/ipc.h>
#include<sys/msg.h>
struct msg_buffer
{
        long msg_type;
        char msg_text[100];
};
int main()
{
        key_t key=ftok("progfile",65);
        int msgid=msgget(key,0666|IPC_CREAT);
        struct msg_buffer message;
        msgrcv(msgid,&message,sizeof(message),1,0);
        printf("received:%s\n",message.msg_text);
      (with use without use)
        msgctl(msdig,IPC_RMID,NULL);
        return 0;
}
```



### Create a program to remove an existing message queue using the msgctl system call. Ensure that the program prompts the user for confirmation before deleting the message queue.

```c
#include<stdio.h>
#include<sys/ipc.h>
#include<sys/msg.h>
int main()
{
        key_t key=ftok("progfile",65);
        int msgid=msgget(key,0666);
        char confirm;
        printf("areyou suer the deleted file(y/n):");
        scanf("%c",&confirm);
        if(confirm=='y')
        {
                msgctl(msgid,IPC_RMID,NULL);
                printf("message removes.\n");
        }
        else
        {
                printf("deletion absorted.\n");
        }
        return 0;
}


```



### Write a C program that initializes a shared memory segment using shmget.
```c
#include<stdio.h>
#include<sys/ipc.h>
#include<sys/shm.h>
int main()
{
        key_t key=ftok("shmfile",65);
        int shmid=shmget(key,1024,0666|IPC_CREAT);
        if(shmid==-1)
        {
                perror("shmget");
                return 1;
        }
        printf("shared memory created id:%d\n",shmid);
        return 0;
}


```
#### Develop a program that attaches to a previously created shared memory segment using shmat and detaches using shmdt.
```c
#include<stdio.h>
#include<unistd.h>
#include<string.h>
#include<sys/shm.h>
#include<sys/ipc.h>
int main()
{
        key_t key=ftok("shmfile",65);
        int shmid=shmget(key,1024,0666);
        char *str=(char *)shmat(shmid,NULL,0);
        printf("read from shared memory:%s\n",str);
        shmdt(str);
        return 0;
}



```
### Create a program that forks multiple processes, and each process communicates using shared memory.
```c
#include<stdio.h>
#include<string.h>
#include<sys/ipc.h>
#include<sys/shm.h>
#include<unistd.h>
int main()
{
        key_t key=ftok("shmfile",65);
        int shmid=shmget(key,1024,066|IPC_CREAT);
        char *str=(char *)shmat(shmid,NULL,0);
        if(fork()==0)
        {
                strcpy(str,"meaasge from child");
        }
        else
        {
                sleep(1);
                printf("parent read:%s\n",str);
                shmdt(str);
                shmctl(shmid,IPC_RMID,NULL);
        }
        return 0;
}
```



### Write a program that dynamically creates shared memory segments based on user input.

```c
#include<stdio.h>
#include<sys/shm.h>
#include<sys/ipc.h>
#include<stdlib.h>
int main()
{
        int size;
        printf("enter shared memory size in bytes :");
        scanf("%d",&size);
        key_t key=ftok("shmfile",65);
        int shmid=shmget(key,1024,0666|IPC_CREAT);
        if(shmid==-1)
        {
                perror("shmget");
                return 1;
        }
        printf("shared memory id:%d created with size %d byte\n",shmid,size);
        return 0;
}

```

### Create a program that monitors and displays the usage statistics ofshared memory segments, such as the amount of memory used and the number of attached processes.

```c
#include<stdio.h>
#include<sys/shm.h>
#include<sys/ipc.h>
int main()
{
        key_t key=ftok("shmfile",65);
        int shmid=shmget(key,1024,0666|IPC_CREAT);

        if(shmid<0)
        {
                perror("shmget");
                return 1;
        }
        struct shmid_ds buf;
        if(shmctl(shmid,IPC_STAT,&buf)==-1)
        {
                perror("shmctl");
                return 0;
        }
        printf("shared memory size:%zu bytes\n",buf.shm_segsz);
        printf("no fo attached processes:%lu\n",buf.shm_nattch);
        return 0;
}

```



#### Design a program that dynamically resizes a shared memory segment based on changing requirements.
```c

#include<stdio.h>
#include<stdlib.h>
#include<sys/ipc.h>
#include<sys/shm.h>
#include<string.h>
#define INIT_SIZE 1024
#define NEW_SIZE 2048
int main()
{
        key_t key=ftok("shmfile",65);
        int shmid=shmget(key,INIT_SIZE,0666|IPC_CREAT);
        if(shmid==-1)
        {
                perror("shmget");
                return 1;
        }
        char *data=(char *)shmat(shmid,NULL,0);
        strcpy(data,"initial data in shared memory");
        shmdt(data);
        shmctl(shmid,IPC_RMID,NULL);
        shmid=shmget(key,NEW_SIZE,0666|IPC_CREAT);
        data=(char *)shmat(shmid,NULL,0);
        strcat(data,  "+extended data");
        printf("updated data:%s\n",data);
        shmdt(data);
        shmctl(shmid,IPC_RMID,NULL);
        return 0;
}


```



### Write a C program that uses semget to create a new semaphore set

```c
#include<stdio.h>
#include<sys/sem.h>
#include<sys/ipc.h>
#include<stdlib.h>
int main()
{
        key_t key=ftok("semfile",75);
        int semid=semget(key,1,IPC_CREAT|0666);
        if(semid==-1)
        {
                perror("senget");
                return 1;
        }
        union semum
        {
                int val;
        }arg;
        arg.val=1;
        semctl(semid,0,SETVAL,arg);
        printf("semaphores createed and initialised.\n");
        return 0;
}



```
##### Create a multithreaded program where threads synchronize using semaphore sets.
```c

#include<stdio.h>
#include<sys/ipc.h>
#include<sys/sem.h>
#include<pthread.h>
#define SEM_COUNT 1
union semun
{
        int val;
};
int semid;
void sem_wait0()
{
        struct sembuf op={0,-1,0};
        semop(semid,&op,1);
}
void sem_signal0()
{
        struct sembuf op={0,1,0};
        semop(semid,&op,1);
}
void* thread_fun(void* arg)
{
        sem_wait0();
        printf("creative section %lu\n",pthread_self());
        sleep(1);
        printf("leaving critical section %lu\n",pthread_self());
        sem_signal0();
        return NULL;
}
int main()
{
        key_t key=ftok("semfile",66);
        semid=semget(key,SEM_COUNT,IPC_CREAT|0666);
        union semun u={1};
        semctl(semid,0,SETVAL,u);
        pthread_t t1,t2;
        pthread_create(&t1,NULL,thread_fun,NULL);
        pthread_create(&t2,NULL,thread_fun,NULL);
        pthread_join(t1,NULL);
        pthread_join(t2,NULL);
        semctl(semid,0,IPC_RMID);
        return 0;
}       
```


####Create a program with two processes that perform semaphore operations (wait andsignal) on a semaphore set using semop.

```c
#include<stdio.h>
#include<unistd.h>
#include<sys/ipc.h>
#include<sys/sem.h>
#include<stdlib.h>
void sem_wait0(int semid)
{
        struct sembuf op={0,-1,0};
        semop(semid,&op,1);
}
void sem_signal0(int semid)
{
        struct sembuf op={0,1,0};
        semop(semid,&op,1);
}
int main()
{
        key_t key=ftok("semfile",67);
        int semid=semget(key,1,IPC_CREAT|0666);
        union semun{int val;}u={1};
        semctl(semid,0,SETVAL,u);
        if (fork()==0)
        {
                sem_wait0(semid);
                printf("childin critical section\n");
                sleep(2);
                sem_signal0(semid);
                exit(0);
        }
        else
        {
                sleep(1);
                sem_wait0(semid);
                printf("parent in critical section\n");
                sem_signal0(semid);
                wait(NULL);
                semctl(semid,0,IPC_RMID);
        }
        return 0;
}
```

#### Write a program that performs control operations on the semaphore set using semctl.

```c
#include<stdlib.h>
#include<sys/ipc.h>
#include<sys/sem.h>
int main()
{
        key_t key=ftok("semfile",68);
        int semid=semget(key,2,IPC_CREAT|0666);
        union semun {int val;}u;
        u.val=1;
        semctl(semid,0,SETVAL,u);
        u.val=2;
        semctl(semid,0,SETVAL,u);
        printf("semaphores 0 value =%d\n",semctl(semid,0,GETVAL,0));
        printf("semaphores 1 value =%d\n",semctl(semid,1,GETVAL,0));
        semctl(semid,0,IPC_RMID);
        return 0;
}

```
#### Write a program where multiple processes compete for access to a critical section using semaphores to ensure mutual exclusion.
```c
#include<stdio.h>
#include<sys/wait.h>
#include<sys/sem.h>
#include<sys/sem.h>
#include<stdlib.h>
#include<unistd.h>
#define PROCS 4
union semun {int val;};
void sem_wait0(int semid)
{
        struct sembuf op={0,-1,0};
        semop(semid,&op,1);
}
void sem_signal0(int semid)
{
        struct sembuf op={0,1,0};
        semop(semid,&op,1);
}
int main()
{
        key_t key=ftok("semfile",70);
        int semid=semget(key,1,IPC_CREAT|0666);
        semctl(semid,0,SETVAL,(union semun){1});
        for(int i=0;i<PROCS;i++)
        {
                if(fork()==0)
                {
                        sem_wait0(semid);
                        printf("process %d in critical section\n",getpid());
                        sleep(1);
                        sem_signal0(semid);
                        exit(0);
                }
  }
        for(int i=0;i<PROCS;i++)wait(NULL);
        semctl(semid,0,IPC_RMID);
        return 0;
}

```
### Write a C program to create a pipe and pass an array of integers from the parent process to the child process through the pipe.
```c

#include<stdio.h>
#include<stdlib.h>
#include<sys/wait.h>
int main()
{
        int pipefd[2];
        int arr[]={1,2,3,4,5};
        int size=sizeof(arr)/sizeof(arr[0]);
        if(pipe(pipefd)==-1)
        {
                printf("pipe");
                return 1;
        }
        pid_t pid=fork();
        if(pid<0)
        {
                printf("fork");
                return 1;
        }
        else if(pid==0)
        {
                close(pipefd[1]);
                int buffer[5];
                read(pipefd[0],buffer,sizeof(buffer));
                printf("child received array :");
                for(int i=0;i<5;i++)
                {
                 printf("%d\n",buffer[i]);
                }
                printf("\n");
                close(pipefd[0]);
        }
        else
        {
                close(pipefd[0]);
                write(pipefd[1],arr,sizeof(arr));
                close(pipefd[1]);
                wait(NULL);
        }
        return 0;
}



```

#### Develop a program that uses pipes for bidirectional communication between two processes, where each process can send and receive messages.
```c
#include<string.h>
#include<sys/wait.h>
#include<stdlib.h>
#include<stdio.h>
int main()
{
        int pipe1[2],pipe2[2];
        char parent_msg="hello from parent";
        char child_msg="hello from child";
        char buffer[100];
        pipe(pipe1);
        pipe(pipe2);
        pid_t pid=fork();
        if(pid==0)
        {
                close(pipe1[1]);
                close(pipe2[0]);
                read(pipe1[0],buffer,sizeof(buffer));
                printf("child received :%s\n",buffer);
                write(pipe2[1],child_msg,strlen(child_msg)+1);
                close(pipe1[0]);
                close(pipe2[1]);
        }
        else
        {
                close(pipe1[0]);
                close(pipe2[1]);
                write(pipe1[1],parent_msg,strlen(parent_msg)+1);
                read(pipe2[1],buffer,sizeof(buffer));
                printf("parent received :%s\n",buffer);
                close(pipe1[1]);
                close(pipe2[0]);
                wait(NULL);
  }
        return 0;
}

```

### Create a C program where multiple processes write data to a named pipe, and another process reads from the named pipe and displays the received data.
 ```c
(writer.c)
#include<stdio.h>
#include<fcntl.h>
#include<string.h>
#include<sys/stat.h>
#include<unistd.h>
int main()
{
        const char *fifo="myfifo";
        mkfifo(fifo,0666);
        char msg[100];
        printf("enter message to write to pipe:");
        fgets(msg,sizeof(msg),stdin);
        int fd=open(fifo,O_WRONLY);
        write(fd,msg,strlen(msg)+1);
        close(fd);
        return 0;
}

(reader.c)

#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>
#include<sys/stat.h>
int main()
{
        const char *fifo="myfifo";
        mkfifo(fifo,0666);
        char buffer[100];
        int fd=open(fifo,O_RDONLY);
        printf("reader received :%s\n",buffer);
        read(fd,buffer,sizeof(buffer));
        close(fd);
        return 0;
}

```

### Implement a program where two processes exchange messages through a named pipe until a termination signal is received.

```c
#include<stdio.h>
#include<stdlib.h>
#include<fcntl.h>
#include<string.h>
#include<sys/stat.h>
#include<unistd.h>
int main()
{
        const char *fifo="myfifo";
        mkfifo(fifo,0666);
        pid_t pid=fork();
        if(pid==0)
        {
                char msg[100];
                while(1)
                {
                        printf("child.\n");
                        fgets(msg,sizeof(msg),stdin);
                        int fd=open(fifo,O_WRONLY);
                        write(msg,sizeof(msg),strlen(msg)+1);
                        close(fd);
                        if(strncmp(msg,"exit",4)==0)break;
                }
        }
        else
        {
                char buffer[100];
                while(1)
                {
                        int fd=open(fifo,O_RDONLY);
                        read(fd,buffer,sizeof(buffer));
                        close(fd);
                        printf("parent received :%s\n",buffer);
                        if(strncmp(buffer,"exit",4)==0)break;
                }
        }
        unlink(fifo);
        return 0;
}


```


### Develop a C program that acts as a server, continuously reading requests from a named pipe, and a client program that sends requests to the server through the same named pipe
```c
(server)
#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>
#include<sys/stat.h>
int main()
{
        const char *fifo="serverfifo";
        mkfifo(fifo,0666);
        char buffer[100];
        while(1)
        {
                int fd=open(fifo,O_RDONLY);
                read(fd,buffer,sizeof(buffer));
                close(fd);
                if(strncmp(buffer,"exit",4)==0)break;
                printf("server receives:%s\n",buffer);
        }
        unlink(fifo);
        return 0;
}
(client)
#include<stdio.h>
#include<string.h>
#include<fcntl.h>
#include<sys/wait.h>
int main()
{
        const char *fifo="clientfifo";
        mkfifo(fifo,0666);
        char msg[100];
        while(1)
        {
                printf("client :");
                fgets(msg,sizeof(msg),stdin);
                int fd=open(fifo,O_WRONLY);
                write(fd,msg,strlen(msg)+1);
                close(fd);
                if(strncmp(msg,"exit",4)==0)break;
        }
        return 0;
}


```


### Develop a program where multiple processes read from and write to a shared memory segment, synchronizing their access using semaphores.

```c
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/ipc.h>
#include<sys/shm.h>
#include<sys/sem.h>
#include<sys/wait.h>
union semun
{
        int val;
};
void p(int id)
{
        struct sembuf s={0,-1,0};
        semop(id,&s,1);
}
void v(int id)
{
        struct sembuf s={0,1,0};
        semop(id,&s,1);
}
int main()
{
        int shmid=shmget(1234,sizeof(int),0666|IPC_CREAT);
        int *data=(int *)shmat(shmid,NULL,0);
        int semid=shmget(5678,1,0666|IPC_CREAT);
        union semun u={1};
        semctl(semid,0,SETVAL,u);
        *data=0;
        for(int i=0;i<3;i++)
        {
                if(fork()==0)
                {
                        for(int j=0;j<5;j++)
                                 {
                                p(semid);
                                printf("PID %d:%d->%d\n",getpid(),*data,++(*data));
                                v(semid);
                                sleep(1);
                        }
                        exit(0);
                }

        }
        for(int i=0;i<3;i++)wait(NULL);
        printf("final:%d\n",*data);
        return 0;
}
```

#### Create a C program where the parent process creates a shared memory segment, writes data into it, and waits for the child process to read the data from the shared memory.
```c
#include<stdio.h>
#include<string.h>
#include<sys/wait.h>
#include<sys/ipc.h>
#include<sys/shm.h>
#include<unistd.h>
int main()
{
        key_t key=1234;
        int shmid=shmget(key,100,IPC_CREAT|0666);
        char *data=(char*)shmat(shmid,NULL,0);
        if(fork()==0)
        {
                sleep(1);
                printf("child read:%s\n",data);
                shmdt(data);
        }
        else
        {
                strcpy(data,"hello world!");
                wait(NULL);
                shmdt(data);
                shmctl(shmid,IPC_RMID,NULL);
        }
        return 0;
}


```


#### Write a program where multiple processes cooperate to calculate the sum of a large array of numbers stored in a shared memory segment.

```c
#include<stdio.h>
#include<stdlib.h>
#include<sys/wait.h>
#include<sys/shm.h>
#include<sys/sem.h>
#include<sys/ipc.h>
#include<unistd.h>
#define N 1000
#define P 4
union semun
{
        int val;
};
void P_sem(int id)
{
        struct sembuf s={0,-1,0};
        semop(id,&s,1);
}
void V_sem(int id)
{
        struct sembuf s={0,1,0};
        semop(id,&s,1);
}
int main()
{
        int aid=shmget(1234,N*sizeof(int),0666|IPC_CREAT);
        int sid=shmget(2345,sizeof(int),0666|IPC_CREAT);
        int sem=semget(3456,1,IPC_CREAT|0666);
        union semun u={1};
        semctl(sem,0,SETVAL,u);
        int *a=shmat(aid,0,0),*sum=shmat(sid,0,0);
        *sum=0;
        for(int i=0;i<N;i++)a[i]=1;
        for(int p=0;p<P;p++)
        {
                if(fork()==0)
                {
                        int s=p*(N/P),e=(p+1)*(N/P),local=0;
                        for(int i=s;i<e;i++)local+=a[i];
                        P_sem(sem);
                        *sum+=local;
                        V_sem(sem);
                        return 0;
                }
        }
        while(wait(NULL)>0);
        printf("total;%d\n",*sum);
        return 0;
}

```

#### Write a program where two processes communicate through a message queue. One process sends a message containing a string to the other process, which receives and prints the message.
```c


#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<sys/ipc.h>
#include<sys/msg.h>
struct msg
{
        long t;
        char txt[100];
};
int main()
{
        int id=msgget(1234,0666|IPC_CREAT);
        struct msg m;
        if(fork())
                m.t=1,strcpy(m.txt,"hello"),msgsnd(id,&m,sizeof(m.txt),0),wait(0),msgctl(id,IPC_RMID,0);
        else
                msgrcv(id,&m,sizeof(m.txt),1,0),printf("%s\n",m.txt);
}

```

### Create a program where multiple processes coordinate access to a shared resource using semaphores(system v). Simulate a scenario where processes request and release access to the resource with proper synchronization

```c
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/ipc.h>
#include<sys/shm.h>
#include<sys/sem.h>
#include<sys/wait.h>
union semun
{
        int val;
};
void p(int id)
{
        struct sembuf s={0,-1,0};
        semop(id,&s,1);
}
void v(int id)
{
        struct sembuf s={0,1,0};
        semop(id,&s,1);
}
int main()
{
        int shmid=shmget(1234,sizeof(int),0666|IPC_CREAT);
        int *val=(int *)shmat(shmid,NULL,0);
        int semid=shmget(5678,1,0666|IPC_CREAT);
        union semun u={1};
        semctl(semid,0,SETVAL,u);
        *val=0;
        for(int i=0;i<3;i++)
        {
                if(fork()==0)
                {
                        for(int j=0;j<5;j++)
                        {
                                p(semid);
                                printf("PID %d:%d->%d\n",getpid(),*val,++(*val));
                                v(semid);
                                sleep(1);
                        }
                        return 0;
                }

        }
        while(wait(NULL)>0);
        printf("final:%d\n",*val);
        return 0;
}


```

#### Develop a program where two processes share an integer value stored in a shared memory segment. One process increments the value and the other process ds decrements it, with proper synchronization

```c
#include<stdio.h>
#include<sys/ipc.h>
#include<sys/shm.h>
#include<sys/sem.h>
#include<unistd.h>
union semun
{
        int val;
};
void wait(int id)
{
        struct sembuf s={0,-1,0};
        semop(id,&s,1);
}
void signal(int id)
{
        struct sembuf s={0,1,0};
        semop(id,&s,1);
}
int main()
{
        int shmid=shmget(1234,sizeof(int),0666|IPC_CREAT);
        int *val=(int *)shmat(shmid,NULL,0);
        int semid=semget(5678,1,0666|IPC_CREAT);
        union semun u={1};
        semctl(semid,0,SETVAL,u);
        if(fork()==0)
 {
                for(int i=0;i<5;i++)
                {
                        wait(semid);
                        (*val)--;
                        printf("child:%d\n",*val);
                        signal(semid);
                        sleep(1);
                }
        }
                else
        {
                *val=0;
                for(int i=0;i<5;i++)
                {
                        wait(semid);
                        (*val)++;
                        printf("parent:%d\n",*val);
                        signal(semid);
                        sleep(1);
                }
        }
        return 0;
}



```

### Design a program where multiple processes are forked and synchronization is achieved using semaphores

```c
#include<stdio.h>
#include<unistd.h>
#include<sys/ipc.h>
#include<sys/shm.h>
#include<sys/sem.h>
#include<sys/wait.h>
union semun
{
        int val;
};
void p(int s)
{
        struct sembuf b={0,-1,0};
        semop(s,&b,1);
}
void v(int s)
{
        struct sembuf b={0,1,0};
        semop(s,&b,1);
}
int main()
{
        int shmid=shmget(1234,sizeof(int),0666|IPC_CREAT);
        int *val=(int *)shmat(shmid,NULL,0);
        int semid=shmget(5678,1,0666|IPC_CREAT);
        union semun u={1};
        semctl(semid,0,SETVAL,u);
        *val=0;
        for(int i=0;i<3;i++)
        if(fork()==0)
                {
                        for(int j=0;j<5;j++)
                        {
                                p(semid);
                                (*val);
                                v(semid);
                                printf("PID %d:%d\n",getpid(),*val);
                                usleep(100000);
                        }return 0;

                }
                while(wait(NULL)>0);
                printf("final:%d\n",*val);
                return 0;
}

```


### Design a program that uses a message queue for synchronization between multiple processes.

```c
#include<stdio.h>
#include<sys/msg.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/ipc.h>
struct msg
{
        long t;
};
int main()
{
        int id=msgget(1234,0666|IPC_CREAT);
        struct msg m;
        for(int i=1;i<=3;i++)
                if(fork()==0)
                        return msgrcv(id,&m,0,i,0),printf("child %d:go\n",i),0;
        sleep(1);
        for(int i=1;i<=3;i++)
                m.t=i,msgsnd(id,&m,0,0),sleep(1);
        while(wait(NULL)>0);
        msgctl(id,IPC_RMID,NULL);
}

```
