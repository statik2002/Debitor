#include "firmsdialog.h"
#include "ui_firmsdialog.h"
#include "database.h"

#include <QToolBar>

FirmsDialog::FirmsDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FirmsDialog)
{
    ui->setupUi(this);



}

FirmsDialog::FirmsDialog(QWidget *parent, DataBase *base) :
    QDialog(parent),
    ui(new Ui::FirmsDialog)
{
    ui->setupUi(this);

    db = base;

    QToolBar *toolbar = new QToolBar(this);
    ui->verticalLayout->insertWidget(0, toolbar);
    toolbar->addAction("Add+", this, SLOT(openAddFirmDialog()));

    mod = new QSqlTableModel(db);
    mod->setTable("postavshik");
    mod->select();
    ui->tableView->setModel(mod);
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableView->hideColumn(0);
    ui->tableView->horizontalHeader()->setStretchLastSection(true);
    ui->tableView->show();

}

FirmsDialog::~FirmsDialog()
{
    delete ui;
}

void FirmsDialog::openAddFirmDialog()
{
    qDebug() << "in add firm dialog";
    AddFirmDialog *addFirmDialog = new AddFirmDialog(this, db);
    addFirmDialog->setModal(true);
    if(addFirmDialog->exec() == QDialog::Accepted)
    {
        qDebug() << "show add firm dialog";

        /*mod->insertRows(0,1);
        mod->setData(mod->index(0, 0), mod->primaryKey().count());
        mod->setData(mod->index(0, 1), addFirmDialog->getFirmName());
        mod->setData(mod->index(0, 2), addFirmDialog->getDaysLeft());
        mod->submitAll();
        if(!mod->submitAll())
        {
            qDebug() << mod->lastError().text();
        }*/

        QSqlQuery query;
        query.prepare("INSERT INTO postavshik (name, otsrochka, debet, credit, dolg) VALUES (:name, :days, :deb, :cred, :dolg)");
        query.bindValue(":name", addFirmDialog->getFirmName());
        query.bindValue(":days", addFirmDialog->getDaysLeft());
        query.bindValue(":deb", 0);
        query.bindValue(":cred", 0);
        query.bindValue(":dolg", 0);

        if(!query.exec())
        {
            qDebug() << query.lastError().text();
        }
        mod->select();


    }
}
