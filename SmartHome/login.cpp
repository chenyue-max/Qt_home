#include "login.h"
#include "ui_login.h"
#include<QSqlTableModel>
#include<QSqlQuery>
#include<QMessageBox>
#include<QDebug>
#include<QSqlError>
#include<resi.h>
#include<menum.h>

login::login(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::login)
{   connDB();
    ui->setupUi(this);
     this->setWindowTitle("登录页面");
    //设计界面的图标
    this->setWindowIcon(QIcon(":/img/登录 (2).png"));
    //固定界面大小
    this->setFixedSize(359,244);
    img.load(":/img/3.png");
}

login::~login()
{
    delete ui;
}

void login::connDB()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("id.db");
    if(db.open())
    {
        qDebug()<<"数据库打开成功";
    }
    else
    {qDebug()<<"数据库打开未成功";
    }
    QString cmd = "create table idlogin (username varchar(64) ,password varchar(64))";
    QSqlQuery query;
    if(query.exec(cmd))
    {
        qDebug()<<"创建成功";
    }
    else
    {
        qDebug()<<"创建失败"<<query.lastError().text();
    }

}



void login::paintEvent(QPaintEvent *)
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



void login::on_loginBt_clicked()
{
    QString  username = ui->userEdit->text();
    QString  password = ui->passEdit->text();
    QSqlTableModel *model = new QSqlTableModel;
    model->setTable("idlogin");
    model->setFilter(QString("username='%1' and password ='%2'").arg(username).arg(password));
    model->select();
    int row = model->rowCount();
    if(row>0)
    {
//        QMessageBox::information(this,"登陆提示","         登陆成功！                      ");
        //输入的用户名，密码认证成功 切换界面
        menu *menuui = new menu ;
        connect(menuui,SIGNAL(backSignal()),this,SLOT(showOwn()));
        menuui->show();
        this->hide();//两个界面切换 信号和槽 返回主页面
       //this->close(); //来回切换
    }
    else

    {
        QMessageBox::information(this,"登陆提示","          用户不存在，登陆失败！请先注册！                ");
    }

    delete model;


}

void login::on_resiBt_clicked()
{


        //输入的用户名，密码认证成功 切换界面
        resi  *resiui = new resi ;
        connect(resiui,SIGNAL(backSignal()),this,SLOT(showOwn()));
        resiui->show();
        this->hide();//两个界面切换 信号和槽 返回主页面
        //this->close(); //来回切换




}



void login::on_squitBt_clicked()
{
   this->close();
}

void login::showOwn()
{
    this->show();
}





