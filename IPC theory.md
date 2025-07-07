### What is meant by an IPC Mechanism? 
```c
IPC (Inter-Process Communication) refers to methods used by processes (independent executing programs) to exchange data and signals with each other.
Since each process has its own memory space, IPC provides a way for them to communicate and coordinate.
```


### Why we use IPC Mechanism? 
```c
We use IPC mechanisms:
 To share data between processes.
 To coordinate actions of multiple processes.
 To support synchronization.
 For resource sharing (like shared memory).
 To allow client-server communication (e.g., databases, file systems).
```


### What are the types of IPC Mechanism's? 
```c

      Type                           Description                                   
------------------------------------------------------------------- 
    Pipes                        Unidirectional communication (parent-child)   
   Named Pipes (FIFO)            Like pipes, but with a name in the filesystem 
   Message Queues                Send and receive messages asynchronously      
   Shared Memory                 Fastest IPC, direct memory sharing            
   Semaphores                    Used for synchronization, not data transfer   
   Sockets                       Communication over a network or locally       
    Signals                      Simple notifications to a process             
```


### What is meant by “unicast” and “multicast” IPC? 
```c
Unicast IPC: Communication from one sender to one receiver.
Example: Pipe between a parent and child process.
Multicast IPC: Communication from one sender to multiple receivers.
Example: Broadcasting a message using sockets to multiple clients
```

### What is meant by PIPES?
```c
A Pipe is a unidirectional communication channel between processes.
It allows one-way data flow:
One process writes into the pipe.
Another process reads from it.
Types:
Unnamed Pipe: For related processes (parent-child).
Named Pipe (FIFO): For unrelated processes.
```
 
### What is meant by Blocking Calls? 
```c
A blocking call causes a process to wait (block) until an operation is completed.
The process is suspended until it gets the required resource or data.
```
### What are the types of Blocking Calls? 
```c
Types of blocking behavior:
Read Blocking: Wait until data is available.
Write Blocking: Wait until buffer has space.
Accept Blocking: Wait for a connection (in sockets).
Wait/Join Blocking: Wait for another process/thread to complete.
```

### What are the different types of I/O Calls? 
```c
Blocking I/O
Non-blocking I/O
Asynchronous I/O (AIO)
Synchronous I/O
```

### What are the I/O calls we are used in IPC Mechanisms? 
```c
common I/O calls in IPC:
read() – read from pipe, FIFO, socket, etc.
write() – write to pipe, FIFO, socket, etc.
recv(), send() – for sockets.
msgrcv(), msgsnd() – for message queues.
shmat() – attach shared memory.
semop() – semaphore operations.
```

### What are the Blocking Calls used in IPC? 
```c
IPC-related blocking calls include:
 IPC Type                      Blocking Calls                 
 ----------------------------------------------- 
   Pipe/FIFO                 `read()`, `write()`            
   Message Queue             `msgrcv()`, `msgsnd()`         
   Socket                    `recv()`, `send()`, `accept()` 
  Shared Memory              `semop()` (used for sync)      

```

### What is meant by Named Pipes? 
```c
Named Pipes (also called FIFOs) are a type of IPC mechanism that allows unrelated processes to communicate.
Unlike unnamed pipes, named pipes have a name in the file system, so different processes can open and use them.
```

### Where is the FIFO Object created? 
```c
A FIFO (named pipe) is created in the file system as a special file (usually in /tmp/ or current directory).
You can see it using ls -l, marked with a p in the permissions (prw-r--r--).

```
### What is the call used to create a FIFO Object? 
```c
int mkfifo(const char *pathname, mode_t mode);
pathname: path to the FIFO file.
mode: permission bits (e.g., 0666).
```

### What are the Blocking Calls used in Named Pipes?
 ```c
In Named Pipes, these can block:
read() → blocks until data is available.
write() → blocks until a reader is available or pipe buffer has space.
open() → open("fifo", O_WRONLY) blocks until a reader opens the FIFO.
```

### Why read system calls acts as a blocking call?
```c
 read() blocks because it waits for data.
  If no data is available, the calling process sleeps until data arrives or the writer closes the pipe.
This avoids busy-waiting and saves CPU.
```

