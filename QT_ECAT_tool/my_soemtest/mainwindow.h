#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMap>
#include <QTimer>
#include <QThread>

#include <inttypes.h>

extern "C"{
#include "ethercat.h"
}

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void getEthInfo(void);                      /* 获取网卡信息 */
    void set_soem_init(void);                   /* 设置从站为Init状态 */
private slots:                                  /* 私有槽函数 */
    void connectToSlavers(void);                /* 连接按钮槽函数，用于处理“连接”按钮的点击事件 */
    void pdoTaskTimout(void);                   /* 定时器槽函数，用于过程数据通信（PDO） */
    void clearTextBrowser(void);                /* 清空TextBrowser */
    void eepromDispSlavers(void);
private:
    Ui::MainWindow *ui;
    QTimer *pdotimer;               /* 定时器对象指针 */
    QMap<QString,QString> ethinfo;  /* 存放网卡信息 */
    QString ifname;                 /* 当前选中的网卡名字 */
    char IOmap[256];                /* PDO 映射的数据缓冲区，用于存储从站过程数据 */
    bool ConnectFlag;               /* 成功初始化标志位 */
};
#endif // MAINWINDOW_H
