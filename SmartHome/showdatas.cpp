#include "showdatas.h"
#include "ui_showdatas.h"
#include <menu.h>


showdatas::showdatas(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::showdatas)
{

    ui->setupUi(this);

    mSerialPort = new QSerialPort; //创建一个串口对象
    mIsOpen = false; //初始化按钮状态标志位
    flag_living = false;
    flag_room = false;
    flag_bath = false;
    flag_kitchken = false;
    flag_win = false;
    flag_curtain=false;
    flag_bee = false;
    flag_lock=false;

   this->startTimer(100);
     this->setWindowTitle("开关控制");
    //设计界面的图标
    this->setWindowIcon(QIcon(":/img/灯泡开关.png"));
    ui->kitchenBt->setCheckable(true);
    ui->roomBt->setCheckable(true);
    ui->livingBt->setCheckable(true);
    ui->bathroomBt->setCheckable(true);
    ui->winBt->setCheckable(true);
    ui->curtainBt->setCheckable(true);
    ui->lockBt->setCheckable(true);
    img.load(":/img/9.jpg");
    connect(ui->kitchenBt,SIGNAL(clicked(bool)),this,SLOT(my_btn_fanc(bool)));
    connect(ui->roomBt,SIGNAL(clicked(bool)),this,SLOT(bath_fanc(bool)));
    connect(ui->bathroomBt,SIGNAL(clicked(bool)),this,SLOT(living_fanc(bool)));
    connect(ui->livingBt,SIGNAL(clicked(bool)),this,SLOT(livingroom_fanc(bool)));
    connect(ui->winBt,SIGNAL(clicked(bool)),this,SLOT(winbt_fanc(bool)));
    connect(ui->curtainBt,SIGNAL(clicked(bool)),this,SLOT(curtain_fanc(bool)));
     connect(ui->lockBt,SIGNAL(clicked(bool)),this,SLOT(lock_fanc(bool)));


}






showdatas::~showdatas()
{
    delete ui;
}
void showdatas::on_pushButton_4_clicked()
{

    emit backSignal();
    this->hide();
}

void showdatas::my_btn_fanc(bool clkFlag)
{
  if(clkFlag) {
      ui->kitchenBt->setStyleSheet("QPushButton{border-image: url(:/img/开关2.png);border:none;color:rgb(255, 255, 255);}");
      ui->roomLb->setStyleSheet("QLabel{border-image: url(:/img/厨房2.png);border:none;color:rgb(255, 255, 255);}");

    }
    else {
      ui->kitchenBt->setStyleSheet("QPushButton{border-image: url(:/img/开关1.png);border:none;color:rgb(255, 255, 255);}");
     ui->roomLb->setStyleSheet("QLabel{border-image: url(:/img/厨房1(1).png);border:none;color:rgb(255, 255, 255);}");


    }

}


void showdatas::bath_fanc(bool clkFlag)
{
    if(clkFlag){
        ui->roomBt->setStyleSheet("QPushButton{border-image: url(:/img/开关2.png);border:none;color:rgb(255, 255, 255);}");
        ui->bathLb->setStyleSheet("QLabel{border-image: url(:/img/卧室2.png);border:none;color:rgb(255, 255, 255);}");

    }
    else{
        ui->roomBt->setStyleSheet("QPushButton{border-image: url(:/img/开关1.png);border:none;color:rgb(255, 255, 255);}");
        ui->bathLb->setStyleSheet("QLabel{border-image: url(:/img/卧室1.png);border:none;color:rgb(255, 255, 255);}");
    }
}

void showdatas::living_fanc(bool clkFlag)
{
   if(clkFlag){

      ui->bathroomBt->setStyleSheet("QPushButton{border-image: url(:/img/开关2.png);border:none;color:rgb(255, 255, 255);}");
      ui->livingLb->setStyleSheet("QLabel{border-image: url(:/img/浴室2.png);border:none;color:rgb(255, 255, 255);}");
    }
    else{
     ui->bathroomBt->setStyleSheet("QPushButton{border-image: url(:/img/开关1.png);border:none;color:rgb(255, 255, 255);}");
     ui->livingLb->setStyleSheet("QLabel{border-image: url(:/img/浴室1.png);border:none;color:rgb(255, 255, 255);}");
    }

}

