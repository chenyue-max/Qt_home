#ifndef SHOWDATAS_H
#define SHOWDATAS_H

#include <QWidget>
#include <QWidget>
#include <QPaintEvent>
#include <QImage>
#include <QPainter>
#include<QLabel>
#include <QSerialPort>
#include <QSerialPortInfo>

namespace Ui {
class showdatas;
}

class showdatas : public QWidget
{
    Q_OBJECT

public:
    explicit showdatas(QWidget *parent = 0);


    ~showdatas();

private:
    Ui::showdatas *ui;
     QImage  img;
     bool clkFlag;

     bool mIsOpen;  //串口按钮是否打开
      //串口对象指针及配置参数
     QSerialPort *mSerialPort;
     QString mPortName;
     QString mBaudRate;
     QString mParity;
     QString mDataBits;
     QString mStopBits;

     bool flag_room;
     bool flag_living;
     bool flag_bee;
     bool flag_bath;
     bool flag_kitchken;
     bool flag_win;
     bool flag_curtain;

    bool flag_lock;

protected:
    void paintEvent(QPaintEvent *);//绘画事件



private slots:
    void on_pushButton_4_clicked();

    void on_kitchenBt_clicked();

    void on_roomBt_clicked();

    void on_bathroomBt_clicked();

    void on_livingBt_clicked();

     void my_btn_fanc(bool clkFlag);

     void  bath_fanc(bool clkFlag);

     void living_fanc(bool clkFlag);

    void livingroom_fanc(bool clkFlag);

    void winbt_fanc(bool clkFlag);

    void  curtain_fanc(bool clkFlag);

    void lock_fanc(bool clkFlag);


    void on_winBt_clicked();

    void on_curtainBt_clicked();

    void on_lockBt_clicked();

signals:
    void backSignal();


};

#endif // SHOWDATAS_H
