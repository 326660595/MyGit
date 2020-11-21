#include <stdio.h>
#include <string.h>

typedef unsigned int  uint32_t;
typedef unsigned short     uint16_t;
//////////////////////日期格式转换时间戳
uint16_t time_bcd[6]={2020,8,27,20,20,20};//

static uint16_t mon_yday[2][12] =
{
	{0,31,59,90,120,151,181,212,243,273,304,334},
	{0,31,60,91,121,152,182,213,244,274,305,335},
};
int isleap(int year)
{
	return (year) % 4 == 0 && ((year) % 100 != 0 || (year) % 400 == 0);
}
uint32_t mktimestamp(uint16_t *dt,uint16_t len)
{
	uint32_t result;
    int i =0;
    // 以平年时间计算的秒数
    result = (dt[0] - 1970) * 365 * 24 * 3600 +
    (mon_yday[isleap(dt[0])][dt[1]-1] + dt[2] - 1) * 24 * 3600 +
    dt[3] * 3600 + dt[4] * 60 + dt[5];
    // 加上闰年的秒数
    for(i=1970; i < dt[0]; i++)
    {
      if(isleap(i))
      {
        result += 24 * 3600;
      }
    }
    return result;
}
/////////////////////

int main()
{
    uint32_t time = mktimestamp(time_bcd,6);
    printf("timestamp : %d",time);

    getchar();
    return 0;

}

// typedef union{
//  char c;
//  int a;
//  int b;
// }Demo;
 
// int main(int argc, char **argv)
// {
//  Demo d;
//  d.c = 'H';
//  d.a = 10;
//  d.b = 52;
// char cc;

// 	printf("sizecc: %s\n", cc);
//  printf("size: %d\n", sizeof(d));
//  printf("c: %c\t a: %d\t b: %d\n", d.c, d.a, d.b);
// //  getchar();



//  printf("aaaaaaaaaaaaaaaaa");

//  getchar();

//   return 0;
// }