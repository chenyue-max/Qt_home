#include "weatherwidget.h"
#include "ui_weatherwidget.h"

WeatherWidget::WeatherWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WeatherWidget)
{
    ui->setupUi(this);
    this->setWindowTitle("天气");
    this->setWindowIcon(QIcon(":/image/weather2.png"));
//    img.load(":/image/timg07.png");
        img.load(":/img/9.jpg");
//    this->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowSystemMenuHint | Qt::WindowMinimizeButtonHint);
    weather=new Weather(QStringLiteral("常熟"));   //默认城市为常熟
    connect(weather,&Weather::getDataSuccessedSignal,this,&WeatherWidget::ShowWeaher);  //接收成功则SHOW
    connect(weather,&Weather::getDataFailedSignal,this,&WeatherWidget::GetWeatherFailed);

    ui->pushButtonMini->setIcon(QIcon(":/image/Min.png"));   //最小化按钮
    ui->pushButtonDestroy->setIcon(QIcon(":/image/Close.png")); //关闭按钮i

    ui->lineEditCityName->setStyleSheet("QLineEdit{background-color: rgba(255,255,225,0.3);border:none;color:#FFFAF0;"
                                        "border-radius:16px;padding:4px 4px}");   //lineEdit圆角样式
    ui->pushButtonQuery->setStyleSheet("QPushButton::hover{font:24px;}"
                                       "QPushButton{background:transparent;color:#FFFAF0}");

    ui->lineEditCityName->setText("常熟");
    ui->tabWidget->setCurrentWidget(ui->tab);



    //绿色背景
    ui->tabWidget->setStyleSheet("QTabBar::tab{height: 1px; width: 150px;}");
    ui->tabWidget->setTabText(0,"今日天气");
    ui->tabWidget->setTabText(1,"昨日/预计天气");
    ui->tableWidget->setColumnWidth(0,100);   //添加四列
    ui->tableWidget->setColumnWidth(1,100);
    ui->tableWidget->setColumnWidth(2,100);
    ui->tableWidget->setColumnWidth(3,140);
    ui->pushButtonMini->setStyleSheet("QPushButton{border:none;color:rgb(122, 197, 205);}"
                                         "QPushButton:hover{background-color: #1E90FF;border:none;color:rgb(255, 255, 255);}");

    ui->pushButtonDestroy->setStyleSheet("QPushButton{border:none;color:rgb(122, 197, 205);}"
                                         "QPushButton:hover{background-color: #FF0000;border:none;color:rgb(255, 255, 255);}");


    ui->tableWidget->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->tableWidget->setShowGrid(false); //无格子线
    ui->tabWidget->setStyleSheet("QTabWidget:pane {border-top:0px solid #e8f3f9;background: transparent; }"
                                  "QTabBar::tab {background:#969686}"
                                 "QTabBar::tab {color:#FFFAF0}"
                                 "QTabBar::tab{height:30}"
                                 "QTabBar::tab{width:150}"
                                 "QTabBar::tab{border:none}"
                                 "QTabBar::tab {font:20px;font-weight:bold}");

    //tableWidget表头样式
    ui->tableWidget->horizontalHeader()->setStyleSheet("QHeaderView::section{background:transparent; padding-left:4px;}"
                                                       "QHeaderView::section:checked{ }");



    ui->tableWidget->verticalHeader()->setVisible(false); //隐藏列表头
    //ui->tableWidget->horizontalHeader()->setVisible(false); //隐藏行表头
   ui->tableWidget->verticalHeader()->setDefaultSectionSize(40);  //设置行高 （除表头外）
    ui->tableWidget->horizontalHeader()->setFixedHeight(40);  //表头行高

//    QMovie *movie = new QMovie(":/image/timg07.gif");   //设置GIF格式背景图
//    QSize si(ui->WeatherWidget->width(),ui->WeatherWidget->height());
//    QSize si(600,400);
//    movie->setScaledSize(si);
//    movie->start();
//    ui->label->setMovie(movie);



}

WeatherWidget::~WeatherWidget()
{
    delete ui;
}

void WeatherWidget::GetWeatherFailed()
{
    ui->lineEditCityName->setText("输入有误");
}

