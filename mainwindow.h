#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "post.h"
#include "dynitem.h"

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
    DynItem* curr;
    int matrix[11][11];
    int counter;
    Ui::MainWindow *ui;
    void showPost();
    int D(QString a, QString b);
    int min(int a, int b, int c);
    int m(QChar y, QChar z);
private slots:
    void addPost();
    void func();
signals:
    void canCheck();


};

#endif // MAINWINDOW_H
