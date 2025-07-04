### Write a C program to create a thread that prints "Hello, World!"?
```c
#include<stdio.h>
#include<pthread.h>
void* print_hello(void *args)
{
        printf("hello,world!\n");
        return NULL;
}
int main()
{
        pthread_t tid;
        pthread_create(&tid,NULL,print_hello,NULL);
        pthread_join(tid,NULL);
        return 0;
}
```
###  Modify the above program to create multiple threads, each printing its own message?
```c
#include<stdio.h>
#include<pthread.h>
void* print_message(void* arg)
{
        char* msg=(char*)arg;
        printf("%s\n",msg);
        return NULL;
}
int main()
{
        pthread_t thread[3];
        char* message[]={"thread1:hello","thread2:world","thread3:welcome"};
        for(int i=0;i<3;i++)
        {
                pthread_create(&thread[i],NULL,print_message,message[i]);
        }
        for(int i=0;i<3;i++)
        {
                pthread_join(thread[i],NULL);
        }
        return 0;
}

```
### Develop a C program to create two threads that print numbers from 1 to 10 concurrently?
```c
#include<stdio.h>
#include<pthread.h>
#include<unistd.h>
void* print_numbers(void* arg)
{
        int id=*(int*)arg;
        for(int i=1;i<=10;i++)
        {
                printf("thread  %d: %d\n",id,i);
                usleep(100000);
        }
        return NULL;
}
int main()
{
        pthread_t t1,t2;
        int id1=1,id2=2;
        pthread_create(&t1,NULL,print_numbers,&id1);
        pthread_create(&t1,NULL,print_numbers,&id2);
        pthread_join(t1,NULL);
        pthread_join(t2,NULL);
        return 0;
}
```



#### Implement a C program to create a thread that calculates the factorial of a given number?
```c
#include<stdio.h>
#include<pthread.h>
typedef struct
{
        int num;
        long long result;
}factorialdata;
void* factorial_thread(void* arg)
{
        factorialdata* data=(factorialdata*)arg;
        data->result=1;
        for(int i=1;i<=data->num;i++)
        {
                data->result*=i;
        }
        return NULL;
}
int main()
{
        pthread_t tid;
        factorialdata data;
        printf("enter a number: ");
        scanf("%d",&data.num);
        pthread_create(&tid,NULL,factorial_thread,&data);
        pthread_join(tid,NULL);
        printf("factorial of %d is %lld\n",data.num,data.result);
        return 0;
}

```

### Write a C program to create two threads that print their thread IDs?
```c
#include<stdio.h>
#include<pthread.h>
void* print_thread_id(void* arg)
{
        pthread_t tid=pthread_self();
        printf("threads id:%lu\n",(unsigned long)tid);
        return NULL;
}
int main()
{
        pthread_t t1,t2;
        pthread_create(&t1,NULL,print_thread_id,NULL);
        pthread_create(&t2,NULL,print_thread_id,NULL);
        pthread_join(t1,NULL);
        pthread_join(t2,NULL);
        return 0;
}
```


### Develop a C program to create a thread that prints the sum of two numbers?
```c
#include<stdio.h>
#include<pthread.h>
typedef struct
{
        int a,b;
}numbers;
void* compute_sum(void* arg)
{
        numbers* nums=(numbers*)arg;
        int sum=nums->a+nums->b;
        printf("sum=%d\n",sum);
        return NULL;
}
int main()
{
        pthread_t tid;
        numbers nums={5,10};
        pthread_create(&tid,NULL,compute_sum,&nums);
        pthread_join(tid,NULL);
        return 0;
}

```