void showdatas::livingroom_fanc(bool clkFlag)
{
    if(clkFlag){

        ui->livingBt->setStyleSheet("QPushButton{border-image: url(:/img/开关2.png);border:none;color:rgb(255, 255, 255);}");
        ui->label->setStyleSheet("QLabel{border-image: url(:/img/客厅2.png);border:none;color:rgb(255, 255, 255);}");

    }
    else{
        ui->livingBt->setStyleSheet("QPushButton{border-image: url(:/img/开关1.png);border:none;color:rgb(255, 255, 255);}");
        ui->label->setStyleSheet("QLabel{border-image: url(:/img/客厅1.png);border:none;color:rgb(255, 255, 255);}");
    }
}

void showdatas::winbt_fanc(bool clkFlag)
{
    if(clkFlag){

        ui->winBt->setStyleSheet("QPushButton{border-image: url(:/img/开关2.png);border:none;color:rgb(255, 255, 255);}");
        ui->winLb->setStyleSheet("QLabel{border-image: url(:/img/风扇.png);border:none;color:rgb(255, 255, 255);}");

    }
    else{
        ui->winBt->setStyleSheet("QPushButton{border-image: url(:/img/开关1.png);border:none;color:rgb(255, 255, 255);}");
        ui->winLb->setStyleSheet("QLabel{border-image: url(:/img/风扇 (1).png);border:none;color:rgb(255, 255, 255);}");

    }
}

void showdatas::curtain_fanc(bool clkFlag)
{
    if(clkFlag){

        ui->curtainBt->setStyleSheet("QPushButton{border-image: url(:/img/开关2.png);border:none;color:rgb(255, 255, 255);}");
        ui->curtainLb->setStyleSheet("QLabel{border-image: url(:/img/窗帘 (1).png);border:none;color:rgb(255, 255, 255);}");

    }
    else{
        ui->curtainBt->setStyleSheet("QPushButton{border-image: url(:/img/开关1.png);border:none;color:rgb(255, 255, 255);}");
        ui->curtainLb->setStyleSheet("QLabel{border-image: url(:/img/窗帘.png);border:none;color:rgb(255, 255, 255);}");

    }
}

void showdatas::lock_fanc(bool clkFlag)
{
    if(clkFlag){

        ui->lockBt->setStyleSheet("QPushButton{border-image: url(:/img/开关2.png);border:none;color:rgb(255, 255, 255);}");
        ui->lockLb->setStyleSheet("QLabel{border-image: url(:/img/门锁 (1).png);border:none;color:rgb(255, 255, 255);}");

    }
    else{
        ui->lockBt->setStyleSheet("QPushButton{border-image: url(:/img/开关1.png);border:none;color:rgb(255, 255, 255);}");
        ui->lockLb->setStyleSheet("QLabel{border-image: url(:/img/门锁.png);border:none;color:rgb(255, 255, 255);}");

    }
}

void showdatas::paintEvent(QPaintEvent *)
{
    //绘画人 画在哪
     QPainter painter(this);
     //图片大小
    QRect source(0,0,img.width(),img.height());
     //目标区域大小
     QRect target(0,0,this->width(),this->height());
     //绘画
     painter.drawImage(target,img,source);
     //定义画笔
     QPen pen;
     pen.setWidth(1);

     pen.setColor(QColor(255,255,255)); //rgb设定颜色
     pen.setStyle(Qt::DashLine); //设置风格

     //把画笔给画家
      painter.setPen(pen);



      painter.drawRect(25, 85, 255,300);

      painter.drawRect(330,85,255,300);







}


