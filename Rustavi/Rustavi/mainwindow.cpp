#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QString _ip,int _port,QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setWindowFlags(Qt::WindowStaysOnTopHint|Qt::MSWindowsFixedSizeDialogHint|Qt::FramelessWindowHint);
    client=new NetUDPClient_Rustavi(_ip,_port,this);
    timer =new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(slotTimer()));

    connect(ui->pushButton_Close,SIGNAL(clicked()),this,SLOT(slotClose()));
    connect(ui->pushButton_Post1,SIGNAL(clicked()),this,SLOT(slotToPost1()));
    connect(ui->pushButton_Post2,SIGNAL(clicked()),this,SLOT(slotToPost2()));

    connect(ui->pushButton_RolgangFwd,SIGNAL(clicked()),this,SLOT(slotRolgangFwd()));
    connect(ui->pushButton_RolgangBwd,SIGNAL(clicked()),this,SLOT(slotRolgangBwd()));
    connect(ui->pushButton_RolgangStop,SIGNAL(clicked()),this,SLOT(slotRolgangStop()));

    connect(ui->pushButton_MABRightBEG,SIGNAL(clicked()),this,SLOT(slotMABBeg()));
    connect(ui->pushButton_MABRightWORK,SIGNAL(clicked()),this,SLOT(slotMABWork()));
    connect(ui->pushButton_MABRightWATER,SIGNAL(clicked()),this,SLOT(slotMABWater()));

    connect(ui->pushButton_MABLeftBEG,SIGNAL(clicked()),this,SLOT(slotMABBeg()));
    connect(ui->pushButton_MABLeftWORK,SIGNAL(clicked()),this,SLOT(slotMABWork()));
    connect(ui->pushButton_MABLeftWATER,SIGNAL(clicked()),this,SLOT(slotMABWater()));


    #define ADD_STATE_INDICATOR( IND , WIDGET)  addStateIndicator( IND ,WIDGET)
    #define ADD_STATE_INDICATOR_T( IND , TYPE)  ADD_STATE_INDICATOR( IND ,ui->TYPE##_##IND)
    #define ADD_STATE_INDICATOR_D( IND )        ADD_STATE_INDICATOR_T( IND , pushButton)
    #define ADD_STATE_INDICATOR_A( IND )        ADD_STATE_INDICATOR_T( IND ,label)


    ADD_STATE_INDICATOR_D(LP_ST_ROLGANG_FWD);
    ADD_STATE_INDICATOR_D(LP_ST_ROLGANG_BWD);
    ADD_STATE_INDICATOR_D(LP_ST_MAB1_WORK);
    ADD_STATE_INDICATOR_D(LP_ST_MAB1_BEG);
    ADD_STATE_INDICATOR_D(LP_ST_MAB1_WATER);
    ADD_STATE_INDICATOR_D(LP_ST_MAB2_WORK);
    ADD_STATE_INDICATOR_D(LP_ST_MAB2_BEG);
    ADD_STATE_INDICATOR_D(LP_ST_MAB2_WATER);
    ADD_STATE_INDICATOR_D(LP_ST_MAB3_WORK);
    ADD_STATE_INDICATOR_D(LP_ST_MAB3_BEG);
    ADD_STATE_INDICATOR_D(LP_ST_MAB3_WATER);
    ADD_STATE_INDICATOR_D(LP_ST_MAB4_WORK);
    ADD_STATE_INDICATOR_D(LP_ST_MAB4_BEG);
    ADD_STATE_INDICATOR_D(LP_ST_MAB4_WATER);

    ADD_STATE_INDICATOR_D(LP_ST_CNTRL_ERROR_STOP);
    ADD_STATE_INDICATOR_D(LP_ST_CNTRL_ERROR_LEVEL);
    ADD_STATE_INDICATOR_A(LP_ST_UDP_WATER_LEVEL1);
    ADD_STATE_INDICATOR_A(LP_ST_UDP_WATER_LEVEL2);
    ADD_STATE_INDICATOR_T( LP_ST_UDP_WATER_LEVEL1 ,progressBar);
    ADD_STATE_INDICATOR_T( LP_ST_UDP_WATER_LEVEL2 ,progressBar);
    ADD_STATE_INDICATOR_A(LP_ST_UDP_ERROR_CODE);


    #define ADD_INDICATOR_FRAME( MODULE , TYPE) indicatorFrames.insert(pair<int,TIndicatorFrame*>(MODULE,ui->frame_##MODULE));ui->frame_##MODULE->setName(""#MODULE);ui->frame_##MODULE->setType(TYPE);ui->frame_##MODULE->setIndSize(14);ui->frame_##MODULE->setIndPerLine(16);
    #define ADD_INDICATOR_FRAME_D( MODULE ) ADD_INDICATOR_FRAME( MODULE ,IndicatorType::IND_DIGIT)
    #define ADD_INDICATOR_FRAME_A( MODULE ) ADD_INDICATOR_FRAME( MODULE ,IndicatorType::IND_ANALOG)
    #define ADD_IND( MODULE , NAME ) ui->frame_##MODULE->addIndicator(NAME)

    ADD_INDICATOR_FRAME_D(LP_ST_DM_RUSTAVI_SLOT_0);                 ADD_INDICATOR_FRAME_D(LP_ST_DM_RUSTAVI_SLOT_1);
    ADD_IND(LP_ST_DM_RUSTAVI_SLOT_0,"ASU_PIPE_LOADING");            ADD_IND(LP_ST_DM_RUSTAVI_SLOT_1,"RESERV2");
    ADD_IND(LP_ST_DM_RUSTAVI_SLOT_0,"CLEANER_HOME");                ADD_IND(LP_ST_DM_RUSTAVI_SLOT_1,"SWITCH_RESOLUTION");
    ADD_IND(LP_ST_DM_RUSTAVI_SLOT_0,"POST_CLEANER_BEGIN");          ADD_IND(LP_ST_DM_RUSTAVI_SLOT_1,"SWITCH_SETUP");
    ADD_IND(LP_ST_DM_RUSTAVI_SLOT_0,"POST_CLEANER_END");            ADD_IND(LP_ST_DM_RUSTAVI_SLOT_1,"SWITCH_WORK");
    ADD_IND(LP_ST_DM_RUSTAVI_SLOT_0,"POST_MAB1_BEGIN");             ADD_IND(LP_ST_DM_RUSTAVI_SLOT_1,"SWITCH_TRANSITE");
    ADD_IND(LP_ST_DM_RUSTAVI_SLOT_0,"POST_MAB1_END");               ADD_IND(LP_ST_DM_RUSTAVI_SLOT_1,"BTN_LOAD_PIPE");
    ADD_IND(LP_ST_DM_RUSTAVI_SLOT_0,"POST_MAB2_END");               ADD_IND(LP_ST_DM_RUSTAVI_SLOT_1,"BTN_UPLOAD_PIPE");
    ADD_IND(LP_ST_DM_RUSTAVI_SLOT_0,"POST_MAB1_WORK");              ADD_IND(LP_ST_DM_RUSTAVI_SLOT_1,"SWITCH_ON_CLEANER");
    ADD_IND(LP_ST_DM_RUSTAVI_SLOT_0,"POST_MAB2_WORK");              ADD_IND(LP_ST_DM_RUSTAVI_SLOT_1,"SWITCH_ROLLER_FORTH");
    ADD_IND(LP_ST_DM_RUSTAVI_SLOT_0,"POST_MAB1_HOME");              ADD_IND(LP_ST_DM_RUSTAVI_SLOT_1,"SWITCH_ROLLER_BACK");
    ADD_IND(LP_ST_DM_RUSTAVI_SLOT_0,"POST_MAB2_HOME");              ADD_IND(LP_ST_DM_RUSTAVI_SLOT_1,"BTN_ROLLER_SLOW");
    ADD_IND(LP_ST_DM_RUSTAVI_SLOT_0,"POST_MAB3_BEGIN");             ADD_IND(LP_ST_DM_RUSTAVI_SLOT_1,"BTN_ROLLER_FAST");
    ADD_IND(LP_ST_DM_RUSTAVI_SLOT_0,"POST_MAB3_END");               ADD_IND(LP_ST_DM_RUSTAVI_SLOT_1,"BTN_SPIRAL_SLOW");
    ADD_IND(LP_ST_DM_RUSTAVI_SLOT_0,"POST_MAB4_END");               ADD_IND(LP_ST_DM_RUSTAVI_SLOT_1,"BTN_SPIRAL_FAST");
    ADD_IND(LP_ST_DM_RUSTAVI_SLOT_0,"POST_MAB3_WORK");              ADD_IND(LP_ST_DM_RUSTAVI_SLOT_1,"BTN_UZK1_WATER");
    ADD_IND(LP_ST_DM_RUSTAVI_SLOT_0,"POST_MAB4_WORK");              ADD_IND(LP_ST_DM_RUSTAVI_SLOT_1,"BTN_UZK2_WATER");
    ADD_IND(LP_ST_DM_RUSTAVI_SLOT_0,"POST_MAB3_HOME");              ADD_IND(LP_ST_DM_RUSTAVI_SLOT_1,"BTN_PR1_ON_WORK");
    ADD_IND(LP_ST_DM_RUSTAVI_SLOT_0,"POST_MAB4_HOME");              ADD_IND(LP_ST_DM_RUSTAVI_SLOT_1,"BTN_PR1_ON_HOME");
    ADD_IND(LP_ST_DM_RUSTAVI_SLOT_0,"POST_DP1_BEGIN");              ADD_IND(LP_ST_DM_RUSTAVI_SLOT_1,"BTN_MAB1_ON_WORK");
    ADD_IND(LP_ST_DM_RUSTAVI_SLOT_0,"POST_DP1_END");                ADD_IND(LP_ST_DM_RUSTAVI_SLOT_1,"BTN_MAB1_ON_HOME");
    ADD_IND(LP_ST_DM_RUSTAVI_SLOT_0,"DEVICE_LEVEL");                ADD_IND(LP_ST_DM_RUSTAVI_SLOT_1,"BTN_MAB2_ON_WORK");
    ADD_IND(LP_ST_DM_RUSTAVI_SLOT_0,"POST_PR1_HOME");               ADD_IND(LP_ST_DM_RUSTAVI_SLOT_1,"BTN_MAB2_ON_HOME");
    ADD_IND(LP_ST_DM_RUSTAVI_SLOT_0,"POST_PR1_WORK");               ADD_IND(LP_ST_DM_RUSTAVI_SLOT_1,"BTN_PR2_ON_WORK");
    ADD_IND(LP_ST_DM_RUSTAVI_SLOT_0,"POST_PR2_HOME");               ADD_IND(LP_ST_DM_RUSTAVI_SLOT_1,"BTN_PR2_ON_HOME");
    ADD_IND(LP_ST_DM_RUSTAVI_SLOT_0,"POST_PR2_WORK");               ADD_IND(LP_ST_DM_RUSTAVI_SLOT_1,"BTN_PR3_ON_WORK");
    ADD_IND(LP_ST_DM_RUSTAVI_SLOT_0,"POST_PR3_HOME");               ADD_IND(LP_ST_DM_RUSTAVI_SLOT_1,"BTN_PR3_ON_HOME");
    ADD_IND(LP_ST_DM_RUSTAVI_SLOT_0,"POST_PR3_WORK");               ADD_IND(LP_ST_DM_RUSTAVI_SLOT_1,"BTN_MAB3_ON_WORK");
    ADD_IND(LP_ST_DM_RUSTAVI_SLOT_0,"POST_PR4_HOME");               ADD_IND(LP_ST_DM_RUSTAVI_SLOT_1,"BTN_MAB3_ON_HOME");
    ADD_IND(LP_ST_DM_RUSTAVI_SLOT_0,"POST_PR4_WORK");               ADD_IND(LP_ST_DM_RUSTAVI_SLOT_1,"BTN_MAB4_ON_WORK");
    ADD_IND(LP_ST_DM_RUSTAVI_SLOT_0,"ASU_PIPE_UPLOADING");          ADD_IND(LP_ST_DM_RUSTAVI_SLOT_1,"BTN_MAB4_ON_HOME");
    ADD_IND(LP_ST_DM_RUSTAVI_SLOT_0,"BTN_ERROR_STOP");              ADD_IND(LP_ST_DM_RUSTAVI_SLOT_1,"BTN_PR4_ON_WORK");
    ADD_IND(LP_ST_DM_RUSTAVI_SLOT_0,"RESERV1");                     ADD_IND(LP_ST_DM_RUSTAVI_SLOT_1,"BTN_PR4_ON_HOME");

    ADD_INDICATOR_FRAME_D(LP_ST_DM_RUSTAVI_SLOT_2);                 ADD_INDICATOR_FRAME_D(LP_ST_DM_RUSTAVI_SLOT_3);                         ADD_INDICATOR_FRAME_D(LP_ST_DM_RUSTAVI_SLOT_4);
    ADD_IND(LP_ST_DM_RUSTAVI_SLOT_2,"AC_SUPPLY");                   ADD_IND(LP_ST_DM_RUSTAVI_SLOT_3,"LED_LOADING_PERMITTED");               ADD_IND(LP_ST_DM_RUSTAVI_SLOT_4,"OUT_MAB1_ON_WORK");
    ADD_IND(LP_ST_DM_RUSTAVI_SLOT_2,"AV_AC_SUPPLY_ON");             ADD_IND(LP_ST_DM_RUSTAVI_SLOT_3,"LED_UPLOADING_PERMITTED");             ADD_IND(LP_ST_DM_RUSTAVI_SLOT_4,"OUT_MAB1_ON_HOME");
    ADD_IND(LP_ST_DM_RUSTAVI_SLOT_2,"AV_CLEANER1_ON");              ADD_IND(LP_ST_DM_RUSTAVI_SLOT_3,"LED_ROLLER_SLOW");                     ADD_IND(LP_ST_DM_RUSTAVI_SLOT_4,"OUT_MAB2_ON_WORK");
    ADD_IND(LP_ST_DM_RUSTAVI_SLOT_2,"AV_CLEANER2_ON");              ADD_IND(LP_ST_DM_RUSTAVI_SLOT_3,"LED_ROLLER_FAST");                     ADD_IND(LP_ST_DM_RUSTAVI_SLOT_4,"OUT_MAB2_ON_HOME");
    ADD_IND(LP_ST_DM_RUSTAVI_SLOT_2,"AV_PUMP_ON");                  ADD_IND(LP_ST_DM_RUSTAVI_SLOT_3,"LED_SPIRAL_SLOW");                     ADD_IND(LP_ST_DM_RUSTAVI_SLOT_4,"OUT_MAB3_ON_WORK");
    ADD_IND(LP_ST_DM_RUSTAVI_SLOT_2,"AV_PUMP_STATION1_ON");         ADD_IND(LP_ST_DM_RUSTAVI_SLOT_3,"LED_SPIRAL_FAST");                     ADD_IND(LP_ST_DM_RUSTAVI_SLOT_4,"OUT_MAB3_ON_HOME");
    ADD_IND(LP_ST_DM_RUSTAVI_SLOT_2,"AV_PUMP_STATION2_ON");         ADD_IND(LP_ST_DM_RUSTAVI_SLOT_3,"LED_UZK1_WATER");                      ADD_IND(LP_ST_DM_RUSTAVI_SLOT_4,"OUT_MAB4_ON_WORK");
    ADD_IND(LP_ST_DM_RUSTAVI_SLOT_2,"CONTACTOR_CLEANER1_ON");       ADD_IND(LP_ST_DM_RUSTAVI_SLOT_3,"LED_UZK2_WATER");                      ADD_IND(LP_ST_DM_RUSTAVI_SLOT_4,"OUT_MAB4_ON_HOME");
    ADD_IND(LP_ST_DM_RUSTAVI_SLOT_2,"CONTACTOR_CLEANER2_ON");       ADD_IND(LP_ST_DM_RUSTAVI_SLOT_3,"LED_BRAK");                            ADD_IND(LP_ST_DM_RUSTAVI_SLOT_4,"OUT_PR1_ON_WORK");
    ADD_IND(LP_ST_DM_RUSTAVI_SLOT_2,"CONTACTOR_PUMP_ON");           ADD_IND(LP_ST_DM_RUSTAVI_SLOT_3,"LED_GODEN");                           ADD_IND(LP_ST_DM_RUSTAVI_SLOT_4,"OUT_PR1_ON_HOME");
    ADD_IND(LP_ST_DM_RUSTAVI_SLOT_2,"CONTACTOR_PUMP_STATION1_ON");  ADD_IND(LP_ST_DM_RUSTAVI_SLOT_3,"LED_ERROR_STOP");                      ADD_IND(LP_ST_DM_RUSTAVI_SLOT_4,"OUT_PR2_ON_WORK");
    ADD_IND(LP_ST_DM_RUSTAVI_SLOT_2,"CONTACTOR_PUMP_STATION2_ON");  ADD_IND(LP_ST_DM_RUSTAVI_SLOT_3,"OUT_RESERV1");                         ADD_IND(LP_ST_DM_RUSTAVI_SLOT_4,"OUT_PR2_ON_HOME");
    ADD_IND(LP_ST_DM_RUSTAVI_SLOT_2,"RESERV3");                     ADD_IND(LP_ST_DM_RUSTAVI_SLOT_3,"OUT_RESERV2");                         ADD_IND(LP_ST_DM_RUSTAVI_SLOT_4,"OUT_PR3_ON_WORK");
    ADD_IND(LP_ST_DM_RUSTAVI_SLOT_2,"RESERV4");                     ADD_IND(LP_ST_DM_RUSTAVI_SLOT_3,"OUT_RESERV3");                         ADD_IND(LP_ST_DM_RUSTAVI_SLOT_4,"OUT_PR3_ON_HOME");
    ADD_IND(LP_ST_DM_RUSTAVI_SLOT_2,"RESERV5");                     ADD_IND(LP_ST_DM_RUSTAVI_SLOT_3,"OUT_RESERV4");                         ADD_IND(LP_ST_DM_RUSTAVI_SLOT_4,"OUT_PR4_ON_WORK");
    ADD_IND(LP_ST_DM_RUSTAVI_SLOT_2,"RESERV6");                     ADD_IND(LP_ST_DM_RUSTAVI_SLOT_3,"OUT_RESERV5");                         ADD_IND(LP_ST_DM_RUSTAVI_SLOT_4,"OUT_PR4_ON_HOME");

    ADD_INDICATOR_FRAME_D(LP_ST_DM_RUSTAVI_SLOT_5);                 ADD_INDICATOR_FRAME_D(LP_ST_DM_RUSTAVI_SLOT_6);                         ADD_INDICATOR_FRAME_D(LP_ST_DM_RUSTAVI_MEM_1);
    ADD_IND(LP_ST_DM_RUSTAVI_SLOT_5,"OUT_CLEANER_ON");              ADD_IND(LP_ST_DM_RUSTAVI_SLOT_6,"WATER_LEVEL1");                        ADD_IND(LP_ST_DM_RUSTAVI_MEM_1,"LOCAL_BLIT");
    ADD_IND(LP_ST_DM_RUSTAVI_SLOT_5,"OUT_PUMP1_STATION_ON");        ADD_IND(LP_ST_DM_RUSTAVI_SLOT_6,"WATER_LEVEL2");                        ADD_IND(LP_ST_DM_RUSTAVI_MEM_1,"LOCAL_NBLIT");
    ADD_IND(LP_ST_DM_RUSTAVI_SLOT_5,"OUT_PUMP2_STATION_ON");                                                                                ADD_IND(LP_ST_DM_RUSTAVI_MEM_1,"LOCAL_ERROR");
    ADD_IND(LP_ST_DM_RUSTAVI_SLOT_5,"OUT_PUMP_ON");                 ADD_INDICATOR_FRAME_D(LP_ST_DM_RUSTAVI_SLOT_7);                         ADD_IND(LP_ST_DM_RUSTAVI_MEM_1,"EXTERN_ERROR");
    ADD_IND(LP_ST_DM_RUSTAVI_SLOT_5,"ASU_ERROR_STOP");              ADD_IND(LP_ST_DM_RUSTAVI_SLOT_7,"DIP_SWITCH_1_DEBUG_EXIT");             ADD_IND(LP_ST_DM_RUSTAVI_MEM_1,"LOCAL_RES_OK");
    ADD_IND(LP_ST_DM_RUSTAVI_SLOT_5,"ASU_EXTRACT_ON");              ADD_IND(LP_ST_DM_RUSTAVI_SLOT_7,"DIP_SWITCH_2_SETUP_MOD_DEBUG");        ADD_IND(LP_ST_DM_RUSTAVI_MEM_1,"LOCAL_RES_BRK");
    ADD_IND(LP_ST_DM_RUSTAVI_SLOT_5,"ASU_LOAD_PIPE");               ADD_IND(LP_ST_DM_RUSTAVI_SLOT_7,"DIP_SWITCH_3");                        ADD_IND(LP_ST_DM_RUSTAVI_MEM_1,"LOCAL_CONTROL_ENABLE");
    ADD_IND(LP_ST_DM_RUSTAVI_SLOT_5,"ASU_UPLOAD_PIPE");             ADD_IND(LP_ST_DM_RUSTAVI_SLOT_7,"DIP_SWITCH_4_ENABLE_BEEP");            ADD_IND(LP_ST_DM_RUSTAVI_MEM_1,"LOCAL_PIPE_NPOSTLOAD");
    ADD_IND(LP_ST_DM_RUSTAVI_SLOT_5,"ASU_ROLLER_FORTH");            ADD_IND(LP_ST_DM_RUSTAVI_SLOT_7,"DIP_SWITCH_5_WATER_CONDITIONING");     ADD_IND(LP_ST_DM_RUSTAVI_MEM_1,"LOCAL_MABS_INITED");
    ADD_IND(LP_ST_DM_RUSTAVI_SLOT_5,"ASU_ROLLER_BACK");             ADD_IND(LP_ST_DM_RUSTAVI_SLOT_7,"DIP_SWITCH_6_ENABLE_ERROE_LEVEL");     ADD_IND(LP_ST_DM_RUSTAVI_MEM_1,"LOCAL_PRS_INITED");
    ADD_IND(LP_ST_DM_RUSTAVI_SLOT_5,"ASU_ROLLER_SLOW");             ADD_IND(LP_ST_DM_RUSTAVI_SLOT_7,"DIP_SWITCH_7_ENABLE_ERROE_STOP");      ADD_IND(LP_ST_DM_RUSTAVI_MEM_1,"LOCAL_PIPE_LOADED");
    ADD_IND(LP_ST_DM_RUSTAVI_SLOT_5,"ASU_ROLLER_FAST");             ADD_IND(LP_ST_DM_RUSTAVI_SLOT_7,"DIP_SWITCH_8_ENABLE_CHECK_POWER_AV");  ADD_IND(LP_ST_DM_RUSTAVI_MEM_1,"LOCAL_PIPE_UPLOADED");
    ADD_IND(LP_ST_DM_RUSTAVI_SLOT_5,"ASU_SPIRAL_SLOW");                                                                                     ADD_IND(LP_ST_DM_RUSTAVI_MEM_1,"LOCAL_PIPE_PRESENT");
    ADD_IND(LP_ST_DM_RUSTAVI_SLOT_5,"ASU_SPIRAL_FAST");             ADD_INDICATOR_FRAME_D(LP_ST_DM_RUSTAVI_SLOT_9);                         ADD_IND(LP_ST_DM_RUSTAVI_MEM_1,"LOCAL_PIPE_POS0");
    ADD_IND(LP_ST_DM_RUSTAVI_SLOT_5,"ASU_BRAK");                    ADD_IND(LP_ST_DM_RUSTAVI_SLOT_9,"ROLLER_SPEED1");                       ADD_IND(LP_ST_DM_RUSTAVI_MEM_1,"LOCAL_PIPE_POS1");
    ADD_IND(LP_ST_DM_RUSTAVI_SLOT_5,"ASU_GODEN");                   ADD_IND(LP_ST_DM_RUSTAVI_SLOT_9,"ROLLER_SPEED2");                       ADD_IND(LP_ST_DM_RUSTAVI_MEM_1,"LOCAL_PIPE_POS2");
    ADD_IND(LP_ST_DM_RUSTAVI_SLOT_5,"OUT_WATER1_ON");               ADD_IND(LP_ST_DM_RUSTAVI_SLOT_9,"ROLLER_SPEED3");                       ADD_IND(LP_ST_DM_RUSTAVI_MEM_1,"LOCAL_PIPE_POS3");
    ADD_IND(LP_ST_DM_RUSTAVI_SLOT_5,"OUT_WATER2_ON");               ADD_IND(LP_ST_DM_RUSTAVI_SLOT_9,"ROLLER_SPEED4");                       ADD_IND(LP_ST_DM_RUSTAVI_MEM_1,"LOCAL_PIPE_POS4");
    ADD_IND(LP_ST_DM_RUSTAVI_SLOT_5,"OUT_WATER3_ON");                                                                                       ADD_IND(LP_ST_DM_RUSTAVI_MEM_1,"LOCAL_PIPE_POS5");
    ADD_IND(LP_ST_DM_RUSTAVI_SLOT_5,"OUT_WATER4_ON");                                                                                       ADD_IND(LP_ST_DM_RUSTAVI_MEM_1,"LOCAL_PIPE_POS6");
    ADD_IND(LP_ST_DM_RUSTAVI_SLOT_5,"OUT_WATER_PIPES_OPEN");                                                                                ADD_IND(LP_ST_DM_RUSTAVI_MEM_1,"LOCAL_PIPE_POS7");
    ADD_IND(LP_ST_DM_RUSTAVI_SLOT_5,"OUT_CLEAN_FLAP_OPEN");                                                                                 ADD_IND(LP_ST_DM_RUSTAVI_MEM_1,"LOCAL_PIPE_POS8");
    ADD_IND(LP_ST_DM_RUSTAVI_SLOT_5,"OUT_RESERV6");                                                                                         ADD_IND(LP_ST_DM_RUSTAVI_MEM_1,"LOCAL_PIPE_POS9");
    ADD_IND(LP_ST_DM_RUSTAVI_SLOT_5,"OUT_RESERV7");                                                                                         ADD_IND(LP_ST_DM_RUSTAVI_MEM_1,"LOCAL_PIPE_POS10");
    ADD_IND(LP_ST_DM_RUSTAVI_SLOT_5,"OUT_ASD_LIGHT_R");                                                                                     ADD_IND(LP_ST_DM_RUSTAVI_MEM_1,"LOCAL_PIPE_POS11");
    ADD_IND(LP_ST_DM_RUSTAVI_SLOT_5,"OUT_ASD_LIGHT_Y");
    ADD_IND(LP_ST_DM_RUSTAVI_SLOT_5,"OUT_ASD_LIGHT_G");
    ADD_IND(LP_ST_DM_RUSTAVI_SLOT_5,"OUT_ASD_BEEP");
    ADD_IND(LP_ST_DM_RUSTAVI_SLOT_5,"OUT_RESERV8");
    ADD_IND(LP_ST_DM_RUSTAVI_SLOT_5,"OUT_RESERV9");
    ADD_IND(LP_ST_DM_RUSTAVI_SLOT_5,"OUT_RESERV10");
    ADD_IND(LP_ST_DM_RUSTAVI_SLOT_5,"OUT_RESERV11");

    ADD_INDICATOR_FRAME_D(LP_ST_DM_RUSTAVI_MEM_2);                  ADD_INDICATOR_FRAME_D(LP_ST_DM_RUSTAVI_1);                              ADD_INDICATOR_FRAME_D(LP_ST_DM_RUSTAVI_2);
    ADD_IND(LP_ST_DM_RUSTAVI_MEM_2,"LOCAL_MAB1_INIT");              ADD_IND(LP_ST_DM_RUSTAVI_1,"ROLGANG_FWD");                              ADD_IND(LP_ST_DM_RUSTAVI_2,"CNTRL_MODE0");
    ADD_IND(LP_ST_DM_RUSTAVI_MEM_2,"LOCAL_MAB2_INIT");              ADD_IND(LP_ST_DM_RUSTAVI_1,"ROLGANG_BWD");                              ADD_IND(LP_ST_DM_RUSTAVI_2,"CNTRL_MODE1");
    ADD_IND(LP_ST_DM_RUSTAVI_MEM_2,"LOCAL_MAB3_INIT");              ADD_IND(LP_ST_DM_RUSTAVI_1,"MAB1_WORK");                                ADD_IND(LP_ST_DM_RUSTAVI_2,"CNTRL_ERROR_STOP");
    ADD_IND(LP_ST_DM_RUSTAVI_MEM_2,"LOCAL_MAB4_INIT");              ADD_IND(LP_ST_DM_RUSTAVI_1,"MAB1_WATER");                               ADD_IND(LP_ST_DM_RUSTAVI_2,"CNTRL_ERROR_LEVEL");
    ADD_IND(LP_ST_DM_RUSTAVI_MEM_2,"LOCAL_PR1_INIT");               ADD_IND(LP_ST_DM_RUSTAVI_1,"MAB2_WORK");                                ADD_IND(LP_ST_DM_RUSTAVI_2,"CNTRL_RESERV1");
    ADD_IND(LP_ST_DM_RUSTAVI_MEM_2,"LOCAL_PR2_INIT");               ADD_IND(LP_ST_DM_RUSTAVI_1,"MAB2_WATER");                               ADD_IND(LP_ST_DM_RUSTAVI_2,"CNTRL_LOAD");
    ADD_IND(LP_ST_DM_RUSTAVI_MEM_2,"LOCAL_PR3_INIT");               ADD_IND(LP_ST_DM_RUSTAVI_1,"MAB3_WORK");                                ADD_IND(LP_ST_DM_RUSTAVI_2,"CNTRL_UPLOAD");
    ADD_IND(LP_ST_DM_RUSTAVI_MEM_2,"LOCAL_PR4_INIT");               ADD_IND(LP_ST_DM_RUSTAVI_1,"MAB3_WATER");                               ADD_IND(LP_ST_DM_RUSTAVI_2,"CNTRL_LOAD_OK");
    ADD_IND(LP_ST_DM_RUSTAVI_MEM_2,"LOCAL_MAB1_HOME");              ADD_IND(LP_ST_DM_RUSTAVI_1,"MAB4_WORK");                                ADD_IND(LP_ST_DM_RUSTAVI_2,"CNTRL_UPLOAD_OK");
    ADD_IND(LP_ST_DM_RUSTAVI_MEM_2,"LOCAL_MAB2_HOME");              ADD_IND(LP_ST_DM_RUSTAVI_1,"MAB4_WATER");                               ADD_IND(LP_ST_DM_RUSTAVI_2,"CNTRL_MAB1_PWORK");
    ADD_IND(LP_ST_DM_RUSTAVI_MEM_2,"LOCAL_MAB3_HOME");              ADD_IND(LP_ST_DM_RUSTAVI_1,"MAB1_BEG");                                 ADD_IND(LP_ST_DM_RUSTAVI_2,"CNTRL_MAB2_PWORK");
    ADD_IND(LP_ST_DM_RUSTAVI_MEM_2,"LOCAL_MAB4_HOME");              ADD_IND(LP_ST_DM_RUSTAVI_1,"MAB2_BEG");                                 ADD_IND(LP_ST_DM_RUSTAVI_2,"CNTRL_MAB3_PWORK");
    ADD_IND(LP_ST_DM_RUSTAVI_MEM_2,"LOCAL_PR1_HOME");               ADD_IND(LP_ST_DM_RUSTAVI_1,"MAB3_BEG");                                 ADD_IND(LP_ST_DM_RUSTAVI_2,"CNTRL_MAB4_PWORK");
    ADD_IND(LP_ST_DM_RUSTAVI_MEM_2,"LOCAL_PR2_HOME");               ADD_IND(LP_ST_DM_RUSTAVI_1,"MAB4_BEG");                                 ADD_IND(LP_ST_DM_RUSTAVI_2,"CNTRL_MAB1_WORK");
    ADD_IND(LP_ST_DM_RUSTAVI_MEM_2,"LOCAL_PR3_HOME");                                                                                       ADD_IND(LP_ST_DM_RUSTAVI_2,"CNTRL_MAB2_WORK");
    ADD_IND(LP_ST_DM_RUSTAVI_MEM_2,"LOCAL_PR4_HOME");                                                                                       ADD_IND(LP_ST_DM_RUSTAVI_2,"CNTRL_MAB3_WORK");
    ADD_IND(LP_ST_DM_RUSTAVI_MEM_2,"LOCAL_MAB1_WORK");                                                                                      ADD_IND(LP_ST_DM_RUSTAVI_2,"CNTRL_MAB4_WORK");
    ADD_IND(LP_ST_DM_RUSTAVI_MEM_2,"LOCAL_MAB2_WORK");                                                                                      ADD_IND(LP_ST_DM_RUSTAVI_2,"CNTRL_PR1_WORK");
    ADD_IND(LP_ST_DM_RUSTAVI_MEM_2,"LOCAL_MAB3_WORK");                                                                                      ADD_IND(LP_ST_DM_RUSTAVI_2,"CNTRL_PR2_WORK");
    ADD_IND(LP_ST_DM_RUSTAVI_MEM_2,"LOCAL_MAB4_WORK");                                                                                      ADD_IND(LP_ST_DM_RUSTAVI_2,"CNTRL_PR3_WORK");
    ADD_IND(LP_ST_DM_RUSTAVI_MEM_2,"LOCAL_PR1_WORK");                                                                                       ADD_IND(LP_ST_DM_RUSTAVI_2,"CNTRL_PR4_WORK");
    ADD_IND(LP_ST_DM_RUSTAVI_MEM_2,"LOCAL_PR2_WORK");                                                                                       ADD_IND(LP_ST_DM_RUSTAVI_2,"CNTRL_MEAS_LEN_OK");
    ADD_IND(LP_ST_DM_RUSTAVI_MEM_2,"LOCAL_PR3_WORK");
    ADD_IND(LP_ST_DM_RUSTAVI_MEM_2,"LOCAL_PR4_WORK");
    ADD_IND(LP_ST_DM_RUSTAVI_MEM_2,"LOCAL_MAB1_WATER_ON");
    ADD_IND(LP_ST_DM_RUSTAVI_MEM_2,"LOCAL_MAB2_WATER_ON");
    ADD_IND(LP_ST_DM_RUSTAVI_MEM_2,"LOCAL_MAB3_WATER_ON");
    ADD_IND(LP_ST_DM_RUSTAVI_MEM_2,"LOCAL_MAB4_WATER_ON");

    ADD_INDICATOR_FRAME_A(LP_ST_AM_RUSTAVI_1);                      ADD_INDICATOR_FRAME_D(PC_DM_RUSTAVI_1);                                 ADD_INDICATOR_FRAME_D(PC_DM_RUSTAVI_2);
    ADD_IND(LP_ST_AM_RUSTAVI_1,"UDP_ERROR_CODE:");                   ADD_IND(PC_DM_RUSTAVI_1,"LP_ST_PC_ROLGANG_FWD");                        ADD_IND(PC_DM_RUSTAVI_2,"LP_ST_PC_ERROR");
    ADD_IND(LP_ST_AM_RUSTAVI_1,"UDP_WATER_LEVEL1:");                 ADD_IND(PC_DM_RUSTAVI_1,"LP_ST_PC_ROLGANG_BWD");                        ADD_IND(PC_DM_RUSTAVI_2,"LP_ST_PC_READY");
    ADD_IND(LP_ST_AM_RUSTAVI_1,"UDP_WATER_LEVEL2:");                 ADD_IND(PC_DM_RUSTAVI_1,"LP_ST_PC_MAB1_WORK");                          ADD_IND(PC_DM_RUSTAVI_2,"LP_ST_PC_RES_OK");
    ADD_IND(LP_ST_AM_RUSTAVI_1,"UDP_SPEED_LEN:");                    ADD_IND(PC_DM_RUSTAVI_1,"LP_ST_PC_MAB1_WATER");                         ADD_IND(PC_DM_RUSTAVI_2,"LP_ST_PC_RES_BRK");
    ADD_IND(LP_ST_AM_RUSTAVI_1,"UDP_PIPE_LEN:");                     ADD_IND(PC_DM_RUSTAVI_1,"LP_ST_PC_MAB2_WORK");                          ADD_IND(PC_DM_RUSTAVI_2,"LP_ST_PC_PROCESS");
    ADD_IND(LP_ST_AM_RUSTAVI_1,"UDP_ZONE_MAB1_ON:");                 ADD_IND(PC_DM_RUSTAVI_1,"LP_ST_PC_MAB2_WATER");                         ADD_IND(PC_DM_RUSTAVI_2,"LP_ST_PC_MAB1_MASK");
    ADD_IND(LP_ST_AM_RUSTAVI_1,"UDP_ZONE_MAB2_ON:");                 ADD_IND(PC_DM_RUSTAVI_1,"LP_ST_PC_MAB3_WORK");                          ADD_IND(PC_DM_RUSTAVI_2,"LP_ST_PC_MAB2_MASK");
    ADD_IND(LP_ST_AM_RUSTAVI_1,"UDP_ZONE_MAB3_ON:");                 ADD_IND(PC_DM_RUSTAVI_1,"LP_ST_PC_MAB3_WATER");                         ADD_IND(PC_DM_RUSTAVI_2,"LP_ST_PC_MAB3_MASK");
    ADD_IND(LP_ST_AM_RUSTAVI_1,"UDP_ZONE_MAB4_ON:");                 ADD_IND(PC_DM_RUSTAVI_1,"LP_ST_PC_MAB4_WORK");                          ADD_IND(PC_DM_RUSTAVI_2,"LP_ST_PC_MAB4_MASK");
    ADD_IND(LP_ST_AM_RUSTAVI_1,"UDP_ZONE_MAB1_OFF:");                ADD_IND(PC_DM_RUSTAVI_1,"LP_ST_PC_MAB4_WATER");
    ADD_IND(LP_ST_AM_RUSTAVI_1,"UDP_ZONE_MAB2_OFF:");
    ADD_IND(LP_ST_AM_RUSTAVI_1,"UDP_ZONE_MAB3_OFF:");
    ADD_IND(LP_ST_AM_RUSTAVI_1,"UDP_ZONE_MAB4_OFF:");

    switchToPost(1);
    client->reconnect();
    timer->start(200);
}
void MainWindow::showInfo()
{
    info.showMaximized();
}
#include <QGroupBox>
#include <QScrollArea>
void MainWindow::initInfo(bool _isExtMode)
{
    int r(0),c(0),i(0),colCount(6);
    ui->toolBox->setItemEnabled(2,false);
    QWidget* cWidget=new QWidget(&info);
    info.setCentralWidget(cWidget);
    info.setWindowTitle("АСУ");
    QGridLayout* gLayout = new QGridLayout();


    QHBoxLayout* hLayout = new QHBoxLayout(cWidget);
    QVBoxLayout* vLayout = new QVBoxLayout();
    QScrollArea*  panel= new QScrollArea(&info);
    panel->setSizePolicy(QSizePolicy::Policy::Expanding,QSizePolicy::Policy::Expanding);
    panel->setFrameShape(QFrame::NoFrame);
    panel->setLayout(gLayout);
    cWidget->setLayout(hLayout);
    hLayout->setMargin(4);
    hLayout->setSpacing(4);
    hLayout->addWidget(panel);

    if(_isExtMode)
    {
        hLayout->addLayout(vLayout);
        vLayout->addWidget(centralWidget());
        colCount=4;
    }
    gLayout->setSpacing(4);
    gLayout->setMargin(0);
    cWidget->setGeometry(info.geometry());

    for(auto f:indicatorFrames)
    {
        c=i%colCount;
        r=i/colCount;
        gLayout->addWidget(f.second,r,c);
        f.second->setStyleSheet(ui->tabWidget->styleSheet()+"QFrame{background-color:rgb(225,225,225)}");
        i++;
    }
}
MainWindow::~MainWindow()
{
    timer->stop();
    delete timer;
    delete ui;
    delete client;
}