### Difference between the Named Pipes and Pipes? 
```c
   Feature         | Named Pipe (FIFO)                Unnamed Pipe               
 --------------- | ----------------------------------------------------- 
    Name             Has a name in file system         No name                    
    Scope            Between unrelated processes       Only parent-child/siblings 
   Creation          `mkfifo()` or `mknod()`          `pipe()` system call       
   Persistence       Exists until deleted              Exists only during process 
   Access            File path based                    File descriptor based      

```
### What is return value of read system call? 
```c
Returns number of bytes read on success.
Returns 0 if end-of-file (e.g., writer closed the pipe).
Returns -1 on error.
```

## What is meant by message queue? 
```c
A Message Queue is an IPC mechanism where processes can send and receive structured messages (not just byte streams).
Messages are stored in the kernel, allowing asynchronous communication between processes.

```
### Why we use message queues? 

To send structured data (not just bytes).
```c
To support asynchronous and non-blocking communication.
To avoid message loss with buffering.
To support priority-based message delivery.
```

### What is difference between Named Pipe and Message Queue?
```c
 Feature            Named Pipe                Message Queue                   
 ----------------- ----- ----------------------------------------------------- 
   Data              Byte stream              Message structure               
   Blocking          Read/write block        Can be blocking or non-blocking 
  Persistence       Removed when deleted      Exists until explicitly deleted 
   Access           Through file path          Access via queue ID             
   Priority             No                            Yes                             
```

### What is the system call used to create the message queue? 
```c
int msgget(key_t key, int msgflg);
key: IPC key
msgflg: permission + creation flags (e.g., IPC_CREAT | 0666)

```
### Where was the message queue created?
```c
 Message queues are created in kernel space, not the file system.
They’re managed by the OS and identified using a queue ID returned by msgget().
```

### What is meant by Shared Memory? 
```c
Shared Memory is an IPC mechanism where multiple processes map a common memory segment into their address space.
It allows fast and direct communication by reading/writing the same memory.
```

#### Why we use Shared Memory?
```c
 It is the fastest IPC mechanism.
 Allows large data transfers without copying.
 Enables real-time communication.
 Useful when speed is critical (e.g., multimedia, games).
```
### Difference between Shared Memory and Message Queues
```c
 Feature              Shared Memory                 Message Queue           
 -------------------  -------------------------  ----------------------- 
      Speed           Very fast (direct access)     Slower (kernel-managed) 
    Data Format         Raw memory (user-defined)     Message structures      
    Synchronization     Requires semaphores/mutex     Handled by queue itself 
      Data Size         Good for large data            Good for small messages 
      Complexity        More complex (needs sync)      Easier to use           

```
#### What is use of stat command? 
```c
The stat command in Linux is used to display detailed information about a file or directory.
Output includes:
       File size
       Permissions
       Inode number
       Last access, modification time
       File type (regular file, FIFO, etc.)

command : stat myfile.txt
```

### What is the use of semctl command? 
```c
The semctl() system call is used to control System V semaphore sets.
It is used for:
       Setting/Getting semaphore values
        Removing semaphore set
        Changing permissions or ownership
commands: semctl(semid, 0, SETVAL, val);   // Set value
          semctl(semid, 0, IPC_RMID);      // Remove semaphore

```
### How do we destroy the shared memory object? 
```c
Use shmctl() with IPC_RMID to destroy a shared memory segment:
             shmctl(shmid, IPC_RMID, NULL);
This marks the shared memory for deletion.

```
#### What is meant by Semaphores
```c
A semaphore is a synchronization object used to control access to a shared resource by multiple processes or threads.
It has an integer value:
        Decrement (P/wait) when acquiring.
        Increment (V/signal) when releasing.

```
### Why we use semaphores? 
```c
To avoid race conditions.
To ensure mutual exclusion.
To synchronize access to shared resources (e.g., memory, files).

```
### What is meant by Synchronization? 
```c
Synchronization is the coordination of concurrent processes or threads to ensure correct execution (e.g., one process writes, another reads).
Used to:
      Ensure data consistency
       Avoid race conditions
       Maintain execution order

```
#### What is meant by Asynchronization? 
```c
Asynchronization means that processes or threads run independently, without waiting for each other.
Pros:
      Better performance
       Parallelism
But can cause:
        Race conditions
        Inconsistent states
```

### Why we use mutex locks?
```c
A mutex (mutual exclusion lock) is used to protect critical sections so only one thread or process can access the resource at a time.
 ```

