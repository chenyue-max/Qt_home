#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    img.load(":/img/9.jpg");
       this->setWindowIcon(QIcon(":/img/待更新.png"));
}

Widget::~Widget()
{
    delete ui;
}

void Widget::paintEvent(QPaintEvent *)
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
