#include "showdata.h"
#include "ui_showdata.h"
#include <QFile>
#include<QScrollArea>
#include<QPushButton>
#include<QSqlTableModel>
#include<QSqlQuery>
#include<QLabel>
#include<QscrollArea>
#include<QCheckBox>



showdata::showdata(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::showdata)
{

    ui->setupUi(this);
    selectData();
    this->setWindowTitle("数据展示");
    this->setWindowIcon(QIcon(":/img/数据 展示.png"));
    QString qss;
    QFile qssFile(":/test.qss");
    qssFile.open(QFile::ReadOnly);
    if(qssFile.isOpen())
    {
      qss = QLatin1String(qssFile.readAll());
      qApp->setStyleSheet(qss);
      qssFile.close();
    }


    img.load(":/img/9.jpg");


      QPalette pa;
      pa.setColor(QPalette::WindowText,Qt::white);
      ui->pmLb->setPalette(pa);
       ui->pmLb->setText(PM2);





       QPalette pua;
       pua.setColor(QPalette::WindowText,Qt::white);
       ui->uaLb->setPalette(pua);
        ui->uaLb->setText(UA);




        QPalette pco;
        pco.setColor(QPalette::WindowText,Qt::white);
        ui->co2Lb->setPalette(pco);
        ui->co2Lb->setText(CO2);


        QPalette pch4;
        pch4.setColor(QPalette::WindowText,Qt::white);
        ui->ch4Lb->setPalette(pch4);
        ui->ch4Lb->setText(CH4);


        QPalette prtem1;
        prtem1.setColor(QPalette::WindowText,Qt::white);
        ui->roomteLb->setPalette(prtem1);
        ui->roomteLb->setText(temp1+"℃");

        QPalette prhum1;
        prhum1.setColor(QPalette::WindowText,Qt::white);
        ui->roomhumLb->setPalette(prhum1);
        ui->roomhumLb->setText(hum1+"%rh");

        QPalette pltem2;
        pltem2.setColor(QPalette::WindowText,Qt::white);
        ui->livingteLb->setPalette(pltem2);
        ui->livingteLb->setText(temp2+"℃");

        QPalette plhum2;
        plhum2.setColor(QPalette::WindowText,Qt::white);
        ui->livinghumLb->setPalette(plhum2);
        ui->livinghumLb->setText(hum2+"%rh");


        QPalette plpe;
        plpe.setColor(QPalette::WindowText,Qt::white);
        ui->peopelLb->setPalette(plpe);
        if("0" == person)
        {ui->peopelLb->setText("无");}
        else
        {
            ui->peopelLb->setText("有");
        }


        QPalette pfire;
        pfire.setColor(QPalette::WindowText,Qt::white);
        ui->fireLb->setPalette(pfire);
        ui->fireLb->setText(hire);

        QPalette pfrog;
        pfrog.setColor(QPalette::WindowText,Qt::white);
        ui->frogLb->setPalette(pfrog);
        ui->frogLb->setText(smoke);

        QPalette ptime;
        ptime.setColor(QPalette::WindowText,Qt::white);
        ui->timeLb->setPalette(pfire);
        ui->timeLb->setText(time);

}











showdata::~showdata()
{
    delete ui;
}




void showdata::paintEvent(QPaintEvent *)
{
    //绘画人 画在哪
     QPainter painter(this);
     //图片大小
    QRect source(0,0,img.width(),img.height());
     //目标区域大小
     QRect target(0,0,this->width(),this->height());
     //绘画
    painter.drawImage(target,img,source);




}

void showdata::selectData()
{
    QSqlDatabase db=QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("id.db");
    if(db.open())
    {
        qDebug()<<"数据库打开成功";
    }
    else
    {
        qDebug()<<"数据库打开失败："<<db.lastError().text();
    }

    QString cmd="select * from sensordata;";
    QSqlQuery query;
    if(query.exec(cmd))
    {
        qDebug()<<"查询成功";
    }
    else

    {
        qDebug()<<"查询失败"<<query.lastError().text();
    }  while (query.last())
    {
        //id-0 name-1 age-2
        qDebug()<<"数据time:"<<query.value(0).toString();
        qDebug()<<"数据temp1:"<<query.value(1).toString();
        qDebug()<<"数据temp2:"<<query.value(2).toString();
        qDebug()<<"数据CO2:"<<query.value(3).toString();
        qDebug()<<"数据UA:"<<query.value(4).toString();
        qDebug()<<"数据light:"<<query.value(5).toString();
        qDebug()<<"数据hum1:"<<query.value(6).toString();
        qDebug()<<"数据CH4:"<<query.value(7).toString();
        qDebug()<<"数据hire:"<<query.value(8).toString();
        qDebug()<<"数据smoke:"<<query.value(9).toString();
        qDebug()<<"数据person:"<<query.value(10).toString();
        qDebug()<<"数据PM2:"<<query.value(11).toString();
        qDebug()<<"数据hum2:"<<query.value(12).toString();
        time=query.value(0).toString();
        temp1=query.value(1).toString();
        temp2=query.value(2).toString();
        CO2=query.value(3).toString();
        UA=query.value(4).toString();
        light=query.value(5).toString();
        hum1=query.value(6).toString();
        CH4=query.value(7).toString();
        hire=query.value(8).toString();
        smoke=query.value(9).toString();
        person=query.value(10).toString();
        PM2=query.value(11).toString();
        hum2=query.value(12).toString();
        break;

    }



}


void showdata::on_pushButton_clicked()
{
    emit backSignal();
    this->hide();
}