### Implement a C program to create a thread that calculates the square of a number?
```c
#include<stdio.h>
#include<pthread.h>
void* square(void* arg)
{
        int num=*(int*)arg;
        printf("square of %d id %d\n",num,num*num);
        return NULL;
}
int main()
{
        pthread_t tid;
        int num=7;
        pthread_create(&tid,NULL,square,&num);
        pthread_join(tid,NULL);
        return 0;
}

``

#### Write a C program to create a thread that prints the current date and time?
```c
#include<stdio.h>
#include<pthread.h>
#include<time.h>
void* print_datetime(void* arg)
{
        time_t now=time(NULL);
        char buffer[64];
        strftime(buffer,sizeof(buffer),"%y-%m-%m %h:%m:%s",localtime(&now));
        printf("current date and time :%s\n",buffer);
        return NULL;
}
int main()
{
        pthread_t tid;
        pthread_create(&tid,NULL,print_datetime,NULL);
        pthread_join(tid,NULL);
        return 0;
}


```

### Develop a C program to create a thread that checks if a number is prime?

```c
#include<stdio.h>
#include<pthread.h>
void* is_prime(void* arg)
{
        int num=*(int*)arg;
        if(num<=1)
        {
                printf("%d is not prime number.\n",num);
                return NULL;
        }
        for(int i=2;i*i<=num;i++)
        {
                if(num%i==0)
                {
                        printf("%d is not prime number",num);
                }
                printf("%d is a prime number",num);
                return NULL;
        }
}
int main()
{
        pthread_t tid;
        int num=23;
        pthread_create(&tid,NULL,is_prime,&num);
        pthread_join(tid,NULL);
        return 0;
}


```

### Implement a C program to create a thread that checks if a given string is a palindrome?
```c

#include<stdio.h>
#include<pthread.h>
#include<string.h>
#include<stdbool.h>
void* is_palidrone(void* arg)
{
        char* str=(char*)arg;
        bool palidrone=true;
        int len=strlen(str);
        for(int i=0;i<len/2;i++)
        {
                if(str[i]!=str[len-i-1])
                {
                        palidrone=false;
                        break;
                }
        }
        if(palidrone)
                printf("\"%s\" is a palidrone.\n",str);
        else
                printf("\"%s\" is not a palidrone.\n",str);
        return NULL;
}
int main()
{
        pthread_t tid;
        char str[]="tit";
        pthread_create(&tid,NULL,is_palidrone,str);
        pthread_join(tid,NULL);
        return 0;
}

```
### Write a C program to create a thread that prints "Hello, World!" with thread synchronization?
```c
#include<stdio.h>
#include<pthread.h>
pthread_mutex_t lock;
void* print_hello(void* arg)
{
        pthread_mutex_lock(&lock);
        printf("hello world!\n");
        pthread_mutex_unlock(&lock);
        return NULL;
}
int main()
{
        pthread_t tid;
        pthread_mutex_init(&lock,NULL);
        pthread_create(&tid,NULL,print_hello,NULL);
        pthread_join(tid,NULL);
        pthread_mutex_destroy(&lock);
        return 0;
}

