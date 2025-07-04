###  Write a C program to create a new text file and write "Hello, World!" to it?
```c
#include<stdio.h>
int main()
{
        FILE *fp=fopen("hello.txt","w");
        if(fp==NULL)
        {
                perror("error");
                return 1;
        }
        fprintf(fp,"hello, world!\n");
        fclose(fp);
        printf("file 'hello.txt' creating with message.\n");
        return 0;
}
```

#### Develop a C program to open an existing text file and display its contents?
```c
#include<stdio.h>
int main()
{
        FILE *fp=fopen("hello.txt","r");
        char ch;
        if(fp==NULL)
        {
                perror("file opening error");
                return 1;
        }
        printf("file contents:\n");
        while((ch=fgetc(fp))!=EOF)
        {
                putchar(ch);
        }
        fclose(fp);
        return 0;
}
```

### Implement a C program to create a new directory named "Test" in the current 
directory?
```c
#include<stdio.h>
#include<sys/stat.h>
#include<sys/types.h>
int main()
{
        int status=mkdir("test",0777);
        if(status==0)
                printf("'text' successfully created .\n");
        else
                printf("error creating ");
        return 0;
}
```
####Write a C program to check if a file named "sample.txt" exists in the current directory?
```c
#include<stdio.h>
int main()
{
        FILE *file=fopen("sample.txt","r");
        if(file)
        {
                printf("file 'sample.txt' exist.\n");
                fclose(file);
        }
        else
        {

                printf("file 'sample.txt' does not exists.\n");
        }
        return 0;
}
```
### Develop a C program to rename a file from "oldname.txt" to "newname.txt"?
```c
#include<stdio.h>
int main()
{
        if(rename("oldname.txt","newname.txt")==0)
                printf("file rename success\n");
        else
                perror("failed rename");
        return 0;
}
```
### Implement a C program to delete a file named "delete_me.txt"?
```c
#include<stdio.h>
int main()
{
        if(remove("delete_me.txt")==0)
                printf("file remove success.\n");
        else
                perror("file remove failed");
        return 0;
}
```
## Write a C program to copy the contents of one file to another?
```c
#include<stdio.h>
int main()
{
       FILE *src=fopen("source.txt","r");
       FILE *des=fopen("copy.txt","w");
        char ch;
        if(!src||!des)
                perror("file error");
        return 1;
        while((ch=fgetc(src))!=EOF)
                fputc(ch,des);
        printf("file copied success.\n");
        fclose(src);
        fclose(des);
        return 0;
}
```
## Develop a C program to move a file from one directory to another?
```c
#include<stdio.h>
int main()
{
        if(rename("filename.txt","newname.txt")==0)
                printf("rename file success.\n");
        else
                printf("rename file failed");
        return 0;
}

```
## Implement a C program to list all files in the current directory?
ans:   we use dirent headerfile
```c
#include<stdio.h>
#include<dirent.h>
int main()
{
        DIR *dir=opendir(".");
        struct dirent *entry;
        if(!dir)
        {
                perror("cannot open directory");
                return 1;
        }
        printf("file in current directory:\n");
        while((entry=readdir(dir))!=NULL)
        {
                printf("%s\n",entry->d_name);
        }
        closedir(dir);
        return 0;
}

```
## Write a C program to get the size of a file named "file.txt"?
```c

#include<stdio.h>
int main()
{
        FILE *fp=fopen("file.txt","r");
        if(!fp)
        {
                perror("error open file");
                return 1;
        }
        fseek(fp,0L,SEEK_END);
        long size=ftell(fp);
        fclose(fp);
        printf("size of 'file.txt'=%ldbytes\n",size);
        return 0;
}
```
## Develop a C program to check if a directory named "Test" exists in the current 
directory?
```c
#include<stdio.h>
#include<sys/stat.h>
int main()
{
        struct stat st;
        if(stat("test",&st)==0 && S_ISDIR(st.st_mode))
                printf("directory 'test' exist.\n");
        else
                printf("directory 'test' does not exist");
        return 0;
}

```
## Implement a C program to create a new directory named "Backup" in the parent 
directory?
```c
#include<stdio.h>
#include<sys/stat.h>
#include<sys/types.h>
int main()
{
        if(mkdir("../bachup",0777)==0)
                printf("bakup successfull.\n");
        else
                printf("backup failed");
        return 0;
}
```
## Implement a C program to count the number of lines in a file named "data.txt"?
```c
#include<stdio.h>
int main()
{
        FILE *fp=fopen("data.txt","r");
        char ch;
        int lines=0;
        if(!fp)
        {
                perror("open failed");
                return 1;
        }
        while((ch=fgetc(fp))!=EOF)
        {
                if(ch=='\n') lines++;
        }
        fclose(fp);
        printf("number of lines:%d\n",lines);
        return 0;
}
```
## Write a C program to append "Goodbye!" to the end of an existing file named 
"message.txt"?
```c

#include<stdio.h>
int main()
{
        FILE *fp=fopen("message.txt","a");
        if(!fp)
        {
                perror("open failed");
                return 1;
        }
        fprintf(fp,"good bye!\n");
        fclose(fp);
        printf("message append.\n");
        return 0;
}

```
## Implement a C program to change the permissions of a file named "file.txt" to read only
```c

#include<stdio.h>
#include<sys/stat.h>
int main()
{
        if(chmod("file.txt",0444)==0)
                printf("change permission readonly.\n");
        else
                printf("not change");
        return 0;
}
```
### Develop a C program to get the last modified timestamp of a file named "file.txt"?
```c
#include<stdio.h>
#include<sys/stat.h>
#include<time.h>
int main()
{
        struct stat st;
        if(stat("file.txt",&st)==0)
                printf("last modified:%s",ctime(&st.st_mtime));
        else
                perror("not modified");
        return 0;
}
```
## Write a C program to check if a given path refers to a file or a directory?
```c
#include<stdio.h>
#include<sys/stat.h>
int main()
{
        struct stat st;
        const char *path="example";
        if(stat(path,&st)==-1)
        {
                perror("failed");
                return 1;
        }
        if(S_ISREG(st.st_mode))
                printf("%s is a file.\n",path);
        else if(S_ISDIR(st.st_mode))
                printf("%s is a directory.\n",path);
        else
                printf("%s is neither a regular file nor a directory.\n",path);
        return 0;
}
```
### Develop a C program to create a hard link named "hardlink.txt" to a file named 
"source.txt"?
```c
#include<stdio.h>
#include<unistd.h>
int main()
{
        if(link("source.txt","hardlink.txt")==0)
                printf("hardlink successful.\n");
        else
                printf("not succesful");
        return 0;
}


```
## Implement a C program to read and display the contents of a CSV file named 
"data.csv"?
```c

#include<stdio.h>
int main()
{
        FILE *fp=fopen("data.csv","r");
        char line[1024];
        if(!fp)
        {
                perror("failed to open");
                return 1;
        }
        printf("csv file contents.\n");
        while(fgets(line,sizeof(line),fp))
        {
                printf("%s",line);
        }
        fclose(fp);
        return 0;
}
```
### Write a C program to get the absolute path of the current working directory?
```c
#include<stdio.h>
#include<limits.h>
#include<unistd.h>
int main()
{
        char cwd[PATH_MAX];
        if(getcwd(cwd,sizeof(cwd))!=NULL)
                printf("current working directory:%s\n",cwd);
        else
                printf("getcwd() error");
        return 0;
}
```
## Write a C program to get the number of files in a directory named "Images"?

