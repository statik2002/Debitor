#include "addfirmdialog.h"
#include "ui_addfirmdialog.h"


AddFirmDialog::AddFirmDialog(QWidget *parent, DataBase *db) :
    QDialog(parent),
    ui(new Ui::AddFirmDialog)
{
    ui->setupUi(this);

    ui->lineEdit->setText("Enter firm name");
    ui->lineEdit_2->setText("Enter days delay");
}

AddFirmDialog::~AddFirmDialog()
{
    delete ui;
}

QString AddFirmDialog::getFirmName()
{
    return ui->lineEdit->text();
}

QString AddFirmDialog::getDaysLeft()
{
    return ui->lineEdit_2->text();
}
