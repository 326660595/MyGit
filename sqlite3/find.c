#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>

/*查找数据个数*/
int sqlite_find_count(sqlite3 *db)

{
    /*查找名字为Sky的个数*/
    char *sql = "select count(*) from local_card_info where id;";
    sqlite3_stmt *stmt = NULL;
    /*将sql语句转换为sqlite3可识别的语句，返回指针到stmt*/
    int res = sqlite3_prepare_v2(db, sql, strlen(sql), &stmt, NULL);
    if (SQLITE_OK != res || NULL == stmt)
    {
        goto err1;
    }
    /*执行准备好的sqlite3语句*/
    res = sqlite3_step(stmt);
    if (res != SQLITE_ROW)
    {
        goto err2;
    }
    int count = sqlite3_column_int(stmt, 0);
    if (count < 0)
    {
        goto err2;
    }
    printf("count = %d\n", count);
    sqlite3_finalize(stmt);
    return count;
err2:
    sqlite3_finalize(stmt);
err1:
    return -1;
}

//查询最后一个id值
int query(sqlite3 *db)
{
    int id_value = 0;
    char *sql = "select * from local_card_info order by ID desc LIMIT 1";

    sqlite3_stmt *pstmt = NULL;
    if ((sqlite3_prepare(db, sql, strlen(sql), &pstmt, NULL)) != SQLITE_OK)
    {
        printf("sqlite3_prepare error ! \n");
        return -1;
    }
    //真正开始执行前面的sql语句
    sqlite3_step(pstmt);
    /* 读取整形数据 第一个数据的ID */
    id_value = sqlite3_column_int(pstmt, 0);
    //释放前面为stmt分配的内存，必须要有，否则会有内存泄露
    sqlite3_finalize(pstmt);

    return id_value;
}

/*查找数据并取出数据*/

int sqlite_find_parse(sqlite3 *db)

{

    /*查找name为Sky的数据*/

    char *sql = "select * from student where name = 'Sky';";

    sqlite3_stmt *stmt = NULL;

    /*将sql语句转换为sqlite3可识别的语句，返回指针到stmt*/

    int res = sqlite3_prepare_v2(db, sql, strlen(sql), &stmt, NULL);

    if (SQLITE_OK != res || NULL == stmt)
    {

        goto err1;
    }

    /*执行准备好的sqlite3语句*/

    while (SQLITE_ROW == sqlite3_step(stmt))
    {

        printf("name: %s, uuid: %u\n", sqlite3_column_text(stmt, 1), sqlite3_column_int(stmt, 2));
    }

    sqlite3_finalize(stmt);

    return 0;

err2:

    sqlite3_finalize(stmt);

err1:

    return -1;
}
int main(int argc, char *argv[])
{
    sqlite3 *db;
    char *zErrMsg = 0;
    int rc;
    char *sql;
    const char *data = "Callback function called";

    /* Open database */
    rc = sqlite3_open("card.db", &db);
    if (rc)
    {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        exit(0);
    }
    else
    {
        fprintf(stderr, "Opened database successfully\n");
    }

    int id_value = query(db);
    printf("end id value = %d",id_value);
    /* Create SQL statement */
    sql = "SELECT * from local_card_info";

    /* Execute SQL statement */
    rc = sqlite_find_count(db);
    //    if( rc != SQLITE_OK ){
    //       fprintf(stderr, "SQL error: %s\n", zErrMsg);
    //       sqlite3_free(zErrMsg);
    //    }else{
    fprintf(stdout, "Operation done successfully\n");
    //    }
    sqlite3_close(db);
    return 0;
}