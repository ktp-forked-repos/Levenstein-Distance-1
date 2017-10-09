#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "post.h"
#include "list.h"
#include <QFile>

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
    Ui::MainWindow *ui;
    Post a;
    void show_l(List *a);
private slots:
    void addPost();
    void makeTable();
    void size_l();
    void show_l();
    void del_l();
    void sim_l();
    void isEmpty_l();
    void save();
    void load();
};

#endif // MAINWINDOW_H
