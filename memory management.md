### Write a C program to demonstrate dynamic memory allocation using malloc().
```c
#include<stdio.h>
#include<stdlib.h>
int main()
{
        int n,i;
        int *arr;
        printf("enter number of elements: ");
        scanf("%d",&n);
        arr=(int *)malloc(sizeof(int));
        if(arr==NULL)
        {
                printf("memory allocation\n");
                return 1;
        }
        printf("enter %d of numbers:\n",n);
        for(i=0;i<n;i++)
        {
                scanf("%d",&arr[i]);
        }
        printf("entered integers:\n");
        for(i=0;i<n;i++)
        {
                printf("%d ",arr[i]);
        }
        printf("\n");
        free(arr);
         return o;
}

```
### Implement a C program to allocate memory for an array dynamically using calloc().
```c
#include<stdio.h>
#include<stdlib.h>
int main()
{

        int n,i;
        int *arr;
        printf("enter number of elements : ");
        scanf("%d",&n);
        arr=(int *)calloc(n,sizeof(int));
        if(arr==NULL)
        {
                printf("memory allocation\n");
                return 1;
        }
        printf("array initialization to zero:\n");
        for(i=0;i<n;i++)
        {
                printf("%d ",arr[i]);
        }
        printf("\n");
        printf("enter %d integers:\n",n);
        for(i=0;i<n;i++)
        {
                scanf("%d",&arr[i]);
        }
        printf("enter elements:\n",n);
        for(i=0;i<n;i++)
        {
                printf("%d ",arr[i]);
        }
        printf("\n");
        free(arr);
        return 0;
}

```
#### Write a C program to resize dynamically allocated memory using realloc().
```c
#include<stdio.h>
#include<stdlib.h>
int main()
{
        int n,new_n,i;
        int *arr;
        printf("enter no.of elements : ");
        scanf("%d",&n);
        arr=(int*)malloc(n * sizeof(int));
        if(arr==NULL)
        {
                printf("memory allocation\n");
                return 1;
        }
        printf("entner %d of integers : \n", n);
        for(i=0;i<n;i++)
        {
                scanf("%d",&arr[i]);
        }
        printf("enter integers :\n");
        for(i=0;i<n;i++)
        {
                printf("%d ",arr[i]);
        }
        printf("\n");
        printf("enter new size of array :\n");
        scanf("%d",&new_n);
        arr=(int *)realloc(arr,new_n*sizeof(int));
        if(arr==NULL)
        {
                printf("memory allocation \n");
                return 1;
        }
        if(new_n>n)
        {
                printf("enter %d of more integers :\n",new_n-n);
                for(i=n;i<new_n;i++)
                {
                        scanf("%d",&arr[i]);
                }
        }
        printf("enter integers :\n");
        for(i=0;i<new_n;i++)
        {
                printf("%d ",arr[i]);
        }
        printf("\n");
        free(arr);
        return 0;
}

```

### Develop a program in C to allocate memory for a linked list node dynamically.
```c
#include<stdio.h>
#include<stdlib.h>
struct node
{
        int data;
        struct node* next;
};
int main()
{
        struct node *node=(struct node *)malloc(sizeof(struct node));
        node->data=10;
        node->next=NULL;
        printf("%d",node->data);
        free(node);
        return 0;
}

```

