#ifndef MENU_H
#define MENU_H

#include <QWidget>
#include <QPaintEvent>
#include <QImage>
#include <QPainter>
#include<QLabel>
#include<weatherwidget.h>



namespace Ui {
class menu;
}

class menu : public QWidget
{
    Q_OBJECT

public:
    explicit menu(QWidget *parent = 0);
    ~menu();
protected:
    void paintEvent(QPaintEvent *);//绘画事件


private slots:
    void on_quitBtn_clicked();

    void on_weatherBtn_clicked();

    void showOwn();//让自己显示出来

    void on_pushButton_4_clicked();

    void on_pushButton_6_clicked();

    void on_pushButton_5_clicked();

signals:
     void backSignal();

private:
    Ui::menu *ui;
 QImage  img;    //存放背景图片
};

#endif // MENU_H
