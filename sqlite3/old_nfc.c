/******************************************************************************

File Name	: srv_nfc.c
Version		: Initial Draft
Author		: wangxiao
Created 		: 2019/05/21
Description	:
History		:

******************************************************************************/

#include "FreeRTOS.h"
#include "task.h"
#include "srv_msg.h"
#include "srv_log.h"
#include "srv_Biz.h"
#include "srv_nfc.h"
#include "srv_net.h"
#include "srv_comm.h"
#include "srv_elock.h"
#include "os_misc.h"
#include "dev_nfc.h"
#include "dev_led.h"
#include "dev_rtc.h"
#include "dev_lcd.h"
#include "log.h"
#include "resAddrDef.h"
#include "ocpp_json.h"
#include "Ble_protocol.h"
#include "wdg.h"
#include "hal_spi.h"
#include "srv_smartchg.h"

#define L1_MANAGER                                                                                     \
    {                                                                                                  \
        0x12, 0x34, 0x56, 0x78, 0xED, 0xCB, 0xFF, 0x07, 0x80, 0x69, 0x56, 0x78, 0x01, 0xFE, 0x01, 0xFE \
    }
#define L2_MANAGER                                                                                     \
    {                                                                                                  \
        0x4C, 0x5A, 0x43, 0x6F, 0x6E, 0x66, 0x69, 0x67, 0x44, 0x61, 0x74, 0x61, 0x43, 0x61, 0x72, 0x64 \
    }
char l1_manager[CARD_ID_LEN] = L1_MANAGER;
char l2_manager[CARD_ID_LEN] = L2_MANAGER;
uint8_t ReadCardBuf[2 * MF1_BLOCK_SIZE];
/*通过管理员卡，或蓝牙等改变add_card_state加卡*/
Add_Card_Type add_card_state = ADD_CARD_BY_ADMIN; // ADD_CARD_DISABLE;
char card_num[2 * 16];
char card_type[1];
uint8_t RfidCardIndex = 0;
char RFID_device_ID[USER_CARD_MAX][16] = {0};
char UserCardID[USER_CARD_MAX][16] = {0};
uint8_t LocalAuthListIndex = 0;
LocalAuthListInfo LocalAuthList[16] = {0};
char auth_idTag[20];
uint8_t offline_full_reject = 0;
sqlite3 *card_db; /*卡数据库指针*/
sqlite3 *white_card_db;

char *get_user_card(void)
{
    strncpy(auth_idTag, card_num, 20);
    return card_num;
}

uint8_t search_rfid_id_from_local_auth_list(char *rfid_id)
{
    uint8_t ret = 0, i = 0;

    for (; i < LocalAuthListIndex; i++)
    {
        if (strncmp(LocalAuthList[i].idTag, rfid_id, 20) == 0)
        {
            if (LocalAuthList[i].status == LOCAL_AUTH_ACCEPTED)
            {
                if (LocalAuthList[i].expiryDate == 0 || LocalAuthList[i].expiryDate > get_rtc_time())
                {
                    ret = 2;
                }
                else
                {
                    ret = 12;
                }
            }
            else
            {
                ret = 11;
            }
            break;
        }
    }

    if (ret != 2)
    {
        offline_full_reject = 0;
    }

    if (ret == 2 && get_net_module() & (NET_ETH | NET_WIFI | NET_4G) && get_network_state() != NETWORK_AVAILABLE && check_offline_record_full())
    {
        if (get_device_status(0) != DEV_PHASE_CHGW && get_device_status(0) != DEV_PHASE_CHG && get_device_status(0) != DEV_PHASE_PAUSE)
        {
            offline_full_reject = 1;
        }
        return 0;
    }

    return ret;
}

