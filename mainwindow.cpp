#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <stdio.h>
#include <QTextStream>

using namespace Distances;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->textEdit_2->setReadOnly(true);
    ui->pushButton_2->setDisabled(true);
    ui->checkBox_2->isCheckable();
    ui->tableWidget->setEditTriggers(QTableWidget::NoEditTriggers);
    QObject::connect(ui->pushButton, SIGNAL(clicked()), this, SLOT(addPost()));
    QObject::connect(ui->pushButton_2, SIGNAL(clicked()), this, SLOT(makeTable()));
    QObject::connect(ui->pushButton_3, SIGNAL(clicked()), this, SLOT(size_l()));
    QObject::connect(ui->pushButton_4, SIGNAL(clicked()), this, SLOT(isEmpty_l()));
    QObject::connect(ui->pushButton_5, SIGNAL(clicked()), this, SLOT(del_l()));
    QObject::connect(ui->pushButton_6, SIGNAL(clicked()), this, SLOT(show_l()));
    QObject::connect(ui->pushButton_7, SIGNAL(clicked()), this, SLOT(sim_l()));
    QObject::connect(ui->pushButton_8, SIGNAL(clicked()), this, SLOT(save()));
    QObject::connect(ui->pushButton_9, SIGNAL(clicked()), this, SLOT(load()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::isEmpty_l()
{
    if(list.isEmpty()) ui->textEdit_2->append("\nEmpty\n"); else ui->textEdit_2->append("\nNot empty\n");
}

void MainWindow::size_l()
{
    ui->textEdit_2->append("\nSize is "+QString::number(list.size()));
}

void MainWindow::show_l(List *a)
{
    int i = 1;
    for(DynItem *t = a->first; t; t = t->next, i++)
        ui->textEdit_2->append("-----Similar post # "+ QString::number(i)+ "------\nName: "+  (t->data.getName()) +"\nDate: "+ (t->data.getDate())+"\nMessage:\n"+ (t->data.getText())+"\n");
}

void MainWindow::show_l()
{
    int i = 1;
    for(DynItem *t = list.first; t; t = t->next, i++)
        ui->textEdit_2->append("-----Post # "+ QString::number(i)+ "------\nName: "+  (t->data.getName()) +"\nDate: "+ (t->data.getDate())+"\nMessage:\n"+ (t->data.getText())+"\n");
}

void MainWindow::del_l()
{
    if(ui->checkBox_2->isChecked()) list.del_back(); else list.del_front();
    if(list.size()>1) ui->pushButton_2->setEnabled(true); else ui->pushButton_2->setDisabled(true);
}

void MainWindow::sim_l()
{
    Post a(ui->lineEdit->text(), ui->lineEdit_3->text(),ui->textEdit->toPlainText());
    List sim = list.similar(a);
    show_l(&sim);
}

void MainWindow::save()
{
    list.writeToF(ui->lineEdit_2->text());
    ui->textEdit_2->append("Saved to file: "+ui->lineEdit_2->text());
}

void MainWindow::load()
{
    list.readFromF(ui->lineEdit_2->text());
    ui->textEdit_2->append("Load from file: "+ui->lineEdit_2->text());
    if(list.size()>1) ui->pushButton_2->setEnabled(true);
    else ui->pushButton_2->setDisabled(true);
}

void MainWindow::addPost()
{   
        if(list.size()>=1) ui->pushButton_2->setEnabled(true); else ui->pushButton_2->setDisabled(true);
        Post a(ui->lineEdit->text(), ui->lineEdit_3->text(),ui->textEdit->toPlainText());
        if(ui->checkBox->isChecked())
        {
            list.push_back(a);
            ui->textEdit_2->append("-----Post # "+ QString::number(list.size())+ "------\nName: "+  list.pop_back()->data.getName() +"\nDate: "+ list.pop_back()->data.getDate() +"\nMessage:\n"+ list.pop_back()->data.getText()+"\n");
        }
        else
        {
            list.push_front(a);
            ui->textEdit_2->append("-----Post # "+ QString::number(list.size())+ "------\nName: "+  list.pop_front()->data.getName() +"\nDate: "+ list.pop_front()->data.getDate() +"\nMessage:\n"+ list.pop_front()->data.getText()+"\n");
        }
        ui->textEdit->clear();
        ui->lineEdit->clear();
        ui->label_5->setText("Enter message # "+QString::number(list.size()+1));
}

void MainWindow::makeTable()
{
    QTableWidgetItem *cell[list.size()][list.size()];
    ui->tableWidget->setRowCount(list.size());
    ui->tableWidget->setColumnCount(list.size());
    for(int i = 0; i<list.size(); i++)
    {
        ui->tableWidget->setVerticalHeaderItem(i, (new QTableWidgetItem(list[i].data.getName())));
        ui->tableWidget->setHorizontalHeaderItem(i, (new QTableWidgetItem(list[i].data.getName())));
    }
    for(int i = 0; i<list.size(); i++)
    {
        for(int j = i; j<list.size(); j++)
        {
            int hamming = distHamming((list[i].data.getText()), (list[j].data.getText()));
            QString D_Lev = QString::number(distLevenstein((list[i].data.getText()), (list[j].data.getText())));
            QString D_Ham = hamming == -1 ? "#" : QString::number(hamming);
            cell[i][j] = new QTableWidgetItem(D_Lev+" "+D_Ham);
            if(i!=j) cell[j][i] = new QTableWidgetItem(D_Lev+" "+D_Ham);
            ui->tableWidget->setItem(i, j , cell[i][j]);
            ui->tableWidget->setItem(j, i , cell[j][i]);
        }
    }
}