```

### Develop a C program to create two threads that print their thread IDs and synchronize their output?

```c
#include<stdio.h>
#include<pthread.h>
pthread_mutex_t lock;
void* print_id(void* arg)
{
        pthread_mutex_lock(&lock);
        printf("thread id:%lu\n",(unsigned long)pthread_self());
        pthread_mutex_unlock(&lock);
        return NULL;
}
int main()
{
        pthread_t t1,t2;
        pthread_mutex_init(&lock,NULL);
        pthread_create(&t1,NULL,print_id,NULL);
        pthread_create(&t2,NULL,print_id,NULL);
        pthread_join(t1,NULL);
        pthread_join(t2,NULL);
        pthread_mutex_unlock(&lock);
        return 0;
}
```

#### Write a C program to create a thread that performs addition of two numbers with mutex locks?
```c
#include<stdio.h>
#include<pthread.h>
pthread_mutex_t lock;
typedef struct
{
        int a,b,sum;
}data;
void* add(void* arg)
{
        data* d=(data*)arg;
        pthread_mutex_lock(&lock);
        d->sum=d->a+d->b;
        pthread_mutex_unlock(&lock);
        return NULL;
}
int main()
{
        pthread_t t1;
        data data={5,10,0};
        pthread_mutex_init(&lock,NULL);
        pthread_create(&t1,NULL,add,&data);
        pthread_join(t1,NULL);
        printf("sum=%d\n",data.sum);
        pthread_mutex_destroy(&lock);
        return 0;
}
```

### Implement a C program to create two threads that increment and decrement a shared variable, respectively, using mutex locks?
```c
#include<stdio.h>
#include<pthread.h>
int value=0;
pthread_mutex_t lock;
void* increment(void* arg)
{
        for(int i=0;i<5;i++)
        {
                pthread_mutex_lock(&lock);
                value++;
                printf("increment:%d\n",value);
                pthread_mutex_unlock(&lock);
        }
        return NULL;
}
void* decrement(void* ard)
{
        for(int i=0;i<5;i++)
        {
                pthread_mutex_lock(&lock);
                value--;
                printf("decrement:%d\n",value);
                pthread_mutex_unlock(&lock);
        }
        return NULL;
}
int main()
{
        pthread_t t1,t2;
        pthread_mutex_init(&lock,NULL);
        pthread_create(&t1,NULL,increment,NULL);
        pthread_create(&t2,NULL,decrement,NULL);
        pthread_join(t1,NULL);
        pthread_join(t2,NULL);
        return 0;
}
```
###  Develop a C program to create a thread that reads input from the user and synchronizes access to shared resources?
```c

#include<stdio.h>
#include<pthread.h>
char shared_input[100];
pthread_mutex_t lock;
void* read_input(void* arg)
{
        pthread_mutex_lock(&lock);
        printf("enter a meaasge:");
        fgets(shared_input,sizeof(shared_input),stdin);
        printf("your entered :%s",shared_input);
        pthread_mutex_unlock(&lock);
        return NULL;
}
int main()
{
        pthread_t t1;
        pthread_mutex_init(&lock,NULL);
        pthread_create(&t1,NULL,read_input,NULL);
        pthread_join(t1,NULL);
        return 0;
}


```
### Implement a C program to create a thread that calculates the sum of Fibonacci numbers up to a given limit using dynamic programming with mutex locks?

```c
#include<stdio.h>
#include<pthread.h>
pthread_mutex_t lock;
typedef struct
{
        int terms;
        int sum;
}fibdata;
void* sum_fibannoci(void* arg)
{
        fibdata* data=(fibdata*)arg;
        int a=0,b=1,next;
        data->sum=a+b;
        pthread_mutex_lock(&lock);
        printf("fibannoci:%d %d ",a,b);
        for(int i=2;i<data->terms;i++)
        {
                next=a+b;
                printf("%d ",next);
                data->sum+=next;
                a=b;
                b=next;
        }
        printf("\nsum=%d\n",data->sum);
        pthread_mutex_unlock(&lock);
        return NULL;
}
int main()
{
        pthread_t t1;
        fibdata data={10,0};
        pthread_mutex_init(&lock,NULL);
        pthread_create(&t1,NULL,sum_fibannoci,&data);
        pthread_join(t1,NULL);
        pthread_mutex_destroy(&lock);
        return 0;
}

```


####  Write a C program to create a thread that checks if a given year is a leap year using dynamic programming with mutex locks?
```c
#include<stdio.h>
#include<pthread.h>
pthread_mutex_t lock;
void* check_leap(void* arg)
{
        int year=*(int*)arg;
        pthread_mutex_lock(&lock);
        if((year%4==0 && year%100==0 )||(year%400==0))
                printf("%d is leap year.\n",year);
        else
                printf("%d is not leap year.\n",year);
        return NULL;
}
int main()
{
        pthread_t t1;
        int year=2025;
        pthread_mutex_init(&lock,NULL);
        pthread_create(&t1,NULL,check_leap,&year);
        pthread_join(t1,NULL);
        return 0;
}

