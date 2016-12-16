#include "addcreditdialog.h"
#include "ui_addcreditdialog.h"

AddCreditDialog::AddCreditDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddCreditDialog)
{
    ui->setupUi(this);

    //ui->summaedit->setInputMask("99999999999.99");
    ui->summaedit->setValidator(new QRegExpValidator(QRegExp("^([1-9][0-9]*|0)(\\.)[0-9]{2}"), this));

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

AddCreditDialog::~AddCreditDialog()
{
    delete ui;
}

QString AddCreditDialog::getSumm()
{
    return ui->summaedit->text();
}

QString AddCreditDialog::getDate()
{
    return ui->dateEdit->text();
}

QString AddCreditDialog::getFirm()
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
