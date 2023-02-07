#include <stdio.h>
#include <string.h>
#include <time.h>

int main(void)
{
    struct tm t1;         // tm结构指针
    struct tm * t;// = &t1; 
    time_t now;          //声明time_t类型变量
    time(&now);          //获取系统日期和时间
    t = localtime(&now); //获取当地日期和时间

    printf("ctime %s", ctime(&now));

    //格式化输出本地时间
    printf("年：%d\n", t->tm_year + 1900); // 
    printf("月：%d\n", t->tm_mon + 1);
    printf("日：%d\n", t->tm_mday);
    printf("周：%d\n", t->tm_wday);
    printf("一年中：%d\n", t->tm_yday);
    printf("时：%d\n", t->tm_hour);
    printf("分：%d\n", t->tm_min);
    printf("秒：%d\n", t->tm_sec);
    printf("夏令时：%d\n", t->tm_isdst);
    // getchar();
    return 0;
}
