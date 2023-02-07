#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <sqlite3.h>

static int callback(void *NotUsed, int argc, char **argv, char **azColName)
{
    int i;
    for (i = 0; i < argc; i++)
    {
        printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
    }
    printf("\n");
    return 0;
}
// char *creat_sql(char *sql, int id, char *version_id, char *card_number, int status,
//                 char *remarks, char type, uint64_t created_at, uint64_t updated_at, uint64_t deleted_at)
// {
//     sprintf(sql, "INSERT INTO local_card_info (id,version_id,card_number,status,remarks,type,created_at,updated_at,deleted_at)"
//                  "VALUES (%d,'%s','%s',%d,'%s','%c',%lu,%lu,%lu);",
//             id, version_id, card_number, status, remarks, type, created_at, updated_at, deleted_at);

//     return sql;
// }
char *creat_sql(char *sql, int id, char *version_id, char *card_number, int status,
                char *remarks, char type, uint64_t created_at, uint64_t updated_at, uint64_t deleted_at)
{
    sql = sqlite3_mprintf("INSERT INTO local_card_info (id,version_id,card_number,status,remarks,type,created_at,updated_at,deleted_at)"
                 "VALUES (%d,'%s','%s',%d,'%s','%c',%lu,%lu,%lu);",
            id, version_id, card_number, status, remarks, type, created_at, updated_at, deleted_at);

    return sql;
}

int main(int argc, char *argv[])
{
    sqlite3 *db;
    char *zErrMsg = 0;
    int rc;
    char *sql = sqlite3_mprintf("INSERT INTO rfid_list (id,version_id,card_number,status,remarks,type,created_at,updated_at,deleted_at)"
                 "VALUES (%d,'%s','%s',%d,'%s','%c','%s','%s','%s');",
                 atoi(argv[1]), "6699887d", "ddkk999999", 1, "this is test card", 'A', "2000", "2000", "2");

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
    // sql = "INSERT INTO local_card_info (id,version_id,card_number,status,remarks,type,created_at,updated_at,deleted_at) "
    //       "VALUES (1,'Paul',32,1,'California','A',20000,2000,NULL); ";
    // sql = (char *)malloc(sizeof(char) * 500);
    // creat_sql(sql, atoi(argv[1]), "6699887d", "ddkk999999", 1, "this is test card", 'A', 20000, 20000, 0);
    printf("---%s---\n",sql);

    /* Execute SQL statement */
    rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);
    if (rc != SQLITE_OK)
    {
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
    }
    else
    {
        fprintf(stdout, "Records created successfully\n");
    }
    sqlite3_close(db);
    return 0;
}