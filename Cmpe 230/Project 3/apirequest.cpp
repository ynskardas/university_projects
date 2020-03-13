#include "apirequest.h"
#include <QLabel>
#include <QApplication>
#include <QTableWidget>
#include <QHeaderView>
#include <QRect>
#include <QHBoxLayout>

#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QTime>
#include <QTimer>


using namespace std;

ApiRequest::ApiRequest(QWidget *parent) : QWidget(parent)
{
    QHBoxLayout *layout = new QHBoxLayout;



    table = new QTableWidget(7, 4);
    table->verticalHeader()->setVisible(false);
    table->horizontalHeader()->setVisible(false);
    table->horizontalHeader()->setDefaultSectionSize(120);

    QRect rect = table->geometry();
    rect.setWidth(table->columnWidth(0)*4+12);
    rect.setHeight(table->rowHeight(0)*7+21);
    rect.center();
    table->setGeometry(rect);


    table->setItem(0, 1, new QTableWidgetItem("USD"));
    table->setItem(0, 2, new QTableWidgetItem("EUR"));
    table->setItem(0, 3, new QTableWidgetItem("GBP"));
    table->setItem(1, 0, new QTableWidgetItem("Bitcoin"));
    table->setItem(2, 0, new QTableWidgetItem("Ethereum"));
    table->setItem(3, 0, new QTableWidgetItem("Ripple"));
    table->setItem(4, 0, new QTableWidgetItem("Litecoin"));
    table->setItem(5, 0, new QTableWidgetItem("Monero"));
    table->setItem(6, 0, new QTableWidgetItem("Zcash"));

    layout->addWidget(table);
    setLayout(layout);
    manager = new QNetworkAccessManager(this) ;

    connect(manager, SIGNAL(finished(QNetworkReply *)),this, SLOT(replyFinished(QNetworkReply *)));

    // Initiate retrieval of  the data from the web page.
    // When completed, slot replyFinished will be called.
    manager->get(QNetworkRequest(QUrl("https://api.coingecko.com/api/v3/simple/price?ids=bitcoin,ethereum,ripple,litecoin,monero,zcash&vs_currencies=usd,eur,gbp")));

    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()),
              this, SLOT(repeat()));

        // msec
    timer->start(20000);

}

void ApiRequest::repeat()
{
    manager = new QNetworkAccessManager(this) ;

    connect(manager, SIGNAL(finished(QNetworkReply *)),this, SLOT(replyFinished(QNetworkReply *)));

    // Initiate retrieval of  the data from the web page.
    // When completed, slot replyFinished will be called.
    manager->get(QNetworkRequest(QUrl("https://api.coingecko.com/api/v3/simple/price?ids=bitcoin,ethereum,ripple,litecoin,monero,zcash&vs_currencies=usd,eur,gbp")));
}

void ApiRequest::replyFinished(QNetworkReply *reply)  {
    QTime ct = QTime::currentTime();
    QString time_str = QString("Time:   ") + QString(ct.toString());
    table->setItem(0, 0, new QTableWidgetItem(time_str));
    QString strReply = (QString)reply->readAll();
    QJsonDocument jsonResponse = QJsonDocument::fromJson(strReply.toUtf8());
    QJsonObject jsonObject = jsonResponse.object();

    string coins[6] = { "bitcoin", "ethereum", "ripple", "litecoin", "monero", "zcash"};
    string moneys[3] = { "usd", "eur", "gbp"};
    for(int coin_idx=0;coin_idx<6;coin_idx+=1){
        for(int money_idx=0;money_idx<3;money_idx+=1){
            QJsonValue value = jsonObject.value(QString::fromStdString(coins[coin_idx])).toObject()[QString::fromStdString(moneys[money_idx])];
            table->setItem(1+coin_idx, 1+money_idx, new QTableWidgetItem(value.toVariant().toString()));
        }
    }

}
