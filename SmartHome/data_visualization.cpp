#include "data_visualization.h"
#include "ui_data_visualization.h"
#include "QList"
#include <qfile.h>

data_visualization::data_visualization(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::data_visualization)
{
    ui->setupUi(this);
        this->setWindowTitle("数据可视化");
        this->setWindowIcon(QIcon(":/img/数据可视化.png"));
            img.load(":/img/9.jpg");
            ui->tabWidget->setTabText(0,"温度");
            ui->tabWidget->setTabText(1,"LED");
            ui->tabWidget->setStyleSheet("QTabWidget:pane {border-top:0px solid #e8f3f9;background: transparent; }"
                                          "QTabBar::tab {background:#969686}"
                                         "QTabBar::tab {color:#FFFAF0}"
                                         "QTabBar::tab{height:30}"
                                         "QTabBar::tab{width:150}"
                                         "QTabBar::tab{border:none}"
                                         "QTabBar::tab {font:20px;font-weight:bold}");


             line_temp();
             zhu();






}

data_visualization::~data_visualization()
{
    delete ui;
}
void data_visualization::paintEvent(QPaintEvent *)
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
void data_visualization::connDB()
{
    QSqlDatabase db=QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("id.db");
    if(db.open())
    {
        qDebug()<<"数据库打开成功";
    }
    else
    {
        qDebug()<<"数据库打开失败："<<db.lastError().text();
    }
}
void data_visualization::zhu()
{
    //柱状图
            connDB();
            QString cmd="select * from sensordata;";
            QSqlQuery query;
            query.exec(cmd);
            if(query.exec(cmd))
            {
                qDebug()<<"查询成功！";
            }
            else
            {
                qDebug()<<"查询失败"<<query.lastError().text();
            }

       QBarSet *set0 = new QBarSet("temp1");
        QBarSet *set1 = new QBarSet("temp2");
        QStringList categories;
        qint8 i=0,j=0;
        while(query.next())
        {
                i+=1;
        }

        QString cmd1="select * from sensordata;";
        QSqlQuery query1;
        query1.exec(cmd1);
        if(query1.exec(cmd1))
        {
            qDebug()<<"查询成功！";
        }
        else
        {
            qDebug()<<"查询失败"<<query1.lastError().text();
        }


            while(query1.next())
            {
                j+=1;
                if(j>=(i-5))
               {  set1->append(query1.value(1).toFloat());
                set0->append(query1.value(2).toFloat());
                  categories<<query1.value(0).toString().mid(10);}
            }

        QBarSeries *series = new QBarSeries();
           series->append(set0);
           series->append(set1);
           QChart *chart = new QChart();
             chart->addSeries(series);
             chart->setTitle("家庭温度对比图");
              chart->setTitleFont(QFont("微软雅黑"));//设置标题字体
             chart->setAnimationOptions(QChart::SeriesAnimations);
                 QBarCategoryAxis *axisX = new QBarCategoryAxis();
                 axisX->append(categories);
                 chart->addAxis(axisX, Qt::AlignBottom);
                 series->attachAxis(axisX);

                 QValueAxis *axisY = new QValueAxis();
                 axisY->setRange(20,40);
                 chart->addAxis(axisY, Qt::AlignLeft);
                 series->attachAxis(axisY);
                 axisY->setTickCount(5);
                 chart->legend()->setVisible(true);
                    chart->legend()->setAlignment(Qt::AlignRight);
                    QChartView *chartView = new QChartView(chart);
                      chartView->setRenderHint(QPainter::Antialiasing);
                        ui->horizontalLayout->addWidget(chartView);


}
void data_visualization::line_temp()
{
    connDB();
    QString cmd="select * from sensordata;";
    QSqlQuery query;
    query.exec(cmd);
    if(query.exec(cmd))
    {
        qDebug()<<"查询成功！";
    }
    else
    {
        qDebug()<<"查询失败"<<query.lastError().text();
    }

   QChart *m_chart = new QChart();

    QPieSeries *series = new QPieSeries();
    series->append("LED1:40%",4);
    series->append("LED2:10%",1);
    series->append("LED3:20%",2);
    series->append("LED4:30%",3);

    series->setLabelsVisible(true);
    series->setUseOpenGL(true);
    series->slices().at(0)->setColor(QColor(13,128,217));   //设置颜色
    series->slices().at(0)->setLabelColor(QColor(13,128,217));

    series->slices().at(1)->setColor(QColor(69,13,217));
    series->slices().at(1)->setLabelColor(QColor(69,13,217));

    series->slices().at(2)->setColor(QColor(13,217,152));
    series->slices().at(2)->setLabelColor(QColor(13,217,152));

    series->slices().at(3)->setColor(QColor(10,113,51));
    series->slices().at(3)->setLabelColor(QColor(12,116,51));

    m_chart->setTheme(QChart::ChartThemeLight);//设置白色主题
    m_chart->setDropShadowEnabled(true);//背景阴影
    m_chart->addSeries(series);//添加系列到QChart上

    m_chart->setTitleBrush(QBrush(QColor(0,0,0)));//设置标题Brush
    m_chart->setTitleFont(QFont("微软雅黑"));//设置标题字体
    m_chart->setTitle("LED灯使用占比情况");

    //修改说明样式
    m_chart->legend()->setVisible(true);
    m_chart->legend()->setAlignment(Qt::AlignBottom);//底部对齐
    m_chart->legend()->setBackgroundVisible(true);//设置背景是否可视
    m_chart->legend()->setAutoFillBackground(true);//设置背景自动填充
    m_chart->legend()->setColor(QColor(222,233,251));//设置颜色
    m_chart->legend()->setLabelColor(QColor(0,100,255));//设置标签颜色
    m_chart->legend()->setMaximumHeight(50);

    QChartView *chartView = new QChartView(m_chart);
    chartView->setRenderHint(QPainter::Antialiasing);

    QVBoxLayout *pVLayout = new QVBoxLayout(this);
    pVLayout->addWidget(chartView);
             ui->horizontalLayout_2->addWidget(chartView);








//折线图
//                QChart *chart = new QChart();
//                chart->setTitle("折线图演示");

//                QLineSeries *series1 = new QLineSeries(chart);
//                QLineSeries *series2 = new QLineSeries(chart);

//                series1->setName("A店铺接单数");
//                series2->setName("B店铺接单数");

////                series1->append(0,6);
////                series1->append(1,10);
////                series1->append(4,12);
////                series1->append(6,5);

////                                series1->append("2020",6);
////                                series1->append("2021",10);
////                                series2->append("2020",6);
////                                series2->append("2021",10);
////                series2->append(0,18);
////                series2->append(3,13);
////                series2->append(5,7);
////                series2->append(6,2);

//                chart->addSeries(series1);
//                chart->addSeries(series2);

//                QScatterSeries *scatterSeries1 = new QScatterSeries();
//                scatterSeries1->setPointLabelsFormat("@yPoint");
//                scatterSeries1->setPointLabelsVisible();
//                scatterSeries1->setMarkerSize(5);
//                // *scatterSeries1 << QPointF(0,6);也可以
//                scatterSeries1->append(0,6);
//                scatterSeries1->append(1,10);
//                scatterSeries1->append(4,12);
//                scatterSeries1->append(6,5);

//                QScatterSeries *scatterSeries2 = new QScatterSeries();
//                scatterSeries2->setPointLabelsFormat("@yPoint");
//                scatterSeries2->setPointLabelsVisible();
//                scatterSeries2->setMarkerSize(5);
//                scatterSeries2->append(0,18);
//                scatterSeries2->append(3,13);
//                scatterSeries2->append(5,7);
//                scatterSeries2->append(6,2);
//                chart->addSeries(scatterSeries1);
//                chart->addSeries(scatterSeries2);

//                chart->legend()->hide();//隐藏legend（图例）

//                //设置动画效果
//                chart->setAnimationOptions(QChart::AllAnimations);

//                chart->createDefaultAxes();// 设置网格
//                chart->axes(Qt::Horizontal).first()->setRange(0, 7);//设置x轴范围
//                chart->axes(Qt::Vertical).first()->setRange(0, 20);//设置y轴范围

//                // Add space to label to add space between labels and axis 在标签和轴之间加空格
//                QValueAxis *axisY = qobject_cast<QValueAxis*>(chart->axes(Qt::Vertical).first());
//                Q_ASSERT(axisY);
//                axisY->setLabelFormat("%.1f  ");
//                chart->setTheme(QChart::ChartThemeDark);
//                QChartView *chartView;
//                chartView = new QChartView(chart);
//                ui->horizontalLayout_2->addWidget(chartView);
      }


void data_visualization::on_quitBtquit_clicked()
{

        emit backSignal();
        this->hide();

}
