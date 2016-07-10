#include "NetUDPClient_Rustavi.h"

NetUDPClient_Rustavi::NetUDPClient_Rustavi(const QString& _ip, int _port,QObject *parent = 0)
    :NetUDPClient(_ip,_port,parent)
{
    int i;
    #define ADD_STATE(STATE,MODULE,MASK)    netDevice.addState( STATE ,new NetState(""#STATE,MODULE,MASK))
    #define ADD_CMD(CMD,MODULE,MASK)        netDevice.addCommand( CMD ,new NetCommand(""#CMD,MODULE,MASK))
    #define ADD_MODULE( NAME )              netDevice.addModule( NAME ,new NetModule(""#NAME,MDL_MODE_INOUT,IO32));

    setBuffer(reinterpret_cast<char*>(netPacket.getPacket()),netPacket.getPacketSize());
    //MODULES
    ADD_MODULE(LP_ST_DM_RUSTAVI_SLOT_0);
    ADD_MODULE(LP_ST_DM_RUSTAVI_SLOT_1);
    ADD_MODULE(LP_ST_DM_RUSTAVI_SLOT_2);
    ADD_MODULE(LP_ST_DM_RUSTAVI_SLOT_3);
    ADD_MODULE(LP_ST_DM_RUSTAVI_SLOT_4);
    ADD_MODULE(LP_ST_DM_RUSTAVI_SLOT_5);
    ADD_MODULE(LP_ST_DM_RUSTAVI_SLOT_6);
    ADD_MODULE(LP_ST_DM_RUSTAVI_SLOT_7);
    ADD_MODULE(LP_ST_DM_RUSTAVI_SLOT_8);
    ADD_MODULE(LP_ST_DM_RUSTAVI_SLOT_9);
    ADD_MODULE(LP_ST_DM_RUSTAVI_MEM_1);
    ADD_MODULE(LP_ST_DM_RUSTAVI_MEM_2);
    ADD_MODULE(LP_ST_DM_RUSTAVI_1);
    ADD_MODULE(LP_ST_DM_RUSTAVI_2);
    ADD_MODULE(LP_ST_AM_RUSTAVI_1);
    ADD_MODULE(PC_DM_RUSTAVI_1);
    ADD_MODULE(PC_DM_RUSTAVI_2);

    //COMMANDS
    ADD_CMD(LP_CMD_ROLGANG_FWD,PC_DM_RUSTAVI_1,0);
    ADD_CMD(LP_CMD_ROLGANG_BWD,PC_DM_RUSTAVI_1,1);
    ADD_CMD(LP_CMD_MAB1_WORK,PC_DM_RUSTAVI_1,2);
    ADD_CMD(LP_CMD_MAB1_WATER,PC_DM_RUSTAVI_1,3);
    ADD_CMD(LP_CMD_MAB2_WORK,PC_DM_RUSTAVI_1,4);
    ADD_CMD(LP_CMD_MAB2_WATER,PC_DM_RUSTAVI_1,5);
    ADD_CMD(LP_CMD_MAB3_WORK,PC_DM_RUSTAVI_1,6);
    ADD_CMD(LP_CMD_MAB3_WATER,PC_DM_RUSTAVI_1,7);
    ADD_CMD(LP_CMD_MAB4_WORK,PC_DM_RUSTAVI_1,8);
    ADD_CMD(LP_CMD_MAB4_WATER,PC_DM_RUSTAVI_1,9);

    //LINPACK_STATES
/*
    ///SLOT 1
    i=0;
    ADD_STATE(LP_ST_ASU_PIPE_LOADING,LP_ST_DM_RUSTAVI_SLOT_0,i++);
    ADD_STATE(LP_ST_CLEANER_HOME,LP_ST_DM_RUSTAVI_SLOT_0,i++);
    ADD_STATE(LP_ST_POST_CLEANER_BEGIN,LP_ST_DM_RUSTAVI_SLOT_0,i++);
    ADD_STATE(LP_ST_POST_CLEANER_END,LP_ST_DM_RUSTAVI_SLOT_0,i++);
    ADD_STATE(LP_ST_POST_MAB1_BEGIN,LP_ST_DM_RUSTAVI_SLOT_0,i++);
    ADD_STATE(LP_ST_POST_MAB1_END,LP_ST_DM_RUSTAVI_SLOT_0,i++);
    ADD_STATE(LP_ST_POST_MAB2_END,LP_ST_DM_RUSTAVI_SLOT_0,i++);
    ADD_STATE(LP_ST_POST_MAB1_WORK,LP_ST_DM_RUSTAVI_SLOT_0,i++);
    ADD_STATE(LP_ST_POST_MAB2_WORK,LP_ST_DM_RUSTAVI_SLOT_0,i++);
    ADD_STATE(LP_ST_POST_MAB1_HOME,LP_ST_DM_RUSTAVI_SLOT_0,i++);
    ADD_STATE(LP_ST_POST_MAB2_HOME,LP_ST_DM_RUSTAVI_SLOT_0,i++);
    ADD_STATE(LP_ST_POST_MAB3_BEGIN,LP_ST_DM_RUSTAVI_SLOT_0,i++);
    ADD_STATE(LP_ST_POST_MAB3_END,LP_ST_DM_RUSTAVI_SLOT_0,i++);
    ADD_STATE(LP_ST_POST_MAB4_END,LP_ST_DM_RUSTAVI_SLOT_0,i++);
    ADD_STATE(LP_ST_POST_MAB3_WORK,LP_ST_DM_RUSTAVI_SLOT_0,i++);
    ADD_STATE(LP_ST_POST_MAB4_WORK,LP_ST_DM_RUSTAVI_SLOT_0,i++);
    ADD_STATE(LP_ST_POST_MAB3_HOME,LP_ST_DM_RUSTAVI_SLOT_0,i++);
    ADD_STATE(LP_ST_POST_MAB4_HOME,LP_ST_DM_RUSTAVI_SLOT_0,i++);
    ADD_STATE(LP_ST_POST_DP1_BEGIN,LP_ST_DM_RUSTAVI_SLOT_0,i++);
    ADD_STATE(LP_ST_POST_DP1_END,LP_ST_DM_RUSTAVI_SLOT_0,i++);
    ADD_STATE(LP_ST_DEVICE_LEVEL,LP_ST_DM_RUSTAVI_SLOT_0,i++);
    ADD_STATE(LP_ST_POST_PR1_HOME,LP_ST_DM_RUSTAVI_SLOT_0,i++);
    ADD_STATE(LP_ST_POST_PR1_WORK,LP_ST_DM_RUSTAVI_SLOT_0,i++);
    ADD_STATE(LP_ST_POST_PR2_HOME,LP_ST_DM_RUSTAVI_SLOT_0,i++);
    ADD_STATE(LP_ST_POST_PR2_WORK,LP_ST_DM_RUSTAVI_SLOT_0,i++);
    ADD_STATE(LP_ST_POST_PR3_HOME,LP_ST_DM_RUSTAVI_SLOT_0,i++);
    ADD_STATE(LP_ST_POST_PR3_WORK,LP_ST_DM_RUSTAVI_SLOT_0,i++);
    ADD_STATE(LP_ST_POST_PR4_HOME,LP_ST_DM_RUSTAVI_SLOT_0,i++);
    ADD_STATE(LP_ST_POST_PR4_WORK,LP_ST_DM_RUSTAVI_SLOT_0,i++);
    ADD_STATE(LP_ST_ASU_PIPE_UPLOADING,LP_ST_DM_RUSTAVI_SLOT_0,i++);
    ADD_STATE(LP_ST_BTN_ERROR_STOP,LP_ST_DM_RUSTAVI_SLOT_0,i++);
    ADD_STATE(LP_ST_RESERV1,LP_ST_DM_RUSTAVI_SLOT_0,i++);
    ///SLOT 2
    i=0;
    ADD_STATE(LP_ST_RESERV2,LP_ST_DM_RUSTAVI_SLOT_1,i++);
    ADD_STATE(LP_ST_SWITCH_RESOLUTION,LP_ST_DM_RUSTAVI_SLOT_1,i++);
    ADD_STATE(LP_ST_SWITCH_SETUP,LP_ST_DM_RUSTAVI_SLOT_1,i++);
    ADD_STATE(LP_ST_SWITCH_WORK,LP_ST_DM_RUSTAVI_SLOT_1,i++);
    ADD_STATE(LP_ST_SWITCH_TRANSITE,LP_ST_DM_RUSTAVI_SLOT_1,i++);
    ADD_STATE(LP_ST_BTN_LOAD_PIPE,LP_ST_DM_RUSTAVI_SLOT_1,i++);
    ADD_STATE(LP_ST_BTN_UPLOAD_PIPE,LP_ST_DM_RUSTAVI_SLOT_1,i++);
    ADD_STATE(LP_ST_SWITCH_ON_CLEANER,LP_ST_DM_RUSTAVI_SLOT_1,i++);
    ADD_STATE(LP_ST_SWITCH_ROLLER_FORTH,LP_ST_DM_RUSTAVI_SLOT_1,i++);
    ADD_STATE(LP_ST_SWITCH_ROLLER_BACK,LP_ST_DM_RUSTAVI_SLOT_1,i++);
    ADD_STATE(LP_ST_BTN_ROLLER_SLOW,LP_ST_DM_RUSTAVI_SLOT_1,i++);
    ADD_STATE(LP_ST_BTN_ROLLER_FAST,LP_ST_DM_RUSTAVI_SLOT_1,i++);
    ADD_STATE(LP_ST_BTN_SPIRAL_SLOW,LP_ST_DM_RUSTAVI_SLOT_1,i++);
    ADD_STATE(LP_ST_BTN_SPIRAL_FAST,LP_ST_DM_RUSTAVI_SLOT_1,i++);
    ADD_STATE(LP_ST_BTN_UZK1_WATER,LP_ST_DM_RUSTAVI_SLOT_1,i++);
    ADD_STATE(LP_ST_BTN_UZK2_WATER,LP_ST_DM_RUSTAVI_SLOT_1,i++);
    ADD_STATE(LP_ST_BTN_PR1_ON_WORK,LP_ST_DM_RUSTAVI_SLOT_1,i++);
    ADD_STATE(LP_ST_BTN_PR1_ON_HOME,LP_ST_DM_RUSTAVI_SLOT_1,i++);
    ADD_STATE(LP_ST_BTN_MAB1_ON_WORK,LP_ST_DM_RUSTAVI_SLOT_1,i++);
    ADD_STATE(LP_ST_BTN_MAB1_ON_HOME,LP_ST_DM_RUSTAVI_SLOT_1,i++);
    ADD_STATE(LP_ST_BTN_MAB2_ON_WORK,LP_ST_DM_RUSTAVI_SLOT_1,i++);
    ADD_STATE(LP_ST_BTN_MAB2_ON_HOME,LP_ST_DM_RUSTAVI_SLOT_1,i++);
    ADD_STATE(LP_ST_BTN_PR2_ON_WORK,LP_ST_DM_RUSTAVI_SLOT_1,i++);
    ADD_STATE(LP_ST_BTN_PR2_ON_HOME,LP_ST_DM_RUSTAVI_SLOT_1,i++);
    ADD_STATE(LP_ST_BTN_PR3_ON_WORK,LP_ST_DM_RUSTAVI_SLOT_1,i++);
    ADD_STATE(LP_ST_BTN_PR3_ON_HOME,LP_ST_DM_RUSTAVI_SLOT_1,i++);
    ADD_STATE(LP_ST_BTN_MAB3_ON_WORK,LP_ST_DM_RUSTAVI_SLOT_1,i++);
    ADD_STATE(LP_ST_BTN_MAB3_ON_HOME,LP_ST_DM_RUSTAVI_SLOT_1,i++);
    ADD_STATE(LP_ST_BTN_MAB4_ON_WORK,LP_ST_DM_RUSTAVI_SLOT_1,i++);
    ADD_STATE(LP_ST_BTN_MAB4_ON_HOME,LP_ST_DM_RUSTAVI_SLOT_1,i++);
    ADD_STATE(LP_ST_BTN_PR4_ON_WORK,LP_ST_DM_RUSTAVI_SLOT_1,i++);
    ADD_STATE(LP_ST_BTN_PR4_ON_HOME,LP_ST_DM_RUSTAVI_SLOT_1,i++);
    ///SLOT 3
    i=0;
    ADD_STATE(LP_ST_AC_SUPPLY,LP_ST_DM_RUSTAVI_SLOT_2,i++);
    ADD_STATE(LP_ST_AV_AC_SUPPLY_ON,LP_ST_DM_RUSTAVI_SLOT_2,i++);
    ADD_STATE(LP_ST_AV_CLEANER1_ON,LP_ST_DM_RUSTAVI_SLOT_2,i++);
    ADD_STATE(LP_ST_AV_CLEANER2_ON,LP_ST_DM_RUSTAVI_SLOT_2,i++);
    ADD_STATE(LP_ST_AV_PUMP_ON,LP_ST_DM_RUSTAVI_SLOT_2,i++);
    ADD_STATE(LP_ST_AV_PUMP_STATION1_ON,LP_ST_DM_RUSTAVI_SLOT_2,i++);
    ADD_STATE(LP_ST_AV_PUMP_STATION2_ON,LP_ST_DM_RUSTAVI_SLOT_2,i++);
    ADD_STATE(LP_ST_CONTACTOR_CLEANER1_ON,LP_ST_DM_RUSTAVI_SLOT_2,i++);
    ADD_STATE(LP_ST_CONTACTOR_CLEANER2_ON,LP_ST_DM_RUSTAVI_SLOT_2,i++);
    ADD_STATE(LP_ST_CONTACTOR_PUMP_ON,LP_ST_DM_RUSTAVI_SLOT_2,i++);
    ADD_STATE(LP_ST_CONTACTOR_PUMP_STATION1_ON,LP_ST_DM_RUSTAVI_SLOT_2,i++);
    ADD_STATE(LP_ST_CONTACTOR_PUMP_STATION2_ON,LP_ST_DM_RUSTAVI_SLOT_2,i++);
    ADD_STATE(LP_ST_RESERV3,LP_ST_DM_RUSTAVI_SLOT_2,i++);
    ADD_STATE(LP_ST_RESERV4,LP_ST_DM_RUSTAVI_SLOT_2,i++);
    ADD_STATE(LP_ST_RESERV5,LP_ST_DM_RUSTAVI_SLOT_2,i++);
    ADD_STATE(LP_ST_RESERV6,LP_ST_DM_RUSTAVI_SLOT_2,i++);
    ///SLOT 4
    i=0;
    ADD_STATE(LP_ST_LED_LOADING_PERMITTED,LP_ST_DM_RUSTAVI_SLOT_3,i++);
    ADD_STATE(LP_ST_LED_UPLOADING_PERMITTED,LP_ST_DM_RUSTAVI_SLOT_3,i++);
    ADD_STATE(LP_ST_LED_ROLLER_SLOW,LP_ST_DM_RUSTAVI_SLOT_3,i++);
    ADD_STATE(LP_ST_LED_ROLLER_FAST,LP_ST_DM_RUSTAVI_SLOT_3,i++);
    ADD_STATE(LP_ST_LED_SPIRAL_SLOW,LP_ST_DM_RUSTAVI_SLOT_3,i++);
    ADD_STATE(LP_ST_LED_SPIRAL_FAST,LP_ST_DM_RUSTAVI_SLOT_3,i++);
    ADD_STATE(LP_ST_LED_UZK1_WATER,LP_ST_DM_RUSTAVI_SLOT_3,i++);
    ADD_STATE(LP_ST_LED_UZK2_WATER,LP_ST_DM_RUSTAVI_SLOT_3,i++);
    ADD_STATE(LP_ST_LED_BRAK,LP_ST_DM_RUSTAVI_SLOT_3,i++);
    ADD_STATE(LP_ST_LED_GODEN,LP_ST_DM_RUSTAVI_SLOT_3,i++);
    ADD_STATE(LP_ST_LED_ERROR_STOP,LP_ST_DM_RUSTAVI_SLOT_3,i++);
    ADD_STATE(LP_ST_OUT_RESERV1,LP_ST_DM_RUSTAVI_SLOT_3,i++);
    ADD_STATE(LP_ST_OUT_RESERV2,LP_ST_DM_RUSTAVI_SLOT_3,i++);
    ADD_STATE(LP_ST_OUT_RESERV3,LP_ST_DM_RUSTAVI_SLOT_3,i++);
    ADD_STATE(LP_ST_OUT_RESERV4,LP_ST_DM_RUSTAVI_SLOT_3,i++);
    ADD_STATE(LP_ST_OUT_RESERV5,LP_ST_DM_RUSTAVI_SLOT_3,i++);
    ///SLOT 5
    i=0;
    ADD_STATE(LP_ST_OUT_MAB1_ON_WORK,LP_ST_DM_RUSTAVI_SLOT_4,i++);
    ADD_STATE(LP_ST_OUT_MAB1_ON_HOME,LP_ST_DM_RUSTAVI_SLOT_4,i++);
    ADD_STATE(LP_ST_OUT_MAB2_ON_WORK,LP_ST_DM_RUSTAVI_SLOT_4,i++);
    ADD_STATE(LP_ST_OUT_MAB2_ON_HOME,LP_ST_DM_RUSTAVI_SLOT_4,i++);
    ADD_STATE(LP_ST_OUT_MAB3_ON_WORK,LP_ST_DM_RUSTAVI_SLOT_4,i++);
    ADD_STATE(LP_ST_OUT_MAB3_ON_HOME,LP_ST_DM_RUSTAVI_SLOT_4,i++);
    ADD_STATE(LP_ST_OUT_MAB4_ON_WORK,LP_ST_DM_RUSTAVI_SLOT_4,i++);
    ADD_STATE(LP_ST_OUT_MAB4_ON_HOME,LP_ST_DM_RUSTAVI_SLOT_4,i++);
    ADD_STATE(LP_ST_OUT_PR1_ON_WORK,LP_ST_DM_RUSTAVI_SLOT_4,i++);
    ADD_STATE(LP_ST_OUT_PR1_ON_HOME,LP_ST_DM_RUSTAVI_SLOT_4,i++);
    ADD_STATE(LP_ST_OUT_PR2_ON_WORK,LP_ST_DM_RUSTAVI_SLOT_4,i++);
    ADD_STATE(LP_ST_OUT_PR2_ON_HOME,LP_ST_DM_RUSTAVI_SLOT_4,i++);
    ADD_STATE(LP_ST_OUT_PR3_ON_WORK,LP_ST_DM_RUSTAVI_SLOT_4,i++);
    ADD_STATE(LP_ST_OUT_PR3_ON_HOME,LP_ST_DM_RUSTAVI_SLOT_4,i++);
    ADD_STATE(LP_ST_OUT_PR4_ON_WORK,LP_ST_DM_RUSTAVI_SLOT_4,i++);
    ADD_STATE(LP_ST_OUT_PR4_ON_HOME,LP_ST_DM_RUSTAVI_SLOT_4,i++);
    ///SLOT 6
    i=0;
    ADD_STATE(LP_ST_OUT_CLEANER_ON,LP_ST_DM_RUSTAVI_SLOT_5,i++);
    ADD_STATE(LP_ST_OUT_PUMP1_STATION_ON,LP_ST_DM_RUSTAVI_SLOT_5,i++);
    ADD_STATE(LP_ST_OUT_PUMP2_STATION_ON,LP_ST_DM_RUSTAVI_SLOT_5,i++);
    ADD_STATE(LP_ST_OUT_PUMP_ON,LP_ST_DM_RUSTAVI_SLOT_5,i++);
    ADD_STATE(LP_ST_ASU_ERROR_STOP,LP_ST_DM_RUSTAVI_SLOT_5,i++);
    ADD_STATE(LP_ST_ASU_EXTRACT_ON,LP_ST_DM_RUSTAVI_SLOT_5,i++);
    ADD_STATE(LP_ST_ASU_LOAD_PIPE,LP_ST_DM_RUSTAVI_SLOT_5,i++);
    ADD_STATE(LP_ST_ASU_UPLOAD_PIPE,LP_ST_DM_RUSTAVI_SLOT_5,i++);
    ADD_STATE(LP_ST_ASU_ROLLER_FORTH,LP_ST_DM_RUSTAVI_SLOT_5,i++);
    ADD_STATE(LP_ST_ASU_ROLLER_BACK,LP_ST_DM_RUSTAVI_SLOT_5,i++);
    ADD_STATE(LP_ST_ASU_ROLLER_SLOW,LP_ST_DM_RUSTAVI_SLOT_5,i++);
    ADD_STATE(LP_ST_ASU_ROLLER_FAST,LP_ST_DM_RUSTAVI_SLOT_5,i++);
    ADD_STATE(LP_ST_ASU_SPIRAL_SLOW,LP_ST_DM_RUSTAVI_SLOT_5,i++);
    ADD_STATE(LP_ST_ASU_SPIRAL_FAST,LP_ST_DM_RUSTAVI_SLOT_5,i++);
    ADD_STATE(LP_ST_ASU_BRAK,LP_ST_DM_RUSTAVI_SLOT_5,i++);
    ADD_STATE(LP_ST_ASU_GODEN,LP_ST_DM_RUSTAVI_SLOT_5,i++);
    ADD_STATE(LP_ST_OUT_WATER1_ON,LP_ST_DM_RUSTAVI_SLOT_5,i++);
    ADD_STATE(LP_ST_OUT_WATER2_ON,LP_ST_DM_RUSTAVI_SLOT_5,i++);
    ADD_STATE(LP_ST_OUT_WATER3_ON,LP_ST_DM_RUSTAVI_SLOT_5,i++);
    ADD_STATE(LP_ST_OUT_WATER4_ON,LP_ST_DM_RUSTAVI_SLOT_5,i++);
    ADD_STATE(LP_ST_OUT_WATER_PIPES_OPEN,LP_ST_DM_RUSTAVI_SLOT_5,i++);
    ADD_STATE(LP_ST_OUT_CLEAN_FLAP_OPEN,LP_ST_DM_RUSTAVI_SLOT_5,i++);
    ADD_STATE(LP_ST_OUT_RESERV6,LP_ST_DM_RUSTAVI_SLOT_5,i++);
    ADD_STATE(LP_ST_OUT_RESERV7,LP_ST_DM_RUSTAVI_SLOT_5,i++);
    ADD_STATE(LP_ST_OUT_ASD_LIGHT_R,LP_ST_DM_RUSTAVI_SLOT_5,i++);
    ADD_STATE(LP_ST_OUT_ASD_LIGHT_Y,LP_ST_DM_RUSTAVI_SLOT_5,i++);
    ADD_STATE(LP_ST_OUT_ASD_LIGHT_G,LP_ST_DM_RUSTAVI_SLOT_5,i++);
    ADD_STATE(LP_ST_OUT_ASD_BEEP,LP_ST_DM_RUSTAVI_SLOT_5,i++);
    ADD_STATE(LP_ST_OUT_RESERV8,LP_ST_DM_RUSTAVI_SLOT_5,i++);
    ADD_STATE(LP_ST_OUT_RESERV9,LP_ST_DM_RUSTAVI_SLOT_5,i++);
    ADD_STATE(LP_ST_OUT_RESERV10,LP_ST_DM_RUSTAVI_SLOT_5,i++);
    ADD_STATE(LP_ST_OUT_RESERV11,LP_ST_DM_RUSTAVI_SLOT_5,i++);
    ///SLOT 7
    i=0;
    ADD_STATE(LP_ST_WATER_LEVEL1,LP_ST_DM_RUSTAVI_SLOT_6,i++);
    ADD_STATE(LP_ST_WATER_LEVEL2,LP_ST_DM_RUSTAVI_SLOT_6,i++);
    ///SLOT 8
    ///SLOT 9
    i=0;
    ADD_STATE(LP_ST_DIP_SWITCH_1_DEBUG_EXIT,LP_ST_DM_RUSTAVI_SLOT_8,i++);
    ADD_STATE(LP_ST_DIP_SWITCH_2_SETUP_MOD_DEBUG,LP_ST_DM_RUSTAVI_SLOT_8,i++);
    ADD_STATE(LP_ST_DIP_SWITCH_3,LP_ST_DM_RUSTAVI_SLOT_8,i++);
    ADD_STATE(LP_ST_DIP_SWITCH_4_ENABLE_BEEP,LP_ST_DM_RUSTAVI_SLOT_8,i++);
    ADD_STATE(LP_ST_DIP_SWITCH_5_WATER_CONDITIONING,LP_ST_DM_RUSTAVI_SLOT_8,i++);
    ADD_STATE(LP_ST_DIP_SWITCH_6_ENABLE_ERROE_LEVEL,LP_ST_DM_RUSTAVI_SLOT_8,i++);
    ADD_STATE(LP_ST_DIP_SWITCH_7_ENABLE_ERROE_STOP,LP_ST_DM_RUSTAVI_SLOT_8,i++);
    ADD_STATE(LP_ST_DIP_SWITCH_8_ENABLE_CHECK_POWER_AV,LP_ST_DM_RUSTAVI_SLOT_8,i++);
    ///SLOT 10
    i=0;
    ADD_STATE(LP_ST_ROLLER_SPEED1,LP_ST_DM_RUSTAVI_SLOT_9,i++);
    ADD_STATE(LP_ST_ROLLER_SPEED2,LP_ST_DM_RUSTAVI_SLOT_9,i++);
    ADD_STATE(LP_ST_ROLLER_SPEED3,LP_ST_DM_RUSTAVI_SLOT_9,i++);
    ADD_STATE(LP_ST_ROLLER_SPEED4,LP_ST_DM_RUSTAVI_SLOT_9,i++);
    ///MEM 1
    i=0;
    ADD_STATE(LP_ST_LOCAL_BLIT,LP_ST_DM_RUSTAVI_MEM_1,i++);
    ADD_STATE(LP_ST_LOCAL_NBLIT,LP_ST_DM_RUSTAVI_MEM_1,i++);
    ADD_STATE(LP_ST_LOCAL_ERROR,LP_ST_DM_RUSTAVI_MEM_1,i++);
    ADD_STATE(LP_ST_EXTERN_ERROR,LP_ST_DM_RUSTAVI_MEM_1,i++);
    ADD_STATE(LP_ST_LOCAL_RES_OK,LP_ST_DM_RUSTAVI_MEM_1,i++);
    ADD_STATE(LP_ST_LOCAL_RES_BRK,LP_ST_DM_RUSTAVI_MEM_1,i++);
    ADD_STATE(LP_ST_LOCAL_CONTROL_ENABLE,LP_ST_DM_RUSTAVI_MEM_1,i++);
    ADD_STATE(LP_ST_LOCAL_PIPE_NPOSTLOAD,LP_ST_DM_RUSTAVI_MEM_1,i++);
    ADD_STATE(LP_ST_LOCAL_MABS_INITED,LP_ST_DM_RUSTAVI_MEM_1,i++);
    ADD_STATE(LP_ST_LOCAL_PRS_INITED,LP_ST_DM_RUSTAVI_MEM_1,i++);
    ADD_STATE(LP_ST_LOCAL_PIPE_LOADED,LP_ST_DM_RUSTAVI_MEM_1,i++);
    ADD_STATE(LP_ST_LOCAL_PIPE_UPLOADED,LP_ST_DM_RUSTAVI_MEM_1,i++);
    ADD_STATE(LP_ST_LOCAL_PIPE_PRESENT,LP_ST_DM_RUSTAVI_MEM_1,i++);
    ADD_STATE(LP_ST_LOCAL_PIPE_POS0,LP_ST_DM_RUSTAVI_MEM_1,i++);
    ADD_STATE(LP_ST_LOCAL_PIPE_POS1,LP_ST_DM_RUSTAVI_MEM_1,i++);
    ADD_STATE(LP_ST_LOCAL_PIPE_POS2,LP_ST_DM_RUSTAVI_MEM_1,i++);
    ADD_STATE(LP_ST_LOCAL_PIPE_POS3,LP_ST_DM_RUSTAVI_MEM_1,i++);
    ADD_STATE(LP_ST_LOCAL_PIPE_POS4,LP_ST_DM_RUSTAVI_MEM_1,i++);
    ADD_STATE(LP_ST_LOCAL_PIPE_POS5,LP_ST_DM_RUSTAVI_MEM_1,i++);
    ADD_STATE(LP_ST_LOCAL_PIPE_POS6,LP_ST_DM_RUSTAVI_MEM_1,i++);
    ADD_STATE(LP_ST_LOCAL_PIPE_POS7,LP_ST_DM_RUSTAVI_MEM_1,i++);
    ADD_STATE(LP_ST_LOCAL_PIPE_POS8,LP_ST_DM_RUSTAVI_MEM_1,i++);
    ADD_STATE(LP_ST_LOCAL_PIPE_POS9,LP_ST_DM_RUSTAVI_MEM_1,i++);
    ADD_STATE(LP_ST_LOCAL_PIPE_POS10,LP_ST_DM_RUSTAVI_MEM_1,i++);
    ADD_STATE(LP_ST_LOCAL_PIPE_POS11,LP_ST_DM_RUSTAVI_MEM_1,i++);
    ///MEM 2
    i=0;
    ADD_STATE(LP_ST_LOCAL_MAB1_INIT,LP_ST_DM_RUSTAVI_MEM_2,i++);
    ADD_STATE(LP_ST_LOCAL_MAB2_INIT,LP_ST_DM_RUSTAVI_MEM_2,i++);
    ADD_STATE(LP_ST_LOCAL_MAB3_INIT,LP_ST_DM_RUSTAVI_MEM_2,i++);
    ADD_STATE(LP_ST_LOCAL_MAB4_INIT,LP_ST_DM_RUSTAVI_MEM_2,i++);
    ADD_STATE(LP_ST_LOCAL_PR1_INIT,LP_ST_DM_RUSTAVI_MEM_2,i++);
    ADD_STATE(LP_ST_LOCAL_PR2_INIT,LP_ST_DM_RUSTAVI_MEM_2,i++);
    ADD_STATE(LP_ST_LOCAL_PR3_INIT,LP_ST_DM_RUSTAVI_MEM_2,i++);
    ADD_STATE(LP_ST_LOCAL_PR4_INIT,LP_ST_DM_RUSTAVI_MEM_2,i++);
    ADD_STATE(LP_ST_LOCAL_MAB1_HOME,LP_ST_DM_RUSTAVI_MEM_2,i++);
    ADD_STATE(LP_ST_LOCAL_MAB2_HOME,LP_ST_DM_RUSTAVI_MEM_2,i++);
    ADD_STATE(LP_ST_LOCAL_MAB3_HOME,LP_ST_DM_RUSTAVI_MEM_2,i++);
    ADD_STATE(LP_ST_LOCAL_MAB4_HOME,LP_ST_DM_RUSTAVI_MEM_2,i++);
    ADD_STATE(LP_ST_LOCAL_PR1_HOME,LP_ST_DM_RUSTAVI_MEM_2,i++);
    ADD_STATE(LP_ST_LOCAL_PR2_HOME,LP_ST_DM_RUSTAVI_MEM_2,i++);
    ADD_STATE(LP_ST_LOCAL_PR3_HOME,LP_ST_DM_RUSTAVI_MEM_2,i++);
    ADD_STATE(LP_ST_LOCAL_PR4_HOME,LP_ST_DM_RUSTAVI_MEM_2,i++);
    ADD_STATE(LP_ST_LOCAL_MAB1_WORK,LP_ST_DM_RUSTAVI_MEM_2,i++);
    ADD_STATE(LP_ST_LOCAL_MAB2_WORK,LP_ST_DM_RUSTAVI_MEM_2,i++);
    ADD_STATE(LP_ST_LOCAL_MAB3_WORK,LP_ST_DM_RUSTAVI_MEM_2,i++);
    ADD_STATE(LP_ST_LOCAL_MAB4_WORK,LP_ST_DM_RUSTAVI_MEM_2,i++);
    ADD_STATE(LP_ST_LOCAL_PR1_WORK,LP_ST_DM_RUSTAVI_MEM_2,i++);
    ADD_STATE(LP_ST_LOCAL_PR2_WORK,LP_ST_DM_RUSTAVI_MEM_2,i++);
    ADD_STATE(LP_ST_LOCAL_PR3_WORK,LP_ST_DM_RUSTAVI_MEM_2,i++);
    ADD_STATE(LP_ST_LOCAL_PR4_WORK,LP_ST_DM_RUSTAVI_MEM_2,i++);
    ADD_STATE(LP_ST_LOCAL_MAB1_WATER_ON,LP_ST_DM_RUSTAVI_MEM_2,i++);
    ADD_STATE(LP_ST_LOCAL_MAB2_WATER_ON,LP_ST_DM_RUSTAVI_MEM_2,i++);
    ADD_STATE(LP_ST_LOCAL_MAB3_WATER_ON,LP_ST_DM_RUSTAVI_MEM_2,i++);
    ADD_STATE(LP_ST_LOCAL_MAB4_WATER_ON,LP_ST_DM_RUSTAVI_MEM_2,i++);
*/
    ///MODULE LP_ST_DM_RUSTAVI_1
    i=0;
    ADD_STATE(LP_ST_ROLGANG_FWD,LP_ST_DM_RUSTAVI_1,i++);
    ADD_STATE(LP_ST_ROLGANG_BWD,LP_ST_DM_RUSTAVI_1,i++);
    ADD_STATE(LP_ST_MAB1_WORK,LP_ST_DM_RUSTAVI_1,i++);
    ADD_STATE(LP_ST_MAB1_WATER,LP_ST_DM_RUSTAVI_1,i++);
    ADD_STATE(LP_ST_MAB2_WORK,LP_ST_DM_RUSTAVI_1,i++);
    ADD_STATE(LP_ST_MAB2_WATER,LP_ST_DM_RUSTAVI_1,i++);
    ADD_STATE(LP_ST_MAB3_WORK,LP_ST_DM_RUSTAVI_1,i++);
    ADD_STATE(LP_ST_MAB3_WATER,LP_ST_DM_RUSTAVI_1,i++);
    ADD_STATE(LP_ST_MAB4_WORK,LP_ST_DM_RUSTAVI_1,i++);
    ADD_STATE(LP_ST_MAB4_WATER,LP_ST_DM_RUSTAVI_1,i++);
    ADD_STATE(LP_ST_MAB1_BEG,LP_ST_DM_RUSTAVI_1,i++);
    ADD_STATE(LP_ST_MAB2_BEG,LP_ST_DM_RUSTAVI_1,i++);
    ADD_STATE(LP_ST_MAB3_BEG,LP_ST_DM_RUSTAVI_1,i++);
    ADD_STATE(LP_ST_MAB4_BEG,LP_ST_DM_RUSTAVI_1,i++);
/*
    ///MODULE LP_ST_DM_RUSTAVI_2
    i=0;
    ADD_STATE(LP_ST_CNTRL_MODE0,LP_ST_DM_RUSTAVI_2,i++);
    ADD_STATE(LP_ST_CNTRL_MODE1,LP_ST_DM_RUSTAVI_2,i++);
    ADD_STATE(LP_ST_CNTRL_ERROR_STOP,LP_ST_DM_RUSTAVI_2,i++);
    ADD_STATE(LP_ST_CNTRL_ERROR_LEVEL,LP_ST_DM_RUSTAVI_2,i++);
    ADD_STATE(LP_ST_CNTRL_RESERV1,LP_ST_DM_RUSTAVI_2,i++);
    ADD_STATE(LP_ST_CNTRL_LOAD,LP_ST_DM_RUSTAVI_2,i++);
    ADD_STATE(LP_ST_CNTRL_UPLOAD,LP_ST_DM_RUSTAVI_2,i++);
    ADD_STATE(LP_ST_CNTRL_LOAD_OK,LP_ST_DM_RUSTAVI_2,i++);
    ADD_STATE(LP_ST_CNTRL_UPLOAD_OK,LP_ST_DM_RUSTAVI_2,i++);
    ADD_STATE(LP_ST_CNTRL_MAB1_PWORK,LP_ST_DM_RUSTAVI_2,i++);
    ADD_STATE(LP_ST_CNTRL_MAB2_PWORK,LP_ST_DM_RUSTAVI_2,i++);
    ADD_STATE(LP_ST_CNTRL_MAB3_PWORK,LP_ST_DM_RUSTAVI_2,i++);
    ADD_STATE(LP_ST_CNTRL_MAB4_PWORK,LP_ST_DM_RUSTAVI_2,i++);
    ADD_STATE(LP_ST_CNTRL_MAB1_WORK,LP_ST_DM_RUSTAVI_2,i++);
    ADD_STATE(LP_ST_CNTRL_MAB2_WORK,LP_ST_DM_RUSTAVI_2,i++);
    ADD_STATE(LP_ST_CNTRL_MAB3_WORK,LP_ST_DM_RUSTAVI_2,i++);
    ADD_STATE(LP_ST_CNTRL_MAB4_WORK,LP_ST_DM_RUSTAVI_2,i++);
    ADD_STATE(LP_ST_CNTRL_PR1_WORK,LP_ST_DM_RUSTAVI_2,i++);
    ADD_STATE(LP_ST_CNTRL_PR2_WORK,LP_ST_DM_RUSTAVI_2,i++);
    ADD_STATE(LP_ST_CNTRL_PR3_WORK,LP_ST_DM_RUSTAVI_2,i++);
    ADD_STATE(LP_ST_CNTRL_PR4_WORK,LP_ST_DM_RUSTAVI_2,i++);
    ADD_STATE(LP_ST_CNTRL_MEAS_LEN_OK,LP_ST_DM_RUSTAVI_2,i++);

    ///MODULE LP_ST_AM_RUSTAVI_1
    i=0;
    ADD_STATE(LP_ST_UDP_ERROR_CODE,LP_ST_AM_RUSTAVI_1,i++);
    ADD_STATE(LP_ST_UDP_WATER_LEVEL1,LP_ST_AM_RUSTAVI_1,i++);
    ADD_STATE(LP_ST_UDP_WATER_LEVEL2,LP_ST_AM_RUSTAVI_1,i++);
    ADD_STATE(LP_ST_UDP_SPEED_LEN,LP_ST_AM_RUSTAVI_1,i++);
    ADD_STATE(LP_ST_UDP_PIPE_LEN,LP_ST_AM_RUSTAVI_1,i++);
    ADD_STATE(LP_ST_UDP_ZONE_MAB1_ON,LP_ST_AM_RUSTAVI_1,i++);
    ADD_STATE(LP_ST_UDP_ZONE_MAB2_ON,LP_ST_AM_RUSTAVI_1,i++);
    ADD_STATE(LP_ST_UDP_ZONE_MAB3_ON,LP_ST_AM_RUSTAVI_1,i++);
    ADD_STATE(LP_ST_UDP_ZONE_MAB4_ON,LP_ST_AM_RUSTAVI_1,i++);
    ADD_STATE(LP_ST_UDP_ZONE_MAB1_OFF,LP_ST_AM_RUSTAVI_1,i++);
    ADD_STATE(LP_ST_UDP_ZONE_MAB2_OFF,LP_ST_AM_RUSTAVI_1,i++);
    ADD_STATE(LP_ST_UDP_ZONE_MAB3_OFF,LP_ST_AM_RUSTAVI_1,i++);
    ADD_STATE(LP_ST_UDP_ZONE_MAB4_OFF,LP_ST_AM_RUSTAVI_1,i++);
*/
    ADD_STATE(LP_ST_UDP_ERROR_CODE,LP_ST_AM_RUSTAVI_1,0);
    ADD_STATE(LP_ST_UDP_WATER_LEVEL1,LP_ST_AM_RUSTAVI_1,1);
    ADD_STATE(LP_ST_UDP_WATER_LEVEL2,LP_ST_AM_RUSTAVI_1,2);
    ADD_STATE(LP_ST_CNTRL_ERROR_STOP,LP_ST_DM_RUSTAVI_2,2);
    ADD_STATE(LP_ST_CNTRL_ERROR_LEVEL,LP_ST_DM_RUSTAVI_2,3);

    cout<<netDevice<<endl;
}

