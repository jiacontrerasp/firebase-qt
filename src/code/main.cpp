#include <QCoreApplication>
#include <QtNetwork/QNetworkAccessManager>
#include <src/headers/actionhandler.h>
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    ActionHandler *actionHandler=new ActionHandler();
    return a.exec();
}

