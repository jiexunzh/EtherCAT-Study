#include "mainwindow.h"
#include "ui_mainwindow.h"
extern "C"{
#include "eepromtool.h"
}

MainWindow::~MainWindow()
{
    delete ui;
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    pdotimer = new QTimer();                    /* 初始PDO通信定时器 */
    pdotimer->setTimerType(Qt::PreciseTimer);   /* 设置精确定时器类型，提高精度，但是对于DC同步模式来说，精度还是不够  */

    // 将槽函数connectToSlavers和“连接按钮按下信号”连接起来
    QObject::connect(ui->con_pushButton, &QPushButton::clicked, this, &MainWindow::connectToSlavers);
    // 将槽函数pdoTaskTimout和“定时器超时信号”连接起来
    QObject::connect(pdotimer, &QTimer::timeout, this, &MainWindow::pdoTaskTimout);
    // 将槽函数clearTextBrowser和“清除按钮按下信号”连接起来
    QObject::connect(ui->clear_pushButton, &QPushButton::clicked, this, &MainWindow::clearTextBrowser);

    QObject::connect(ui->eepdisp_pushButton, &QPushButton::clicked, this, &MainWindow::eepromDispSlavers);

    ConnectFlag = false;     /* 默认未连接 */

    /* 获取网卡信息 */
    getEthInfo();
}

/**
 * @brief 获取网卡信息，并显示到组合框
 */
void MainWindow::getEthInfo(void)
{
    ec_adaptert* adapter = NULL;
    adapter = ec_find_adapters();
    while (adapter != NULL)
    {
        ui->eth_comboBox->addItem(QString::fromUtf8(adapter->desc, -1));
        ethinfo.insert(adapter->desc, adapter->name);
        adapter = adapter->next;
    }
    // 释放链表
    ec_free_adapters(adapter);
}

/**
 * @brief 设置所有从站为Init状态
 */
void MainWindow::set_soem_init(void)
{
    /* stop RT thread */
    pdotimer->stop();

    ui->textBrowser->append("Request Init state for all slaves\n");
    ec_slave[0].state = EC_STATE_INIT;
    /* request INIT state for all slaves */
    ec_writestate(0);
    /* stop SOEM, close socket */
    ec_close();

    ConnectFlag = false;
    ui->con_pushButton->setText(QString::fromLocal8Bit("Try to Op"));
}

/**
 * @brief 槽函数，用于配置和切换从站状态
 */
