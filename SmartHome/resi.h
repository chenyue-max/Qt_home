#ifndef RESI_H
#define RESI_H

#include <QWidget>
#include <QPaintEvent>
#include <QImage>
#include <QPainter>

namespace Ui {
class resi;
}

class resi : public QWidget
{
    Q_OBJECT

public:
    explicit resi(QWidget *parent = 0);
    ~resi();

private slots:
    void on_quitBt_clicked();

    void on_submitBt_clicked();

protected:
    void paintEvent(QPaintEvent *);//绘画事件




signals:
    void backSignal();

private:
    Ui::resi *ui;
    QImage  img;
};

#endif // RESI_H
