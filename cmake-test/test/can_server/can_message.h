#pragma once
#include <cstdint>
#include <string>
using namespace std;

namespace CANj1939 {
namespace Message {

struct PGN {
    enum Type {
        SYNC_TIME = 0x0100,
        VERSION = 0x0200,
        VERSION_ACK = 0x0300,
        UPGRADE = 0x2200,
        UPGRADE_ACK = 0x2300,
        RESET = 0x2400,
        RESET_ACK = 0x2500,
        CCU_INFO_CHECK = 0x2C00,
        CCU_INFO_CHECK_ACK = 0x2D00,
        BCU_HEART_BEAT = 0x4000,
        PDU_HEART_BEAT = 0x4100,
        CCU_HEART_BEAT = 0x4200,
        CCU_REMOTE_SIGNALLING = 0x4300,
        CCU_REMOTE_MEASURING = 0x4400,
        PDU_REMOTE_SIGNALLING = 0x4500,
        PDU_REMOTE_MEASURING = 0x4600,
        PDU_SELF_TEST_RESULT = 0x4800,
        PDU_SELF_TEST_RESULT_ACK = 0x4900,
        BCU_REMOTE_SIGNALLING = 0x4A00,
        CCU_VEHICLE_DATA = 0x4E00,
        CCU_VEHICLE_DATA_ACK = 0x4F00,
        //PDU_ERRORS = 0x5000,
        //CCU_ERRORS = 0x5100,

        START_CHARGING = 0x0400,
        START_CHARGING_ACK = 0x0500,
        STOP_CHARGING = 0x0600,
        STOP_CHARGING_ACK = 0x0700,
        AUTHORIZATION = 0x1200,
        AUTHORIZATION_ACK = 0x1300,
        LOCK_CONNECTOR = 0x1800,
        LOCK_CONNECTOR_ACK = 0x1900,

        START_CHARGING_RESULT = 0x3000,
        START_CHARGING_RESULT_ACK = 0x3100,
        STOP_CHARGING_RESULT = 0x3200,
        STOP_CHARGING_RESULT_ACK = 0x3300,
        AUTHORIZATION_RESULT =0x3A00,
        AUTHORIZATION_RESULT_ACK =0x3B00,
        LOCK_CONNECTOR_RESULT = 0x3C00,
        LOCK_CONNECTOR_RESULT_ACK = 0x3D00,

        OUTPUT_POWER_DEMAND = 0x1600,
        OUTPUT_POWER_DEMAND_ACK = 0x1700,
        PM_REMOTE_MEASURING = 0x1A00,
        PM_REMOTE_MEASURING_ACK = 0x1B00,
        PM_REMOTE_CONTROLLING = 0x1C00,
        PM_REMOTE_CONTROLLING_ACK = 0x1D00,
        PDU_SELF_TEST = 0x1E00,
        PDU_SELF_TEST_ACK = 0x1F00,

        Sentinel,
    };

    static Type FromString(const char *input)
    {
        string str(input);
        if (input == 0)
        {
            return Message::PGN::Sentinel;
        }

        if (!str.compare("SYNC_TIME"))
        {
            return Message::PGN::SYNC_TIME;
        }

        else if (!str.compare("VERSION"))
        {
            return Message::PGN::VERSION;
        }

        else if (!str.compare("VERSION_ACK"))
        {
            return Message::PGN::VERSION_ACK;
        }

        else if (!str.compare("UPGRADE"))
        {
            return Message::PGN::UPGRADE;
        }

        else if (!str.compare("UPGRADE_ACK"))
        {
            return Message::PGN::UPGRADE_ACK;
        }
        else if (!str.compare("RESET"))
        {
            return Message::PGN::RESET;
        }
        else if (!str.compare("RESET_ACK"))
        {
            return Message::PGN::RESET_ACK;
        }
        else if (!str.compare("CCU_INFO_CHECK"))
        {
            return Message::PGN::CCU_INFO_CHECK;
        }
        else if (!str.compare("CCU_INFO_CHECK_ACK"))
        {
            return Message::PGN::CCU_INFO_CHECK_ACK;
        }
        else if (!str.compare("BCU_HEART_BEAT"))
        {
            return Message::PGN::BCU_HEART_BEAT;
        }
        else if (!str.compare("PDU_HEART_BEAT"))
        {
            return Message::PGN::PDU_HEART_BEAT;
        }
        else if (!str.compare("CCU_HEART_BEAT"))
        {
            return Message::PGN::CCU_HEART_BEAT;
        }
        else if (!str.compare("CCU_REMOTE_SIGNALLING"))
        {
            return Message::PGN::CCU_REMOTE_SIGNALLING;
        }
        else if (!str.compare("CCU_REMOTE_MEASURING"))
        {
            return Message::PGN::CCU_REMOTE_MEASURING;
        }
        else if (!str.compare("PDU_REMOTE_SIGNALLING"))
        {
            return Message::PGN::PDU_REMOTE_SIGNALLING;
        }
        else if (!str.compare("PDU_REMOTE_MEASURING"))
        {
            return Message::PGN::PDU_REMOTE_MEASURING;
        }
        else if (!str.compare("PDU_SELF_TEST_RESULT"))
        {
            return Message::PGN::PDU_SELF_TEST_RESULT;
        }
        else if (!str.compare("PDU_SELF_TEST_RESULT_ACK"))
        {
            return Message::PGN::PDU_SELF_TEST_RESULT_ACK;
        }
        else if (!str.compare("BCU_REMOTE_SIGNALLING"))
        {
            return Message::PGN::BCU_REMOTE_SIGNALLING;
        }
        else if (!str.compare("CCU_VEHICLE_DATA"))
        {
            return Message::PGN::CCU_VEHICLE_DATA;
        }
        else if (!str.compare("CCU_VEHICLE_DATA_ACK"))
        {
            return Message::PGN::CCU_VEHICLE_DATA_ACK;
        }
        /*else if (!str.compare("PDU_ERRORS"))
        {
            return Message::PGN::PDU_ERRORS;
        }
        else if (!str.compare("CCU_ERRORS"))
        {
            return Message::PGN::CCU_ERRORS;
        }*/
        else if (!str.compare("START_CHARGING"))
        {
            return Message::PGN::START_CHARGING;
        }
        else if (!str.compare("START_CHARGING_ACK"))
        {
            return Message::PGN::START_CHARGING_ACK;
        }
        else if (!str.compare("STOP_CHARGING"))
        {
            return Message::PGN::STOP_CHARGING;
        }
        else if (!str.compare("STOP_CHARGING_ACK"))
        {
            return Message::PGN::STOP_CHARGING_ACK;
        }
        else if (!str.compare("AUTHORIZATION"))
        {
            return Message::PGN::AUTHORIZATION;
        }
        else if (!str.compare("AUTHORIZATION_ACK"))
        {
            return Message::PGN::AUTHORIZATION_ACK;
        }
        else if (!str.compare("LOCK_CONNECTOR"))
        {
            return Message::PGN::LOCK_CONNECTOR;
        }
        else if (!str.compare("LOCK_CONNECTOR_ACK"))
        {
            return Message::PGN::LOCK_CONNECTOR_ACK;
        }
        else if (!str.compare("START_CHARGING_RESULT"))
        {
            return Message::PGN::START_CHARGING_RESULT;
        }
        else if (!str.compare("START_CHARGING_RESULT_ACK"))
        {
            return Message::PGN::START_CHARGING_RESULT_ACK;
        }
        else if (!str.compare("STOP_CHARGING_RESULT"))
        {
            return Message::PGN::STOP_CHARGING_RESULT;
        }
        else if (!str.compare("STOP_CHARGING_RESULT_ACK"))
        {
            return Message::PGN::STOP_CHARGING_RESULT_ACK;
        }
        else if (!str.compare("AUTHORIZATION_RESULT"))
        {
            return Message::PGN::AUTHORIZATION_RESULT;
        }
        else if (!str.compare("AUTHORIZATION_RESULT_ACK"))
        {
            return Message::PGN::AUTHORIZATION_RESULT_ACK;
        }
        else if (!str.compare("LOCK_CONNECTOR_RESULT"))
        {
            return Message::PGN::LOCK_CONNECTOR_RESULT;
        }
        else if (!str.compare("LOCK_CONNECTOR_RESULT_ACK"))
        {
            return Message::PGN::LOCK_CONNECTOR_RESULT_ACK;
        }
        else if (!str.compare("OUTPUT_POWER_DEMAND"))
        {
            return Message::PGN::OUTPUT_POWER_DEMAND;
        }
        else if (!str.compare("OUTPUT_POWER_DEMAND_ACK"))
        {
            return Message::PGN::OUTPUT_POWER_DEMAND_ACK;
        }
        else if (!str.compare("PM_REMOTE_MEASURING"))
        {
            return Message::PGN::PM_REMOTE_MEASURING;
        }
        else if (!str.compare("PM_REMOTE_MEASURING_ACK"))
        {
            return Message::PGN::PM_REMOTE_MEASURING_ACK;
        }
        else if (!str.compare("PM_REMOTE_CONTROLLING"))
        {
            return Message::PGN::PM_REMOTE_CONTROLLING;
        }
        else if (!str.compare("PM_REMOTE_CONTROLLING_ACK"))
        {
            return Message::PGN::PM_REMOTE_CONTROLLING_ACK;
        }
        else if (!str.compare("PDU_SELF_TEST"))
        {
            return Message::PGN::PDU_SELF_TEST;
        }
        else if (!str.compare("PDU_SELF_TEST_ACK"))
        {
            return Message::PGN::PDU_SELF_TEST_ACK;
        }

        else
        {
            return Message::PGN::Sentinel;
        }
    }

