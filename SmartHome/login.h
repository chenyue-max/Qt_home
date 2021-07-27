#ifndef LOGIN_H
#define LOGIN_H

#include <QWidget>
#include <QPaintEvent>
#include <QImage>
#include <QPainter>
#include <resi.h>
#include<menu.h>
#include<weatherwidget.h>

namespace Ui {
class login;
}

class login : public QWidget
{
    Q_OBJECT

public:
    explicit login(QWidget *parent = 0);
    ~login();
  void connDB(); //连接数据库


protected:
    void paintEvent(QPaintEvent *);//绘画事件

private slots:

private slots:

    void showOwn();//让自己显示出来

    void on_loginBt_clicked();

    void on_resiBt_clicked();

    void on_squitBt_clicked();

private:

    Ui::login *ui;
    QImage  img;    //存放背景图片
};

#endif // LOGIN_H
