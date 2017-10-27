#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <dialog.h>
#include <stdio.h>
#include <QTextStream>

using namespace Distances;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    checkTimer = new QTimer;
    checkTimer->start(100);
    ui->textEdit_2->setReadOnly(true);
    ui->pushButton_2->setDisabled(true);
    ui->tableWidget->setEditTriggers(QTableWidget::NoEditTriggers);
    ui->progressBar->setVisible(false);
    ui->progressBar->setValue(0);
    QObject::connect(ui->pushButton, SIGNAL(clicked()), this, SLOT(addPost()));
    QObject::connect(ui->pushButton_2, SIGNAL(clicked()), this, SLOT(makeTable()));
    QObject::connect(ui->pushButton_3, SIGNAL(clicked()), this, SLOT(showSize()));
    QObject::connect(ui->pushButton_4, SIGNAL(clicked()), this, SLOT(showEmptyness()));
    QObject::connect(ui->pushButton_5, SIGNAL(clicked()), this, SLOT(deleteFromList()));
    QObject::connect(ui->pushButton_6, SIGNAL(clicked()), this, SLOT(showList()));
    QObject::connect(ui->pushButton_7, SIGNAL(clicked()), this, SLOT(similarPosts()));
    QObject::connect(ui->pushButton_8, SIGNAL(clicked()), this, SLOT(save()));
    QObject::connect(ui->pushButton_9, SIGNAL(clicked()), this, SLOT(load()));
    QObject::connect(ui->pushButton_10, SIGNAL(clicked()), this, SLOT(randPost()));
    QObject::connect(ui->pushButton_11, SIGNAL(clicked()), this, SLOT(changeFirst()));
    QObject::connect(ui->pushButton_12, SIGNAL(clicked()), this, SLOT(changeLast()));
    QObject::connect(checkTimer, SIGNAL(timeout()), this, SLOT(checkButtons()));
    ui->mainToolBar->addWidget(ui->pushButton_3);
    ui->mainToolBar->addSeparator();
    ui->mainToolBar->addWidget(ui->pushButton_4);
    ui->mainToolBar->addSeparator();
    ui->mainToolBar->addWidget(ui->pushButton_6);
    ui->mainToolBar->addSeparator();
    ui->mainToolBar->addWidget(ui->pushButton_7);
    ui->mainToolBar->addSeparator();
    ui->mainToolBar->addWidget(ui->pushButton_2);
    this->setFixedSize(824, 674);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::changeFirst()
{
    dial = new Dialog;
    dial->changingPost = &list.front();
    dial->show();
}

void MainWindow::changeLast()
{
    dial = new Dialog;
    dial->changingPost = &list.back();
    dial->show();
}

void MainWindow::checkButtons()
{
    if(list.size()<2) ui->pushButton_2->setDisabled(true);
    else ui->pushButton_2->setEnabled(true);
    if(ui->lineEdit->text()==""||ui->lineEdit_3->text()==""||ui->textEdit->toPlainText()=="") ui->pushButton->setDisabled(true);
    else ui->pushButton->setEnabled(true);
    if(ui->lineEdit->text()==""||ui->lineEdit_3->text()==""||ui->textEdit->toPlainText()==""||list.isEmpty()) ui->pushButton_7->setDisabled(true);
    else ui->pushButton_7->setEnabled(true);
    if(ui->lineEdit_2->text()==""||list.isEmpty()) ui->pushButton_8->setDisabled(true);
    else ui->pushButton_8->setEnabled(true);
    if(ui->lineEdit_2->text()=="") ui->pushButton_9->setDisabled(true);
    else ui->pushButton_9->setEnabled(true);
    if(list.isEmpty()) ui->pushButton_5->setDisabled(true), ui->pushButton_6->setDisabled(true);
    else ui->pushButton_5->setEnabled(true),ui->pushButton_6->setEnabled(true);
    if(list.isEmpty()) ui->pushButton_11->setDisabled(true), ui->pushButton_12->setDisabled(true);
    else ui->pushButton_11->setEnabled(true), ui->pushButton_12->setEnabled(true);
}

void MainWindow::showEmptyness()
{
    if(list.isEmpty()) ui->textEdit_2->append("\nEmpty\n"); else ui->textEdit_2->append("\nNot empty\n");
}

void MainWindow::showSize()
{
    ui->textEdit_2->append("\nSize is "+QString::number(list.size()));
}

void MainWindow::showList(List *a)
{
    for(int i = 0; i<a->size(); i++)
        ui->textEdit_2->append("-----Similar post # "+ QString::number(i+1)+ "------\nName: "+  ((*a)[i].getName()) +"\nDate: "+ ((*a)[i].getDate())+"\nMessage:\n"+ ((*a)[i].getText())+"\n");
}