```


### Develop a C program to create a thread that calculates the area of a triangle?

```c
#include<stdio.h>
#include<pthread.h>
pthread_mutex_t lock;
typedef struct
{
        float base;
        float height;
}triangle;
void* area_triangle(void* arg)
{
        triangle* t=(triangle*)arg;
        pthread_mutex_lock(&lock);
        float area=0.5*t->base*t->height;
        printf("area of triangle:%.2f\n",area);
        pthread_mutex_unlock(&lock);
        return NULL;
}
int main()
{
        pthread_t t1;
        triangle t={5.0,10.0};
        pthread_mutex_init(&lock,NULL);
        pthread_create(&t1,NULL,area_triangle,&t);
        pthread_join(t1,NULL);
        pthread_mutex_destroy(&lock);
        return 0;
}

```


### Write a C program to create a thread that calculates the sum of squares of numbers from 1 to 100?
```c
#include<stdio.h>
#include<pthread.h>
pthread_mutex_t lock;
void* sum_of_squares(void* arg)
{
        int sum=0;
        pthread_mutex_lock(&lock);
        for(int i=0;i<=100;i++)
        {
                sum+=i*i;
        }
        printf("sum of squares 1 to 100:%d\n",sum);
        return NULL;
}
int main()
{
        pthread_t t1;
        pthread_mutex_init(&lock,NULL);
        pthread_create(&t1,NULL,sum_of_squares,NULL);
        pthread_join(t1,NULL);
        pthread_mutex_unlock(&lock);
        return 0;
}
```
### Write a C program to create a thread that generates a random array of integers?
```c
#include<stdio.h>
#include<pthread.h>
#include<time.h>
#include<stdlib.h>
pthread_mutex_t lock;
int arr[10];
void* generate_array(void* arg)
{
        pthread_mutex_lock(&lock);
        srand(time(NULL));
        printf("random array: ");
        for(int i=0;i<10;i++)
        {
                arr[i]=rand()%100;
                printf("%d ",arr[i]);
        }
        printf("\n");
        pthread_mutex_unlock(&lock);
}
int main()
{
        pthread_t t1;
        pthread_mutex_init(&lock,NULL);
        pthread_create(&t1,NULL,generate_array,NULL);
        pthread_join(t1,NULL);
        pthread_mutex_destroy(&lock);
        return 0;
}
```

### Develop a C program to create a thread that calculates the greatest common divisor (GCD) of two numbers?
```c
#include<stdio.h>
#include<pthread.h>
typedef struct
{
        int a,b;
}gcdinput;
void* calculate_gcdinput(void* arg)
{
        gcdinput* input=(gcdinput*)arg;
        int a=input->a;
        int b=input->b;
        while(b!=0)
        {
                int temp=b;
                b=a%b;
                a=temp;
        }
        printf("gcdinput:%d\n",a);
        return NULL;
}
int main()
{
        pthread_t t1;
        gcdinput  input={23,45};
        pthread_create(&t1,NULL,calculate_gcdinput,&input);
        pthread_join(t1,NULL);
        return 0;
}
```
####  Write a C program to create a thread that calculates the sum of Fibonacci numbers up to a given limit?
```c
#include<stdio.h>
#include<pthread.h>
int limits=10;
void* fibannoci_sum(void* arg)
{
        int a=0,b=1,sum=a+b;
        printf("fibannoci :%d %d",a,b);
        for(int i=2;i<limits;i++)
        {
                int next=a+b;
                printf("%d ",next);
                sum+=next;
                a=b;
                b=next;
        }
        printf("\nsum=%d\n",sum);
        return NULL;
}
int main()
{
        pthread_t t1;
        pthread_create(&t1,NULL,fibannoci_sum,NULL);
        pthread_join(t1,NULL);
        return 0;
}
```
####  Implement a C program to create a thread that calculates the sum of even numbers from 1 to 100
```c
#include<stdio.h>
#include<pthread.h>
void* even_sum(void* arg)
{
        int sum=0;
        for(int i=2;i<=100;i+=2)
        {
                sum+=i;
        }
        printf("sum of even numbers from 1 to 100:%d\n",sum);
        return NULL;
}
int main()
{
        pthread_t t1;
        pthread_create(&t1,NULL,even_sum,NULL);
        pthread_join(t1,NULL);
        return 0;
}
```
##### Develop a C program to create a thread that calculates the factorial of a given number using iteration?
```c
#include<stdio.h>
#include<pthread.h>
int number=5;
void* factorial(void* arg)
{
        long long fact=1;
        for(int i=2;i<=number;i++)
        {
                fact*=i;
        }
        printf("factorial of %d is %lld\n",fact,number);
        return NULL;
}
int main()
{
        pthread_t t1;
        pthread_create(&t1,NULL,factorial,NULL);
        pthread_join(t1,NULL);
        return 0;
}
```
### Write a C program to create a thread that checks if a given year is a leap year?
```c
#include<stdio.h>
#include<pthread.h>
int year=2025;
void* leap_year(void* arg)
{
        if((year%4==0 && year%100==0)||(year%400==0))
                printf("%d is a leap year.\n",year);
        else
                printf("%d is not a leap year.\n",year);
        return NULL;
}
int main()
{
        pthread_t t1;
        pthread_create(&t1,NULL,leap_year,NULL);
        pthread_join(t1,NULL);
        return 0;
}
```
### Implement a C program to create a thread that performs multiplication of two matrices?
```c
#include<stdio.h>
#include<pthread.h>
int a[2][2]={{1,2},{3,4}};
int b[2][2]={{5,6},{7,8}};
int c[2][2];
void* multiply_matrix(void* arg)
{
        for(int i=0;i<2;i++)
                for(int j=0;j<2;j++)
                {
                        c[i][j]=0;
                        for(int k=0;k<2;k++)
                                c[i][j]+=a[i][k]*b[j][k];
                }
        printf("result\n");
        for(int i=0;i<2;i++,printf("\n"))
                for(int j=0;j<2;j++)
                        printf("%d ",c[i][j]);
        return NULL;
}
int main()
{
        pthread_t t1;
        pthread_create(&t1,NULL,multiply_matrix,NULL);
        pthread_join(t1,NULL);
        return 0;
}
```
### Develop a C program to create a thread that calculates the average of numbers from 1 to 100?
```c
#include<stdio.h>
#include<pthread.h>
void* avg_1_to_100(void* arg)
{
        int sum=0;
        for(int i=1;i<=100;i++)
                sum+=i;
        printf("average :%.2f\n",sum/100.0);
        return NULL;
}
int main()
{
        pthread_t t1;
        pthread_create(&t1,NULL,avg_1_to_100,NULL);
        pthread_join(t1,NULL);
        return 0;
}

