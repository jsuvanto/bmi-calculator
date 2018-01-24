// TIE-02006 fall 2017
// Project 03
// Juha Suvanto 189427
// jsuvanto@iki.fi

#include "mainwindow.hh"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