void showdatas::on_kitchenBt_clicked()
{
ui->kitchenBt->setStyleSheet("QPushButton{border-image: url(:/img/开关 关 (3).png);border:none;color:rgb(255, 255, 255);}");
QByteArray btn_data;
mPortName ="COM9";
mSerialPort->setPortName(mPortName);
mSerialPort->setBaudRate(QSerialPort::Baud9600);
mSerialPort->setParity(QSerialPort::NoParity);
mSerialPort->setDataBits(QSerialPort::Data8);
mSerialPort->setStopBits(QSerialPort::OneStop);
mSerialPort->close();
if(true ==  mSerialPort->open(QSerialPort::ReadWrite))
{
   mIsOpen = true;
   qDebug() << "成功打开串口" << mPortName;

}

if(false == flag_kitchken)
 { QByteArray btn_data;
    btn_data[0] = 0xFE;
    btn_data[1] = 0xFE;
    btn_data[2] = 0x00;
    btn_data[3] = 0xFF;
    btn_data[4] = 0xFF;
    btn_data[5] = 0x0A;
    btn_data[6] = 0x10;
    btn_data[7] = 0x13;
    btn_data[8] = 0xFF;
    btn_data[9] = 0xFF;
    mSerialPort->write(btn_data);
    qDebug()<<"开";
   // ui->roomBt->setText("关闭");
        flag_kitchken = true;
 }
 else
 {
    btn_data[0] = 0xFE;
    btn_data[1] = 0xFE;
    btn_data[2] = 0x00;
    btn_data[3] = 0xFF;
    btn_data[4] = 0xFF;
    btn_data[5] = 0x0A;
    btn_data[6] = 0x10;
    btn_data[7] = 0x13;
    btn_data[8] = 0x00;
    btn_data[9] = 0xFF;
    mSerialPort->write(btn_data);
    qDebug()<<"关";
   // ui->roomBt->setText("打开");
    flag_kitchken = false;
 }
}

void showdatas::on_roomBt_clicked()
{
    ui->roomBt->setStyleSheet("QPushButton{border-image: url(:/img/开关 关 (3).png);border:none;color:rgb(255, 255, 255);}");

    QByteArray btn_data;
    mPortName ="COM9";
    mSerialPort->setPortName(mPortName);
    mSerialPort->setBaudRate(QSerialPort::Baud9600);
    mSerialPort->setParity(QSerialPort::NoParity);
    mSerialPort->setDataBits(QSerialPort::Data8);
    mSerialPort->setStopBits(QSerialPort::OneStop);
    mSerialPort->close();
   if(true ==  mSerialPort->open(QSerialPort::ReadWrite))
  {
       mIsOpen = true;
       qDebug() << "成功打开串口" << mPortName;

   }

    if(false == flag_room)
     { QByteArray btn_data;
        btn_data[0] = 0xFE;
        btn_data[1] = 0xFE;
        btn_data[2] = 0x00;
        btn_data[3] = 0xFF;
        btn_data[4] = 0xFF;
        btn_data[5] = 0x0A;
        btn_data[6] = 0x10;
        btn_data[7] = 0x12;
        btn_data[8] = 0xFF;
        btn_data[9] = 0xFF;
        mSerialPort->write(btn_data);
        qDebug()<<"开";
       // ui->roomBt->setText("关闭");
            flag_room = true;
     }
     else
     {
        btn_data[0] = 0xFE;
        btn_data[1] = 0xFE;
        btn_data[2] = 0x00;
        btn_data[3] = 0xFF;
        btn_data[4] = 0xFF;
        btn_data[5] = 0x0A;
        btn_data[6] = 0x10;
        btn_data[7] = 0x12;
        btn_data[8] = 0x00;
        btn_data[9] = 0xFF;
        mSerialPort->write(btn_data);
        qDebug()<<"关";
       // ui->roomBt->setText("打开");
        flag_room = false;
     }

}

void showdatas::on_bathroomBt_clicked()
{
    ui->bathroomBt->setStyleSheet("QPushButton{border-image: url(:/img/开关 关 (3).png);border:none;color:rgb(255, 255, 255);}");

    QByteArray btn_data;
    mPortName ="COM9";
    mSerialPort->setPortName(mPortName);
    mSerialPort->setBaudRate(QSerialPort::Baud9600);
    mSerialPort->setParity(QSerialPort::NoParity);
    mSerialPort->setDataBits(QSerialPort::Data8);
    mSerialPort->setStopBits(QSerialPort::OneStop);
    mSerialPort->close();
   if(true ==  mSerialPort->open(QSerialPort::ReadWrite))
  {
       mIsOpen = true;
       qDebug() << "成功打开串口" << mPortName;

   }

    if(false == flag_bath)
     { QByteArray btn_data;
        btn_data[0] = 0xFE;
        btn_data[1] = 0xFE;
        btn_data[2] = 0x00;
        btn_data[3] = 0xFF;
        btn_data[4] = 0xFF;
        btn_data[5] = 0x0A;
        btn_data[6] = 0x10;
        btn_data[7] = 0x11;
        btn_data[8] = 0xFF;
        btn_data[9] = 0xFF;
        mSerialPort->write(btn_data);
        qDebug()<<"开";
       // ui->roomBt->setText("关闭");
            flag_bath = true;
     }
     else
     {
        btn_data[0] = 0xFE;
        btn_data[1] = 0xFE;
        btn_data[2] = 0x00;
        btn_data[3] = 0xFF;
        btn_data[4] = 0xFF;
        btn_data[5] = 0x0A;
        btn_data[6] = 0x10;
        btn_data[7] = 0x11;
        btn_data[8] = 0x00;
        btn_data[9] = 0xFF;
        mSerialPort->write(btn_data);
        qDebug()<<"关";
       // ui->roomBt->setText("打开");
        flag_bath = false;
     }
}