```
##### Implement a C program to create a thread that generates a random string?
```c
#include<stdio.h>
#include<pthread.h>
#include<stdlib.h>
#include<time.h>
void* random_string(void* arg)
{
        char str[11];
        srand(time(NULL));
        for(int i=0;i<10;i++)
                str[i]='A'+rand()%26;
        str[10]='\0';
        printf("random string :%s\n",str);
        return NULL;
}
int main()
{
        pthread_t t1;
        pthread_create(&t1,NULL,random_string,NULL);
        pthread_join(t1,NULL);
        return 0;
}
```
##### Write a C program to create a thread that checks if a given number is a perfect square?
```c
#include<stdio.h>
#include<pthread.h>
int number=49;
void* square(void* arg)
{
        for(int i=0;i*i<=number;i++)
        {
                if(i*i==number)
                {
                        printf("%d is a perfect number.\n",number);
                        return NULL;
                }
        }
        printf("%d is not a perfect number.\n",number);
        return NULL;
}
int main()
{
        pthread_t t1;
        pthread_create(&t1,NULL,square,NULL);
        pthread_join(t1,NULL);
        return 0;
}
```

#### Write a C program to create a thread that calculates the sum of digits of a given number?
```c
#include<stdio.h>
#include<pthread.h>
int num=12345;
void* sum_digits(void* arg)
{
        int n=num,sum=0;
        while(n)
        {
                sum+=n%10;
                n/=10;
        }
        printf("sum of the digits %d:%d\n",sum,num);
        return NULL;
}
int main()
{
        pthread_t t1;
        pthread_create(&t1,NULL,sum_digits,NULL);
        pthread_join(t1,NULL);
        return 0;
}