    static const char* ToString(Type pgn)
    {
        static char unknown[16];

        switch (pgn)
        {
            case Message::PGN::SYNC_TIME:                   return "SYNC_TIME";
            case Message::PGN::VERSION:                     return "VERSION";
            case Message::PGN::VERSION_ACK:                 return "VERSION_ACK";
            case Message::PGN::UPGRADE:                     return "UPGRADE";
            case Message::PGN::UPGRADE_ACK:                 return "UPGRADE_ACK";
            case Message::PGN::RESET:                       return "RESET";
            case Message::PGN::RESET_ACK:                   return "RESET_ACK";
            case Message::PGN::CCU_INFO_CHECK:              return "CCU_INFO_CHECK";
            case Message::PGN::CCU_INFO_CHECK_ACK:          return "CCU_INFO_CHECK_ACK";
            case Message::PGN::BCU_HEART_BEAT:              return "BCU_HEART_BEAT";
            case Message::PGN::PDU_HEART_BEAT:              return "PDU_HEART_BEAT";
            case Message::PGN::CCU_HEART_BEAT:              return "CCU_HEART_BEAT";
            case Message::PGN::CCU_REMOTE_SIGNALLING:       return "CCU_REMOTE_SIGNALLING";
            case Message::PGN::CCU_REMOTE_MEASURING:        return "CCU_REMOTE_MEASURING";
            case Message::PGN::PDU_REMOTE_SIGNALLING:       return "PDU_REMOTE_SIGNALLING";
            case Message::PGN::PDU_REMOTE_MEASURING:        return "PDU_REMOTE_MEASURING";
            case Message::PGN::PDU_SELF_TEST_RESULT:        return "PDU_SELF_TEST_RESULT";
            case Message::PGN::PDU_SELF_TEST_RESULT_ACK:    return "PDU_SELF_TEST_RESULT_ACK";
            case Message::PGN::BCU_REMOTE_SIGNALLING:       return "BCU_REMOTE_SIGNALLING";
            case Message::PGN::CCU_VEHICLE_DATA:            return "CCU_VEHICLE_DATA";
            case Message::PGN::CCU_VEHICLE_DATA_ACK:        return "CCU_VEHICLE_DATA_ACK";
            /*case Message::PGN::PDU_ERRORS:                  return "PDU_ERRORS";
            case Message::PGN::CCU_ERRORS:                  return "CCU_ERRORS";*/
            case Message::PGN::START_CHARGING:              return "START_CHARGING";
            case Message::PGN::START_CHARGING_ACK:          return "START_CHARGING_ACK";
            case Message::PGN::STOP_CHARGING:               return "STOP_CHARGING";
            case Message::PGN::STOP_CHARGING_ACK:           return "STOP_CHARGING_ACK";
            case Message::PGN::AUTHORIZATION:               return "AUTHORIZATION";
            case Message::PGN::AUTHORIZATION_ACK:           return "AUTHORIZATION_ACK";
            case Message::PGN::LOCK_CONNECTOR:              return "LOCK_CONNECTOR";
            case Message::PGN::LOCK_CONNECTOR_ACK:          return "LOCK_CONNECTOR_ACK";
            case Message::PGN::START_CHARGING_RESULT:       return "START_CHARGING_RESULT";
            case Message::PGN::START_CHARGING_RESULT_ACK:   return "START_CHARGING_RESULT_ACK";
            case Message::PGN::STOP_CHARGING_RESULT:        return "STOP_CHARGING_RESULT";
            case Message::PGN::STOP_CHARGING_RESULT_ACK:    return "STOP_CHARGING_RESULT_ACK";
            case Message::PGN::AUTHORIZATION_RESULT:        return "AUTHORIZATION_RESULT";
            case Message::PGN::AUTHORIZATION_RESULT_ACK:    return "AUTHORIZATION_RESULT_ACK";
            case Message::PGN::LOCK_CONNECTOR_RESULT:       return "LOCK_CONNECTOR_RESULT";
            case Message::PGN::LOCK_CONNECTOR_RESULT_ACK:   return "LOCK_CONNECTOR_RESULT_ACK";
            case Message::PGN::OUTPUT_POWER_DEMAND:         return "OUTPUT_POWER_DEMAND";
            case Message::PGN::OUTPUT_POWER_DEMAND_ACK:     return "OUTPUT_POWER_DEMAND_ACK";
            case Message::PGN::PM_REMOTE_MEASURING:         return "PM_REMOTE_MEASURING";
            case Message::PGN::PM_REMOTE_MEASURING_ACK:     return "PM_REMOTE_MEASURING_ACK";
            case Message::PGN::PM_REMOTE_CONTROLLING:       return "PM_REMOTE_CONTROLLING";
            case Message::PGN::PM_REMOTE_CONTROLLING_ACK:   return "PM_REMOTE_CONTROLLING_ACK";
            case Message::PGN::PDU_SELF_TEST:               return "PDU_SELF_TEST";
            case Message::PGN::PDU_SELF_TEST_ACK:           return "PDU_SELF_TEST_ACK";

            default:
            case Message::PGN::Sentinel:
                snprintf(unknown, sizeof(unknown), "%d", pgn);
                return unknown;
        }
    }
};

enum NodeId
{
    BCU_NODE_ID = 0xB0,
    CCU_NODE_ID = 0x01,
    PDU_NODE_ID = 0xD0,
    BROADCAST_NODE_ID = 0xFF,
};

enum Priority
{
    SyncTimePriority = 6,
    VersionPriority = 6,
    VersionAckPriority = 6,
    UpgradePriority = 6,
    UpgradeAckPriority = 6,
    ResetPriority = 6,
    ResetAckPriority = 6,
    CcuInfoCheckPriority = 6,
    CcuInfoCheckAckPriority = 6,
    BcuHeartBeatPriority = 6,
    PduHeartBeatPriority = 6,
    CcuHeartBeatPriority = 6,
    CcuRemoteSignallingPriority = 6,
    CcuRemoteMeasuringPriority = 6,
    PduRemoteSignallingPriority = 6,
    PduRemoteMeasuringPriority = 6,
    PduSelfTestResultPriority = 6,
    PduSelfTestResultAckPriority = 6,
    BcuRemoteSignallingPriority = 6,
    CcuVehicleDataPriority = 6,
    CcuVehicleDataAckPriority = 6,
    PduErrorsPriority = 4,
    CcuErrorsPriority = 4,

    StartChargingPriority = 4,
    StartChargingAckPriority = 4,
    StopChargingPriority = 4,
    StopChargingAckPriority = 4,
    AuthorizationPriority = 4,
    AuthorizationAckPriority = 4,
    LockConnectorPriority = 6,
    LockConnectorAckPriority = 6,

    StartChargingResultPriority = 4,
    StartChargingResultAckPriority = 4,
    StopChargingResultPriority = 4,
    StopChargingResultAckPriority = 4,
    AuthorizationResultPriority = 4,
    AuthorizationResultAckPriority = 4,
    LockConnectorResultPriority = 4,
    LockConnectorResultAckPriority = 4,

    OutputPowerDemandPriority = 6,
    OutputPowerDemandAckPriority = 6,
    PmRemoteMeasuringPriority = 6,
    PmRemoteMeasuringAckPriority = 6,
    PmRemoteControllingPriority = 6,
    PmRemoteControllingAckPriority = 6,
    PduSelfTestPriority = 6,
    PduSelfTestAckPriority = 6,
};

enum Interval
{
    SyncTimeIntervalMs = (uint32_t)(12 * 60 * 60 * 1000),
    VersionIntervalMs = 500,
    VersionAckIntervalMs = 500,
    UpgradeIntervalMs = 500,
    UpgradeAckIntervalMs = 500,
    ResetIntervalMs = 500,
    ResetAckIntervalMs = 500,
    CcuInfoCheckIntervalMs = 1000,
    CcuInfoCheckAckIntervalMs = 1000,
    BcuHeartBeatIntervalMs = 1000,
    PduHeartBeatIntervalMs = 1000,
    CcuHeartBeatIntervalMs = 1000,
    CcuRemoteSignallingIntervalMs = 500,
    CcuRemoteMeasuringIntervalMs = 1000,
    PduRemoteSignallingIntervalMs = 500,
    PduRemoteMeasuringIntervalMs = 1000,
    PduSelfTestResultIntervalMs = 500,
    PduSelfTestResultAckIntervalMs = 500,
    CcuVehicleAckIntervalMs = 1000,    // TODO: It only needs to be sent once when receive vehicle data
    BcuRemoteSignallingIntervalMs = 1000,
    PduErrorsIntervalMs = 500,
    CcuErrorsIntervalMs = 500,

