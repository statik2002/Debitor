#ifndef ADDFIRMDIALOG_H
#define ADDFIRMDIALOG_H

#include "database.h"

#include <QDialog>

namespace Ui {
class AddFirmDialog;
}

class AddFirmDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddFirmDialog(QWidget *parent = 0, DataBase *db = 0);
    ~AddFirmDialog();

    QString getFirmName();
    QString getDaysLeft();

private:
    Ui::AddFirmDialog *ui;
};

#endif // ADDFIRMDIALOG_H