### What is the difference between mutex locks and semaphores?
```c
  Feature      Mutex Lock                              Semaphore                    
 -----------  --------------------------------------  ---------------------------- 
 Value Range  Binary (0 or 1)                         Integer (0 or more)          
 Ownership    Has ownership (only locker can unlock)  No ownership                 
 Usage        Thread-level locking                    Inter-process or thread sync 
 Type         Lighter weight                          More general purpose         

```
#### What is meant by Race Condition? 
```c
A race condition occurs when multiple processes or threads access shared data at the same time and outcome depends on timing.

```
### What is meant by Deadlock? 
```c
A deadlock occurs when two or more processes are waiting indefinitely for each other to release resources, and none can proceed.
Conditions for deadlock:
                      Mutual exclusion
                      Hold and wait
                      No preemption
                      Circular wait
```

### What is meant by Critical Section?
```c
A critical section is a section of code that accesses shared resources (memory, file, etc.),
and must not be executed by more than one thread/process at a time.
```

### What is the difference between system v and POSIX?
```

 Feature      System V IPC                  POSIX IPC                         
 -----------  ----------------------------  --------------------------------- 
 APIs         `semget`, `msgget`, `shmget`  `sem_open`, `mq_open`, `shm_open` 
 Naming       Integer keys (`ftok`)         Named using strings               
 Portability  Less portable                 More portable (POSIX-compliant)   
 Flexibility   More legacy style             Modern and easier to use          


```
### Describe the steps involved in creating and using a named pipe (FIFO) for IPC
```c
Create FIFO:
        mkfifo("myfifo", 0666);
Writer Process:
        int fd = open("myfifo", O_WRONLY);
         write(fd, "Hello", 5);

Reader Process:
            int fd = open("myfifo", O_RDONLY);
            read(fd, buffer, sizeof(buffer));
Close FIFO:
           close(fd);
Remove FIFO:
           rm myfifo

used between reacted processes:
Create pipe:
         int fd[2];
         pipe(fd);  // fd[0] = read end, fd[1] = write end
Fork process:
           pid_t pid = fork();
Child Process (Writer):
             close(fd[0]);             // Close read end
             write(fd[1], "Hi", 2);
             close(fd[1]);
Parent Process (Reader):
                close(fd[1]);             // Close write end
                read(fd[0], buffer, 100);
                close(fd[0]);

```

## Describe the steps involved in creating and using a pipe for IPC
```c
A pipe is a unidirectional communication channel used between related processes (typically parent-child).
It allows one-way data flow: one process writes, another reads.
Steps to Create and Use a Pipe for IPC
Step 1: Create the Pipe
            int fd[2];
            pipe(fd);
            fd[0] → read end of the pipe
            fd[1] → write end of the pipe
            Returns 0 on success; -1 on failure
Step 2: Fork a Child Process
            pid_t pid = fork();
This creates a child process.
After fork(), both parent and child can use the pipe.
Step 3: Use the Pipe for Communication
Parent Process (Reader):
                close(fd[1]); // Close unused write end
                read(fd[0], buffer, sizeof(buffer));
                close(fd[0]);
Child Process (Writer):
                close(fd[0]); // Close unused read end
                 write(fd[1], "Hello", 5);
                 close(fd[1]);
Step 4: Wait and Exit
          Parent can wait for the child using wait(NULL);
          Both processes exit cleanly

  pipe(fd) ─────→ [ fd[0] Read | fd[1] Write ]

       Parent                          Child
    ------------                   ------------
   | close(fd[1]); |             | close(fd[0]); |
   | read(fd[0]);  |  ←───────   | write(fd[1]); |
   | close(fd[0]); |             | close(fd[1]); |
    ------------                   ------------
```
#### What is Interprocess communication?
a) allows processes to communicate and synchronize their actions when using 
the same address space
b) allows processes to communicate and synchronize their actions
c) allows the processes to only synchronize their actions without 
communication
d) none of the mentioned
```c
Ans:  b
```

#### Message passing system allows processes to __________
a) communicate with each other without sharing the same address space
b) communicate with one another by resorting to shared data
c) share data
d) name the recipient or sender of the message
```c
Ans:  a
```
### Which of the following two operations are provided by the IPC facility
a) write & delete message
b) delete & receive message
c) send & delete message
d) receive & send message
```c
Ans:d

```
### Messages sent by a process __________
a) have to be of a fixed size
b) have to be a variable size
c) can be fixed or variable sized
d) none of the mentioned
```c
Ans:  c
```
#### The link between two processes P and Q to send and receive messages is called 
__________
a) communication link
b) message-passing link
c) synchronization link
d) all of the mentioned
```c
Ans: a
```
### Which of the following are TRUE for direct communication?
a) A communication link can be associated with N number of process(N = 
max. number of processes supported by system)
b) A communication link is associated with exactly two processes
c) Exactly N/2 links exist between each pair of processes(N = max. number of 
processes supported by system)
d) Exactly two link exists between each pair of processes
```c
Ans: b
```

