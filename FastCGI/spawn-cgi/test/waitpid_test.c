// https://www.cnblogs.com/wuyepeng/p/9789498.html

// wait和waitpid出现的原因：
// --当子进程退出的时候，内核会向父进程发送SIGCHLD信号，子进程的退出是个异步事件（子进程可以在父进程运行的任何时刻终止）
// --子进程退出时，内核将子进程置为僵尸状态，这个进程成为僵尸进程，它只保留最小的一些内核数据结构，以便父进程查询子进程的退出状态
// --父进程查询子进程的退出状态可以用wait/waitpid函数

// pid_t waitpid(pid_t pid,int *status,int options)
// 函数功能：用来等待某个特定进程的结束
// 参数：
    // pid>0时，只等待进程ID等于pid的子进程，不管其它已经有多少子进程运行结束退出了，只要指定的子进程还没有结束，waitpid就会一直等下去。
    // pid=-1时，等待任何一个子进程退出，没有任何限制，此时waitpid和wait的作用一模一样。
    // pid=0时，等待同一个进程组中的任何子进程，如果子进程已经加入了别的进程组，waitpid不会对它做任何理睬。
    // pid<-1时，等待一个指定进程组中的任何子进程，这个进程组的ID等于pid的绝对值。
    // status如果不为空，会把状态信息写到它指向的位置
    // options允许改变waitpid的行为，最有用的一个选项是WNOHANG，它的作用是防止waitpid把调用者的执行挂起
    // 目前在Linux中只支持WNOHANG和WUNTRACED两个选项，这是两个常数，可以用"|"运算符把它们连接起来使用，比如：ret=waitpid(-1,NULL,WNOHANG | WUNTRACED); 如果我们不想使用它们，也可以把options设为0，如：ret=waitpid(-1,NULL,0); 

// 返回值：成功返回等待子进程的pid，失败返回-1
// 当正常返回的时候，waitpid返回收集到的子进程的进程ID；
// 如果设置了选项WNOHANG，而调用中waitpid发现没有已退出的子进程可收集，则返回0；
// 如果调用中出错，则返回-1，这时errno会被设置成相应的值以指示错误所在；
 
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main()
{
    pid_t pid, childpid;
    int status = 0;
    pid = fork();
    if (pid < 0)
        printf("Error occured on forking.\n");
    else if (pid == 0)    //子进程
    {
        sleep(3);   //换成30s，然后kill -9 子进程pid
        exit(0);
    }   
    else                    //父进程
    {
        //返回后继续执行父进程的代码段
    }
    printf("pid:%d\n",pid); //打印子进程id

    do
    {
        childpid = waitpid(pid, &status, WNOHANG);
        printf("childpid = %d\n", childpid);
        if (childpid == 0)
        {
            printf("No child exited,ret = %d\n", childpid);
            sleep(1);
        }
    } while (childpid == 0);

    if (WIFEXITED(status))
        printf("正常退出:%d\n",childpid);

    if(WIFSIGNALED(status) && WTERMSIG(status) == SIGKILL)
        printf("被SIGKILL信号结束\n");

}