    StartChargingIntervalMs = 250,
    StartChargingAckIntervalMs = 250,
    StopChargingIntervalMs = 250,
    StopChargingAckIntervalMs = 250,
    AuthorizationIntervalMs = 500,
    AuthorizationAckIntervalMs = 500,
    LockConnectorIntervalMs = 500,
    LockConnectorAckIntervalMs = 500,

    StartChargingResultIntervalMs = 500,
    StartChargingResultAckIntervalMs = 500,
    StopChargingResultIntervalMs = 500,
    StopChargingResultAckIntervalMs = 500,
    AuthorizationResultIntervalMs = 500,
    AuthorizationResultAckIntervalMs = 500,
    LockConnectorResultIntervalMs = 500,
    LockConnectorResultAckIntervalMs = 500,

    OutputPowerDemandIntervalMs = 500,
    OutputPowerDemandAckIntervalMs = 500,
    PmRemoteMeasuringIntervalMs = 500,
    PmRemoteMeasuringAckIntervalMs = 500,
    PmRemoteControllingIntervalMs = 500,
    PmRemoteControllingAckIntervalMs = 500,
    PduSelfTestIntervalMs = 500,
    PduSelfTestAckIntervalMs = 500,
};

enum _TimeoutMsDefault
{
    TimeoutMsDefault0 = -1, // means never timeout
    TimeoutMsDefault1 = 2000,
    TimeoutMsDefault2 = 5000,
    TimeoutMsDefault3 = 60000,
    TimeoutMsDefault4 = 120000,
};

enum _ErrorCode
{
    EC_NO_ERROR = 0,
    EC_CCU_EMERGENCY_STOP = 100,
    EC_CCU_SMOKING_SENSOR_ALARM = 101,
    EC_CCU_AC_CONTACTOR_FAULT = 102,
    EC_CCU_DC_PLUS_CONTACTOR_FAULT = 103,
    EC_CCU_WATER_IMMERSION_ALARM = 104,
    EC_CCU_CONNECTOR_LOCK_FAULT = 105,
    EC_CCU_CONTACTOR_OUTSIDE_VOLTAGE_FAULT = 106,
    EC_CCU_ISOLATION_COMM_FAULT = 107,
    EC_CCU_ISOLATION_DETECT_FAULT = 108,
    EC_CCU_ISOLATION_INVERSED_FAULT = 109,
    EC_CCU_HUMIDITY_ALARM = 110,
    EC_CCU_CONNECTOR_OVER_TEMPERATURE_FAULT = 112,
    EC_CCU_CONNECTOR_NOT_AT_POSITION = 113,
    EC_CCU_INPUT_OVER_VOLTAGE = 115,
    EC_CCU_INPUT_UNDER_VOLTAGE = 116,
    EC_CCU_OUTPUT_OVER_VOLTAGE = 117,
    EC_CCU_OUTPUT_UNDER_VOLTAGE = 118,
    EC_CCU_OUTPUT_OVER_CURRENT = 119,
    EC_CCU_ACDC_MODULE_FAULT = 120,
    EC_CCU_ACDC_MODULE_AC_FAULT = 121,
    EC_CCU_ACDC_MODULE_AC_OVER_VOLTAGE = 122,
    EC_CCU_ACDC_MODULE_AC_UNDER_VOLTAGE = 123,
    EC_CCU_ACDC_MODULE_AC_PHASE_LOST = 124,
    EC_CCU_ACDC_MODULE_DC_SHORT_CIRCUIT = 125,
    EC_CCU_ACDC_MODULE_DC_OVER_CURRENT = 126,
    EC_CCU_ACDC_MODULE_DC_OVER_VOLTAGE = 127,
    EC_CCU_ACDC_MODULE_DC_UNDER_VOLTAGE = 128,
    EC_CCU_ACDC_MODULE_OVER_TEMPERATURE = 129,
    EC_CCU_ACDC_MODULE_COMM_FAULT = 130,
    EC_CCU_ACDC_MODULE_FAN_FAULT = 131,
    EC_CCU_DC_MINUS_CONTACTOR_FAULT = 132,
    EC_CCU_DC_PLUS_CASCADED_CONTACTOR_FAULT = 133,
    EC_CCU_DC_MINUS_CASCADED_CONTACTOR_FAULT = 134,
    EC_CCU_DC_CONVERT_CONTACTOR_FAULT = 135,
    EC_CCU_ACDC_MODULE_PARTIAL_COMM_FAULT = 136,
    EC_CCU_SMOKING_SENSOR_COMM_FAULT = 139,
    EC_CCU_WATER_IMMERSION_SENSOR_COMM_FAULT = 140,
    EC_CCU_HUMITURE_SENSOR1_COMM_FAULT = 141,
    EC_CCU_HUMITURE_SENSOR2_COMM_FAULT = 142,
    EC_CCU_DOOR_FAULT = 144,
    EC_CCU_DISCHARGING_FAULT = 145,
    EC_CCU_ISOLATION_ALARM = 146,
    EC_CCU_CONNECTOR_OVER_TEMPERATURE_ALARM = 148,
    EC_CCU_CONNECTOR_CC1_ALARM = 151,
    EC_CCU_ENERGY_METER_COMM_FAULT = 152,
    EC_CCU_COMM_FAULT = 153,
    EC_CCU_ENERGY_DATA_ABNORMAL = 154,
    EC_CCU_DC_FUSE_PLUS_FAULT = 156,
    EC_CCU_DC_FUSE_MINUS_FAULT = 157,
    EC_CCU_OVER_TEMPERATURE_ALARM = 158,
    EC_CCU_OVER_TEMPERATURE_FAULT = 159,
    EC_CCU_FAN1_FAULT = 160,
    EC_CCU_FAN2_FAULT = 161,
    EC_CCU_FAN3_FAULT = 162,
    EC_CCU_FAN4_FAULT = 163,
    EC_CCU_FAN5_FAULT = 164,
    EC_CCU_FAN6_FAULT = 165,
    EC_CCU_BCU_COMM_LOST = 180,
    EC_CCU_PDU_COMM_LOST = 181,
    EC_CCU_PARAM_ABNORMAL = 182,
    EC_CCU_LIQUID_LEVER_FAULT = 183,
    EC_CCU_LIQUID_COOLER_COMM_FAULT = 184,
    EC_CCU_LIQUID_SWITCH_FAULT = 185,
    EC_CCU_LIQUID_INPUT_TEMPERATURE_SENSOR_FAULT = 186,
    EC_CCU_LIQUID_OUTPUT_TEMPERATURE_SENSOR_FAULT = 187,
    EC_CCU_LIQUID_OUTPUT_FLOW_SENSOR_FAULT = 188,
    EC_CCU_LIQUID_OUTPUT_PRESSURE_SENSOR_FAULT = 189,
    EC_CCU_LOOP_PUMP_FAULT = 190,
    EC_CCU_SPEED_DRAUGHT_FANS_FAULT = 191,
    EC_CCU_GUN_TEMPERATURE_FAULT = 192,
    EC_CCU_ENVIROMENT_TEMPERATURE_FAULT = 193,
    EC_CCU_COOLER_SOURCE_TEMPERATURE_FAULT = 194,
    EC_CCU_COOLER_SOURCE_PRESSURE_OVER_LIMIT = 195,
    EC_CCU_COOLER_SOURCE_PRESSURE_LOWER_LIMIT = 196,
    EC_CCU_COOLER_FLOW_HIGH = 197,
    EC_CCU_COOLER_FLOW_LOW = 198,
    EC_CCU_COOLER_PUMP_OVER_TEMPERATURE = 199,
    EC_CCU_COOLER_PUMP_STALL = 200,
    EC_CCU_COOLER_PUMP_OVER_PRESSURE = 201,
    EC_CCU_COOLER_PUMP_OVER_CURRENT = 202,
    EC_CCU_COOLER_PUMP_COM_LOSS = 203,
    EC_CCU_PDU_WORK_STATE_NOTMATCH = 204,
    EC_CCU_BCL_REQCUR_OVER_BCP_MAXALLOWED = 205,

