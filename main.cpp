#include <QtGui/QApplication>
#include "mainwindow.h"
#include <QTextStream>
#include <stdio.h>
#include <cassert>
#include <iostream>


int main(int argc, char *argv[])
{
    QApplication a (argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
