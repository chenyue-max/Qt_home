#include "menu.h"
#include "ui_menu.h"
#include <QDesktopWidget>
#include <weatherwidget.h>
#include<showdata.h>
#include<showdatas.h>
#include<data_visualization.h>


menu::menu(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::menu)
{
    ui->setupUi(this);
    this->setWindowTitle("选择页面");
   //设计界面的图标
   this->setWindowIcon(QIcon(":/img/选择.png"));
    img.load(":/img/9.jpg");




}

menu::~menu()
{
    delete ui;
}

void menu::paintEvent(QPaintEvent *)
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

void menu::on_quitBtn_clicked()
{
    emit backSignal();
    this->hide();
}

void menu::on_weatherBtn_clicked()
{
    //输入的用户名，密码认证成功 切换界面
    WeatherWidget  *weather= new WeatherWidget ;
    connect(weather,SIGNAL(backSignal()),this,SLOT(showOwn()));
    weather->show();
    this->hide();//两个界面切换 信号和槽 返回主页面
    //this->close(); //来回切换
}
void menu::showOwn()
{
    this->show();
}

void menu::on_pushButton_4_clicked()
{
     showdata *show= new showdata ;
        connect(show,SIGNAL(backSignal()),this,SLOT(showOwn()));
        show->show();
        this->hide();//两个界面切换 信号和槽 返回主页面
        //this->close(); //来回切换
}

void menu::on_pushButton_6_clicked()
{
    //输入的用户名，密码认证成功 切换界面
        showdatas *show1= new showdatas ;
        connect(show1,SIGNAL(backSignal()),this,SLOT(showOwn()));
        show1->show();
        this->hide();//两个界面切换 信号和槽 返回主页面
        //this->close(); //来回切换
}

void menu::on_pushButton_5_clicked()
{
    data_visualization *show2= new data_visualization ;
    connect(show2,SIGNAL(backSignal()),this,SLOT(showOwn()));
    show2->show();
    this->hide();//两个界面切换 信号和槽 返回主页面
    //this->close(); //来回切换
}
