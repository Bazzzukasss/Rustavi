#include "mainwindow.h"
#include <QApplication>
#include <QDebug>
#include <QRect>
#include <QFile>

#define LOCALHOST_IP            "127.0.0.1"
#define LINPACK_IP              "192.168.22.6"
#define SERVER_PORT             9123
#define SERVER_IP               LINPACK_IP

#define APLICATION_MODE_STANDART    0
#define APLICATION_MODE_INFO        1
#define APLICATION_MODE_ALL         2
#define APLICATION_MODE_ALL_EXT     3

#define ARGV_LEFT       1
#define ARGV_TOP        2
#define ARGV_WIDTH      3
#define ARGV_HEIGHT     4
#define ARGV_IP         5
#define ARGV_PORT       6
#define ARGV_MODE       7

int main(int argc, char *argv[])
{
    int port(SERVER_PORT);
    int mode(APLICATION_MODE_STANDART);
    QString ip(SERVER_IP);
    QApplication a(argc, argv);

    if(argc>=7)
    {
        ip=argv[ARGV_IP];
        port=atoi(argv[ARGV_PORT]);
    }
    MainWindow w(ip,port);

    if(argc>=5)
    {
        w.setGeometry(QRect( atoi(argv[ARGV_LEFT]),atoi(argv[ARGV_TOP]),atoi(argv[ARGV_WIDTH]),atoi(argv[ARGV_HEIGHT]) ));
        w.centralWidget()->setMaximumWidth(atoi(argv[ARGV_WIDTH]));
        w.centralWidget()->setMinimumHeight(atoi(argv[ARGV_WIDTH]));
    }
    if(argc>=8)
        mode=atoi(argv[ARGV_MODE]);
    switch(mode)
    {
        default:
        case APLICATION_MODE_STANDART:
            w.show();
            break;
        case APLICATION_MODE_INFO:
            w.initInfo();
            w.showInfo();
            break;
        case APLICATION_MODE_ALL:
            w.show();
            w.initInfo();
            w.showInfo();
            break;
        case APLICATION_MODE_ALL_EXT:
            w.initInfo(true);
            w.showInfo();
            break;
    }

    return a.exec();
}
