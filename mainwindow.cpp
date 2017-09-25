#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <stdio.h>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->textEdit_2->setReadOnly(true);
    ui->pushButton_2->setDisabled(true);
    ui->tableWidget->setEditTriggers(QTableWidget::NoEditTriggers);
    counter = 0;
    QObject::connect(ui->pushButton, SIGNAL(clicked()), this, SLOT(addPost()));
    QObject::connect(ui->pushButton_2, SIGNAL(clicked()), this, SLOT(func()));
    curr = new DynItem;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::addPost()
{
    if( ui->lineEdit->text()!="" && ui->textEdit->toPlainText()!="")
    {
        if(counter==1) ui->pushButton_2->setEnabled(true);
        if(counter>=curr->size) curr->resize();
        curr->data[counter].date = ui->dateEdit->date().toString("dd/MMMM/yyyy");
        curr->data[counter].name = ui->lineEdit->text();
        curr->data[counter].text = ui->textEdit->toPlainText();
        ui->textEdit->clear();
        ui->lineEdit->clear();
        ui->textEdit_2->append("-----Post # "+ QString::number(counter+1)+ "------\nName: "+  curr->data[counter].name +"\nDate: "+ curr->data[counter].date +"\nMessage:\n"+ curr->data[counter].text+"\n");
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
    int M[400][400];
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
    QTableWidgetItem *cell[counter][counter];
    ui->tableWidget->setRowCount(counter);
    ui->tableWidget->setColumnCount(counter);
    for(int i = 0; i<counter; i++) ui->tableWidget->setVerticalHeaderItem(i, new QTableWidgetItem(curr->data[i].name)),
             ui->tableWidget->setHorizontalHeaderItem(i, new QTableWidgetItem(curr->data[i].name));
    for(int i = 0; i<counter; i++)
        for(int j = i; j<counter; j++)
        {
            cell[i][j] = new QTableWidgetItem(QString::number( D(curr->data[i].text, curr->data[j].text)));
            if(i!=j) cell[j][i] = new QTableWidgetItem(QString::number(D(curr->data[i].text, curr->data[j].text)));
            ui->tableWidget->setItem(i, j , cell[i][j]);
            ui->tableWidget->setItem(j, i , cell[j][i]);
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
