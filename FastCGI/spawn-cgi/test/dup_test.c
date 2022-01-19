// https://blog.csdn.net/silent123go/article/details/71108501

// 写过CGI程序的人都清楚，当浏览器使用post方法提交表单数据时，CGI读数据是从标准输入stdin，
// 写数据是写到标准输出stdout(C语言利用printf函数)。按照我们正常的理解，printf的输出应该
// 在终端显示，原来CGI程序使用dup2函数将STDOUT_FINLENO(这个宏在unitstd.h定义，为１)这
// 个文件描述符重定向到了连接套接字：dup2(connfd, STDOUT_FILENO)。