void WeatherWidget::ShowWeaher()    //显示信息
{
    ui->lineEditCity->setText(weather->GetCityName());
//    ui->lineEditTime->setText(weather->GetDate());
    ui->lineEditTemp->setText(weather->GetTemperature()+"度");
    ui->lineEditTempMax->setText(weather->GetTemperatureMax());
    ui->lineEditWin->setText(weather->GetWind());
    ui->lineEditWeatherType->setText(weather->GetWeatherType());
//    ui->textBrowser->setText(weather->GetFluenza());

    ui->tableWidget->clearContents();
    ui->tableWidget->setRowCount(0);

    QMap<QString,QMap<QString,QString>>map=weather->getDataMap();


    //Json文件  例：合肥
    //QJsonDocument({"data":{"city":"合肥",
    //      "forecast":[{"date":"27日星期四","fengli":"<![CDATA[2级]]>",
    //       "fengxiang":"西北风","high":"高温 29℃","low":"低温 21℃","type":"多云"},
    //       {"date":"28日星期五","fengli":"<![CDATA[2级]]>","fengxiang":"北风","high":"高温 30℃","low":"低温 21℃","type":"多云"}
    //       ,{"date":"29日星期六","fengli":"<![CDATA[2级]]>","fengxiang":"东北风","high":"高温 32℃","low":"低温 24℃","type":"多云"},
    //        {"date":"30日星期天","fengli":"<![CDATA[2级]]>","fengxiang":"东北风","high":"高温 31℃","low":"低温 23℃","type":"小雨"},
    //        {"date":"31日星期一","fengli":"<![CDATA[2级]]>","fengxiang":"东北风","high":"高温 29℃","low":"低温 22℃","type":"小雨"}],
    //         "ganmao":"感冒低发期，天气舒适，请注意多吃蔬菜水果，多喝水哦。","wendu":"25","yesterday":{"date":"26日星期三",
    //       "fl":"<![CDATA[3级]]>","fx":"西北风","high":"高温 30℃","low":"低温 24℃","type":"中雨"}},"desc":"OK","status":1000})


    int n=0;
    foreach(QString date,map.keys())
    {
        ui->tableWidget->insertRow(ui->tableWidget->rowCount());
        QMap<QString,QString>mapvalue=map.value(date);

        ui->tableWidget->setItem(n,0,new QTableWidgetItem(date));
        ui->tableWidget->setItem(n,1,new QTableWidgetItem(mapvalue.value("type")));
        QString low=mapvalue.value("low");
        QString high=mapvalue.value("high");
        ui->tableWidget->setItem(n,2,new QTableWidgetItem(low.mid(low.length()-3,4)+"-"+high.mid(high.length()-3,4)));
//        mid 返回一个包含该字符串的n个字符的字符串，从指定的位置索引开始。
//        如果位置索引超过字符串的长度，则返回空字符串。如果从给定位置开始的字符串中可用字符少于n个，或者如果n是-1(默认)，函数将返回指定位置中可用的所有字符。

        QString strength=mapvalue.value("fengli");
        strength.remove(0,8);   //remove 从给定位置索引处开始，从字符串中删除n个字符，并返回对该字符串的引用。
        //如果指定的位置索引在字符串中，但是position + n超出了字符串的末尾，则在指定的位置截断字符串。

        strength.remove(strength.length()-2,2);
        ui->tableWidget->setItem(n,3,new QTableWidgetItem(mapvalue.value("fengxiang")+strength));
        n++;
    }
    weather->getDataMap();
}

void WeatherWidget::mousePressEvent(QMouseEvent *event)
{
    mousePoint = event->pos(); //获取鼠标相对主窗口位置
    if(mousePoint.x()<=0)    //位置横坐标小于0
        return;
    if(mousePoint.x()>=this->width())  //位置大于窗口宽
        return;
    if(mousePoint.y()<=0)    //位置纵坐标小于零
        return;
    if(mousePoint.y()>=this->height())  //位置纵坐标大于窗口高
        return;
    isMouseClick=true; //鼠标已被按下
}

void WeatherWidget::mouseMoveEvent(QMouseEvent *event)
{
    if(isMouseClick)
    {
        QPoint WinMove=event->globalPos()-mousePoint;
        move(WinMove);   //窗口移动是相对于屏幕而言的
    }
}

void WeatherWidget::mouseReleseEvent(QMouseEvent *)
{
    isMouseClick=false;
}

void WeatherWidget::on_pushButtonMini_clicked()//窗口最小化
{
    showMinimized();
}

void WeatherWidget::on_pushButtonDestroy_clicked()//窗口关闭按钮
{
    this->close();
}

void WeatherWidget::on_pushButtonQuery_clicked()  //查询按钮
{
    if(ui->lineEditCityName->text().isEmpty())
        return;
    weather->setCityName(ui->lineEditCityName->text());
    weather->refresh();   //刷新
}

void WeatherWidget::paintEvent(QPaintEvent *)
{
    //绘画人 画在哪
      QPainter painter(this);
      //图片大小
      QRect source(0,0,img.width(),img.height());
      //目标区域大小
      QRect target(0,0,this->width(),this->height());
      //绘画
      painter.drawImage(target,img,source);

}
void WeatherWidget::on_quitBtquit_clicked()
{
    emit backSignal();
    this->hide();
}

