#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "post.h"
#include "list.h"
#include <QFile>
#include <QTimer>
#include "dialog.h"

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
    void showList(List *a);
    QTimer *checkTimer;
    Dialog *dial;
private slots:
    void addPost();
    void makeTable();
    void showSize();
    void showList();
    void deleteFromList();
    void similarPosts();
    void showEmptyness();
    void randPost();
    void save();
    void load();
    void checkButtons();
    void changeFirst();
    void changeLast();
};

#endif // MAINWINDOW_H
