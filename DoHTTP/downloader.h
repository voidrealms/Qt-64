#ifndef DOWNLOADER_H
#define DOWNLOADER_H

#include <QObject>
#include <QHttp>
#include <QFile>
#include <QDebug>


class downloader : public QObject
{
    Q_OBJECT
public:
    explicit downloader(QObject *parent = 0);

    void Do_Download();

signals:

public slots:
    void stateChanged ( int state );
    void responseHeaderReceived ( const QHttpResponseHeader & resp );
    void requestFinished ( int id, bool error );

private:
    QHttp *http;

};

#endif // DOWNLOADER_H
