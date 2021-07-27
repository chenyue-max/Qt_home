#include "menum.h"
#include "ui_menum.h"
#include <QTabWidget>
#include <QTextEdit>
menum::menum(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::menum)
{
    ui->setupUi(this);
    QWidget *tabCalibration = new QWidget(this);
    QWidget *tabImage = new QWidget(this);
    ui->tabWidget->setTabsClosable(true);

    connect(ui->tabWidget,SIGNAL(tabCloseRequested(int)),this,SLOT(removeSubTab(int)));


}

menum::~menum()
{
    delete ui;
}


void menum::removeSubTab(int index)
{
      ui->tabWidget->removeTab(index);
}

void menum::on_pushButton_clicked()
{
      QTextEdit *edit=new QTextEdit;
      ui->tabWidget->addTab(edit,"hitemp 1");
}
