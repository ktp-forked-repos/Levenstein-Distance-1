#include <QtGui/QApplication>
#include "mainwindow.h"
#include <QTextStream>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
//    Post b;
//    QTextStream stream (stdout);
//    stream<<b.name<<endl<<b.date<<endl<<b.text<<endl<<endl;
//    Post b1("Georgiy", "20/10/2015", "Hi, Pavel!");
//    stream<<b1.name<<endl<<b1.date<<endl<<b1.text<<endl<<endl;
//    Post b2 = b1;
//    stream<<b2.name<<endl<<b2.date<<endl<<b2.text<<endl<<endl;
    
    return a.exec();  //0;
}
