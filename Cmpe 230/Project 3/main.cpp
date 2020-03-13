#include "mainwindow.h"
#include "apirequest.h"

#include <QApplication>
#include <QTableWidget>
#include <QHeaderView>
#include <QRect>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ApiRequest areq;

    areq.show();

    return a.exec();
}
