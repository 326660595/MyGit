#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <linux/rtc.h>
#include <stdint.h>

#define RTC_DS1302_FILENAME "/dev/ds1302"

int rtc_fd;

int rtc_init(void)
{
    rtc_fd = open(RTC_DS1302_FILENAME, O_RDWR); // 2==O_RDWR
    if (rtc_fd < 0)
    {
        printf("can't open file %s\r\n", RTC_DS1302_FILENAME);
        return -1;
    }

    return 0;
}

/*
 * @description		: 给rtc设备写入初始时间（）
 * @param - filp 	: 设备文件，表示打开的文件描述符
 * @param - buf 	: 要写给设备写入的数据
 * @param - cnt 	: 要写入的数据长度
 * @param - offt 	: 相对于文件首地址的偏移
 * @return 			: 写入的字节数，如果为负值，表示写入失败
 */
int write_time_to_rtc(uint64_t timestamp)
{
    int ret;
    char data[20];
    sprintf(data, "%llu", timestamp);

    printf("time = %s,strlen = %d\n", data, strlen(data));

    ret = write(rtc_fd, data, strlen(data));
    if (!ret)
        printf("time write fail,ret = %d\n", ret);
}

/*
 * @description		: 从rtc设备获取时间
 * @param - filp 	: 设备文件，表示打开的文件描述符
 * @param - buf 	: 要写给设备写入的数据
 * @param - cnt 	: 要写入的数据长度
 * @param - offt 	: 相对于文件首地址的偏移
 * @return 			: 写入的字节数，如果为负值，表示写入失败
 */
int get_rtc_time(void)
{
}

int main(void)
{
    time_t tDate;
    struct tm *eventTime;
    time(&tDate); //取得时间戳
    // tDate += 60 * 60;
    eventTime = localtime(&tDate); //时间戳转换日期结构体
    // sprintf(dbTime, "%04d-%02d-%02dT%02d:%02d:%02d.000Z",
    //         (eventTime->tm_year + 1900), (eventTime->tm_mon + 1), (eventTime->tm_mday),
    //         (eventTime->tm_hour), (eventTime->tm_min), (eventTime->tm_sec));
    printf("timestamp++--- = %ld\n", tDate);

    write_time_to_rtc(tDate);

    return 0;
}