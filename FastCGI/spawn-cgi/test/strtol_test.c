// https://www.cnblogs.com/cyx-b/p/12491043.html

// strtol是一个C语言函数，包含在头文件：#include <stdlib.h>，在c++中则是头文件<cstdlib>

// 作用就是将一个字符串转换为长整型long，其函数原型为：
// long int strtol (const char* str, char** endptr, int base);
// 参数：
    // str是要转换的字符串
    // endptr是指向第一个不可转换的字符位置的指针
    // base为基数，表示转换成为几进制的数
// 返回值：
    // 返回转换后的长整型数；
    // 如果不能转换或者 str 为空字符串，那么返回 0(0L)；
    // 如果转换得到的值超出 long int 所能表示的范围，函数将返回 LONG_MAX 或 LONG_MIN（在 limits.h 头文件中定义），并将 errno 的值设置为 ERANGE。

// 注意：
