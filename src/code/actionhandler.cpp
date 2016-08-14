#include "src/headers/actionhandler.h"
#include <QUrl>
#include <src/headers/firebase.h>
ActionHandler::ActionHandler()
{
    Firebase *firebase=new Firebase("https://jiacp-firebase.firebaseio.com/");
    firebase->setToken("o4XzD4KnhMjeqCnLoPLHemYsB48Xbp8XuSEkWKwG");

    qDebug()<<"Create firebase object and set token";
    firebase->getValue();
    qDebug()<<"Get values";
    firebase->listenEvents();
    qDebug()<<"Listen events";
    connect(firebase,SIGNAL(eventResponseReady(QString)),this,SLOT(onResponseReady(QString)));
    connect(firebase,SIGNAL(eventDataChanged(DataSnapshot*)),this,SLOT(onDataChanged(DataSnapshot*)));

    qDebug()<<"Conecting...";
}
void ActionHandler::onResponseReady(QString data)
{
    qDebug()<<"answer";
    qDebug()<<data;
}
void ActionHandler::onDataChanged(DataSnapshot *data)
{
    qDebug()<<data->getDataMap();
}