void MainWindow::switchToPost(int _post)
{
    if(post!=_post)
    {
        post=_post;

        ui->label_Post->setText("УЗК\n№ "+QString().number(post));
        ui->label_MABRight->setText("МАБ\n№"+QString().number(getMABRightNumber()));
        ui->label_MABLeft->setText("МАБ\n№"+QString().number(getMABLeftNumber()));

        ui->pushButton_MABLeftBEG->setToolTip("МАБ №"+QString().number(getMABLeftNumber())+" в исходное");
        ui->pushButton_MABLeftWORK->setToolTip("МАБ №"+QString().number(getMABLeftNumber())+" в рабочее");
        ui->pushButton_MABLeftWATER->setToolTip("вода на МАБ №"+QString().number(getMABLeftNumber()));

        ui->pushButton_MABRightBEG->setToolTip("МАБ №"+QString().number(getMABRightNumber())+" в исходное");
        ui->pushButton_MABRightWORK->setToolTip("МАБ №"+QString().number(getMABRightNumber())+" в рабочее");
        ui->pushButton_MABRightWATER->setToolTip("вода на МАБ №"+QString().number(getMABRightNumber()));

        refreshPost();

        qApp->beep();
    }
}

void MainWindow::refreshPost()
{
    #define REFRESH_POST(POST, NUM , IND )        ui->pushButton_MAB##POST####IND->setChecked( client->getNetDevice()->getState(LP_ST_MAB##NUM##_##IND)? true:false )
    if(post==1)
    {
        REFRESH_POST(Right,1,WORK);
        REFRESH_POST(Right,1,BEG);
        REFRESH_POST(Right,1,WATER);
        REFRESH_POST(Left,2,WORK);
        REFRESH_POST(Left,2,BEG);
        REFRESH_POST(Left,2,WATER);
    }
    else
    {
        REFRESH_POST(Right,3,WORK);
        REFRESH_POST(Right,3,BEG);
        REFRESH_POST(Right,3,WATER);
        REFRESH_POST(Left,4,WORK);
        REFRESH_POST(Left,4,BEG);
        REFRESH_POST(Left,4,WATER);
    }
}

