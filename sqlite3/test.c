#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <sys/time.h>
#include <time.h>
#include <string.h>
#include <sqlite3.h>
// sprintf(sql,"VALUES (%d,'6699887d','ddkk999999',1,'this is test card','A',20000,20000,NULL);",999,"lll");
// sprintf(sql,"VALUES (%d,%s,%s,%d,%s,%s,%u,%u,%u);",1,"6699887d","ddkk999999",1,"this is test card","A",20000,20000,0);
char *creat_sql(char *sql, int id, char *version_id, char *card_number, int status,
                char *remarks, char type, uint64_t created_at, uint64_t updated_at, uint64_t deleted_at)
{
    sprintf(sql, "INSERT INTO local_card_info (id,version_id,card_number,status,remarks,type,created_at,updated_at,deleted_at)"
                 "VALUES (%d,%s,%s,%d,%s,%c,%lu,%lu,%lu);",
            id, version_id, card_number, status, remarks, type, created_at, updated_at, deleted_at);

    return sql;
}

char dbTime[32];

struct tm *get_rtc_time()
{
    time_t tDate;
    struct tm *eventTime;
    time(&tDate); //取得时间戳
    // tDate += 60 * 60;
    eventTime = localtime(&tDate); //时间戳转换日期结构体
    sprintf(dbTime, "%04d-%02d-%02dT%02d:%02d:%02d.000Z",
            (eventTime->tm_year + 1900), (eventTime->tm_mon + 1), (eventTime->tm_mday),
            (eventTime->tm_hour), (eventTime->tm_min), (eventTime->tm_sec));

    printf("11timestamp = %ld\n",tDate);

    // printf("gmtime=%s\n",gmtime(&tDate));

    return eventTime;
}
uint64_t trans_time(char *time_data)
{
    char time_c[10] = {0};
    uint64_t timestamp = 0;
    struct tm eventTime;
    snprintf(time_c, 5, "%s", time_data);
    printf("JJ%sjj\n", time_c);
    eventTime.tm_year = atol((char *)time_c) - 1900;
    memset(time_c, 0, 10);
    snprintf(time_c, 2, "%s", time_data + 6);
    eventTime.tm_mon = atoi(time_c) - 1;
    memset(time_c, 0, 10);
    snprintf(time_c, 2, "%s", time_data + 9);
    eventTime.tm_mday = atoi(time_c);
    memset(time_c, 0, 10);
    snprintf(time_c, 3, "%s", time_data + 11);
    eventTime.tm_hour = atoi(time_c);
    memset(time_c, 0, 10);
    snprintf(time_c, 3, "%s", time_data + 14);
    eventTime.tm_min = atoi(time_c);
    memset(time_c, 0, 10);
    snprintf(time_c, 3, "%s", time_data + 17);
    eventTime.tm_sec = atoi(time_c);
    eventTime.tm_isdst = -1;

    printf("%d-%d-%dT%d:%d:%d.000Z\n",
           (eventTime.tm_year), (eventTime.tm_mon), (eventTime.tm_mday),
           (eventTime.tm_hour), (eventTime.tm_min), (eventTime.tm_sec));

    printf("lllll\n");
    timestamp = mktime(&eventTime);

    printf("timestamp = %ld\n",timestamp);

    return timestamp;
}
// n=5,created_at = 2021-03-24T10:44:11.000Z
int main(int argc, char *argv[])
{
    printf("hello world\n");
    get_rtc_time();
    printf("time date = %s\n", dbTime);
    trans_time(dbTime);

    //    char *sql;// = sqlite3_mprintf("INSERT INTO parameters VALUES(%d,'DeviceID','TCB060CN41020010',1);",1);
    //    sql = sqlite3_mprintf("INSERT INTO parameters VALUES(%d,'DeviceID','TCB060CN41020010',1);",1);
    //    char *sql1 = (char *)malloc(sizeof(char)*500);
    //    creat_sql(sql1,1,"6699887d","ddkk999999",1,"this is test card",'A',20000,20000,0);

    //    printf("sql : %s\n",sql);
    //    printf("sql1 : %s\n%ld\n",sql1,strlen(sql1));

    // free(sql1);
    return 0;
}