void rfid_led_write_ind(unsigned char enable)
{
}
void rfid_led_add_ind(unsigned char index)
{
}
/*保存到授权信息*/
void save_local_auth_list(LocalAuthListInfo *buf, int num, uint8_t flag)
{
    int i = 0, j = 0, k = 0, m = 0;
    uint8_t list_void_pos[16] = {0}; // record which list is deleted
    uint8_t *p_msg = NULL;

    if (flag == LIST_UPDATE_CLEAR)
    {
        // send_msg_to_log(MSG_WRITE,FILE_STORE_LOCAL_AUTH_LIST,NULL,0);
        printf("save_local_auth_list FILE_STORE_LOCAL_AUTH_LIST");
        LocalAuthListIndex = 0;
        memset(LocalAuthList, 0, sizeof(LocalAuthList));
        return;
    }

    const uint16_t list_max_length = get_local_auth_list_max_length_cfg();
    p_msg = (uint8_t *)malloc(list_max_length * sizeof(LocalAuthListInfo));
    if (p_msg != NULL)
    {
        uint8_t list_idx = 0;
        LocalAuthListInfo *list = (LocalAuthListInfo *)p_msg;

        if (flag == LIST_UPDATE_FULL)
        {
            LocalAuthListIndex = 0;
            memset(LocalAuthList, 0, sizeof(LocalAuthList));
        }
        else if (flag == LIST_UPDATE_DIFF)
        {
            if (LocalAuthListIndex < list_max_length)
            {
                memset(&LocalAuthList[LocalAuthListIndex], 0, (list_max_length - LocalAuthListIndex) * sizeof(LocalAuthListInfo));
            }
        }

        for (i = 0; i < num; i++)
        {
            for (j = 0; j < LocalAuthListIndex; j++)
            {
                if (strncmp(LocalAuthList[j].idTag, buf[i].idTag, 20) == 0)
                {
                    break;
                }
            }

            // idTag is exist
            if (j < LocalAuthListIndex)
            {
                if (flag == LIST_UPDATE_DIFF && buf[i].expiryDate == 0 && buf[i].status == 0)
                {
                    // delete this idTag
                    list_void_pos[j] = 1;
                }
                else
                {
                    // cover existed idTag
                    memcpy(&LocalAuthList[j], &buf[i], sizeof(LocalAuthListInfo));
                }
            }
            else
            {
                // search deleted idTag
                for (k = 0; k < LocalAuthListIndex; k++)
                {
                    if (list_void_pos[k])
                    {
                        break;
                    }
                }

                if (k < LocalAuthListIndex)
                {
                    // find deleted idTag positon, copy new idTag
                    memcpy(&LocalAuthList[k], &buf[i], sizeof(LocalAuthListInfo));
                    list_void_pos[k] = 0;
                }
                else
                {
                    if (LocalAuthListIndex < list_max_length)
                    {
                        // list is not full
                        memcpy(&LocalAuthList[LocalAuthListIndex], &buf[i], sizeof(LocalAuthListInfo));
                        LocalAuthListIndex++;
                    }
                    else
                    {
                        // list is full, cover NOT-valid or oldest idTag
                        int rmv = 0;
                        for (m = 0; m < LocalAuthListIndex; m++)
                        {
                            if (LocalAuthList[m].status != LOCAL_AUTH_ACCEPTED)
                            {
                                rmv = m;
                                break;
                            }
                            if (LocalAuthList[m].entryTime < LocalAuthList[rmv].entryTime)
                            {
                                rmv = m;
                            }
                        }
                        memcpy(&LocalAuthList[rmv], &buf[i], sizeof(LocalAuthListInfo));
                    }
                }
            }
        }

        for (k = 0; k < LocalAuthListIndex; k++)
        {
            if (list_void_pos[k] == 0)
            {
                memcpy(&list[list_idx], &LocalAuthList[k], sizeof(LocalAuthListInfo));
                list_idx++;
            }
        }

        LocalAuthListIndex = list_idx;
        memset(LocalAuthList, 0, sizeof(LocalAuthList));
        memcpy((uint8_t *)LocalAuthList, p_msg, LocalAuthListIndex * sizeof(LocalAuthListInfo));
        printf("MSG_WRITE,FILE_STORE_LOCAL_AUTH_LIST msg:%s", (char *)p_msg);
        // send_msg_to_log(MSG_WRITE,FILE_STORE_LOCAL_AUTH_LIST,p_msg,LocalAuthListIndex*sizeof(LocalAuthListInfo));
        if (LocalAuthListIndex == 0)
        {
            set_local_auth_list_version_cfg(0, 1);
        }
    }
    free(p_msg);
}
/*看juno代码，此函数操作的数据没有使用*/
/*
void save_authorize_cache(char *date)
{
    uint8_t *p_msg = NULL;
    uint8_t len;

    len = 64;
    p_msg = (uint8_t *)malloc(len);
    if (p_msg != NULL)
    {
        if (date != NULL)
        {
            sprintf((char *)p_msg, "idTag:%s,date:%s", card_num, date);
        }
        else
        {
            sprintf((char *)p_msg, "idTag:%s,date:null", card_num);
        }
        LOGD("save: %s\r\n", p_msg);
        send_msg_to_log(MSG_WRITE, FILE_INSERT_AUTHORIZE_CACHE, p_msg, len);
    }
}

void delete_authorize_cache(void)
{
    uint8_t *p_msg = NULL;
    uint8_t len;

    len = 32;
    p_msg = (uint8_t *)malloc(len);
    if (p_msg != NULL)
    {
        sprintf((char *)p_msg, "idTag:%s", card_num);
        LOGD("delete: %s\r\n", p_msg);
        send_msg_to_log(MSG_WRITE, FILE_DELETE_AUTHORIZE_CACHE, p_msg, len);
    }
}
*/
void Authentic_Success(uint8_t num, uint8_t accesstype)
{
    uint16_t user_type = 0;

    if (get_available_en_fact() == AVAILABLE_DISABLE)
    {
        return;
    }

    switch (get_device_status(num))
    {
    case DEV_PHASE_STB:
        if (get_error_type(num) /*&(~OFFLINE_ERROR)*/)
        {
            break;
        }
        if (get_auth_before_plugin_cfg())
        {
            if (accesstype < ACCESS_BY_BLUE || accesstype == ACCESS_BY_UNKNOW_CARD)
            {
                set_user_id(num, (uint8_t *)card_num, sizeof(card_num));
            }
            else if (accesstype == ACCESS_BY_BLUE)
            {
                set_user_id(num, (uint8_t *)ble_respond.AppUserUID, sizeof(ble_respond.AppUserUID));
            }
            else if (accesstype == ACCESS_BY_MODBUS)
            {
                set_user_id(num, "MODBUS", 6);
            }
            set_auth_status(num, 1);
            set_auth_time_cnt(num, 1);
            set_device_status(num, DEV_PHASE_UNLOCK);
            set_stopcause_status(num, NULL_STOP);
            set_user_access_type_bak(num, accesstype);
            send_msg_to_net(MSG_SRC_NFC, MSG_ID_EVENT_STATUS, 0, NULL, 0);
            // Sound_Play(SOUND_AUTH_PLUG_IN);
        }
        else
        {
            // Sound_Play(SOUND_CARD_OK_BUT_NOT_INSERT);
        }
        break;
    case DEV_PHASE_CHGW:
    case DEV_PHASE_CHG:
    case DEV_PHASE_PAUSE:
        if (get_stopchg_by_card_cfg())
        {
            if ((accesstype != ACCESS_BY_WHITE_CARD && accesstype != ACCESS_BY_MODBUS) ||
                ((accesstype == ACCESS_BY_WHITE_CARD) && (memcmp((uint8_t *)card_num, get_user_id_addr(0), sizeof(card_num)) == 0)))
            {
                StopCharging_byHand(num, CARD_STOP);
            }
        }
        break;
    case DEV_PHASE_CHGF:
        if (!get_charge_again_cfg())
        {
            break;
        }
        else
        {
            set_stopcause_status(num, NULL_STOP);
        }
    case DEV_PHASE_TIM:
    case DEV_PHASE_CDM:
        if (get_error_type(num) /*&(~OFFLINE_ERROR)*/)
        {
            break;
        }
        if (accesstype < ACCESS_BY_BLUE || accesstype == ACCESS_BY_UNKNOW_CARD)
        {
            set_user_id(num, (uint8_t *)card_num, sizeof(card_num));
            user_type = 0x02;
        }
        else if (accesstype == ACCESS_BY_BLUE)
        {
            set_user_id(num, (uint8_t *)ble_respond.AppUserUID, sizeof(ble_respond.AppUserUID));
            user_type = get_login_type();
        }
        else if (accesstype == ACCESS_BY_TIME)
        {
            set_user_id(num, (uint8_t *)get_time_user_id(), strlen(get_time_user_id()));
            user_type = 0x02;
        }
        else if (accesstype == ACCESS_BY_MODBUS)
        {
            set_user_id(num, "MODBUS", 6);
        }
        set_auth_status(num, 1);
        set_cpstart_status(num, 1);
        if (get_user_access_type(num) != ACCESS_BY_NULL)
        {
            if (get_cp(num) != CP_12V)
            {
                // Sound_Play(SOUND_AUTH_PASS);
                set_user_access_type_bak(num, accesstype);
                if (!get_elock_ctrl_flag())
                {
                    if (get_local_load_management_cfg())
                    {
                        set_device_status(num, DEV_PHASE_LLM);
                        if (get_smart_meter_cfg())
                        {
                            send_msg_to_smartchg(MSG_SRC_NFC, MSG_ID_START_CHARGE, num, 1);
                        }
                    }
                    else
                    {
                        // set_power_out_percent(100);
                        set_device_status(num, DEV_PHASE_CHGW);
                        send_msg_to_biz(MSG_ID_START_CHARGE, MSG_ID_START_CHARGE, num, 1);
                    }
                }
                else
                {
                    set_elock_ctrl_state(ELOCK_LOCK);
                    set_device_status(num, DEV_PHASE_UNLOCK);
                    set_lock_ack_type(ACK_NULL);
                }
                LOGD("START_CHARGE\r\n");
                save_system_log(SYS_STATUS_TYPE, accesstype, user_type);
            }
        }
        break;
    default:
        break;
    }
}

