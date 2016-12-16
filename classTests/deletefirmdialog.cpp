#include "deletefirmdialog.h"
#include "ui_deletefirmdialog.h"

DeleteFirmDialog::DeleteFirmDialog(QWidget *parent, DataBase *db) :
    QDialog(parent),
    ui(new Ui::DeleteFirmDialog)
{
    ui->setupUi(this);


    QStringList list;

    if(query.exec("SELECT * FROM 'postavshik'"))
    {
        rec = query.record();
        while(query.next())
        {
            list << query.value(rec.indexOf("name")).toString();
        }

        ui->comboBox->addItems(list);
    }
}

DeleteFirmDialog::~DeleteFirmDialog()
{
    delete ui;
}

int DeleteFirmDialog::getFirmId()
{
    QString str = ui->comboBox->currentText();
    QString qstring = "SELECT * FROM 'postavshik' WHERE name='"+str+"'";

    if(query.exec(qstring))
    {
        rec = query.record();
        while(query.next())
        {
            return query.value(rec.indexOf("id")).toInt();
        }

    }
    return 0;
}