```
#### Implement a C program to create a thread that calculates the factorial of a given number using recursion?
```c
#include<stdio.h>
#include<pthread.h>
int num=5;
long long fact(int n)
{
        return (n>1)?1:n*fact(n-1);
}
void* fact_thread(void* arg)
{
        printf("fact of %d is %lld\n",fact(num),num);
        return NULL;
}
int main()
{
        pthread_t t1;
        pthread_create(&t1,NULL,fact_thread,NULL);
        pthread_join(t1,NULL);
        return 0;
}
```

### Develop a C program to create a thread that finds the maximum element in an array?
```c
#include<stdio.h>
#include<pthread.h>
int arr[]={1,2,3,4,5};
int n=5;
void* find_max(void* arg)
{
        int max=arr[0];
        for(int i=1;i<n;i++)
                if(arr[i]>max)
                        max=arr[i];
        printf("max element: %d\n",max);
        return NULL;
}
int main()
{
        pthread_t t1;
        pthread_create(&t1,NULL,find_max,NULL);
        pthread_join(t1,NULL);
        return 0;
}
```

######  .Implement a C program to create a thread that calculates the square root of a number?
```c
#include<stdio.h>
#include<pthread.h>
#include<math.h>
int num=64;
void* square_root(void* arg)
{
        printf("square root of %d :%.2f\n",num,sqrt(num));
        return NULL;
}
int main()
{
        pthread_t t1;
        pthread_create(&t1,NULL,square_root,NULL);
        pthread_join(t1,NULL);
        return 0;
}
```
#### Develop a C program to create a thread that calculates the average of numbers in an array?
```c
#include<stdio.h>
#include<pthread.h>
int arr[]={1,2,3,4,5};
int n=5;
void* avg_array(void* arg)
{
        int sum=0;
        for(int i=0;i<n;i++)
                sum+=arr[i];
        printf("average:%.2f\n",sum/(float)n);
        return NULL;
}
int main()
{
        pthread_t t1;
        pthread_create(&t1,NULL,avg_array,NULL);
        pthread_join(t1,NULL);
        return 0;
}
```
#### Implement a C program to create a thread that checks if a number is even or odd?
```c
#include<stdio.h>
#include<pthread.h>
int number=7;
void* even_odd(void* arg)
{
        if(number%2==0)
                printf("%d is even\n",number);
        else
                printf("%d is odd\n",number);
        return NULL;
}
int main()
{
        pthread_t t1;
        pthread_create(&t1,NULL,even_odd,NULL);
        pthread_join(t1,NULL);
        return 0;
}
```
### Write a C program to create a thread that calculates the factorial of numbers from 1 to 10?
```c
#include<stdio.h>
#include<pthread.h>
long long fact(int n)
{
        long long result=1;
        for(int i=2;i<=n;i++)
                result*=i;
                return result;
}
void* fact_1_to_10(void* arg)
{
        for(int i=1;i<10;i++)
        {
                printf("factorial:%d=%lld\n",fact[i]);
        }
        return NULL;
}
int main()
{
        pthread_t t1;
        pthread_create(&t1,NULL,fact_1_to_10,NULL);
        pthread_join(t1,NULL);
        return 0;
}
```

### Implement a C program to create a thread that calculates the area of a rectangle?
```c
#include<stdio.h>
#include<pthread.h>
typedef struct
{
        int length;
        int width;
}rectangle;
void* cal_area(void* arg)
{
        rectangle* rect=(rectangle*)arg;
        int area=rect->length*rect->width;
        printf("area of rectangle:%d\n",area);
        return NULL;
}
int main()
{
        pthread_t t1;
        pthread_create(&t1,NULL,cal_area,NULL);
        pthread_join(t1,NULL);
        return 0;
}
```
###.Write a C program to create a thread that performs addition of two matrices?
```c
#include<stdio.h>
#include<pthread.h>
int a[2][2]={{1,2},{3,4}};
int b[2][2]={{5,6},{7,8}};
int c[2][2];
void* add_matrix(void* arg)
{
        for(int i=0;i<2;i++)
                for(int j=0;j<2;j++)
                        c[i][j]=a[i][j]+b[i][j];
                }
        printf("result\n");
        for(int i=0;i<2;i++,printf("\n"))
                for(int j=0;j<2;j++)
                        printf("%d ",c[i][j]);
        return NULL;
}
int main()
{
        pthread_t t1;
        pthread_create(&t1,NULL,add__matrix,NULL);
        pthread_join(t1,NULL);
        return 0;
}
```
###.Write a C program to create a thread that prints the even numbers between 1 and 20?
```c
#include<stdio.h>
#include<pthread.h>
void*  print_even(void *arg)
{
        for(int i=2;i<=20;i+=2)
                printf("even:%d\n",i);
        return NULL;
}
int main()
{
        pthread_t t1;
        pthread_create(&t1,NULL,print_even,NULL);
        pthread_join(t1,NULL);
        return 0;
}
```
###.Implement a C program to create a thread that calculates the sum of squares of numbers from 1 to 10?
```c
#include<stdio.h>
#include<pthread.h>
void* sum_of_squares(void *arg)
{
        int sum=0;
        for(int i=1;i<=10;i++)
                sum+=i*i;
                printf("ssum of squares:%d\n",sum);
        return NULL;
}
int main()
{
        pthread_t t1;
        pthread_create(&t1,NULL,sum_of_squares,NULL);
        pthread_join(t1,NULL);
        return 0;
}
```
##.Write a C program to create a thread that calculates the product of numbers from 1 to 5?
```c
#include<stdio.h>
#include<pthread.h>
void* product_of_numbers(void *arg)
{
        int product=1;
        for(int i=1;i<=5;i++)
                product*=i;
                printf("product from 1 to 5:%d\n",product);
        return NULL;
}
int main()
{
        pthread_t t1;
        pthread_create(&t1,NULL,product_of_numbers,NULL);
        pthread_join(t1,NULL);
        return 0;
}
```
###.Develop a C program to create a thread that prints the first 10 terms of the Fibonacci sequence?

```c
#include<stdio.h>
#include<pthread.h>
void* fib(void* arg)
{
        int a=0,b=1;
        printf("fib:%d %d",a,b);
        for(int i=2;i<10;i++)
        {
                int c=a+b;
                printf("%d ",c);
                a=b;
                b=c;
        }
        printf("\n");
        return NULL;
}
int main()
{
        pthread_t t1;
        pthread_create(&t1,NULL,fib,NULL);
        pthread_join(t1,NULL);
        return 0;
}

