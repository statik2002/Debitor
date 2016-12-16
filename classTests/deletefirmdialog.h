#ifndef DELETEFIRMDIALOG_H
#define DELETEFIRMDIALOG_H

#include "database.h"

#include <QDialog>

namespace Ui {
class DeleteFirmDialog;
}

class DeleteFirmDialog : public QDialog
{
    Q_OBJECT

public:
    explicit DeleteFirmDialog(QWidget *parent = 0, DataBase *db = 0);
    ~DeleteFirmDialog();

    int getFirmId();

private:
    Ui::DeleteFirmDialog *ui;

    QSqlQuery query;
    QSqlRecord rec;
};

#endif // DELETEFIRMDIALOG_H
