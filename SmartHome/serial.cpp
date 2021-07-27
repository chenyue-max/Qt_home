#include "serial.h"
#include "ui_serial.h"
#include "QDebug"

Serial::Serial(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Serial)
{
    ui->setupUi(this);
}

Serial::~Serial()
{
    delete ui;
}


void Serial::on_openPortBtn_clicked()
{

          serial.setPortName("COM1");	//设置COM口
          serial.setBaudRate(QSerialPort::Baud9600,QSerialPort::AllDirections);//设置波特率和读写方向
          serial.setDataBits(QSerialPort::Data8);		//数据位为8位
          serial.setFlowControl(QSerialPort::NoFlowControl);//无流控制
          serial.setParity(QSerialPort::NoParity);	//无校验位
          serial.setStopBits(QSerialPort::OneStop);	//一位停止位
          serial.close();					//先关串口，再打开，可以保证串口不被其它函数占用。
          if(serial.open(QIODevice::ReadWrite))		//以可读写的方式打开串口
          {
              qDebug("device was opened!");
              connect(&serial,SIGNAL(readyRead()),this,SLOT(read_Com()));	//把串口的readyRead()信号绑定到read_Com()这个槽函数上
          }


}
void Serial::read_Com()
{
    QByteArray temp=serial.readAll();//在缓冲区中读一个byte
    if(!temp.isEmpty())//如果读到的数据不为空
    {
       qDebug()<<temp.toHex();
    }

}



