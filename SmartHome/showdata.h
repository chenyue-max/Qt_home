#ifndef SHOWDATA_H
#define SHOWDATA_H

#include <QWidget>
#include <QPaintEvent>
#include <QImage>
#include <QPainter>
#include <QScrollArea>
#include<QSqlDatabase>
#include<QSqlQuery>
#include<QSqlError>
#include<QDebug>
#include<QPushButton>


namespace Ui {
class showdata;
}

class showdata : public QWidget
{
    Q_OBJECT
protected:
    void paintEvent(QPaintEvent *);//绘画事件
public:
    explicit showdata(QWidget *parent = 0);
    ~showdata();



    void selectData();


private slots:





    void on_pushButton_clicked();

private:
    Ui::showdata *ui;
     QImage  img;
     QString temp1;
      QString temp2;
      QString CO2;
      QString UA;
      QString light;
      QString hum1;
      QString CH4;
      QString hire;
      QString smoke;
      QString person;
      QString PM2;
      QString hum2;
      QString time;

signals:
    void backSignal();
};

#endif // SHOWDATA_H
