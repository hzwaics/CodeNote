// fork函数可以算是Linux里有点不好明白的函数了，调用一次，返回两次，虽然在平时的写法中，有基本固定的写法，但是有时候看起来还是有些让人头疼的。这里就把关于fork函数好好整理一下

// 函数介绍
// 功能：fork函数是从一个已经存在的进程中创建一个新的进程，新的进程称为子进程，原来的进程称为父进程。
// 参数：无
// 返回值：
// 成功：子进程中返回 0，父进程中返回子进程 ID。pid_t，为无符号整型。
// 失败：返回 -1。

// 失败的两个主要原因是：
// 1）当前的进程数已经达到了系统规定的上限，这时 errno 的值被设置为 EAGAIN。
// 2）系统内存不足，这时 errno 的值被设置为 ENOMEM。

#include <iostream>
#include <unistd.h>
#include <sys/types.h>

int main(){
    int pid=1;
    pid=fork();
    if(0==pid){ //pid为0，表示为子进程
        cout<<"我是子进程，我的pid是："<<getpid()<<endl;
    }
    else if(pid>0){ //pid>0表示父进程，此时返回值为子进程的pid
        cout<<"我是父进程，我的pid是"<<getpid()<<endl;
    }
    else {  //fork 失败
        cout<<"fork失败"<<endl;
    }
}


// https://cloud.tencent.com/developer/article/1350406