```c
#include<stdio.h>
#include<dirent.h>
#include<string.h>
int main()
{
        struct dirent *entry;
        DIR *dir=opendir("images");
        int count=0;
        if(!dir)
        {
                perror("cannot open directory");
                return 1;
        }
        while(entry=readdir(dir))
        {
                if(entry->d_type==DT_REG)
                        count++;
        }
        closedir(dir);
        printf("number of files in 'images':%d\n",count);
        return 0
}


```
## Develop a C program to create a FIFO (named pipe) named "myfifo" in the current 
directory?
```c
#include<stdio.h>
#include<sys/stat.h>
int main()
{
        if(mkfifo("myfifo",0666)==0)
                printf("file created successful.\n");
        else
                printf("file not created");
        return 0;
}

```
## Write a C program to truncate a file named "file.txt" to a specified length?
```c
#include<stdio.h>
#include<unistd.h>
int main()
{
        if(truncate("file.txt",10)==0)
                printf("truncate successful to 10 bytes.\n");
        else
                perror("truncate failed");
        return 0;
}



```
# Write a C program to change the ownership of a file named "file.txt" to the user "user1"?
```c
#include<stdio.h>
#include<unistd.h>
#include<pwd.h>
#include<sys/types.h>
int main()
{
        struct passwd *pwd=getpwnam("user1");
        if(!pwd)
        {
                printf("user not found");
                return 1;
        }
        if(chown("file.txt",pwd->pw_uid,pwd->pw_gid)==0)
                printf("ownership successful.\n");
        else
                printf("not successful");
        return 0;
}
```
### Implement a C program to create a temporary file and write some data to it?
```c

#include<stdio.h>
int main()
{
        char filename[]="/tmp/tempfilexxxxxx";
        int fd=mkstemp(filename);
        if(fd==-1)
        {
                perror("mkstemp");
                return 1;
        }
        FILE *fp=fdopen(fd,"w");
        fprintf(fp,"temp file data.\n");
        fclose(fp);
        printf("temp file data:%s\n",filename);
        return 0;
}
```

