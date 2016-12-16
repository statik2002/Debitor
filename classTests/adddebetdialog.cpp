#include "adddebetdialog.h"
#include "ui_adddebetdialog.h"

AddDebetDialog::AddDebetDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddDebetDialog)
{
    ui->setupUi(this);
    //ui->summaedit->setValidator(new QRegExpValidator(QRegExp("^([1-9][0-9]*|0)(\\.|,)[0-9]{2}"), this));

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

AddDebetDialog::~AddDebetDialog()
{
    delete ui;
}

QString AddDebetDialog::getFirm()
{
    QString str = ui->comboBox->currentText();
    QString qstring = "SELECT * FROM 'postavshik' WHERE name='"+str+"'";

    if(query.exec(qstring))
    {
        rec = query.record();
        while(query.next())
        {
            QString a = query.value(rec.indexOf("id")).toString();
            return a;
        }

    }
    return 0;
}

QString AddDebetDialog::getNumPlatezh()
{
    return ui->numBankPayment->text();
}

QString AddDebetDialog::getSumm()
{
    return ui->payment->text();
}

QString AddDebetDialog::getDate()
{
    return ui->dateEdit->text();
}
