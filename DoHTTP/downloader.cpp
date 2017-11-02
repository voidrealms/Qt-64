#include "downloader.h"

downloader::downloader(QObject *parent) :
    QObject(parent)
{
}

void downloader::Do_Download()
{
    http = new QHttp(this);

    connect(http,SIGNAL(stateChanged(int)), this, SLOT(stateChanged(int)));
    connect(http, SIGNAL(responseHeaderReceived(QHttpResponseHeader)),this,SLOT(responseHeaderReceived(QHttpResponseHeader)));
    connect(http,SIGNAL(requestFinished(int,bool)),this,SLOT(requestFinished(int,bool)));

    http->setHost("voidrealms.com");
    http->get("/index.html");
}

void downloader::stateChanged ( int state )
{
    switch(state)
    {
    case 0:
        qDebug() << "Unconnected";
        break;
    case 1:
        qDebug() << "Hhost Lookup";
        break;
    case 2:
        qDebug() << "Connecting";
        break;
    case 3:
        qDebug() << "Sending";
        break;
    case 4:
        qDebug() << "Reading";
        break;
    case 5:
        qDebug() << "Connect";
        break;
    case 6:
        qDebug() << "Closing";
        break;
    }
}

void downloader::responseHeaderReceived ( const QHttpResponseHeader & resp )
{
    qDebug() << "Size" << resp.contentLength();
    qDebug() << "Type" << resp.contentType();
    qDebug() << "Status" << resp.statusCode();
}

void downloader::requestFinished ( int id, bool error )
{
    if(error)
    {
        qDebug() << "ERROR!";
    }
    else
    {
        qDebug() << "OK";

        QFile *file = new QFile("E:/Test/Downloads/test.txt");
        if(file->open(QFile::Append))
        {
            file->write(http->readAll());
            file->flush();
            file->close();
        }
        delete file;
    }
}