NetUDPClient_Rustavi::~NetUDPClient_Rustavi()
{
}

void NetUDPClient_Rustavi::CMD_SET_handler()
{

}
void NetUDPClient_Rustavi::CMD_GET_handler()
{

}

void NetUDPClient_Rustavi::send_CMD_SET()
{
    QMutexLocker locker(&mutex);
    netPacket.fill(PC_DM_RUSTAVI_1,netDevice.getPCModule(PC_DM_RUSTAVI_1));
    //netPacket.fill(PC_DM_RUSTAVI_2,netDevice.getPCModule(PC_DM_RUSTAVI_2));
    send_CMD(CMD_SET);
}
void NetUDPClient_Rustavi::send_CMD_GET()
{
    send_CMD(CMD_GET);
}

void NetUDPClient_Rustavi::send_CMD(int _cmd, bool _isWaitForAnswer)
{
    netPacket.fill(_cmd,0,netDevice.getModulesCount());
    //cout<<netPacket;
    send(reinterpret_cast<char*>(netPacket.getPacket()),netPacket.getPacketSize(),_isWaitForAnswer);
}
void NetUDPClient_Rustavi::handler()
{
    //cout<<netPacket;
    if(netPacket.getRes()==(int)RES_ERROR)
    {
        qDebug()<<"NetUDPClient_Rustavi: RES_ERROR!";
    }
    else
    {
        netDevice.setData(netPacket.getData()->modules,netPacket.getHeader()->modules_count);
        //cout<<netDevice;
        switch(netPacket.getCmd())
        {
            case CMD_SET:
                CMD_SET_handler();
                break;
            case CMD_GET:
                CMD_GET_handler();
                break;
        }
    }
    //cout<<netPacket;
}