```
###.Implement a C program to create a thread that prints the ASCII values of characters in a given string?
```c
#include<stdio.h>
#include<pthread.h>
char str[]="hello";
void* print_ascii(void* arg)
{
        for(int i=0;str[i]!='\0';i++)
        {
                printf("character:%c,ascii:%d\n",str[i],str[i]);
        }
        return NULL;
}
int main()
{
        pthread_t t1;
        pthread_create(&t1,NULL,print_ascii,NULL);
        pthread_join(t1,NULL);
        return 0;
}
```
##.Write a C program to create a thread that calculates the area of a circle using a given radius
```c
#include<stdio.h>
#include<pthread.h>
#include<math.h>
float radius=5.0;
void* area_circle(void* arg)
{
        float area=M_PT*radius*radius;
        printf("area of circle with radius %.2f:%.2f\n",radius,area);        return NULL;
}
int main()
{
        pthread_t t1;
        pthread_create(&t1,NULL,area_circle,NULL);
        pthread_join(t1,NULL);
        return 0;
}

```
##.Develop a C program to create a thread that calculates the average of a given array of floating-point numbers?
```c
#include<stdio.h>
#include<pthread.h>
int arr[]={1.0,2.0,3.0,4.0,5.0};
int n=5;
void* avg_array(void* arg)
{
        int sum=0;
        for(int i=0;i<n;i++)
                sum+=arr[i];
        printf("average:%.2f\n",sum/n);
        return NULL;
}
int main()
{
        pthread_t t1;
        pthread_create(&t1,NULL,avg_array,NULL);
        pthread_join(t1,NULL);
        return 0;
}
```
###.Implement a C program to create a thread that prints the factors of a given number?
```c
#include<stdio.h>
#include<pthread.h>
int num=28;
void* print_factors(void* arg)
{
        printf("factors of %d: ",num);
        for(int i=1;i<=num;i++)
                if(num%i==0)
                        printf("%d ",i);
        printf("\n");
        return NULL;
}
int main()
{
        pthread_t t1;
        pthread_create(&t1,NULL,print_factors,NULL);
        pthread_join(t1,NULL);
        return 0;
}
```
###.Develop a C program to create a thread that prints the English alphabet in uppercase?
```c
#include<stdio.h>
#include<pthread.h>
void* print_uppercase(void* arg)
{
        for(char c='A';c<='Z';c++)
                printf("%c ",c);
        printf("\n");
        return NULL;
}
int main()
{
        pthread_t t1;
        pthread_create(&t1,NULL,print_uppercase,NULL);
        pthread_join(t1,NULL);
        return 0;
}
```

### .Implement a C program to create a thread that checks if a given number is divisible by another given number?

```c
#include<stdio.h>
#include<pthread.h>
typedef struct
{
        int a,b;
}divargs;
void* check_divisible(void* arg)
{
        divargs* d=(divargs*)arg;
        if(d->b==0)
        {
                printf("divisible by zero is not allowed.\n");
        }
        else if(d->a%d->b==0)
        {
                printf("%d is divisible by %d\n",d->a,d->b);
        }
        else
        {
                printf("%d is divisible by %d\n",d->a,d->b);
        }
        return NULL;
}
int main()
{
        pthread_t t1;
        pthread_create(&t1,NULL,check_divisible,NULL);
        pthread_join(t1,NULL);
        return 0;
}