void MainWindow::showList()
{
    for(int i = 0; i<list.size(); i++)
        ui->textEdit_2->append("-----Post # "+ QString::number(i+1)+ "------\nName: "+  (list[i].getName()) +"\nDate: "+ (list[i].getDate())+"\nMessage:\n"+ (list[i].getText())+"\n");
}

void MainWindow::deleteFromList()
{
    if(ui->checkBox->isChecked()) list.pop_back(); else list.pop_front();
    if(list.size()>1) ui->pushButton_2->setEnabled(true); else ui->pushButton_2->setDisabled(true);
}

void MainWindow::similarPosts()
{
    Post a(ui->lineEdit->text(), ui->lineEdit_3->text(),ui->textEdit->toPlainText());
    List sim = list.similar(a);
    showList(&sim);
}

void MainWindow::save()
{
    list.writeToFile(ui->lineEdit_2->text());
    ui->textEdit_2->append("Saved to file: "+ui->lineEdit_2->text());
}

void MainWindow::load()
{
    list.readFromFile(ui->lineEdit_2->text());
    ui->textEdit_2->append("Load from file: "+ui->lineEdit_2->text());
}

void MainWindow::addPost()
{    
    if(ui->checkBox->isChecked())
    {
        if(!ui->checkBox_3->isChecked())
            list.push_back(new Post(ui->lineEdit->text(), ui->lineEdit_3->text(),ui->textEdit->toPlainText())),ui->textEdit_2->append("-----Last post-----\n");
        else
            list.push_back(new HiddenPost(ui->lineEdit_3->text(),ui->textEdit->toPlainText())), ui->textEdit_2->append("-----Last post-----\n");
        ui->textEdit_2->append( "Name: "+  list.back().getName() +"\nDate: "+ list.back().getDate() +"\nMessage:\n"+ list.back().getText()+"\n");
    }
    else
    {
        if(!ui->checkBox_3->isChecked())
            list.push_front(new Post(ui->lineEdit->text(), ui->lineEdit_3->text(),ui->textEdit->toPlainText())), ui->textEdit_2->append("-----First post-----\n");
        else
            list.push_front(new HiddenPost(ui->lineEdit_3->text(),ui->textEdit->toPlainText())),ui->textEdit_2->append("-----First post-----\n");
        ui->textEdit_2->append( "Name: "+  list.front().getName() +"\nDate: "+ list.front().getDate() +"\nMessage:\n"+ list.front().getText()+"\n");
    }
    ui->textEdit->clear();
    ui->lineEdit->clear();
    ui->lineEdit_3->clear();
    ui->label_5->setText("Enter post # "+QString::number(list.size()+1));
}

void MainWindow::randPost()
{
    if(!ui->checkBox->isChecked())
        list.push_front((list.randPost())), ui->textEdit_2->append("-----First post-----\n");
    else
        list.push_front((list.randPost())), ui->textEdit_2->append("-----Last post-----\n");
    ui->textEdit_2->append("Name: "+  list.front().getName() +"\nDate: "+ list.front().getDate() +"\nMessage:\n"+ list.front().getText()+"\n");
    ui->label_5->setText("Enter post # "+QString::number(list.size()+1));
}

void MainWindow::makeTable()
{
    ui->progressBar->setVisible(true);
    QTableWidgetItem *cell[list.size()][list.size()];
    ui->tableWidget->setRowCount(list.size());
    ui->tableWidget->setColumnCount(list.size());
    for(int i = 0; i<list.size(); i++)
    {
        ui->tableWidget->setVerticalHeaderItem(i, (new QTableWidgetItem(list[i].getName())));
        ui->tableWidget->setHorizontalHeaderItem(i, (new QTableWidgetItem(list[i].getName())));
    }
    int progress = 0;
    ui->progressBar->setMinimum(0);
    ui->progressBar->setMaximum(list.size()*list.size()/2);
    ui->progressBar->setValue(progress);
    for(int i = 0; i<list.size(); i++)
    {
        for(int j = i; j<list.size(); j++)
        {
            ui->label_6->setText(list[i].getName()+" from "+list[j].getName());
            int hamming = distHamming((list[i].getText()), (list[j].getText()));
            QString D_Lev = QString::number(distLevenstein((list[i].getText()), (list[j].getText())));
            QString D_Ham = hamming == -1 ? "#" : QString::number(hamming);
            cell[i][j] = new QTableWidgetItem(D_Lev+" "+D_Ham);
            if(i!=j) cell[j][i] = new QTableWidgetItem(D_Lev+" "+D_Ham);
            ui->tableWidget->setItem(i, j , cell[i][j]);
            ui->tableWidget->setItem(j, i , cell[j][i]);
            progress+=1;
            ui->progressBar->setValue(progress);
        }
    }
    ui->label_6->setText("Distances:");
    ui->progressBar->setValue(0);
    ui->progressBar->setVisible(false);
}