## Implement a C program to read data from a FIFO named "myfifo"?
```c
#include<stdio.h>
#include<fcntl.h>
#include<unistd.h>
int main()
{
        char buf[100];
        int fd=open("myfifo",O_RDONLY);
        if(fd==-1)
        {
                perror("open");
                return 1;
        }
        read(fd,buf,sizeof(buf));
        printf("received:%s\n",buf);
        close(fd);
        return 0;
}

```
## Develop a C program to search for a specific string in a file named "data.txt" and display the line number(s) where it occurs?
```c

#include<stdio.h>
#include<string.h>
int main()
{
        FILE *fp=fopen("data.txt","r");
        char line[100],keyword[]="search
        int linenum=1;
        if(!fp)
        {
                perror("data.txt");
                return 1;
        }
        while(fgets(line,sizeof(line),fp))
        {
                if(strstr(line,keyword))
                        printf("found on line %d :%s",linenum,line);
                linenum++;
        }
        fclose(fp);
        return 0;
}
```
### Develop a C program to get the permissions (mode) of a file named "file.txt"?
```c
#include<stdio.h>
#include<sys/stat.h>
int main()
{
        struct stat st;
        if(stat("file.txt",&st)==-1)
        {
                perror("stat");
                return 1;
        }
        printf("permission:%o (octal)\n",st.st_mode & 0777);
        return 0;
}
```
## Write a C program to create a new empty file named "empty.txt"?
```c
#include<stdio.h>
#include<string.h>
int main()
{
        FILE *fp=fopen("empty.txt","w");
        if(fp==NULL)
        {
                perror("fopen");
                return 1;
        }
        fclose(fp);
        printf("file 'empty.txt' created.\n");
        return 0;
}

```
## Write a C program to read and display the first 10 lines of a file named "log.txt"?
```c
#include<stdio.h>
int main()
{
        FILE *fp=fopen("log.txt","r");
        char line[256];
        int count=0;
        if(!fp)
        {
                printf("fopen");
                return 1;
        }
        while(fgets(line,sizeof(line),fp)&&count==0)
        {
                printf("%s",line);
                count++;
        }
        fclose(fp);
        return 0;
}
```



## Develop a C program to read data from a text file named "input.txt" and write it to another file named "output.txt" in reverse order?
```c
#include<stdio.h>
#include<stdlib.h>
int main()
{
        FILE *in=fopen("input.txt","r");
        FILE *out=fopen("output.txt","w");
        if(!in||!out)
        {
                printf("file open");
                return 1;
        }
        fseek(in,0,SEEK_END);
        long size=ftell(in);
        for(long i=size-1;i>=0;i--)
        {
                fseek(in,1,SEEK_SET);
                char ch=fgetc(in);
                fputc(ch,out);
        }
        fclose(in);
        fclose(out);
        printf("reversed content written to output.txt\n");
        return 0;
}

```
## Implement a C program to create a new directory named with the current date in the format "YYYY-MM-DD"?
```c
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<sys/stat.h>
int main()
{
        char dirname[32];
        time_t t=time(NULL);
        struct tm *tm_info=localtime(&t);
        strftime(dirname,sizeof(dirname),"%y-%m-%d",tm_info);
        if(mkdir(dirname,0755)==0)
                printf("directory '%s' created.\n",dirname);
        else
                printf("mkdir");
        return 0;
}

```

