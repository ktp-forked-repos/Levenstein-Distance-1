#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include "hiddenpost.h"

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit Dialog(QWidget *parent = 0);
    ~Dialog();
    HiddenPost *changingPost;
    
private:
    Ui::Dialog *ui;
private slots:
    void change();
};

#endif // DIALOG_H