#### Implement a C program to simulate memory allocation using the first-fit algorithm.
```c
#include<stdio.h>
void firstfit(int blocksize[],int n,int processsize[,int n])
{
        int allocation[n];
        for(int i=0;i<n;i++)
                allocation[i]=-1;
        for(int i=0;i<n;i++)
        {
                for(int j=0;j<m;j++)
                {
                        if(blocksize[j]>=processsize[i])
                        {
                                allocation[i]=j;
                                blocksize[j]-=processsize[j];
                                break;
                        }
                }
        }
        printf("\npro no.\tpro size\tblock no\n");
        for(int i=0;i<n;i++)
        {
                printf("%d\t\t%d\t\t",i+1,processsize[i]);
                if(allocation[i]!=-1)
                        printf("%d\n",allocation[i]+1);
                else
                        printf("not allocation\n");
        }
}
int main()
{
        int blocksize[]={100,200,300,400,500};
        int processsize[]={123,232,334,456,505};
        int m=sizeof(blocksize)/sizeof(blocksize[0]);
        int n=sizeof(processsize)/sizeof(processsize[0]);
        firstfit(blocksize,m,processsize,n);
         return 0:
}


```
### Write a C program to simulate memory allocation using the best-fit algorithm.
```c

#include<stdio.h>
void bestfit(int blocksize[],int m,int processsize[],int n)
{
        int allocation[n];
        for(int i=0;i<n;i++)
        {
                allocation[i]=-1;
                for(int i=0;i<n;i++)
                {
                        int bestidx=-1;
                        for(int j=0;j<m;j++)
                        {
                                if(blocksize[j]>=processsize[i])
                                        if(bestidx==-1||blocksize[j]<blocksize[bestidx])
                                                bestidx=j;
                        }
                }
                if(bestidx !=-1)
                {
                        allocation[i]=bestidx;
                        blocksize[bestidx]-=processsize[i];
                }
        }
        printf("\npro.no \tpro size\tblock no.\n");
        for(int i=0;i<n;i++)
 {
                printf("%d\t\t%d\t\t",i+1,processsize[i]);
                if(allocation[i]!=-1)
                        printf("%d\n",allocation[i]+1);
                else
                        printf("not allocated\n");
        }
}
int main()
{
        int blocksize[]={100,200,300,400,500};
        int processsize[]={123,234,342,456,435};
        int m=sizeof(blocksize)/sizeof(blocksize[0]);
        int n=sizeof(processsize)/sizeof(processsize[0]);
        bestfit(blocksize,n,processsize,m);
        return 0;
}


```
#### Develop a C program to simulate memory allocation using the worst-fit algorithm.

```c
#include<stdio.h>
void bestfit(int blocksize[],int m,int processsize[],int n)
{
        int allocation[n];
        for(int i=0;i<n;i++)
        {
                allocation[i]=-1;
                for(int i=0;i<n;i++)
                {
                        int wortidx=-1;
                        for(int j=0;j<m;j++)
                        {
                                if(blocksize[j]>=processsize[i])
                                        if(worstidx==-1||blocksize[j]<blocksize[worstidx])
                                                worstidx=j;
                        }
                }
                if(worstidx !=-1)
                {
                        allocation[i]=worstidx;
                        blocksize[worstidx]-=processsize[i];
                }
        }
        printf("\npro.no \tpro size\tblock no.\n");
        for(int i=0;i<n;i++)
          {
                printf("%d\t\t%d\t\t",i+1,processsize[i]);
                if(allocation[i]!=-1)
                        printf("%d\n",allocation[i]+1);
                 else
                        printf("not allocated\n");
        }
}
           int main()
{
        int blocksize[]={100,200,300,400,500};
        int processsize[]={123,234,342,456,435};
        int m=sizeof(blocksize)/sizeof(blocksize[0]);
        int n=sizeof(processsize)/sizeof(processsize[0]);
        worstfit(blocksize,n,processsize,m);
        return 0;
}



```

### Implement a C program to simulate memory allocation using the next-fit algorithm.
```c
#include<stdio.h>
void(int blocksize[],int m,int processsize[],int n)
{
        int allocation[n];
        for(int i=0;i<n;i++)
                allocation[i]=-1;
        int j=0;
        for(int i=0;i<n;i++)
        {
                int count=0;
                while(count<m)
                {
                        if(blocksize[j]>=processsize[i])
                        {
                                allocation[i]=j;
                                blocksize[j]-=processize[j];
                                break;
                        }
                        j=(j+1)%m;
                        count++;
                }
        }
        printf("\npro.no \tpro size\tblock no.\n");
        for(int i=0;i<n;i++)
          {
                printf("%d\t\t%d\t\t",i+1,processsize[i]);
                if(allocation[i]!=-1)
                        printf("%d\n",allocation[i]+1);
                 else
                        printf("not allocated\n");
        }
}
           int main()
{
        int blocksize[]={100,200,300,400,500};
        int processsize[]={123,234,342,456,435};
        int m=sizeof(blocksize)/sizeof(blocksize[0]);
        int n=sizeof(processsize)/sizeof(processsize[0]);
        worstfit(blocksize,n,processsize,m);
        return 0;
}


```


