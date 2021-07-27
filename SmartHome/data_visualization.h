#ifndef DATA_VISUALIZATION_H
#define DATA_VISUALIZATION_H

#include <QWidget>
#include <QImage>
#include <QPainter>
#include <QtCharts>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
namespace Ui {
class data_visualization;
}

class data_visualization : public QWidget
{
    Q_OBJECT


protected:
    void paintEvent(QPaintEvent *);//绘画事件

public:
    explicit data_visualization(QWidget *parent = 0);
    ~data_visualization();
    void zhu();
     void line_temp();
     void connDB();


private slots:
    void on_asd_destroyed();

    void on_quitBtquit_clicked();

private:
    Ui::data_visualization *ui;
        QImage  img;    //存放背景图片
signals:
    void backSignal();
};

#endif // DATA_VISUALIZATION_H

