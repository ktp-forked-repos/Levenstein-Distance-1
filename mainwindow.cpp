#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <stdio.h>
#include <QTextStream>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->textEdit_2->setReadOnly(true);
    ui->pushButton_2->setDisabled(true);
    ui->checkBox_2->isCheckable();
    ui->tableWidget->setEditTriggers(QTableWidget::NoEditTriggers);
    counter = 0;
    QObject::connect(ui->pushButton, SIGNAL(clicked()), this, SLOT(addPost()));
    QObject::connect(ui->pushButton_2, SIGNAL(clicked()), this, SLOT(func()));
    QObject::connect(ui->pushButton_3, SIGNAL(clicked()), this, SLOT(size_l()));
    QObject::connect(ui->pushButton_4, SIGNAL(clicked()), this, SLOT(isEmpty_l()));
    QObject::connect(ui->pushButton_5, SIGNAL(clicked()), this, SLOT(del_l()));
    QObject::connect(ui->pushButton_6, SIGNAL(clicked()), this, SLOT(show_l()));
    QObject::connect(ui->pushButton_7, SIGNAL(clicked()), this, SLOT(similar()));
    QObject::connect(ui->pushButton_8, SIGNAL(clicked()), this, SLOT(writeToF()));
    QObject::connect(ui->pushButton_9, SIGNAL(clicked()), this, SLOT(readFromF()));
}

void MainWindow::readFromF()
{
    QString fname = ui->lineEdit_2->text();
    file.setFileName(fname);
    file.open(QIODevice::ReadOnly);
    while(!file.atEnd())
    {
        QString name = file.readLine();
        QString date = file.readLine();
        QString text = file.readLine();

        name.remove("\r\n");
        text.remove("\r\n");
        text.remove("\n");
        name.remove("\n");
        Post a(name, date, text);
        list.push_front(a);
        ui->textEdit_2->append((a.getName()));
        ui->textEdit_2->append((a.getDate()));
        ui->textEdit_2->append((a.getText()));
        counter+=1;
    }
    file.close();
    if(list.size()>1) ui->pushButton_2->setEnabled(true); else ui->pushButton_2->setDisabled(true);
}

void MainWindow::writeToF()
{
    QString fname = ui->lineEdit_2->text();
    file.setFileName(fname);
    file.open(QIODevice::WriteOnly);
    QTextStream stream(&file);
    for(int i = 0; i<list.size(); i++)
    {
        //list[i]->data.name.remove("\n");
        //list[i]->data.text.remove("\n");
        stream<<(list[i].data.getName())+"\r\n"+(list[i].data.getDate())+"\r\n"+(list[i].data.getText())+"\r\n";
    }
    file.close();
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

void MainWindow::show_l()
{
    for(int i = 0; i<list.size(); i++)
        ui->textEdit_2->append("-----Post # "+ QString::number(i+1)+ "------\nName: "+  (list[i].data.getName()) +"\nDate: "+ (list[i].data.getDate())+"\nMessage:\n"+ (list[i].data.getText())+"\n");
}

void MainWindow::del_l()
{
    if(ui->checkBox_2->isChecked()) list.del_back(); else list.del_front();
    if(list.size()>1) ui->pushButton_2->setEnabled(true); else ui->pushButton_2->setDisabled(true);
    show_l();
}

void MainWindow::similar()
{
    int min = 0;
    if(ui->textEdit->toPlainText()!=""&&list.size()>=1)
    {
        qDebug("similar");
        Post a(ui->lineEdit->text(),ui->lineEdit_3->text(), ui->textEdit->toPlainText() );
        int x = 0;
        min=D((a.getText()), (list[0].data.getText()));
        for(int i = 1; i<list.size(); i++)
        {
            if(D((a.getText()), (list[0].data.getText()))<min) min = D((a.getText()), (list[0].data.getText()));
        }
        qDebug("%d", min);
        ui->textEdit_2->append("Minimum distance is "+QString::number(min));
        for(int i = 0; i<list.size(); i++)
        {
            if(min == D((a.getText()), (list[0].data.getText()))) ui->textEdit_2->append("Similar post:\nName:"+  list[i].data.getName() +"\nDate: "+ list[i].data.getDate() +"\nMessage:\n"+ list[i].data.getText()+"\n");
        }
    }
}

void MainWindow::addPost()
{   
    if( ui->lineEdit->text()!="" && ui->textEdit->toPlainText()!="")
    {
        if(list.size()>=1) ui->pushButton_2->setEnabled(true); else ui->pushButton_2->setDisabled(true);
        Post a(ui->lineEdit->text(), ui->lineEdit_3->text(),ui->textEdit->toPlainText());
        if(ui->checkBox->isChecked())
        {
            list.push_back(a);
            ui->textEdit_2->append("-----Post # "+ QString::number(counter+1)+ "------\nName: "+  list.pop_back().data.getName() +"\nDate: "+ list.pop_back().data.getDate() +"\nMessage:\n"+ list.pop_back().data.getText()+"\n");
        }
        else
        {
            list.push_front(a);
            ui->textEdit_2->append("-----Post # "+ QString::number(counter+1)+ "------\nName: "+  list.pop_front().data.getName() +"\nDate: "+ list.pop_front().data.getDate() +"\nMessage:\n"+ list.pop_front().data.getText()+"\n");
        }
        ui->textEdit->clear();
        ui->lineEdit->clear();
        counter+=1;
        ui->label_5->setText("Enter message # "+QString::number(counter+1));
    }
    else
    {
        ui->textEdit_2->append("Incorrect post, missed information fields\n");
    }
}

int MainWindow::D(QString a, QString b)
{
    int M[a.length()+1][b.length()+1];
    int n = a.length();
    int m = b.length();
    if(m==0) return n;
    if (n==0) return m;

    for(int i = 0; i<=n; i++) M[i][0]=i;
    for(int i = 0; i<=m; i++) M[0][i]=i;

    int ac, lc, dc, cost;

    for(int i = 1; i<=n;i++)
        for(int j = 1; j<=m; j++)
        {
            cost = a.at(i-1) == b.at(j-1) ? 0:1;
            ac=M[i-1][j];
            lc=M[i][j-1];
            dc = M[i-1][j-1];
            M[i][j] = min(ac+1, lc+1, dc+cost);
        }
    return M[n][m];
}

int MainWindow::m(QChar y, QChar z)
{
    if(y==z) return 0 ; else return 1;
}

void MainWindow::func()
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
            cell[i][j] = new QTableWidgetItem(QString::number( D((list[i].data.getText()), (list[j].data.getText()))));
            if(i!=j) cell[j][i] = new QTableWidgetItem(QString::number(D((list[i].data.getText()), (list[j].data.getText()))));
            ui->tableWidget->setItem(i, j , cell[i][j]);
            ui->tableWidget->setItem(j, i , cell[j][i]);
        }
    }
}

int MainWindow::min(int a, int b, int c)
{
    if(a>=b&&a>=c)
    {
        if(b>=c) return c;
        else return b;
    }
    if(b>=a&&b>=c)
    {
        if(a>=c) return c;
        else return a;
    }
    if(c>=a&&c>=b)
    {
        if(a>=b) return b;
        else return a;
    }

}