### Develop a C program to implement a memory allocator using a custom memory management algorithm.
```c
#include<stdio.h>
#include<string.h>
#define SIZE 100
char memory[SIZE];
int used=0;
void* my_alloc(int size)
{
        if(used+size>SIZE)
                return NULL;
        void* ptr=&memory[used];
        used+=size;
        return ptr;
}
int main()
{
        char* p1=(char*)my_alloc(10);
        char* p2=(char*)my_alloc(20);
        char*  p3=(char*)my_alloc(80);
        if(p1)strcpy(p1,"hello");
        if(p2)strcpy(p2,"world");
        if(p1)printf("p1:%s\n",p1);
        if(p2)printf("p2:%s\n",p2);
        if(!p3)printf("p3:allocation failed \n");
        return 0;
}


```

#### Write a C program to demonstrate memory mapping using mmap().
```c
#include<stdio.h>
#include<sys/mman.h>
#include<fcntl.h>
#include<unistd.h>
int main()
{
       
       int fd=open("file.txt",O_RDONLY);
        const *data=mmap(NULL,100,PROT_READ,MAP_PRIVATE,fd,0);
        write(1,data,100);
        munmap(data,100);
        close(fd);
        return 0;
}

```


### Implement a C program to read from and write to a memory-mapped file.
```c

#include<unistd.h>
#include<sys/mman.h>
#include<fcntl.h>
int main()
{
        int fd=open("file.txt",O_RDWR);
        const *data=mmap(NULL,100,PROT_WRITE,MAP_SHARED,fd,0);
        data[0]='x';
        munmap(data,100);
        close(fd);
        return 0;
}

```


#### Develop a C program to demonstrate shared memory usage using shmget() and shmat().
```c
#include<stdio.h>                                                       
#include<sys/ipc.h>                                                    
#include<sys/shm.h>                                                    
int main()
{  
int id=shmget(1234,1024,IPC_CREAT|0666);                                
char *data=(char *)shmat(id,NULL,0);
sprintf(data,"hello world");
printf("%s\n",data); 
shmdt(data);
shmctl(id,IPC_RMID,NULL);                                               
return 0;                                                      
}                         

```


### Write a C program to create a shared memory segment and synchronize access using semaphores.

```c
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/ipc.h>
#include<sys/shm.h>
#include<semaphore.h>
#define SHM_KEY 1234
#define SIZE 256
typedef struct
{
        sem_t sem;
        char data[SIZE];
}shared;
int main()
{
        int shmid;
        shared *shm;
        shmid=shmget(SHM_KEY,sizeof(shared),IPC_CREAT|0666);
        if(shmid==-1)
        {
                perror("shmget");
                return 1;
        }
        shm=(shared *)shmat(shmid,NULL,0);
        if(shm==(void *)-1)
        {
                perror("shmat");
                return 1;
        }
        sem_init(&shm->sem,1,1);
        pid_t pid=fork();
        if(pid==0)
        {
                sleep(1);
                sem_wait(&shm->sem);
                printf("child read:%s\n",shm->data);
                sem_post(&shm->sem);
                shmdt(shm);
        }
        else
        {
                sem_wait(&shm->sem);
                strcpy(shm->data,"hello world");
                printf("parent wrote message.\n");
                sem_post(&shm->sem);
                wait(NULL);
                sem_destroy(&shm->sem);
                shmdt(shm);
                shmctl(shmid,IPC_RMID,NULL);
        }
        return 0;
}


```


