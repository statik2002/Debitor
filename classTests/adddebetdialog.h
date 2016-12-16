#ifndef ADDDEBETDIALOG_H
#define ADDDEBETDIALOG_H

#include "database.h"

#include <QDialog>

namespace Ui {
class AddDebetDialog;
}

class AddDebetDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddDebetDialog(QWidget *parent = 0);
    ~AddDebetDialog();

    QString getFirm();
    QString getNumPlatezh();
    QString getSumm();
    QString getDate();

private:
    Ui::AddDebetDialog *ui;

    QSqlQuery query;
    QSqlRecord rec;
    QStringList list;
};

#endif // ADDDEBETDIALOG_H
