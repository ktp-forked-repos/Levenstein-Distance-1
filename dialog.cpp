#include "dialog.h"
#include "ui_dialog.h"

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
    QObject::connect(ui->pushButton, SIGNAL(clicked()), this, SLOT(change()));
    changingPost = new HiddenPost;

}

void Dialog::change()
{
    changingPost->setName(ui->lineEdit->text());
    changingPost->setDate(ui->lineEdit_2->text());
    changingPost->setText(ui->textEdit->toPlainText());
    this->close();
}

Dialog::~Dialog()
{
    delete ui;
}
