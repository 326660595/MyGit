#include <stdio.h>
#include <stdlib.h>
#include <sqlite3.h>
#include <string.h>
// SQLITE_API int sqlite3_get_table(
//   sqlite3 *db,                /* The database on which the SQL executes */
//   const char *zSql,           /* The SQL to be executed */
//   char ***pazResult,          /* Write the result table here */
//   int *pnRow,                 /* Write the number of rows in the result here */
//   int *pnColumn,              /* Write the number of columns of result here */
//   char **pzErrMsg             /* Write error messages here */
// )

static int callback(void *data, int argc, char **argv, char **azColName)
{
   int i;
   fprintf(stderr, "%s: ", (const char *)data);
   for (i = 0; i < argc; i++)
   {
      // if (strcmp("id", azColName[i]) != 0)
      //    break;
      printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
      if (strcmp("2", argv[i]) == 0)
      {
         printf("_______________222222222222222222_________\n");
         data = argv[i];
         sprintf(data,argv[i],strlen(argv[i]));
         memset(data,'a',1);
         printf("%s---\n",(char*)data);
         return 0;
      }
      // if (strcmp("id", azColName[i]) == 0)
      // if (atoi(argv[i]) == 2)
      // {
      //    for (int n = 0; n < argc; n++)
      //    {
      //       printf("n=%d,%s = %s\n", n, azColName[n], argv[n] ? argv[n] : "NULL");
      //       if (strcmp("ddkk999999", argv[n]) == 0)
      //             printf("_____________________________jjjjjjjjjjjjj______________\n");
      //    }
      // }
   }
   printf("\n");
   return 0;
}

int main(int argc, char *argv[])
{
   sqlite3 *db;
   char *zErrMsg = 0;
   int rc;
   char *sql;
   // const char *data = "Callback function called";
   char *data = (char *)malloc(100);

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

   /* Create SQL statement */
   sql = "SELECT * from local_card_info";

   /* Execute SQL statement */
   rc = sqlite3_exec(db, sql, callback, (void *)data, &zErrMsg);
   printf("----------+%s+---\n",(char *)data);
   if (rc != SQLITE_OK)
   {
      fprintf(stderr, "SQL error: %s\n", zErrMsg);
      sqlite3_free(zErrMsg);
   }
   else
   {
      fprintf(stdout, "Operation done successfully\n");
   }
   sqlite3_close(db);
   return 0;
}