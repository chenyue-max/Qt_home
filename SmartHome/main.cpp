#include "widget.h"
#include <QApplication>
#include<login.h>
#include<weatherwidget.h>
#include<data_visualization.h>
#include<serial.h>
#include<showdata.h>
#include<widget.h>

int main(int argc, char *argv[])
{

    QApplication a(argc, argv);

    QString qss;
    QFile qssFile(":/test.qss");
    qssFile.open(QFile::ReadOnly);
    if(qssFile.isOpen())
    {
      qss = QLatin1String(qssFile.readAll());
      qApp->setStyleSheet(qss);
      qssFile.close();
    }
    login w;
    w.show();

   return a.exec();


}
