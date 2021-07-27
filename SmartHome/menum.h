#ifndef MENUM_H
#define MENUM_H

#include <QWidget>

namespace Ui {
class menum;
}

class menum : public QWidget
{
    Q_OBJECT

public:
    explicit menum(QWidget *parent = 0);
    ~menum();

signals:
    void backSignal();
      void tabCloseRequested(int index) ;
private slots:
   void removeSubTab(int index);


    void on_pushButton_clicked();
private:
    Ui::menum *ui;
};


#endif // MENUM_H


