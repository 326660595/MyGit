#include <stdio.h>
#include <stdint.h>

char card_type[1];

/*
 *发送刷卡信息到server；
 */
static void send_nfc_info_to_server(void)
{
    printf("send_nfc_info_to_server,type:\r\n");

    char ctype = card_type[0];
    if (ctype == 'A' || ctype == 'B')
    {
        printf("ab:\r\n");
    }
    else if (ctype == 'V')
    {
        printf("v:\r\n" );
    }
    else
    {
        printf("e:\r\n");
    }

    return;
}


int main(void)
{
    printf("hello world\n");
    memset(card_type, 'A', 1);
    printf("card type = %c\n",card_type[0]);
    send_nfc_info_to_server();

    return 0;
}