#### In indirect communication between processes P and Q __________
a) there is another process R to handle and pass on the messages between P 
and Q
b) there is another machine between the two processes to help communication
c) there is a mailbox to help communication between P and Q
d) none of the mentioned
```c
Ans: c
```
#### In the non blocking send __________
a) the sending process keeps sending until the message is received
b) the sending process sends the message and resumes operation
c) the sending process keeps sending until it receives a message
d) none of the mentioned
```c
Ans: b
```
### What is the role of a semaphore in IPC?
a) Coordinating access to shared resources
b) Transferring data between processes
c) Sending signals to other processes
d) Creating communication channels
```c
Ans:a
```
#### Bounded capacity and Unbounded capacity queues are referred to as __________
a) Programmed buffering
b) Automatic buffering
c) User defined buffering
d) No buffering
```c
Ans: b
```

#### What is the role of a semaphore in IPC?
a) Coordinating access to shared resources
b) Transferring data between processes
c) Sending signals to other processes
d) Creating communication channels
```c
Ans: a
```

#### Which IPC mechanism provides a message-oriented communication model?
a) Shared memory
b) Pipes
c) Message queues
d) Sockets
```c
Ans: c
```

#### In the context of IPC, what are signals used for?
a) Synchronizing processes
b) Coordinating access to shared memory
c) Sending messages between processes
d) Notifying processes about events or conditions
```c
Ans: d

```
## Which synchronization primitive is used to ensure mutually exclusive access to 
critical sections of code?
a) Semaphore
b) Mutex
c) Condition variable
d) Barrier
```c
Ans: b
```
#### Which IPC mechanism provides a communication endpoint for processes to 
communicate over a network or between processes on the same system
a) Named pipes
b) Message queues
c) Shared memory
d) Sockets
```c
Ans: d
```

#### What is the primary advantage of using message queues for IPC compared to shared 
memory?
a) Higher performance
b) More flexible communication model
c) Simplicity of implementation
d) Direct access to shared data
```c
Ans: b
```

#### Which IPC mechanism involves copying data between processes, potentially 
incurring additional overhead?
a) Shared memory
b) Message queues
c) Sockets
d) Semaphores
```c
Ans: b
```

### Which aspect is crucial in IPC to ensure that multiple processes or threads coordinate 
their activities and access shared resources safely?
a) Data transfer efficiency
b) Synchronization
c) Message passing
d) Resource allocation
```c

Ans: b 

```
### Which IPC mechanism involves copying data between processes through a temporary 
storage area in the kernel?
a. Shared memory
b. Message queues
c. Sockets
d. Named pipes

```c
Ans: d

```
#### Which IPC mechanism provides a high-performance, shared memory region for data 
exchange between processes?
a) Pipes
b) Semaphores
c) Message queues
d) Shared memory
```c
Ans:d
```

### Which IPC mechanism is being used in the following pseudocode snip?
/ Producer process
while (true) {
 produce_item(item);
 send_item_to_queue(item);
}
// Consumer process
while (true) {
 receive_item_from_queue(item);
 consume_item(item);
}
a) Shared memory
b) Message queues
c) Sockets
d) Named pipes
```c
Ans: b
```

### What synchronization primitive is being used in the following pseudocode snippet?
// Mutex initialization
mutex = create_mutex();
// Thread 1
lock_mutex(mutex);
// Critical section
// Access shared resource
unlock_mutex(mutex);
// Thread 2
lock_mutex(mutex);
// Critical section
// Access shared resource
unlock_mutex(mutex);
a) Semaphore
b) Mutex
c) Condition variable
d) Barrier
```c
Ans: b 
```

### What type of communication is being used in the following pseudocode snippet?
// Server process
create_socket();
bind_socket();
listen_for_connections();
while (true)
{
 accept_connection();
 receive_data_from_client();
 process_data();
 send_response_to_client();
}
// Client process
create_socket();
connect_to_server();
send_data_to_server();
receive_response_from_server();
a) Shared memory
b) Message passing
c) Message queues
d) Sockets
```c
Ans: d
```
