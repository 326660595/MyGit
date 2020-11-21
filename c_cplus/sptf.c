#include <stdio.h>
#include <string.h>
#include <stdbool.h>

bool test_bool(){
    int a=1;
    // return false;
}

int main(){
    char *h = "hellow world";
    int num = 53;
    char a[20];// = malloc(10);
    //sprintf(a,"%d",num);
    // printf("h is: %s\n",a);

    // char s[10];
    // char* who = "I";
    // char* whom = "CSDN";

    char btest = 0;

    bool atest = test_bool();
    printf("true or false :%d",atest);
    if(atest){
        printf("good");
        putchar(atest);
    }
    
    printf("\n");

    memcpy(a,h,strlen(h));

    printf("a is: %s\n",a);
    // free(a);
    // // sprintf(s, "%-8d%8d", 123, 4567);
    // //sprintf(s, "%8x", 4567);
    // int i = 100;
    // //sprintf(s, "%.2f", i);
    // sprintf(s, "%s love %s.", who, whom); //产生："I love CSDN. "

    // //sprintf(s, "%.2f", (double)i);
    // printf("s is: %s\n",s);

    // printf("h is: %#x\n",num);
    getchar();
}

// int main(void)
// {
//    char buffer[80];
//    sprintf(buffer, "An approximation ofPi is %f\n", 20);
//    printf("put \n");
//    puts(buffer);
//    getchar();
//    return 0;
// }

//  int main()
// {
//     char *s="Golden Global View";
//     char d[20];
//     memcpy(d,s,strlen(s));
//     d[strlen(s)]=0;
//     printf("%s",d);

//     getchar();
//     return 0;
// }


// 嫦娥闹钟项目：
//     1.嫦娥闹钟项目发布了版本1.1.3修复了1.1.2重启会偶现丢失开机那段时间指令的问题。
//     复查了昨天开机有偶现丢指令的问题的原因：为优化交互灯代码时加入了printf语句，
//     开机动画原来是每ms闪烁一次，printf占用cpu资源多，加上cpu性能不够强造成了这个问题。

//     2.mcu已检测几天没有出现问题，嫦娥闹钟现在等待阿里测试通过。

// 星语地球仪：
//     通过了准入准出测试，录制了视频，寄出到阿里进行声学测试。

// 云米洗衣机：
//     通过了准入准出测试，

//bool型返回值函数，没写return语句的时候返回啥？