void StopCharging_byHand(uint8_t num, Stop_cause type)
{
    uint16_t user_type = 0;

    if (get_device_status(num) != DEV_PHASE_STB || get_stake_charge_state() == 0xFF)
    {
        set_stopcause_status(num, type);
        // set_device_status(num,DEV_PHASE_CHGF);
        // Sound_Play(SOUNE_STOP_CHARGING);
        LOGD("STOP_CHARGE\r\n");
        send_msg_to_biz(MSG_ID_STOP_CHARGE, MSG_ID_STOP_CHARGE, num, 1);
        if (type == UNLOCK_STOP)
        {
            os_delayms(3000);
        }
        if (get_cpstart_status(num))
        {
            if (type == CARD_STOP)
            {
                user_type = 2;
            }
            else if (type == BLUE_STOP)
            {
                user_type = get_login_type();
            }

            if ((type > 15) && (type != MODBUS_STOP) && (type != SOFTRESET_STOP) && (type != POWER_LOSS_STOP) && (type != OFFLINE_RECORD_FULL) && (type != MODBUS_FAIL_STOP))
            {
                save_system_log(SYS_STATUS_TYPE, type, user_type);
            }

            if (type == SOFTRESET_STOP)
            {
                save_system_log(SYS_STATUS_TYPE, type, user_type);
            }
            else if (type == POWER_LOSS_STOP)
            {
                save_system_log(SYS_STATUS_TYPE, type, user_type);
            }
            else if (type == OFFLINE_RECORD_FULL)
            {
                save_system_log(SYS_STATUS_TYPE, type, user_type);
            }
            else if (type == MODBUS_FAIL_STOP)
            {
                save_system_log(SYS_STATUS_TYPE, type, user_type);
            }
            else
            {
                save_system_log(SYS_STATUS_TYPE, type + 6, user_type);
            }
        }
        if (type == MODBUS_STOP || type == INPUT_UNAVAILABLE_STOP)
        {
            save_system_log(SYS_STATUS_TYPE, type, user_type);
        }
        set_user_access_type_bak(num, ACCESS_BY_NULL);
        set_stake_charge_state(0);
        // send_msg_to_net(MSG_SRC_PCOM, MSG_ID_EVENT_STATUS,DEV_PHASE_CHGF,NULL,0);

        if (type == CARD_STOP)
        {
            set_stop_user_id(num, (uint8_t *)card_num, sizeof(card_num));
        }
        else if (type == BLUE_STOP)
        {
            set_stop_user_id(num, (uint8_t *)ble_respond.AppUserUID, sizeof(ble_respond.AppUserUID));
        }
        else if (type == MODBUS_STOP)
        {
            set_stop_user_id(num, "MODBUS", 6);
        }
        else
        {
            set_stop_user_id(num, get_user_id_addr(num), CID_STR_LEN);
        }
    }
}

