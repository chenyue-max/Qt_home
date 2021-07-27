#include "resi.h"
#include "ui_resi.h"
#include<QSqlTableModel>
#include<QSqlQuery>
#include<QMessageBox>
#include<QDebug>
#include<QSqlError>

resi::resi(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::resi)
{
    ui->setupUi(this);
    this->setWindowTitle("注册页面");
   //设计界面的图标
   this->setWindowIcon(QIcon(":/img/6.png"));
   //固定界面大小
   //this->setFixedSize(359,244);
   img.load(":/img/3.png");
}

resi::~resi()
{
    delete ui;
}


void resi::on_quitBt_clicked()
{
     emit backSignal();
     this->hide();
}

void resi::paintEvent(QPaintEvent *)
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


void resi::on_submitBt_clicked()
{
        QString  username = ui->userEdit->text();
        QString  password = ui->passEdit->text();
        QString cmd = "insert into idlogin values("
                      "'%1','%2');";
        cmd = cmd.arg(username).arg(password);
        QSqlQuery query;
        if((username!=NULL & password!=NULL))
        {if(query.exec(cmd))
        {
            QMessageBox::information(this,"注册提示","       注册成功！      ");
        }
        else

        {
            QMessageBox::information(this,"注册提示","       注册失败！       ");
        }
       }
       emit backSignal();
       this->hide();
}
