
#include "weather.h"

Weather::Weather(QObject *parent) : QObject(parent)
{
    manager = new QNetworkAccessManager(this);  //新建QNetworkAccessManager对象
    connect(manager,SIGNAL(finished(QNetworkReply*)),this,SLOT(replyFinished(QNetworkReply*)));//关联信号和槽
}

Weather::Weather(QString cityName)
{
    manager = new QNetworkAccessManager(this);  //新建QNetworkAccessManager对象
    connect(manager,SIGNAL(finished(QNetworkReply*)),this,SLOT(replyFinished(QNetworkReply*)));//关联信号和槽
    this->CityName=cityName;
    refresh();
}


void Weather::refresh()
{
    this->TemperMax.clear();
    this->currentTemper.clear();
    this->Wind.clear();
    this->WeatherType.clear();
    this->Fever.clear();
    this->allInfo.clear();
    queryWeather();
    dataMap.clear();//刷新的清空，待获取时在加载
}

void Weather::queryWeather()
{
    char request[256]="http://wthrcdn.etouch.cn/weather_mini?city=";  //"http://wthrcdn.etouch.cn/weather_mini?city="为天气服务器接口
    QNetworkRequest quest;
    sprintf(request,"%s%s",request,CityName.toUtf8().data());
    quest.setUrl(QUrl(request));
    quest.setHeader(QNetworkRequest::UserAgentHeader,"RT-Thread ART");
    manager->get(quest);
}


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


QMap<QString, QMap<QString, QString> > Weather::getDataMap(bool *ok)
{
    bool Oktemp;
    if(ok==nullptr)
    {
        ok=&Oktemp;
    }

    if(!this->dataMap.isEmpty())
    {
        *ok=true;
        return this->dataMap;
    }
    *ok=false;
    if(!this->isGetData)   //是否成功获取数据
        return this->dataMap;
    QJsonParseError err;
    QJsonDocument json_recv=QJsonDocument::fromJson(allInfo.toUtf8(),&err);  //解析json对象

    if(!json_recv.isNull())
    {
        QJsonObject object=json_recv.object();
        if(object.contains("data"))
        {
            QJsonValue value=object.value("data");  //获取指定key对应的value
            if(value.isObject())
            {
                QJsonObject object_data=value.toObject();
                if(object_data.contains("yesterday")&&object_data.contains("forecast"))  //若存在昨日或与预测天气则加载所有数据
                {
                    QJsonValue value=object_data.value("yesterday");
                    if(value.isObject())
                    {
                        QMap<QString,QString>mapvalue;
                        mapvalue["high"]=value.toObject().value("high").toString();
                        mapvalue["low"]=value.toObject().value("low").toString();
                        mapvalue["fengxiang"]=value.toObject().value("fx").toString();
                        mapvalue["fengli"]=value.toObject().value("fl").toString();
                        mapvalue["type"]=value.toObject().value("type").toString();
                        dataMap[value.toObject().value("date").toString()]=mapvalue;
                    }
                    value=object_data.value("forecast");
                    if(value.isArray())
                    {
                        QJsonArray valueArray=value.toArray();
                        for(int i=0;i<valueArray.count();i++)
                        {
                            QJsonObject object=valueArray.at(i).toObject();
                            QMap<QString,QString>mapvalue;
                            mapvalue["high"]=object.value("high").toString();
                            mapvalue["low"]=object.value("low").toString();
                            mapvalue["fengxiang"]=object.value("fengxiang").toString();
                            mapvalue["fengli"]=object.value("fengli").toString();
                            mapvalue["type"]=object.value("type").toString();
                            dataMap[object.value("date").toString()]=mapvalue;
                        }
                        *ok=true;
                        return dataMap;
                    }
                }
            }
        }
    }
    return dataMap;
}

void Weather::replyFinished(QNetworkReply *reply) //刷新的槽
{
    this->isGetData=false;
    allInfo=reply->readAll();


    QJsonParseError err;
    QJsonDocument json_recv=QJsonDocument::fromJson(allInfo.toUtf8(),&err);  //解析json对象
    if(!json_recv.isNull())
    {
        QJsonObject object=json_recv.object();

        if(object.contains("data"))
        {
            QJsonValue value=object.value("data");  //获取指定key对应的value
            if(value.isObject())
            {
                QJsonObject object_data=value.toObject();
                this->CityName=object_data.value("city").toString();
                this->currentTemper=object_data.value("wendu").toString();
                this->Fever=object_data.value("ganmao").toString();
                if(object_data.contains("forecast"))
                {
                    QJsonValue value=object_data.value("forecast");
                    if(value.isArray())
                    {
                        QJsonObject today_weather=value.toArray().at(0).toObject();
                        WeatherType=today_weather.value("type").toString();
                        currentDate=today_weather.value("date").toString();

                        QString low=today_weather.value("low").toString();
                        QString high=today_weather.value("high").toString();
                        TemperMax=low.mid(low.length()-3,4)+"-"+high.mid(high.length()-3,4);
                        QString windStrength=today_weather.value("fengli").toString();
                        windStrength.remove(0,8);
                        windStrength.remove(windStrength.length()-2,2);
                        Wind=today_weather.value("fengxiang").toString()+windStrength;
                        this->isGetData=true;
                    }
                }
            }
        }
    }
    reply->deleteLater();
    if(isGetData)
    {
        emit this->getDataSuccessedSignal();
    }
    else
    {
        emit this->getDataFailedSignal();
    }
    emit this->getDataFinisedSignal();
}


QString Weather::getAllInfo()
{
    return this->allInfo;
}
void Weather::setCityName(QString city)
{
    this->CityName=city;
}

QString Weather::GetCityName()
{
    return this->CityName;
}

QString Weather::GetDate()
{
    return this->currentDate;
}

QString Weather::GetTemperature()
{
    return this->currentTemper;
}

QString Weather::GetTemperatureMax()
{
    return this->TemperMax;
}

QString Weather::GetWind()
{
    return this->Wind;
}

QString Weather::GetFluenza()
{
    return this->Fever;
}

QString Weather::GetWeatherType()
{
    return this->WeatherType;
}




