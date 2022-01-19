// https://www.cnblogs.com/skyfsm/p/7079458.html

// int select(int maxfdp, fd_set *readset, fd_set *writeset, fd_set *exceptset,struct timeval *timeout);

// 参数说明：
// maxfdp：被监听的文件描述符的总数，它比所有文件描述符集合中的文件描述符的最大值大1，因为文件描述符是从0开始计数的；
// readfds、writefds、exceptset：分别指向可读、可写和异常等事件对应的描述符集合。
// timeout:用于设置select函数的超时时间，即告诉内核select等待多长时间之后就放弃等待。timeout == NULL 表示等待无限长的时间(即永远阻塞)
// timeval结构体定义如下：
// struct timeval
// {      
//     long tv_sec;   /*秒 */
//     long tv_usec;  /*微秒 */   
// };

// 返回值：超时返回0;失败返回-1；成功返回大于0的整数，这个整数表示就绪描述符的数目。

// int FD_ZERO(int fd, fd_set *fdset);   //一个 fd_set类型变量的所有位都设为 0
// int FD_CLR(int fd, fd_set *fdset);  //清除某个位时可以使用
// int FD_SET(int fd, fd_set *fd_set);   //设置变量的某个位置位
// int FD_ISSET(int fd, fd_set *fdset); //测试某个位是否被置位


#include <sys/select.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>


int main()
{
	fd_set rd;
	struct timeval tv;
	int err;

    FD_ZERO(&rd);
	FD_SET(0,&rd);

    tv.tv_sec = 5;
	tv.tv_usec = 0;
	err = select(1,&rd,NULL,NULL,&tv);

    if(err == 0) //超时
	{
		printf("select time out!\n");
	}
	else if(err == -1)  //失败
	{
		printf("fail to select!\n");
	}
	else  //成功
	{
		printf("data is available!\n");
	}

	
	return 0;
}