### Implement a C program to check if a file named "data.txt" is readable?
```c
#include<stdio.h>
#include<unistd.h>
int main()
{
        if(access("data.txt",R_OK)==0)
                printf("file 'data.txt' is readable.\n");
        else
                printf("file 'data.txt' is not readable.\n");
        return 0;
}

```
#### Develop a C program to check if a file named "config.ini" is writable
```c

#include<stdio.h>
#include<unistd.h>
int main()
{
        if(access("config.ini",W_OK)==0)
                printf("file 'config_ini' is writable.\n");
        else
                printf("file 'config.ini' is not writable.\n");
        return 0;
}
```
## Write a C program to get the number of hard links to a file named "file.txt"?
```c
#include<stdio.h>
#include<sys/stat.h>
int main()
{
        struct stat st;
        if(stat("file.txt",&st)==-1)
        {
                perror("stat");
                return 1;
        }
        printf("no.of hard links to 'file.txt':%lu\n",st.st_nlink);
        return 0;
}
```

### Implement a C program to read the contents of a text file named"instructions.txt" and execute the instructions as shell commands?
```c

#include<stdio.h>
#include<stdlib.h>
int main()
{
        FILE *fp=fopen("instruction.txt","r");
        char command[256];
        if(!fp)
        {
                printf("fopen");
                return 1;
        }
        while(fgets(command,sizeof(command),fp))
        {
                command[strcspn(command,"\n")]=='\0';
                if(system(command)==-1)
                {
                        printf("failed to execute:%s\n",command);
                }
        }
        return 0;
}

```
### Write a C program to get the number of bytes in a file named "data.bin"?

```c
#include<stdio.h>
int main()
{
        FILE *fp=fopen("data.txt","rb");
        if(!fp)
        {
                printf("fopen");
                return 1;
        }
        fseek(fp,0L,SEEK_END);
        long size=ftell(fp);
        fclose(fp);
        printf("no.of bytes:%ld bytes \n",size);
        return 0;
}


```
### Develop a C program to create a new directory named with the current timestamp in the format "YYYY-MM-DD-HH-MM-SS"?
```c
#include<stdio.h>                                                    #include<sys/stat.h>
#include<time.h>
#include<stdlib.h>
int main()
{
        char dirname[64];
        time _t now=time(NULL);
        struct tm *tm_info=longtime(&now);
        strftime(dirname,sizeof(dirname),"%y-%m-%d-%h-%m-%s",tm_info);
        if(mkdir("dirname",0755)==0)
                printf("directory '%s' created.\n",dirname);
        else
                printf("mkdir");
        return 0;
}

```

### Write a C program to create a new directory named "Documents" in the current directory?
```c

#include<stdio.h>
#include<sys/stat.h>
int main()
{
        if(mkdir("documenst",0755)==0)
                printf("directoey 'documnets' creates.\n");
        else
                printf("mkdir");
        return 0;
}



```
## Develop a C program to check if a file named "file.txt" exists in the current directory?
```c

#include<stdio.h>
int main()
{
        FILE *fp=fopen("file.txt","r");
        if(fp)
        {
                printf("file 'file.txt' exist.\n");
                fclose(fp);
        }
        else
        {
                printf("file 'file.txt' does not exists.\n");
        }
        return 0;
}



```
## Implement a C program to open a file named "data.txt" in read mode and display its contents
```c

#include<stdio.h>
int main()
{
        FILE *fp=fopen("data.txt","r");
        char ch;
        if(!fp)
        {
                printf("fopen");
                return 1;
        }
        while((ch=fgetc(fp))!=EOF)
        {
                putchar(ch);
        }
        fclose(fp);
        return 0;
}

```




