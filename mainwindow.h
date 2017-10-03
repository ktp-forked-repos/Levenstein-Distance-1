#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "post.h"
#include "list.h"
#include <QFile>
using namespace A;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
private:
    List list;
    int counter;
    Ui::MainWindow *ui;
    void showPost();
    int D(QString a, QString b);
    int min(int a, int b, int c);
    int m(QChar y, QChar z);
    Post a;
    QFile file;
private slots:
    void addPost();
    void func();
    void size_l();
    void show_l();
    void del_l();
    void isEmpty_l();
    void similar();
    void writeToF();
    void readFromF();
signals:
    void canCheck();


};

#endif // MAINWINDOW_H