```
###.Develop a C program to create a thread that prints the multiplication table of a given number up to a given limit?
```c
#include<stdio.h>
#include<pthread.h>
typedef struct
{
        int num;
        int limit;
}tableargs;
void* print_table(void* arg)
{
        tableargs* t=(tableargs*)arg;
        for(int i=1;i<=t->limit;i++)
        {
                printf("%d x %d=%d\n",t->num,i,t->num*i);
        }
        return NULL;
}
int main()
{
        pthread_t t1;
        pthread_create(&t1,NULL,print_table,NULL);
        pthread_join(t1,NULL);
        return 0;
}
```
### .Develop a C program to create a thread that prints the current system time?
```c

#include<stdio.h>
#include<pthread.h>
#include<time.h>
void* print_time(void* arg)
{
        time_t now=time(NULL);
        printf("current time:%s",ctime(&now));
        return NULL;
}
int main()
{
        pthread_t t1;
        pthread_create(&t1,NULL,print_time,NULL);
        pthread_join(t1,NULL);
        return 0;
}
```
### .Develop a C program to create a thread that prints numbers from 10 to 1 in descending order using mutex locks
```c

#include<stdio.h>
#include<pthread.h>
pthread_mutex_t lock=PTHREAD_MUTEX_INITIALIZER;
void* print_decending(void* args)
{
        pthread_mutex_lock(&lock);
        for(int i=10;i>=1;i--)
        {
                printf("%d ",i);
        }
        printf("\n");
        pthread_mutex_unlock(&lock);
        return NULL;
}
int main()
{
        pthread_t t1;
        pthread_create(&t1,NULL,print_decending,NULL);
        pthread_join(t1,NULL);
        return 0;
}
```