    EC_PDU_EMERGENCY_STOP = 300,
    EC_PDU_DOOR_ALARM = 301,
    EC_PDU_INPUT_OVER_VOLTAGE = 302,
    EC_PDU_INPUT_UNDER_VOLTAGE = 303,
    EC_PDU_OUTPUT_OVER_VOLTAGE = 304,
    EC_PDU_OUTPUT_OVER_CURRENT = 305,
    EC_PDU_DC_FUSE1_FAULT = 306,
    EC_PDU_DC_FUSE2_FAULT = 307,
    EC_PDU_DC_FUSE3_FAULT = 308,
    EC_PDU_DC_FUSE4_FAULT = 309,
    EC_PDU_ENV_COOLER1_COMM_FAULT = 310,
    EC_PDU_ENV_COOLER1_DORR_FAULT = 311,
    EC_PDU_ENV_COOLER1_COMPRESSOR_FAULT = 312,
    EC_PDU_ENV_COOLER2_COMM_FAULT = 313,
    EC_PDU_ENV_COOLER2_DORR_FAULT = 314,
    EC_PDU_ENV_COOLER2_COMPRESSOR_FAULT = 315,
    EC_PDU_RCD1_FAULT = 316,
    EC_PDU_RCD2_FAULT = 317,
    EC_PDU_SPD1_FAULT = 318,
    EC_PDU_SPD2_FAULT = 319,
    EC_PDU_AC_CONTACTOR1_FAULT = 320,
    EC_PDU_AC_CONTACTOR2_FAULT = 321,
    EC_PDU_ONBOARD_FAULT = 322,
    EC_PDU_DISTURBANCE_FAN1_FAULT = 323,
    EC_PDU_DISTURBANCE_FAN2_FAULT = 324,
    EC_PDU_DISTURBANCE_FAN3_FAULT = 325,
    EC_PDU_SMOKING_SENSOR_COMM_FAULT = 326,
    EC_PDU_SMOKING_SENSOR_ALARM = 327,
    EC_PDU_TEMPERATURE_SENSOR_COMM_FAULT = 328,
    EC_PDU_TEMPERATURE_SENSOR_ALARM = 329,
    EC_PDU_WATER_IMMERSION_SENSOR_COMM_FAULT = 330,
    EC_PDU_WATER_IMMERSION_SENSOR_ALARM = 331,
    EC_PDU_HUMIDITY_SENSOR_COMM_FAULT = 332,
    EC_PDU_HUMIDITY_SENSOR_ALARM = 333,
    EC_PDU_MATRIX_SWITCH_FAULT = 334,
    EC_PDU_POWER_MODULES_FAULT = 335,
    EC_PDU_POWER_MODULES_COMM_FAULT = 336,
    EC_PDU_POWER_MODULE_FAN_FAULT = 337,
    EC_PDU_POWER_MODULE_OVER_TEMPERATURE = 338,
    EC_PDU_POWER_MODULT_AC_FAULT = 339,
    EC_PDU_POWER_MODULE_DC_SHORT_CIRCUIT = 340,
    EC_PDU_POWER_MODULE_DC_OVER_CURRENT = 341,
    EC_PDU_POWER_MODULE_DC_OVER_VOLTAGE = 342,
    EC_PDU_POWER_MODULE_DC_UNDER_VOLTAGE = 343,
    EC_PDU_POWER_MODULE_AC_OVER_VOLTAGE = 344,
    EC_PDU_POWER_MODULE_AC_UNDER_VOLTAGE = 345,
    EC_PDU_POWER_MODULE_AC_PHASE_LOST = 346,
    EC_PDU_POWER_MODULE_PARTIAL_FAULT = 347,
    EC_PDU_POWER_MODULE_PARTIAL_COMM_FAULT = 348,
    EC_PDU_POWER_MODULE_GROUP_ADDRESS_ERROR = 349,
    EC_PDU_PARAM_ERROR = 350,
    EC_PDU_ALTITUDE_SETTING_ERROR = 351,
    EC_PDU_POWER_DISTRIBUTION_ERROR = 352,
    EC_PDU_POWER_MODULE_ADDRESS_ERROR = 353,
    EC_PDU_POWER_ALLOCATION_TIMEOOUT = 354,
    EC_PDU_GLOBAL_INTERLOCK_FAULT = 355,