void showdatas::on_livingBt_clicked()
{
    ui->livingBt->setStyleSheet("QPushButton{border-image: url(:/img/开关 关 (3).png);border:none;color:rgb(255, 255, 255);}");

    QByteArray btn_data;
    mPortName ="COM9";
    mSerialPort->setPortName(mPortName);
    mSerialPort->setBaudRate(QSerialPort::Baud9600);
    mSerialPort->setParity(QSerialPort::NoParity);
    mSerialPort->setDataBits(QSerialPort::Data8);
    mSerialPort->setStopBits(QSerialPort::OneStop);
    mSerialPort->close();
   if(true ==  mSerialPort->open(QSerialPort::ReadWrite))
  {
       mIsOpen = true;
       qDebug() << "成功打开串口" << mPortName;

   }

    if(false == flag_living)
     { QByteArray btn_data;
        btn_data[0] = 0xFE;
        btn_data[1] = 0xFE;
        btn_data[2] = 0x00;
        btn_data[3] = 0xFF;
        btn_data[4] = 0xFF;
        btn_data[5] = 0x0A;
        btn_data[6] = 0x10;
        btn_data[7] = 0x14;
        btn_data[8] = 0xFF;
        btn_data[9] = 0xFF;
        mSerialPort->write(btn_data);
        qDebug()<<"开";
       // ui->roomBt->setText("关闭");
            flag_living = true;
     }
     else
     {
        btn_data[0] = 0xFE;
        btn_data[1] = 0xFE;
        btn_data[2] = 0x00;
        btn_data[3] = 0xFF;
        btn_data[4] = 0xFF;
        btn_data[5] = 0x0A;
        btn_data[6] = 0x10;
        btn_data[7] = 0x14;
        btn_data[8] = 0x00;
        btn_data[9] = 0xFF;
        mSerialPort->write(btn_data);
        qDebug()<<"关";
       // ui->roomBt->setText("打开");
        flag_living = false;
     }
}


void showdatas::on_winBt_clicked()
{
ui->winBt->setStyleSheet("QPushButton{border-image: url(:/img/开关 关 (3).png);border:none;color:rgb(255, 255, 255);}");
QByteArray btn_data;
mPortName ="COM9";
mSerialPort->setPortName(mPortName);
mSerialPort->setBaudRate(QSerialPort::Baud9600);
mSerialPort->setParity(QSerialPort::NoParity);
mSerialPort->setDataBits(QSerialPort::Data8);
mSerialPort->setStopBits(QSerialPort::OneStop);
mSerialPort->close();
if(true ==  mSerialPort->open(QSerialPort::ReadWrite))
{
   mIsOpen = true;
   qDebug() << "成功打开串口" << mPortName;

}

if(false == flag_win)
 {
    QByteArray btn_data;
    btn_data[0] = 0xFE;
    btn_data[1] = 0xFE;
    btn_data[2] = 0x00;
    btn_data[3] = 0xFF;
    btn_data[4] = 0xFF;
    btn_data[5] = 0x0A;
    btn_data[6] = 0x70;
    btn_data[7] = 0x27;
    btn_data[8] = 0x01;
    btn_data[9] = 0xFF;
    mSerialPort->write(btn_data);
    qDebug()<<"开";
   // ui->roomBt->setText("关闭");
        flag_win = true;
 }
 else
 {
    btn_data[0] = 0xFE;
    btn_data[1] = 0xFE;
    btn_data[2] = 0x00;
    btn_data[3] = 0xFF;
    btn_data[4] = 0xFF;
    btn_data[5] = 0x0A;
    btn_data[6] = 0x70;
    btn_data[7] = 0x27;
    btn_data[8] = 0x02;
    btn_data[9] = 0xFF;
    mSerialPort->write(btn_data);
    qDebug()<<"关";
   // ui->roomBt->setText("打开");
    flag_win = false;
 }
}



