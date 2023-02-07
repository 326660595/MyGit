#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>

//russell:我改编的查询最后一个id值在find.c当中

/* 查询数据中，表内，第一个数据的ID和最后一条数据的ID */
/* WORD 为unsigned short 型*/
/*  table_name 为表格名称
 *  first_id 保存第一行的ID
 *  tail_id 保存最后一行的ID
 */
 
int SQLite3SearchID(char* table_name,WORD* first_id, WORD* tail_id)
{
	if(table_name == NULL || first_id == 0 || tail_id == 0)
		{
			pri("input error ! \n");
			return -1;
		}
		
	sqlite3_stmt      *pstmt = 0;
	
	
	/* 拼接命令： “ select * from apple LIMIT 1；” */
	
	char first[64]  = "select * from "; 
	BYTE *tmp_first = " LIMIT 1";
	strcat(first,table_name);
	strcat(first,tmp_first);



	/* 拼接命令： “ select * from apple order by ID desc LIMIT 1；” */
	char tail[64]  = "select * from ";
	BYTE *tmp_tail = " order by ID desc LIMIT 1";
	strcat(tail, table_name);
	strcat(tail, tmp_tail);
	
	
	printf("first : %s \n", first);
	printf("tail : %s \n", tail);
	if( (sqlite3_prepare(sqlDB, first, strlen(first), &pstmt, NULL)) != SQLITE_OK )
		{
			pri("sqlite3_prepare error ! \n");
			fprintf(stderr,"sqlite3_prepare error %s\r\n",sqlite3_errmsg(JT808_sqlDB));
			return -1;
		}
		
	//真正开始执行前面的sql语句
	sqlite3_step(pstmt);
	
	/* 读取整形数据 第一个数据的ID */
	*first_id = sqlite3_column_int(pstmt,0);
	
	//释放前面为stmt分配的内存，必须要有，否则会有内存泄露
	sqlite3_finalize(pstmt);
	
	
	
	if( (sqlite3_prepare(sqlDB, tail, strlen(tail), &pstmt, NULL)) != SQLITE_OK )
		{
			pri("sqlite3_prepare error ! \n");
			return -1;
		}
		
	//真正开始执行前面的sql语句
	sqlite3_step(pstmt);
	
	/* 读取整形数据 第一个数据的ID */
	*tail_id = sqlite3_column_int(pstmt,0);
	
	//释放前面为stmt分配的内存，必须要有，否则会有内存泄露
	sqlite3_finalize(pstmt);
}
