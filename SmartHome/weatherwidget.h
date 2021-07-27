#ifndef WEATHERWIDGET_H
#define WEATHERWIDGET_H

#include <QWidget>
#include<QStringList>
#include<QHeaderView>
#include<QTableWidget>
#include<QTabWidget>
#include<QMovie>
#include<QPainter>
#include<QPixmap>
#include<QMouseEvent>
#include<QHeaderView>
#include<QTabBar>
#include"weather.h"

namespace Ui {
class WeatherWidget;
}

class WeatherWidget : public QWidget
{
    Q_OBJECT



protected:
    void paintEvent(QPaintEvent *);//绘画事件

public:
    explicit WeatherWidget(QWidget *parent = 0);
    ~WeatherWidget();

private slots:
    void on_pushButtonMini_clicked();

    void on_pushButtonDestroy_clicked();

    void GetWeatherFailed();

    void ShowWeaher();

    void on_quitBtquit_clicked();


    void on_pushButtonQuery_clicked();
    void on_lineEditTime_cursorPositionChanged(int arg1, int arg2);

private:
    void mousePressEvent(QMouseEvent *event); //鼠标点击事件  //窗口移动
    void mouseMoveEvent(QMouseEvent *event);  //鼠标移动事件  //窗口移动
    void mouseReleseEvent(QMouseEvent *); //鼠标松开事件  //窗口移动
    bool isMouseClick;  //是否被按下
    QPoint mousePoint; //鼠标位置

    Weather *weather;

    bool isgetData=false;
    Ui::WeatherWidget *ui;
    QImage  img;    //存放背景图片
signals:
     void backSignal();

};

#endif // WEATHERWIDGET_H

