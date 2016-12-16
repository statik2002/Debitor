#ifndef ADDCREDITDIALOG_H
#define ADDCREDITDIALOG_H

#include "database.h"

#include <QDialog>

namespace Ui {
class AddCreditDialog;
}

class AddCreditDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddCreditDialog(QWidget *parent = 0);
    ~AddCreditDialog();

    QString getSumm();
    QString getDate();
    QString getFirm();

private:
    Ui::AddCreditDialog *ui;

    QSqlQuery query;
    QSqlRecord rec;
    QStringList list;
};

#endif // ADDCREDITDIALOG_H