    EC_UNKNOWN_ERROR = 65535,
};

#pragma pack(1)

//Message::PGN::SYNC_TIME, 0x0100
typedef union _tSyncTime
{
    struct
    {
        uint16_t milliseconds;
        uint8_t  minutes : 6;
        uint8_t  reserved1 : 2;
        uint8_t  hours : 5;
        uint8_t  reserved2 : 3;
        uint8_t  mdays : 5;
        uint8_t  wdays : 3;
        uint8_t  months : 4;
        uint8_t  reserved3 : 4;
        uint8_t  years : 7;
        uint8_t  reserved4 : 1;
    }fields;

    uint8_t data[7];
}tSyncTime;

//Message::PGN::VERSION, 0x0200
typedef union _tVersion
{
    struct
    {
        uint8_t minorNo : 4;
        uint8_t majorNo : 4;
    }protocolVersion;

    uint8_t data;
}tVersion;

//Message::PGN::VERSION_ACK, 0x0300
typedef union _tVersionAck
{
    struct
    {
        struct
        {
            uint8_t minorNo : 4;
            uint8_t majorNo : 4;
        }protocolVersion;

        struct
        {
            uint8_t  majorNo;
            uint8_t  minorNo;
            uint8_t  revisionNo;
            uint16_t buildNo;
        }firmwareVersion;

        struct
        {
            uint8_t  pcbNo;
            uint8_t  pcbaNo;
        }hardwareVersion;

        uint32_t     boardNo;
        uint8_t      cabinetNo[20];
    }fields;

    uint8_t data[32];
}tVersionAck;

//Message::PGN::UPGRADE, 0x2200
typedef union _tUpgrade
{
    struct
    {
        struct
        {
            uint8_t majorNo;
            uint8_t minorNo;
            uint8_t revisionNo;
        }version;

        uint32_t timestamp;
    }fields;

    uint8_t data[7];
}tUpgrade;

//Message::PGN::UPGRADE_ACK, 0x2300
typedef struct _tUpgradeAck
{
    uint8_t result; // 0-disable, 1-enable
}tUpgradeAck;

//Message::PGN::RESET, 0x2400
typedef union _tReset
{
    struct
    {
        uint8_t  reason;
    }fields;

    uint8_t data[1];

}tReset;

//Message::PGN::RESET_ACK, 0x2500
typedef struct _tResetAck
{
    uint8_t result;  // 0-refused, 1-reset immediately
}tResetAck;

enum _RebootReason
{
    REASON_NORMAL = 0,
    REASON_POWER_ON,
    REASON_REMOTE_BOOT,
    REASON_UPGRADE,
    REASON_WATCHDOG,
    REASON_PROGRAM_ABNORMAL,
};

//Message::PGN::CCU_INFO_CHECK, 0x2C00
typedef struct _tCcuInfoCheck
{
    uint8_t Check;
}tCcuInfoCheck;

//Message::PGN::CCU_INFO_CHECK_ACK, 0x2D00
typedef struct _tCcuInfoCheckAck
{
    uint8_t CustomerId;
    uint8_t CustomerSn[30];
}tCcuInfoCheckAck;

typedef union _tClientHeartBeatStates
{
    struct
    {
        uint16_t client1 : 1; // 0-normal, 1-timeout
        uint16_t client2 : 1; // 0-normal, 1-timeout
        uint16_t client3 : 1; // 0-normal, 1-timeout
        uint16_t client4 : 1; // 0-normal, 1-timeout
        uint16_t client5 : 1; // 0-normal, 1-timeout
        uint16_t client6 : 1; // 0-normal, 1-timeout
        uint16_t client7 : 1; // 0-normal, 1-timeout
        uint16_t client8 : 1; // 0-normal, 1-timeout
        uint16_t client9 : 1; // 0-normal, 1-timeout
        uint16_t client10 : 1; // 0-normal, 1-timeout
        uint16_t client11 : 1; // 0-normal, 1-timeout
        uint16_t client12 : 1; // 0-normal, 1-timeout
        uint16_t client13 : 1; // 0-normal, 1-timeout
        uint16_t client14 : 1; // 0-normal, 1-timeout
        uint16_t client15 : 1; // 0-normal, 1-timeout
        uint16_t client16 : 1; // 0-normal, 1-timeout
    }fields;

    uint16_t data;
}tClientHeartBeatStates;

//Message::PGN::BCU_HEART_BEAT, 0x4000
typedef union _tBcuHeartBeat
{
    struct
    {
        uint16_t seqNo;
        uint8_t  state;             //0-normal, 1-fault, 255-reboot
        uint8_t  rebootReason;      // 0-normal, 1-power on, 2-remote reboot, 3-upgrade, 4-watchdog, 5-program abnormal
        uint8_t  numOfOnlineBoards;
        uint8_t  pduHeartBeatState;         // 0-normal, 1-timeout
        tClientHeartBeatStates clientHeartBeatStates;
    }fields;

    uint8_t data[8];
}tBcuHeartBeat;

//Message::PGN::PDU_HEART_BEAT, 0x4100
typedef union _tPduHeartBeat
{
    struct
    {
        uint16_t seqNo;
        uint8_t  state; // 0-normal, 1-fault, 255-reboot
        uint8_t  rebootReason;      // 0-normal, 1-power on, 2-remote reboot, 3-upgrade, 4-watchdog, 5-program abnormal
        uint8_t  bcuHeartBeatState;  // 0-normal, 1-timeout
        uint8_t  numOfOnlineClients;
        tClientHeartBeatStates clientHeartBeatStates;
    }fields;

    uint8_t data[8];
}tPduHeartBeat;

//Message::PGN::CCU_HEART_BEAT, 0x4200
typedef union _tCcuHeartBeat
{
    struct
    {
        uint16_t seqNo;
        uint8_t  state; // 0-normal, 1-fault, 255-reboot
        uint8_t  rebootReason;      // 0-normal, 1-power on, 2-remote reboot, 3-upgrade, 4-watchdog, 5-program abnormal
        uint8_t  bcuHeartBeatState; // 0-normal, 1-timeout
        uint8_t  pduHeartBeatState; // 0-normal, 1-timeout
    }fields;

    uint8_t data[6];
}tCcuHeartBeat;

enum _tCcuWorkingState
{
    STATE_IDLE = 0,
    STATE_PREPARING,
    STATE_CHARGING,
    STATE_STOPPING,
    STATE_WARNING,
    STATE_FAULT,
};

//Message::PGN::CCU_REMOTE_SIGNALLING, 0x4300
typedef union _tCcuRemoteSignalling
{
    struct
    {
        uint8_t workingState : 3;
        uint8_t vehicleConnected : 1;             // 0-disconnected, 1-connected
        uint8_t emergencyButtonPressed : 1;       // 0-released, 1-pressed
        uint8_t doorOpenAlarm : 1;                // 0-closed, 1-open
        uint8_t outputOverVoltage1 : 1;           // 0-normal, 1-alarm
        uint8_t outputUnderVoltage : 1;           // 0-normal, 1-alarm

        uint8_t outputOverCurrent1 : 1;           // 0-normal, 1-alarm
        uint8_t connectorLockAlarm : 1;           // 0-normal, 1-alarm
        uint8_t dcPlusContactorAlarm : 1;         // 0-normal, 1-alarm
        uint8_t dcMinusContactorAlarm : 1;        // 0-normal, 1-alarm
        uint8_t connectorPositionAlarm : 1;       // 0-normal, 1-alarm
        uint8_t cc1LevelAlarm : 1;                // 0-normal, 1-alarm
        uint8_t overTemperatureAlarm : 1;         // 0-normal, 1-alarm
        uint8_t overTemperatureFault : 1;         // 0-normal, 1-alarm

        uint8_t connectorTemperatureAlarm : 1;    // 0-normal, 1-alarm
        uint8_t connectorTemperatureFault : 1;    // 0-normal, 1-alarm
        uint8_t smokingAlarm : 1;                 // 0-normal, 1-alarm
        uint8_t waterImmersionAlarm : 1;          // 0-normal, 1-alarm
        uint8_t humitdtyAlarm : 1;                // 0-normal, 1-alarm
        uint8_t coolingFanAlarm : 1;              // 0-normal, 1-alarm
        uint8_t disturbedFlowFanAlarm : 1;        // 0-normal, 1-alarm
        uint8_t bcuCommLost : 1;                  // 0-normal, 1-alarm

        uint8_t pduCommLost : 1;                  // 0-normal, 1-alarm
        uint8_t energyMeterCommFault : 1;         // 0-normal, 1-alarm
        uint8_t humitureSensorCommFault : 1;      // 0-normal, 1-alarm
        uint8_t isolationDetectAlarm : 1;
        uint8_t liquidLevelAbnormal : 1;
        uint8_t coolingSourceCommFault : 1;             // 0-normal, 1-alarm
        uint8_t liquidLevelSwitchFault : 1;
        uint8_t liquidInputTempSensorFault : 1;

        uint8_t liquidOutputTempSensorFault : 1;
        uint8_t liquidOutputFlowSensorFault : 1;
        uint8_t liquidOutputFlowPressureSensorFault : 1;
        uint8_t loopPumpFault : 1;
        uint8_t variableSpeedFansFault : 1;
        uint8_t gunTempFault : 1;
        uint8_t environmentTempFault : 1;
        uint8_t liquidCoolerTempFault : 1;

        uint8_t liquidCoolerPressureOverLimit : 1;
        uint8_t liquidCoolerPressureLowerLimit : 1;
        uint8_t outputOverVoltage2 : 1;                  // 0-normal, 1-alarm
        uint8_t outputOverCurrent2 : 1;                  // 0-normal, 1-alarm
        uint8_t dcFuseFault : 1;                         // 0-normal, 1-alarm
        uint8_t matrixSwitchFault : 1;                   // 0-normal, 1-alarm
        uint8_t powerModuleFanFault : 1;                 // 0-normal, 1-alarm
        uint8_t powerModuleOverTemperature : 1;          // 0-normal, 1-alarm

        uint8_t powerModuleAcInputFault : 1;             // 0-normal, 1-alarm
        uint8_t powerModuleOutputShortCircuit : 1;       // 0-normal, 1-alarm
        uint8_t powerModuleOutputOverCurrent : 1;        // 0-normal, 1-alarm
        uint8_t powerModuleOutputOverVoltage : 1;        // 0-normal, 1-alarm
        uint8_t powerModuleOutputUnderVoltage : 1;       // 0-normal, 1-alarm
        uint8_t powerModuleInputOverVoltage : 1;         // 0-normal, 1-alarm
        uint8_t powerModuleInputUnderVoltage : 1;        // 0-normal, 1-alarm
        uint8_t powerModuleAcInputPhaseLost : 1;         // 0-normal, 1-alarm

        uint8_t someOfPowerModulesFault : 1;             // 0-normal, 1-alarm
        uint8_t someOfPowerModulesCommFault : 1;         // 0-normal, 1-alarm
        uint8_t powerModuleGroupAddressError : 1;        // 0-normal, 1-alarm
        uint8_t powerDistributionError : 1;              // 0-normal, 1-alarm
        uint8_t paramError : 1;                          // 0-normal, 1-alarm
        uint8_t powerModuleAddressError : 1;             // 0-normal, 1-alarm
        uint8_t connectorLockState :1;                   // 0-unlock, 1-lock
        uint8_t coolingFlowHigh : 1;                     // 0-normal, 1-alarm

        uint8_t coolingFlowLow : 1;                      // 0-normal, 1-alarm
        uint8_t circulatingPumpOverTemperature : 1;      // 0-normal, 1-alarm
        uint8_t circulatingPumpStall : 1;                // 0-normal, 1-alarm
        uint8_t circulatingPumpOverPressure : 1;         // 0-normal, 1-alarm
        uint8_t circulatingPumpOverCurrent : 1;          // 0-normal, 1-alarm
        uint8_t circulatingPumpComLoss : 1;              // 0-normal, 1-alarm
        uint8_t pduWorkStateNotMatch : 1;                // 0-normal, 1-alarm
        uint8_t ContactorOutsideVoltageAbnormal : 1;     // 0-normal, 1-alarm

        uint8_t bclOverBcpMaxAllowedCurrent : 1;         // 0-normal, 1-alarm
        uint8_t reserved : 7;
    }fields;

    uint8_t data[10];
}tCcuRemoteSignalling;

//Message::PGN::CCU_REMOTE_MEASURING, 0x4400
typedef union _tCcuRemoteMeasuring
{
    struct
    {
        uint16_t dcOutputVoltage;                 // 0-1000V, precision: 0.1V/bit
        uint16_t dcOutputCurrent;                 // 0-650A, precision: 0.1A/bit
        uint8_t  cc1Voltage;                      // 0-24V, precision: 0.1V/bit
        uint8_t  socLevel;                        // 0-100
        uint16_t bmsMeasuredVoltage;              // 0-1000V, precision: 0.1V/bit
        uint16_t bmsMeasuredCurrent;              // 0-650A, precision: 0.1A/bit
        uint16_t bmsVoltageDemand;                // 0-1000V, 0.1V
        uint16_t bmsCurrentDemand;                // 0-650A, 0.1A
        uint16_t remainingChargingTime;           // 0-600min, 1min/bit
        uint8_t  dcPlusConnectorTemperature;      // [-50, +200]℃, offset: -50℃, precision: 1℃
        uint8_t  dcMinusConnectorTemperature;     // [-50, +200]℃, offset: -50℃, precision: 1℃
        uint8_t  cabinetTemperature;              // [-50, +200]℃, offset: -50℃, precision: 1℃
        uint8_t  cabinetHumidity;                 // 0-100
        uint16_t energyMeterVoltage;              // 0-1000V, 0.1V
        uint32_t energyMeterCurrent;              // 0-650A, 0.001A
        uint32_t totalEnergyKwh;                  // 0-650Kwh, 0.001Kwh
        uint8_t  bmsAuxSupplyVoltage;             // 0-24V, 0.1V
        uint8_t  boardTemperature;                // [-50, +200]℃, offset: -50℃, precision: 1℃
        uint8_t  liquidCoolerInflowTemperature;   // [-50, +200]℃, offset: -50℃, precision: 1℃
        uint8_t  liquidCoolerOutflowTemperature;  // [-50, +200]℃, offset: -50℃, precision: 1℃
        uint8_t  liquidPressure;
        uint8_t  liquidFlowRate;
    }fields;

    uint8_t data[36];
}tCcuRemoteMeasuring;

//Message::PGN::PDU_REMOTE_SIGNALLING, 0x4500
typedef union _tPduRemoteSignalling
{
    struct
    {
        uint8_t emergencyButtonPressed : 1;              // 0-normal, 1-pressed
        uint8_t doorOpenAlarm : 1;                       // 0-closed, 1-open
        uint8_t inputOverVoltage : 1;                    // 0-normal, 1-alarm
        uint8_t inputUnderVoltage : 1;                   // 0-normal, 1-alarm
        uint8_t environmentCooler1CommFault : 1;         // 0-normal, 1-alarm
        uint8_t environmentCooler1DoorAlarm : 1;         // 0-normal, 1-alarm
        uint8_t environmentCooler1CompressorFault : 1;   // 0-normal, 1-alarm
        uint8_t environmentCooler2CommFault : 1;         // 0-normal, 1-alarm

        uint8_t environmentCooler2DoorAlarm : 1;         // 0-normal, 1-alarm
        uint8_t environmentCooler2CompressorFault : 1;   // 0-normal, 1-alarm
        uint8_t rcd1Fault : 1;                           // 0-normal, 1-alarm
        uint8_t rcd2Fault : 1;                           // 0-normal, 1-alarm
        uint8_t SPD1Fault : 1;                           // 0-normal, 1-alarm
        uint8_t SPD2Fault : 1;                           // 0-normal, 1-alarm
        uint8_t acContactor1Fault : 1;                   // 0-normal, 1-alarm
        uint8_t acContactor2Fault : 1;                   // 0-normal, 1-alarm

        uint8_t onBoardFault : 1;                        // 0-normal, 1-alarm
        uint8_t disturbedFlowFan1Alarm : 1;              // 0-normal, 1-alarm
        uint8_t disturbedFlowFan2Alarm : 1;              // 0-normal, 1-alarm
        uint8_t disturbedFlowFan3Alarm : 1;              // 0-normal, 1-alarm
        uint8_t smokingSensorCommFault : 1;              // 0-normal, 1-alarm
        uint8_t smokingSensorAlarm : 1;                  // 0-normal, 1-alarm
        uint8_t temperatureSensorCommFault : 1;          // 0-normal, 1-alarm
        uint8_t temperatureSensorAlarm : 1;              // 0-normal, 1-alarm

        uint8_t waterImmersionSensorCommFault : 1;       // 0-normal, 1-alarm
        uint8_t waterImmersionSensorAlarm : 1;           // 0-normal, 1-alarm
        uint8_t humiditySensorCommFault : 1;             // 0-normal, 1-alarm
        uint8_t humiditySensorAlarm : 1;                 // 0-normal, 1-alarm
        uint8_t allPowerModulesFault : 1;                // 0-normal, 1-alarm
        uint8_t allPowerModulesCommFault : 1;            // 0-normal, 1-alarm
        uint8_t paramError : 1;                          // 0-normal, 1-alarm
        uint8_t altitudeSettingError : 1;                // 0-normal, 1-alarm

        uint8_t powerAllocationTimeout : 1;              // 0-normal, 1-alarm
        uint8_t globalInterlockFault : 1;                // 0-normal, 1-alarm
        uint8_t reserved : 6;
    }fields;

    uint8_t data[5];

}tPduRemoteSignalling;

#define GET_AC_INPUT_VOLTAGE_PHASEA(voltageHi, voltageLo)   ((uint16_t)((((voltageHi) << 8) & 0x01) + ((voltageLo) & 0xFF)))
#define GET_AC_INPUT_VOLTAGE_PHASEB(voltageHi, voltageLo)   ((uint16_t)((((voltageHi) << 7) & 0x03) + ((voltageLo) & 0x7F)))
#define GET_AC_INPUT_VOLTAGE_PHASEC(voltageHi, voltageLo)   ((uint16_t)((((voltageHi) << 6) & 0x07) + ((voltageLo) & 0x3F)))

//Message::PGN::PDU_REMOTE_MEASURING, 0x4600
typedef union _tPduRemoteMeasuring
{
    struct
    {
        uint8_t  ambientTemperature;          // [-50, +200]℃, offset: -50℃, precision: 1℃
        uint16_t dcOutputVoltage;             // 0-1000V, precision: 0.1V/bit
        uint16_t dcOutputCurrent;             // [-3000, 0]A offset: -3000A, precision: 0.1A/bit
        uint32_t acInputVoltagePhaseALo : 8;  // 0-500V, precision: 1V/bit
        uint32_t acInputVoltagePhaseAHi : 1;  // 0-500V, precision: 1V/bit
        uint32_t acInputVoltagePhaseBLo : 7;  // 0-500V, precision: 1V/bit
        uint32_t acInputVoltagePhaseBHi : 2;  // 0-500V, precision: 1V/bit
        uint32_t acInputVoltagePhaseCLo : 6;  // 0-500V, precision: 1V/bit
        uint32_t acInputVoltagePhaseCHi : 3;  // 0-500V, precision: 1V/bit
        uint32_t reserved : 5;
    }fields;

    uint8_t data[9];

}tPduRemoteMeasuring;

enum _SelfTestResult
{
    SelfTestResultNormal = 0,
    SelfTestResultWarning = 1,
    SelfTestResultFault = 2,
    SelfTestResultNotTest = 3,
    SelfTestResultAbortedByClient = 11,
    SelfTestResultAbortedByHost = 12,
};

typedef struct _tDcContactorSelfTestDetails
{
    uint8_t generalResult;          // 0-normal, 1-warning, 2-fault
    uint8_t numberOfDcContactors;
    uint8_t details[0];
}tDcContactorSelfTestDetails;

typedef struct _tPowerModuleSelfTestDetails
{
    uint8_t generalResult;         // 0-normal, 1-warning, 2-fault
    uint8_t numberOfPowerModules;
    uint8_t details[0];
}tPowerModuleSelfTestDetails;

typedef struct _tIsolationModuleSelfTestDetails
{
    uint8_t generalResult;           // 0-normal, 1-warning, 2-fault
    uint8_t communicationState : 2;  // 0-normal, 1-warning, 2-fault, 3-unknown
    uint8_t runningState       : 2;  // 0-normal, 1-warning, 2-fault, 3-unknown
    uint8_t reserved           : 4;  // 0-normal, 1-warning, 2-fault, 3-unknown
}tIsolationModuleSelfTestDetails;

typedef struct _tMiscSelfTestDetails
{
    uint8_t acRelayResult : 2;  // 0-normal, 1-warning, 2-fault, 3-unknown
    uint8_t coolerResult  : 2;  // 0-normal, 1-warning, 2-fault, 3-unknown
    uint8_t resvered      : 4;
}tMiscSelfTestDetails;

//Message::PGN::PDU_SELF_TEST_RESULT, 0x4800
typedef struct _tPduSelfTestResult
{
    uint32_t identifier;
    uint8_t  mode;                      // 0-timed self-test, 1-remote self-test
    uint8_t  result;                    // reference to _SelfTestResult

    struct
    {
        uint8_t  generalResult;         // 0-normal, 1-warning, 2-fault
        uint16_t memoryResult;          // 0-normal, 1-warning, 2-fault, 3-unknown
        uint16_t flashResult;           // 0-normal, 1-warning, 2-fault, 3-unknown
        uint16_t samplingCurcuitResult; // 0-normal, 1-warning, 2-fault, 3-unknown
        uint16_t reserved;
        uint16_t memoryUsagePercentage; // [0.00, 100.00]%, offset: 0%, precision: 0.01%/bit
        uint16_t flashUsagePercentage;  // [0.00, 100.00]%, offset: 0%, precision: 0.01%/bit
        uint8_t  maxMcuTemperature;     // [-50, 200]℃, offset: -50℃, precision: 1℃/bit
        uint32_t runningTimeSeconds;
        uint8_t  unexpectedRebootingTimes; // 0-255
    }pduBoardDetail;

    uint8_t otherDetails[0];
}tPduSelfTestResult;

//Message::PGN::PDU_SELF_TEST_RESULT_ACK, 0x4900
typedef union _tPduSelfTestResultAck
{
    struct
    {
        uint32_t identifier;
        uint8_t  result;      // 0-successful, 1-failed
    }fields;

    uint8_t data[5];
}tPduSelfTestResultAck;

//Message::PGN::CCU_VEHICLE_DATA, 0x4E00
typedef struct _tCcuVehicleData
{
    char vin[20];
}tCcuVehicleData;

//Message::PGN::CCU_VEHICLE_DATA_ACK, 0x4F00
typedef struct _tCcuVehicleDataAck
{
    uint8_t result;
}tCcuVehicleDataAck;

enum _InternetLinkType
{
    ILINK_TYPE_MODEM = 0,
    ILINK_TYPE_ETHERNET,
    ILINK_TYPE_INVALID
};

enum _InternetLinkStatus
{
    ILINK_STATUS_DISCONNECTED = 0,
    ILINK_STATUS_CONNECTED,
};

enum _ModemSignalStrength
{
    MIN_SIGNAL_STRENGTH = 0,
    MAX_SIGNAL_STRENGTH = 4,
};

//Message::PGN::BCU_REMOTE_SIGNALLING, 0x4A00
typedef union _tBcuRemoteSignalling
{
    struct
    {
        uint8_t  internet_link_type : 2;  // 0-4G, 1-ethernet
        uint8_t  signal_strength    : 3;  // ethernet: 0-disconnected, 1-connected
                                         // 4G modem: 0-disconnected, 1~4 - signal strength level
        uint8_t  backend_connected  : 1;  // 0-disconnected, 1-connected
        uint8_t  reserved0          : 2;
        uint8_t  reserved1[7];
    }fields;

    uint8_t data[8];
}tBcuRemoteSignalling;

//Message::PGN::PDU_ERRORS, 0x5000
/*typedef union _tPduErrors
{
    struct
    {

    }fields;

    uint8_t data[];

}tPduErrors;

//Message::PGN::CCU_ERRORS, 0x5100
typedef union _tCcuErrors
{
    struct
    {

    }fields;

    uint8_t data[];

}tCcuErrors;*/

//Message::PGN::START_CHARGING, 0x0400
typedef union _tStartCharging
{
    struct
    {
        uint8_t  userId[20];
        uint32_t outputPower;  //Watt
    }fields;

    uint8_t data[24];
}tStartCharging;

enum _StartChargingAckFlag
{
    StartChargingSuccessful = 0,
    ChargingClientFault = 1,
    ChargingClientInUpgrading = 2,
    otherFault = 255,
};

//Message::PGN::START_CHARGING_ACK, 0x0500
typedef struct _tStartChargingAck
{
    uint8_t result;
}tStartChargingAck;

enum _EndCode
{
    SwipeCard = 1,
    BackendServer = 2,
    PowerEnergyReached = 3,
    ChargingTimeExpired = 4,
    AuthorizationFailed = 5,
    ExceedPaymentAmount = 6,
    StartTimeout = 0x0B,
    ResetRemotely = 0x0F,
    CommunicationFault = 0x10,
    Unknown = 0xFF,
};
//Message::PGN::STOP_CHARGING, 0x0600
typedef union _tStopCharging
{
    struct
    {
        uint8_t reason;  //0-normal, 1-fault
        uint8_t endCode;
    }fields;

    uint8_t data[2];
}tStopCharging;

//Message::PGN::STOP_CHARGING_ACK, 0x0700
typedef struct _tStopChargingAck
{
    uint8_t result;  // 0-successful, 1-failed
}tStopChargingAck;

enum _AuthorizationReason
{
    ToStartCharging = 0,
    ToStopCharging,
    InvalidAuthorization = 0xFF,
};

enum _AuthorizationType
{
    AUTH_TYPE_RFID = 0,
    AUTH_TYPE_VIN,
    AUTH_TYPE_PNC,
    AUTH_TYPE_OFFLINE,
};

//Message::PGN::AUTHORIZATION, 0x1200
typedef union _tAuthorization
{
    struct
    {
        uint8_t reason;
        uint8_t type;
        uint8_t identifier[20];
    }fields;

    uint8_t data[22];
}tAuthorization;

//Message::PGN::AUTHORIZATION_ACK, 0x1300
typedef struct _tAuthorizationAck
{
    uint8_t result; // 0-successful, 1-failed
}tAuthorizationAck;

enum _LockConnectorAction
{
    UNLOCK_CONNECTOR = 0,
    LOCK_CONNECTOR = 1,
};

//Message::PGN::LOCK_CONNECTOR, 0x1800
typedef union _tLockConnector
{
    struct
    {
        uint8_t action;
    }fields;

    uint8_t data;
}tLockConnector;

//Message::PGN::LOCK_CONNECTOR_ACK, 0x1900
typedef struct _tLockConnectorAck
{
    uint8_t result;  // 0-successful, 1-failed
}tLockConnectorAck;

enum _BatteryType
{
    LeadAcidBattery = 1,
    NickelMetalHydrideBattery,
    LithiumIronPhosphateBattery,
    LithiumManganateBattery,
    LithiumCobaltBattery,
    TernaryMaterialBattery,
    PolymerLithiumIonBattery,
    LithiumTitanateBattery,
    UnknownBattery = 255,
};

//Message::PGN::START_CHARGING_RESULT, 0x3000
typedef union _tStartChargingResult
{
    struct
    {
        uint8_t result;                         // 0-successful, 1-failed
        uint8_t chargerProtocolNo[3];
        uint8_t bmsProtocolNo[3];
        uint8_t handshakeResult;                // 0-successful, 1-failed
        uint8_t batteryType;
        uint8_t maxAllowedTemperature;          // [-50, 200]℃, offset: -50℃, precision: 1℃/bit
        uint16_t maxAllowedChargingVoltage;     // offset: 0V, precision: 0.1V/bit
        uint16_t maxAllowedCellChargingVoltage; // [0, 24]V, offset: 0V, precision: 0.01V/bit
        uint16_t maxAllowedChargingCurrent;     // offset: -3000A, precision: 0.1A/bit
        uint16_t ratedVoltageOfBattery;         // offset: 0V, precision: 0.1V/bit
        uint16_t totalVoltageOfBattery;         // offset: 0V, precision: 0.1V/bit
        uint16_t ratedCapacityOfBattery;        // offset: 0Ah, precision: 0.1Ah/bit
        uint16_t ratedPowerEnergyOfBattery;     // [0, 1000]kWh, offset: 0kWh, precision: 0.1kWh/bit
        uint16_t socLevel;                      // [0, 1000]%, offset: 0%, precision: 0.1%/bit
        uint16_t maxOutputVoltageOfCharger;     // offset: 0V, precision: 0.1V/bit
        uint16_t minOutputVoltageOfCharger;     // offset: 0V, precision: 0.1V/bit
        uint16_t maxOutputCurrentOfCharger;     // offset: -3000A, precision: 0.1A/bit
    }fields;

    uint8_t data[32];
}tStartChargingResult;

enum _ResultFlag
{
    ResultSuccessful = 0,
    ResultFailed = 1,
};

//Message::PGN::START_CHARGING_RESULT_ACK, 0x3100
typedef union _tStartChargingResultAck
{
    struct
    {
        uint8_t result; //0-successful, 1-failed
    }fields;

    uint8_t data;
}tStartChargingResultAck;

enum _stopReason
{
    BcuRequested = 1,
    CcuFault,
    BmsAbnormalDetectedByCcu,
    BmsStoppedNormally,
    BmsFault,
    ControlPilotDetected,
    CcuCommunicationFault,
    PduFault,
    PduCommunicationFault,
};

//Message::PGN::STOP_CHARGING_RESULT, 0x3200
typedef union _tStopChargingResult
{
    struct
    {
        uint8_t  reason;
        uint32_t totalChargingTime;     // seconds
        uint32_t totalChargingEnergy;   // kWh, precision: 0.001kWh
        uint8_t  socLevel;              // [0, 1000]%, offset: 0%, precision: 1%/bit
        uint16_t minCellVoltage;        // [0, 24]V, offset: 0V, precision: 0.01V/bit
        uint16_t maxCellVoltage;        // [0, 24]V, offset: 0V, precision: 0.01V/bit
        uint8_t  minBatteryTemperature; // [-50, 200]℃, offset: -50℃, precision: 1℃/bit
        uint8_t  maxBatteryTemperature; // [-50, 200]℃, offset: -50℃, precision: 1℃/bit
        uint16_t endCode;
        uint16_t endCodeDetail;
    }fields;

    uint8_t data[20];
}tStopChargingResult;

//Message::PGN::STOP_CHARGING_RESULT_ACK, 0x3300
typedef union _tStopChargingResultAck
{
    struct
    {
        uint8_t result; //0-successful, 1-failed
    }fields;

    uint8_t data;
}tStopChargingResultAck;

enum _AuthorizationResult
{
    AuthorizationSuccessful = 0,
    AccountFrozen,
    AccountOverdue,
    AccountInvalid,
    AuthorizationRepeated,
    AuthorizationTimeout,
    ChargerOffline,
};

//Message::PGN::AUTHORIZATION_RESULT, 0x3A00
typedef union _tAuthorizationResult
{
    struct
    {
        uint8_t result;
        uint32_t accountBalance;  // 0.01 RMB
    }fields;

    uint8_t data[5];
}tAuthorizationResult;

//Message::PGN::AUTHORIZATION_RESULT_ACK, 0x3B00
typedef union _tAuthorizationResultAck
{
    struct
    {
        uint8_t result;  // 0-successful, 1-failed
    }fields;

    uint8_t data;
}tAuthorizationResultAck;

//Message::PGN::LOCK_CONNECTOR_RESULT, 0x3C00
typedef union _tLockConnectorResult
{
    struct
    {
        uint8_t action;
        uint8_t result;  //0-successful, 1-failed
    }fields;

    uint8_t data[2];
}tLockConnectorResult;

//Message::PGN::LOCK_CONNECTOR_RESULT_ACK, 0x3D00
typedef union _tLockConnectorResultAck
{
    struct
    {
        uint8_t result; //0-successful, 1-failed
    }fields;

    uint8_t data;
}tLockConnectorResultAck;

enum _PowerParamType
{
    POWER_ABSOLUTE_VALUE = 0,
    POWER_PERCENTAGE,
};

//Message::PGN::OUTPUT_POWER_DEMAND, 0x1600
typedef union _tOutputPowerDemand
{
    struct
    {
        uint8_t  autoPowerAllocation : 1;  // 0-Disabled, 1-Enabled
        uint8_t  reserved : 7;
        uint8_t  powerParamType;           // 0-Absolute Value, 1-Percentage
        uint16_t outputPower;              // offset: 0kWh, precision: 0.1kWh/bit
                                           // [0, 1000]%, offset: 0%, precision: 1%/bit
        uint8_t  gunNumber;
    }fields;

    uint8_t data[5];
}tOutputPowerDemand;

//Message::PGN::OUTPUT_POWER_DEMAND_ACK, 0x1700
typedef struct _tOutputPowerDemandAck
{
    uint8_t result;  // 0-successful, 1-failed
}tOutputPowerDemandAck;

//Message::PGN::PM_REMOTE_MEASURING, 0x1A00
typedef union _tPmRemoteMeasuring
{
    struct
    {
        uint8_t type;  // 01-all data
    }fields;

    uint8_t data;
}tPmRemoteMeasuring;

#define GET_OUTPUT_VOLTAGE_HI(voltage)             ((uint8_t)(((voltage) >> 8) & 0x3F))
#define GET_OUTPUT_VOLTAGE_LO(voltage)             ((uint8_t)((voltage) & 0xFF))
#define GET_OUTPUT_CURRENT_HI(current)             ((uint8_t)(((current) >> 2) & 0xFF))
#define GET_OUTPUT_CURRENT_LO(current)             ((uint8_t)((current) & 0x03))
#define GET_POWER_GROUP_ID_HI(index)               ((uint8_t)(((index) >> 1) & 0x0F))
#define GET_POWER_GROUP_ID_LO(index)               ((uint8_t)((index) & 0x01))
#define GET_CHARGER_CLIENT_ID_HI(index)            ((uint8_t)(((index) >> 4) & 0x01))
#define GET_CHARGER_CLIENT_ID_LO(index)            ((uint8_t)((index) & 0x0F))
#define GET_POWER_ALARM_STATE_HI(state)            ((uint16_t)(((state) >> 7) & 0xFFFF))
#define GET_POWER_ALARM_STATE_LO(state)            ((uint8_t)((state) & 0x7F))
#define GET_OUTPUT_VOLTAGE(voltHi, voltLo)         ((uint16_t)((((voltHi) & 0x3F) << 8) + ((voltLo) & 0xFF)))
#define GET_OUTPUT_CURRENT(currHi, currLo)         ((uint16_t)((((currHi) & 0xFF) << 2) + ((currLo) & 0x03)))
#define GET_POWER_GROUP_ID(indexHi, indexLo)       ((uint8_t)((((indexHi) & 0x0F) << 1) + ((indexLo) & 0x01)))
#define GET_CHARGER_CLIENT_ID(indexHi, indexLo)    ((uint8_t)((((indexHi) & 0x01) << 4) + ((indexLo) & 0x0F)))
#define GET_POWER_ALARM_STATE(stateHi, stateLo)    ((uint32_t)((((stateHi) & 0xFFFF) << 7) + ((stateLo) & 0x7F)))

enum _powerModuleState
{
    PM_STATE_ON = 0,
    PM_STATE_OFF = 1,
};

enum _dcContactorState
{
    DC_CONTACTOR_STATE_OPEN = 0,
    DC_CONTACTOR_STATE_CLOSED,
};

//Message::PGN::PM_REMOTE_MEASURING_ACK, 0x1B00
typedef struct _tPmRemoteMeasuringAck
{
    uint8_t numberOfPowerModules;
    union
    {
        struct{
            uint8_t outputVoltageLo  : 8;
            uint8_t outputVoltageHi  : 6;
            uint8_t outputCurrentLo  : 2;
            uint8_t outputCurrentHi : 8;

            uint8_t state            : 1; // 0-on, 1-off
            uint8_t dcContactorState : 1; // 0-open, 1-closed
            uint8_t address          : 5; // 0-31
            uint8_t groupIndexLo     : 1; // 0-31, 0-invalid
            uint8_t groupIndexHi     : 4;
            uint8_t clientIndexLo    : 4; // 0-16
            uint8_t clientIndexHi    : 1;
            uint8_t alarmStateLo     : 7;
            uint16_t alarmStateHi    : 16;
        }fields;

        uint8_t data[8];
    }powerModules[0];
}tPmRemoteMeasuringAck;

//Message::PGN::PM_REMOTE_CONTROLLING, 0x1C00
typedef union _tPmRemoteControlling
{
    struct
    {
        uint8_t powerGroupNo;  // 0-31, 0-all group
        uint8_t reserved;
        struct
        {
            uint8_t enablePowerGroupOnOffCtrl : 1;   // 0-disable, 1-enable
            uint8_t enableDcContactorCtrl : 1;       // 0-disable, 1-enable
            uint8_t enableDcVoltageCurrentCtrl : 1;  // 0-disable, 1-enable
            uint8_t reserved1 : 1;
            uint8_t powerGroupOnOff : 1;             // 0-ON, 1-OFF, precondition: enablePowerGroupOnOffCtrl == 1
            uint8_t dcContactorState : 1;            //0-OPEN, 1-CLOSE, precondition: enableDcContactorCtrl == 1
            uint8_t reserved2 : 2;
        }actions;
        uint16_t dcVoltage;                          // offset: 0V, precision: 0.1V/bit
        uint16_t dcCurrent;                          // offset: -3000A, precision: 0.1A/bit
    }fields;

    uint8_t data[7];
}tPmRemoteControlling;

//Message::PGN::PM_REMOTE_CONTROLLING_ACK, 0x1D00
typedef struct _tPmRemoteControllingAck
{
    uint8_t result;  // 0-successful, 1-failed
}tPmRemoteControllingAck;

//Message::PGN::PDU_SELF_TEST, 0x1E00
typedef union _tPduSelfTest
{
    struct
    {
        uint8_t  demand;      // 0-start, 1-stop
        uint8_t  mode;        // 0-timed self-test, 1-remote self-test
        uint32_t identifier;  // timestamp to execute self-test
    }fields;

    uint8_t data[6];
}tPduSelfTest;

//Message::PGN::PDU_SELF_TEST_ACK, 0x1F00
typedef union _tPduSelfTestAck
{
    struct
    {
        uint8_t  demand;     // 0-start, 1-stop
        uint16_t mode;       // 0-timed self-test, 1-remote self-test
        uint16_t identifier; // timestamp to execute self-test
        uint16_t result;     // 0-successful,
                             // 1-has fault,
                             // 2-busy because of charging,
                             // 3-vehicle connected
    }fields;

    uint8_t data[7];
}tPduSelfTestAck;
#pragma pack()

} // Message
} // CANj1939