/*juno从本地配置文件读取白名单信息，hydra不用*/
/*
void set_local_auth_list(uint8_t *data, int len)
{

    if (len <= sizeof(LocalAuthListInfo) * get_local_auth_list_max_length_cfg())
    {
        memcpy((uint8_t *)LocalAuthList, data, len);
        LocalAuthListIndex = len / sizeof(LocalAuthListInfo);
    }
    int i = 0;
    date_t date;
    LOGD("LocalAuthListVersion: %d\r\n", get_local_auth_list_version_cfg());
    LOGD("Local Auth List count: %d\r\n", LocalAuthListIndex);
    for (; i < LocalAuthListIndex; i++)
    {
        LOGD("%d --> %s\r\n", i + 1, LocalAuthList[i].idTag);
    }
}
*/
uint8_t check_local_auth_list_conflict(uint8_t status, uint32_t expiryDate)
{
    int i = 0;

    if (get_local_authorize_offline_cfg() == 0 || get_local_auth_list_cfg() == 0)
    {
        return 0;
    }

    while (i < LocalAuthListIndex)
    {
        if (strcmp(LocalAuthList[i].idTag, auth_idTag) == 0)
        {
            if (LocalAuthList[i].status == status && (expiryDate == 0 || LocalAuthList[i].expiryDate == expiryDate))
            {
                return 0;
            }
            else
            {
                return 1;
            }
        }
        i++;
    }

    return 0;
}

