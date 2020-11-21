#include <stdio.h>
#include <time.h>
#include <stdbool.h>

typedef unsigned char      uint8_t;
bool rbool();


int atest(){
    if(rbool()){
        return 1;
    }
    return 0;
}

int main(){

        // uint8_t a=10;
        // uint8_t b=20;
        // uint8_t c=a-b;
		// time_t sum_time;
		// sum_time=time(NULL);
        int a = atest();

        printf("The a is  %d\n",a);
		// printf("The number of seconds since January 1, 1970 is  %d\n",366&111);

        getchar();
}

static  bool screen_open = true;//闹钟屏幕开或关
bool rbool(){
    if(screen_open){
        return true;
    }
    return false;
}