void MainWindow::connectToSlavers(void)
{
    int chk;
    char* eth0;
    /* 获取网卡 */
    ifname = ui->eth_comboBox->currentText();
    QByteArray ba = ethinfo[ifname].toLatin1();
    eth0 = ba.data();

    if (ConnectFlag == false)   /* 建立连接 */
    {
        ui->textBrowser->append("Starting simple test\n");
        /* initialise SOEM, bind socket to eth0 */
        if (ec_init(eth0))
        {
            ui->textBrowser->append(QString::asprintf("ec_init on %s succeeded.\n", eth0));

            /* 扫描从站 */
            if (ec_config_init(FALSE) > 0)  // 扫描EtherCAT网络上的所有从站，并初始化从站配置, 返回值为从站数量
            {
                ui->textBrowser->append(QString::asprintf("%d slaves found and configured.\n",ec_slavecount));     // 从站数量

                ec_config_map(&IOmap);

                ec_configdc();  // 配置从站的分布式时钟（DC）

                /* 配置DC周期 周期理想的状态是和定时器的周期一样，但是由于定时器精度不够，所以周期需要增加，测试不建议使用DC同步模式 */
                // ec_dcsync0(1, TRUE, 50000000, 0);    // 从站1；启用同步；同步周期：50ms；同步偏移：0ns
                ec_dcsync0(1, FALSE, 0, 0);      // 不启用DC同步模式

                ui->textBrowser->append("Slaves mapped, state to SAFE_OP.\n");
                /* wait for all slaves to reach SAFE_OP state */
                ec_statecheck(0, EC_STATE_SAFE_OP, EC_TIMEOUTSTATE * 4);

                // 输出段信息
                ui->textBrowser->append(QString::asprintf("segments : %d : %d %d %d %d\n",ec_group[0].nsegments, \
                                        ec_group[0].IOsegment[0], ec_group[0].IOsegment[1], \
                                        ec_group[0].IOsegment[2], ec_group[0].IOsegment[3]));
                ui->textBrowser->append("Request operational state for all slaves\n");

                // 设置主站的状态为 OP，表示准备进行实时数据传输
                ec_slave[0].state = EC_STATE_OPERATIONAL;
                /* send one valid process data to make outputs in slaves happy*/
                ec_send_processdata();
                ec_receive_processdata(EC_TIMEOUTRET);

                /* 启动PDO通信任务，每20ms发送和接收PDO数据 */
                pdotimer->start(20);

                /* request OP state for all slaves */
                ec_writestate(0);   /* Slave number, 0: all slaves */
                chk = 50;
                /* wait for all slaves to reach OP state */
                do
                {
                    ec_statecheck(0, EC_STATE_OPERATIONAL, 50000);
                }
                while (chk-- && (ec_slave[0].state != EC_STATE_OPERATIONAL));
                if (ec_slave[0].state == EC_STATE_OPERATIONAL)
                {
                    ui->textBrowser->append("Operational state reached for all slaves.\n");
                    ConnectFlag = true;
                    ui->con_pushButton->setText(QString::fromLocal8Bit("Try to Init"));
                }
                else
                {
                    ui->textBrowser->append("Not all slaves reached operational state.\n");
                    ec_readstate();
                    for(int i = 1; i<=ec_slavecount ; i++)
                    {
                        if(ec_slave[i].state != EC_STATE_OPERATIONAL)
                        {
                            ui->textBrowser->append( \
                                        QString::asprintf("Slave %d State=0x%2.2x StatusCode=0x%4.4x : %s\n",
                                                          i, \
                                                          ec_slave[i].state, \
                                                          ec_slave[i].ALstatuscode, \
                                                          ec_ALstatuscode2string(ec_slave[i].ALstatuscode)));
                        }
                    }
                    set_soem_init();
                }
            }
            else
            {
                ui->textBrowser->append("No slaves found\n");
            }
        }
        else
        {
            ui->textBrowser->append("SOEM init fail\n");
        }
    }
    else    /* 关闭连接 */
    {        
        set_soem_init();
    }
}

/**
 * @brief 槽函数，用于PDO通信
 */
void MainWindow::pdoTaskTimout(void)
{
    int wkc = 0;
    ec_send_processdata();  // 将过程数据发送到从站
    wkc = ec_receive_processdata(EC_TIMEOUTRET);    // 接收从站过程数据
}

/**
 * @brief 槽函数，用于清空textBrowser
 */
void MainWindow::clearTextBrowser(void)
{
    ui->textBrowser->clear();  // 直接清空所有内容
}

void MainWindow::eepromDispSlavers(void)
{
    char* eth0;
    /* 获取网卡 */
    ifname = ui->eth_comboBox->currentText();
    QByteArray ba = ethinfo[ifname].toLatin1();
    eth0 = ba.data();

    if (ConnectFlag == true)
    {
        set_soem_init();    // 确保读取时不处于OP状态
    }

    EEPROM_info_t eep_info{};   // C++ 结构体初始化写法
    my_eeprom_display(eth0, 1, (char*)"test.bin", &eep_info);
    ui->textBrowser->append(QString::asprintf("Slave %d data: ", eep_info.slave_num));
    ui->textBrowser->append(QString::asprintf(" Vendor ID        : 0x%8.8X", eep_info.vendor_id));
    ui->textBrowser->append(QString::asprintf(" Product Code     : 0x%8.8X\n", eep_info.product_code));
}
