#ifndef APIREQUEST_H
#define APIREQUEST_H

#include <QMainWindow>
#include <QWidget>
#include <QTableWidget>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>

class ApiRequest : public QWidget
{
    Q_OBJECT
public:
    explicit ApiRequest(QWidget *parent = nullptr);

public slots:
    void replyFinished(QNetworkReply * reply) ;
    void repeat() ;

signals:

private:
    QTableWidget *table;
    QNetworkAccessManager *manager ;
};

#endif // APIREQUEST_H
