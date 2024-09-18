#include <stdint.h>
#include <stdio.h>
// cp56time2a时间格式
typedef union
{
	// 低7字节是七个八位位组二进制时间	
	uint64_t Cp56Time;  // uint8_t Cp56Time[7];
	
	struct
	{
		uint16_t msec;
		uint8_t min	: 6;
		uint8_t res1    : 1;
		uint8_t iv 	: 1;
		uint8_t hour 	: 5;
		uint8_t res2 	: 2;
		uint8_t su 	: 1;
		uint8_t mday 	: 5;
		uint8_t wday 	: 3;
		uint8_t month   : 4;
		uint8_t res3 	: 4;
		uint8_t year 	: 7;
		uint8_t res4 	: 1;
	}Compts;
}Cp56Time2a;

// 本地时间结构体 
typedef struct
{
	uint8_t year;
	uint8_t month;
	uint8_t mday;
	uint8_t hour;
	uint8_t min;
	uint16_t msec;
}Time;
#pragma pack(pop)


Time time = {0};  // 定义一个保存时间的结构体
Cp56Time2a cp56time2a =  {0};  // 定义一个cp56time2a的结构体

// cp56time2a 转本地时间
static uint64_t Cp56time2aToLocalTime(uint64_t cp56time2atime)
{
	printf("\n\t Year  :  %d \n\r", cp56time2a.Compts.year);
	printf("\n\t month :  %d \n\r", cp56time2a.Compts.month);
	printf("\n\t mday  :  %d \n\r", cp56time2a.Compts.mday);
	printf("\n\t wday  :  %d \n\r", cp56time2a.Compts.wday);	
	printf("\n\t hour  :  %d \n\r", cp56time2a.Compts.hour);
	printf("\n\t min   :  %d \n\r", cp56time2a.Compts.min);
	printf("\n\t msec  :  %d \n\r", cp56time2a.Compts.msec);
	return 0;
}	

// 本地时间转cp56time2a格式 
uint64_t LocalTimeToCp56Time2a(const Time *time)
{	
    cp56time2a.Compts.year 	= time->year;
	cp56time2a.Compts.month	= time->month;
	cp56time2a.Compts.mday	= time->month;
	cp56time2a.Compts.hour	= time->hour;
	cp56time2a.Compts.min	= time->min;
	cp56time2a.Compts.msec	= time->msec;
	
    return cp56time2a.Cp56Time;
}

int main(void)
{
    time.year = 23;
	time.month = 12;
	time.mday = 12;
	time.hour =18;
	time.min = 30;
	time.msec = 40;
	
	printf("\n\t cp56time2a 0X:%llX \n\r", LocalTimeToCp56Time2a(&time));
    return 0;
}