void MainWindow::addStateIndicator(int _id, QWidget* _widget)
{
    stateIndicators.insert(pair<int,QWidget*>(_id,_widget));
}

void MainWindow::refreshStateIndicators()
{
    QPushButton* pButton;
    QProgressBar* pProgress;
    QLabel* pLabel;
    for(auto& ind:stateIndicators)
    {
        pButton=dynamic_cast<QPushButton*>(ind.second);
        pProgress=dynamic_cast<QProgressBar*>(ind.second);
        pLabel=dynamic_cast<QLabel*>(ind.second);
        if(pButton)
            pButton->setChecked(client->getNetDevice()->getState(ind.first)? true:false);
        if(pProgress)
            pProgress->setValue(client->getNetDevice()->getState(ind.first));
        if(pLabel)
            pLabel->setText(QString().number(client->getNetDevice()->getState(ind.first)));
    }

    for(auto& ind:indicatorFrames)
    {
        const NetModule* lpModule=client->getNetDevice()->getLPModule(ind.first);
        if(lpModule!=nullptr)
            ind.second->setValues(lpModule->getIOValues());
    }

}
//SLOTS
void MainWindow::slotTimer()        { client->send_CMD_SET();refreshStateIndicators();refreshPost(); }
void MainWindow::slotClose()        { qApp->quit(); }
void MainWindow::slotToPost2()      { switchToPost(2); }
void MainWindow::slotToPost1()      { switchToPost(1); }
//ROLGANG
void MainWindow::slotRolgangFwd()
{
    client->getNetDevice()->setCommand(LP_CMD_ROLGANG_FWD);
    client->getNetDevice()->setCommand(LP_CMD_ROLGANG_BWD,0);
}
void MainWindow::slotRolgangBwd()
{
    client->getNetDevice()->setCommand(LP_CMD_ROLGANG_BWD);
    client->getNetDevice()->setCommand(LP_CMD_ROLGANG_FWD,0);
}
void MainWindow::slotRolgangStop()
{
    client->getNetDevice()->setCommand(LP_CMD_ROLGANG_BWD,0);
    client->getNetDevice()->setCommand(LP_CMD_ROLGANG_FWD,0);
}
//MAB
void MainWindow::slotMABWork()
{
    int mab_num;
    if(QObject::sender()==ui->pushButton_MABRightWORK)
        mab_num=getMABRightNumber();
    else
        mab_num=getMABLeftNumber();

    switch(mab_num)
    {
        case 1:client->getNetDevice()->setCommand(LP_CMD_MAB1_WORK);break;
        case 2:client->getNetDevice()->setCommand(LP_CMD_MAB2_WORK);break;
        case 3:client->getNetDevice()->setCommand(LP_CMD_MAB3_WORK);break;
        case 4:client->getNetDevice()->setCommand(LP_CMD_MAB4_WORK);break;
    }
}
void MainWindow::slotMABBeg()
{
    int mab_num;
    if(QObject::sender()==ui->pushButton_MABRightBEG)
        mab_num=getMABRightNumber();
    else
        mab_num=getMABLeftNumber();

    switch(mab_num)
    {
        case 1:client->getNetDevice()->setCommand(LP_CMD_MAB1_WORK,0);break;
        case 2:client->getNetDevice()->setCommand(LP_CMD_MAB2_WORK,0);break;
        case 3:client->getNetDevice()->setCommand(LP_CMD_MAB3_WORK,0);break;
        case 4:client->getNetDevice()->setCommand(LP_CMD_MAB4_WORK,0);break;
    }
}
void MainWindow::slotMABWater()
{
    int mab_num,value;
    QPushButton* pButton=dynamic_cast<QPushButton*>(QObject::sender());
    if(pButton==ui->pushButton_MABRightWATER)
        mab_num=getMABRightNumber();
    else
        mab_num=getMABLeftNumber();
    value=(pButton->isChecked())?(1):(0);

    switch(mab_num)
    {
        case 1:client->getNetDevice()->setCommand(LP_CMD_MAB1_WATER,value);break;
        case 2:client->getNetDevice()->setCommand(LP_CMD_MAB2_WATER,value);break;
        case 3:client->getNetDevice()->setCommand(LP_CMD_MAB3_WATER,value);break;
        case 4:client->getNetDevice()->setCommand(LP_CMD_MAB4_WATER,value);break;
    }
}



void MainWindow::mousePressEvent(QMouseEvent* event)
{
    position=event->pos();
}

void MainWindow::mouseReleaseEvent(QMouseEvent*)
{
    position=QPoint(-1,-1);
}

void MainWindow::mouseMoveEvent(QMouseEvent* event)
{
    if (position.x() >= 0 && event->buttons() == Qt::LeftButton)
        this->move(QPoint(this->pos() + event->pos() - position));
    //qDebug()<<cursor().pos().x()<<cursor().pos().y();
}
