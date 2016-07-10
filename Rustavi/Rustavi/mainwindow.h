#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QScopedPointer>
#include "NetUDPClient_Rustavi.h"
#include "TIndicatorFrame.h"
#include <QTimer>
#include <map>
#include <QMouseEvent>
#include <QDesktopWidget>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QString _ip,int _port, QWidget *parent = 0);
    ~MainWindow();
    void switchToPost(int _post);
    int getMABRightNumber(){return post*2-1;}
    int getMABLeftNumber(){return post*2;}
    void refreshStateIndicators();
    void refreshPost();
    void addStateIndicator(int _id,QWidget* _widget);
    void initInfo(bool _isExtMode=false);
    void showInfo();
private slots:
    void slotClose();
    void slotToPost2();
    void slotToPost1();
    void slotTimer();

    void slotRolgangFwd();
    void slotRolgangBwd();
    void slotRolgangStop();

    void slotMABWork();
    void slotMABBeg();
    void slotMABWater();
private:
    QMainWindow info;
    TIndicatorFrame frame;
    QPoint position{QPoint(-1,-1)};
    int post{0};
    QTimer* timer;
    Ui::MainWindow *ui;
    NetUDPClient_Rustavi* client;
    multimap<int,QWidget*> stateIndicators;
    multimap<int,TIndicatorFrame*> indicatorFrames;

protected:
    void mousePressEvent(QMouseEvent* event);
    void mouseReleaseEvent(QMouseEvent*);
    void mouseMoveEvent(QMouseEvent* event);
};

#endif // MAINWINDOW_H