// uint8_t check_offline_record_full(void)
// {
//     if (offline_chg_statistics.total_record_num >= OFFLINE_CHARGE_RECORD_MAX)
//     {
//         return 1;
//     }
//     else
//     {
//         return 0;
//     }
// }
/*蓝牙获取card_num*/
void get_rfidcard_num(uint8_t *tmpbuf, uint16_t len)
{
    memcpy(tmpbuf, (uint8_t *)RFID_device_ID, len);
}

uint8_t get_rfidcard_index(void)
{
    return RfidCardIndex;
}

void get_rfidcard_num_by_index(uint8_t *tmpbuf, uint8_t idex)
{
    if (RfidCardIndex == 0)
    {
        return;
    }

    if (idex <= 0 || idex > USER_CARD_MAX)
    {
        idex = RfidCardIndex;
    }
    memcpy(tmpbuf, (uint8_t *)&RFID_device_ID[idex - 1], 16);
}

void clen_usercard_in_ram(void)
{
    memset(RFID_device_ID, 0, USER_CARD_MAX * 16);
    memset(UserCardID, 0, USER_CARD_MAX * 16);
    RfidCardIndex = 0;
}


int get_usercard_by_ble(uint8_t *data, uint8_t num)
{
    uint8_t loop_i = 0;
    uint16_t len = 0;

    if ((data + num * 20 - 1) == NULL) // overflow
    {
        return -1;
    }

    for (loop_i = 0; loop_i < num; loop_i++)
    {
        memset(data + 20 * loop_i, 0, 20);
        memcpy(data + 20 * loop_i, UserCardID[loop_i], 16);
    }

    return 0;
}
