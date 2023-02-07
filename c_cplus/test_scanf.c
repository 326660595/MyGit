#include <stdio.h>
int main()
{
    char password[20] = {0};
    printf("请输入密码:>");

    scanf("%s", password);

    printf("请确认密码(Y/N):>");
    int ch = getchar();
    printf("------ch = %d,\npassword = %s\n", ch, password);
    if (ch == 'Y')
    {
        printf("确认成功\n");
    }
    else
    {
        printf("确认失败\n");
    }

    return 0;
}