void showdatas::on_curtainBt_clicked()
{
    ui->curtainBt->setStyleSheet("QPushButton{border-image: url(:/img/开关 关 (3).png);border:none;color:rgb(255, 255, 255);}");
    QByteArray btn_data;
    mPortName ="COM9";
    mSerialPort->setPortName(mPortName);
    mSerialPort->setBaudRate(QSerialPort::Baud9600);
    mSerialPort->setParity(QSerialPort::NoParity);
    mSerialPort->setDataBits(QSerialPort::Data8);
    mSerialPort->setStopBits(QSerialPort::OneStop);
    mSerialPort->close();
    if(true ==  mSerialPort->open(QSerialPort::ReadWrite))
    {
       mIsOpen = true;
       qDebug() << "成功打开串口" << mPortName;

    }

    if(false == flag_curtain)
     {
        QByteArray btn_data;
        btn_data[0] = 0xFE;
        btn_data[1] = 0xFE;
        btn_data[2] = 0x00;
        btn_data[3] = 0xFF;
        btn_data[4] = 0xFF;
        btn_data[5] = 0x0A;
        btn_data[6] = 0x70;
        btn_data[7] = 0x26;
        btn_data[8] = 0x01;
        btn_data[9] = 0xFF;
        mSerialPort->write(btn_data);
        qDebug()<<"开";
       // ui->roomBt->setText("关闭");
            flag_curtain = true;
     }
     else
     {
        btn_data[0] = 0xFE;
        btn_data[1] = 0xFE;
        btn_data[2] = 0x00;
        btn_data[3] = 0xFF;
        btn_data[4] = 0xFF;
        btn_data[5] = 0x0A;
        btn_data[6] = 0x70;
        btn_data[7] = 0x26;
        btn_data[8] = 0x02;
        btn_data[9] = 0xFF;
        mSerialPort->write(btn_data);
        qDebug()<<"关";
       // ui->roomBt->setText("打开");
        flag_curtain = false;
     }
}

void showdatas::on_lockBt_clicked()
{
    ui->lockBt->setStyleSheet("QPushButton{border-image: url(:/img/开关 关 (3).png);border:none;color:rgb(255, 255, 255);}");
    QByteArray btn_data;
    mPortName ="COM9";
    mSerialPort->setPortName(mPortName);
    mSerialPort->setBaudRate(QSerialPort::Baud9600);
    mSerialPort->setParity(QSerialPort::NoParity);
    mSerialPort->setDataBits(QSerialPort::Data8);
    mSerialPort->setStopBits(QSerialPort::OneStop);
    mSerialPort->close();
    if(true ==  mSerialPort->open(QSerialPort::ReadWrite))
    {
       mIsOpen = true;
       qDebug() << "成功打开串口" << mPortName;

    }

    if(false == flag_lock)
     {
        QByteArray btn_data;
        btn_data[0] = 0xFE;
        btn_data[1] = 0xFE;
        btn_data[2] = 0x00;
        btn_data[3] = 0xFF;
        btn_data[4] = 0xFF;
        btn_data[5] = 0x0A;
        btn_data[6] = 0x80;
        btn_data[7] = 0x2A;
        btn_data[8] = 0x01;
        btn_data[9] = 0xFF;
        mSerialPort->write(btn_data);
        qDebug()<<"开";
       // ui->roomBt->setText("关闭");
            flag_lock = true;
     }
     else
     {
        btn_data[0] = 0xFE;
        btn_data[1] = 0xFE;
        btn_data[2] = 0x00;
        btn_data[3] = 0xFF;
        btn_data[4] = 0xFF;
        btn_data[5] = 0x0A;
        btn_data[6] = 0x80;
        btn_data[7] = 0x2A;
        btn_data[8] = 0x02;
        btn_data[9] = 0xFF;
        mSerialPort->write(btn_data);
        qDebug()<<"关";
       // ui->roomBt->setText("打开");
        flag_lock = false;
     }
}
