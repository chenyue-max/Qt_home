#ifndef WEATHER_H
#define WEATHER_H

#include<QObject>
#include<QNetworkAccessManager>
#include<QNetworkReply>
#include<QNetworkRequest>
#include<QJsonDocument>
#include<QJsonArray>
#include<QJsonObject>

class Weather : public QObject
{
    Q_OBJECT
public:
    explicit Weather(QObject *parent = nullptr);
    explicit Weather(QString cityName = "");

public:

    void refresh();
    void setCityName(QString city);
    QString GetCityName();  //获取城市
    QString GetDate();    //获取时间
    QString GetTemperature();  //获取当前温度
    QString GetTemperatureMax();  //获取温度范围
    QString GetWind();   //获取风向
    QString GetWeatherType();  //获取天气类型
    QString GetFluenza();   //获取感冒提醒
    QString getAllInfo(); //获取原始的所有字段
    void queryWeather();

    QMap<QString, QMap<QString, QString> > getDataMap(bool *ok=nullptr);    //获取昨天以及未来5天的天气预测

private:
    QNetworkAccessManager *manager;
    QString allInfo;
    QString CityName;
    QString currentDate;
    QString currentTemper;
    QString TemperMax;
    QString Wind;
    QString WeatherType;
    QString Fever;
    bool isGetData=false;//是否成功获取数据
    QMap<QString,QMap<QString,QString>> dataMap;

public slots:
    void replyFinished(QNetworkReply *reply);//刷新的槽

signals:
    void getDataFinisedSignal();//获取数据结束的信号
    void getDataSuccessedSignal();//获取数据成功的信号
    void getDataFailedSignal();//获取数据失败的信号
};

#endif // WEATHER_H

