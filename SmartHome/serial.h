#ifndef SERIAL_H
#define SERIAL_H
#include <QtSerialPort/QSerialPort>
#include <QWidget>

namespace Ui {
class Serial;
}

class Serial : public QWidget
{
    Q_OBJECT

public:
    explicit Serial(QWidget *parent = 0);
    ~Serial();

private slots:
    void on_openPortBtn_clicked();
    void read_Com();

private:
    Ui::Serial *ui;
     QSerialPort serial;			//声明串口类
};

#endif // RESI_H




