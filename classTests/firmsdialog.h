#ifndef FIRMSDIALOG_H
#define FIRMSDIALOG_H

#include "database.h"
#include "addfirmdialog.h"

#include <QDialog>

namespace Ui {
class FirmsDialog;
}

class FirmsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit FirmsDialog(QWidget *parent = 0);
    explicit FirmsDialog(QWidget *parent = 0, DataBase *base = 0);
    ~FirmsDialog();

private:
    Ui::FirmsDialog *ui;

    DataBase *db;
    QSqlTableModel *mod;

private slots:
    void openAddFirmDialog();
};

#endif // FIRMSDIALOG_H
