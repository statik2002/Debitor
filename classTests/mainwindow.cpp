#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "database.h"
//#include "editfirmsdialog.h"
#include "firmsdialog.h"
#include "addcreditdialog.h"
#include "adddebetdialog.h"
#include "deletefirmdialog.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    database = new DataBase(this, "maindb");
    QString result = database->DBConnect();
    if(result!="Ok")
    {
       qDebug() << result;
    }
    else {
        qDebug() << "connected";
    }

    //Устанавливаем ActionBar
    ui->mainToolBar->addAction("Добавить поставщика +", this, SLOT(slotEditFirmsDialog()));
    ui->mainToolBar->addAction("Удалить поставщика -", this, SLOT(slotDeleteFirm()));
    ui->mainToolBar->addAction("Добавить приход +", this, SLOT(slotAddCredit()));
    ui->mainToolBar->addAction("Добавить расход -", this, SLOT(slotAddDebet()));




    //tableModel = new QSqlRelationalTableModel(database);
    //tableModel->setTable("postavshik");
    //tableModel->setRelation(1, QSqlRelation("postavshik", "id", "name"));
    //tableModel->setRelation(2, QSqlRelation("postavshik", "id", "otsrochka"));
    //tableModel->setRelation(3, QSqlRelation("debet", "id", "summa"));
    //tableModel->setRelation(4, QSqlRelation("credit", "id", "summa"));
    //tableModel->select();




    /*for(int i=0; i<tableModel->rowCount(); i++)
    {
        QSqlRecord record = tableModel->record(i);
        tableModel->setData(tableModel->index(i, 3), (float)calcDebitor(record.value("id").toInt())/100);
        tableModel->setData(tableModel->index(i, 4), (float)calcCredit(record.value("id").toInt())/100);
        float total = (calcDebitor(record.value("id").toInt()-calcCredit(record.value("id").toInt())))/100;
        tableModel->setData(tableModel->index(i, 5), total);
    }


    ui->tableView->setModel(tableModel);
    tableModel->setEditStrategy(QSqlTableModel::OnRowChange);
    tableModel->setHeaderData(1, Qt::Horizontal, tr("Фирма"));
    tableModel->setHeaderData(2, Qt::Horizontal, tr("Отсрочка дней"));
    tableModel->setHeaderData(3, Qt::Horizontal, tr("Сумма отгрузки"));
    tableModel->setHeaderData(4, Qt::Horizontal, tr("Оплачено"));
    tableModel->setHeaderData(5, Qt::Horizontal, tr("Долг"));
    //ui->tableView->hideColumn(0);
    //ui->tableView->hideColumn(6);
    ui->tableView->horizontalHeader()->setStretchLastSection(true);
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableView->show();*/

    ui->tableWidget->setColumnCount(6);
    ui->tableWidget->horizontalHeader()->setStretchLastSection(true);
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableWidget->setSelectionMode(QAbstractItemView::NoSelection);



    FillTable();

}

MainWindow::~MainWindow()
{
    delete ui;
}

int MainWindow::calcDebitor(int firmid)
{
    QSqlQuery query;
    QSqlRecord rec;
    int summ=0;
    //query.prepare("SELECT * FROM 'debet'");


    if(query.exec("SELECT * FROM 'debet' WHERE parentid="+QString::number(firmid)+""))
    {
        rec = query.record();
        while(query.next())
        {
            summ = summ + query.value(rec.indexOf("summa")).toInt();
        }
    }
    //ui->statusBar->showMessage(QString::number(summ), 10000);
    return summ;
}

int MainWindow::calcCredit(int firmid)
{
    QSqlQuery query;
    QSqlRecord rec;
    int summ=0;
    //query.prepare("SELECT * FROM 'debet'");

    if(query.exec("SELECT * FROM 'credit' WHERE parentid="+QString::number(firmid)+""))
    {
        rec = query.record();
        while(query.next())
        {
            summ = summ + query.value(rec.indexOf("summa")).toInt();
        }
    }
    return summ;
}

int MainWindow::calcAllDebet()
{
    QSqlQuery query;
    QSqlRecord rec;
    int summ=0;
    //query.prepare("SELECT * FROM 'debet'");

    if(query.exec("SELECT * FROM 'debet'"))
    {
        rec = query.record();
        while(query.next())
        {
            summ = summ + query.value(rec.indexOf("summa")).toInt();
        }
    }
    return summ;
}

int MainWindow::calcAllCredit()
{
    QSqlQuery query;
    QSqlRecord rec;
    int summ=0;
    //query.prepare("SELECT * FROM 'debet'");

    if(query.exec("SELECT * FROM 'credit'"))
    {
        rec = query.record();
        while(query.next())
        {
            summ = summ + query.value(rec.indexOf("summa")).toInt();
        }
    }
    return summ;
}

void MainWindow::repaintTableAfterCalc()
{
    /*tableModel->setTable("postavshik");
    tableModel->select();
    for(int i=0; i<tableModel->rowCount(); i++)
    {
        QSqlRecord record = tableModel->record(i);
        tableModel->setData(tableModel->index(i, 3), (float)calcDebitor(record.value("id").toInt())/100);
        tableModel->setData(tableModel->index(i, 4), (float)calcCredit(record.value("id").toInt())/100);
        tableModel->setData(tableModel->index(i, 5), (float)(calcDebitor(record.value("id").toInt())-calcCredit(record.value("id").toInt()))/100);
    }*/

}

void MainWindow::FillTable()
{
    QSqlQuery query;
    QSqlRecord rec;
    qint8 row=0;

    ui->tableWidget->clear();
    QStringList horizontalHeader;
    horizontalHeader << "id" << "Поставщик" << "Отсрочка" << "Приход" << "Расход" << "Долг";
    ui->tableWidget->setHorizontalHeaderLabels(horizontalHeader);
    ui->tableWidget->setRowCount(0);


    if(query.exec("SELECT * FROM 'postavshik'"))
    {

        rec = query.record();
        while(query.next())
        {
            //qDebug() << row;
            ui->tableWidget->insertRow(row);
            ui->tableWidget->setItem(row, 0, new QTableWidgetItem(query.value(rec.indexOf("id")).toString()));
            ui->tableWidget->setItem(row, 1, new QTableWidgetItem(query.value(rec.indexOf("name")).toString()));
            ui->tableWidget->setItem(row, 2, new QTableWidgetItem(query.value(rec.indexOf("otsrochka")).toString()));
            //qDebug() << (float)calcCredit(query.value(rec.indexOf("id")).toInt())/100;
            //ui->tableWidget->setItem(row, 3, new QTableWidgetItem(QString::number((float)calcCredit(query.value(rec.indexOf("id")).toInt())/100, 'f', 2)));
            ui->tableWidget->setItem(row, 3, new QTableWidgetItem(IntToMoney(calcCredit(query.value(rec.indexOf("id")).toInt()), " ", "руб.")));
            //ui->tableWidget->setItem(row, 4, new QTableWidgetItem(QString::number((float)calcDebitor(query.value(rec.indexOf("id")).toInt())/100, 'f', 2)));
            ui->tableWidget->setItem(row, 4, new QTableWidgetItem(IntToMoney(calcDebitor(query.value(rec.indexOf("id")).toInt()), " ", " руб.")));
            //qDebug() << ui->tableWidget->item(row, 3)->text();
            ui->tableWidget->setItem(row, 5, new QTableWidgetItem(IntToMoney(calcCredit(query.value(rec.indexOf("id")).toInt())-
                                                                             calcDebitor(query.value(rec.indexOf("id")).toInt()), " ", " руб")));

            row++;
        }
        //row++;
        ui->tableWidget->insertRow(row);
        qint64 totalcredit = calcAllCredit();
        qint64 totaldebet = calcAllDebet();
        ui->tableWidget->setItem(row, 3, new QTableWidgetItem(IntToMoney(totalcredit, " ", " руб")));
        ui->tableWidget->item(row, 3)->setBackground(Qt::gray);
        ui->tableWidget->setItem(row, 4, new QTableWidgetItem(IntToMoney(totaldebet, " ", " руб")));
        ui->tableWidget->item(row, 4)->setBackground(Qt::gray);
        ui->tableWidget->setItem(row, 5, new QTableWidgetItem(IntToMoney(totalcredit-totaldebet, " ", " руб")));
        ui->tableWidget->item(row, 5)->setBackground(Qt::yellow);

        ui->tableWidget->resizeColumnsToContents();
    }
}

QString MainWindow::IntToMoney(long summa, QString delitel, QString moneysign)
{
    QString ret="";

    int kopeiki = summa % 100;

    summa = summa / 100;

    if(summa == 0)
    {
        ret = " 0";
    }

    int ostatok=0;

    while (summa>0) {
        ostatok = summa % 1000;
        if(ostatok>0)
        {
            ret = delitel+QString::number(ostatok)+ret;
        }
        else {
            ret = delitel+"000"+ret;
        }

        summa = summa / 1000;
    }

    ret.remove(0, 1);

    return ret+","+QString::number(kopeiki)+moneysign;
}

void MainWindow::slotEditFirmDebitor()
{

}

void MainWindow::slotEditFirmsDialog()
{
    qDebug() << "slotEditFirmsDialog";
    FirmsDialog *dialog = new FirmsDialog(this, database);
    dialog->setModal(true);
    if(dialog->exec() == QDialog::Accepted)
    {
        qDebug() << "show dialog";
        //ui->tableView->repaint();

    }
    //tableModel->select();
    FillTable();
}

void MainWindow::slotAddCredit()
{
    qDebug() << "slotAddCredit";
    QString sum;
    AddCreditDialog *dialog = new AddCreditDialog(this);
    dialog->setModal(true);
    if(dialog->exec() == QDialog::Accepted)
    {
        QSqlTableModel *mod = new QSqlTableModel(database);
        mod->setTable("credit");
        mod->select();
        sum = dialog->getSumm();
        qDebug() << sum;
        qDebug() << sum.toFloat();
        qint32 tot = sum.toFloat()*100;
        mod->insertRows(0,1);
        mod->setData(mod->index(0, 1), dialog->getDate());
        mod->setData(mod->index(0, 2), tot);
        mod->setData(mod->index(0, 3), dialog->getFirm().toInt(0, 10));
        if(!mod->submitAll())
        {
            qDebug() << mod->lastError().text();
        }

    }
    ui->statusBar->showMessage(sum, 10000);
    FillTable();
}

void MainWindow::slotAddDebet()
{
    qDebug() << "slotAddDebet";
    AddDebetDialog *dialog = new AddDebetDialog(this);
    dialog->setModal(true);
    if(dialog->exec() == QDialog::Accepted)
    {
        QSqlTableModel *mod = new QSqlTableModel(database);
        mod->setTable("debet");
        mod->select();
        qint32 tot = dialog->getSumm().toFloat()*100;
        mod->insertRows(0,1);
        mod->setData(mod->index(0, 1), dialog->getDate());
        mod->setData(mod->index(0, 2), tot);
        mod->setData(mod->index(0, 3), dialog->getNumPlatezh());
        mod->setData(mod->index(0, 4), dialog->getFirm());
        if(!mod->submitAll())
        {
            qDebug() << mod->lastError().text();
        }

    }
    FillTable();
}

void MainWindow::slotDeleteFirm()
{
    DeleteFirmDialog *dialog = new DeleteFirmDialog(this);
    dialog->setModal(true);
    if(dialog->exec() == QDialog::Accepted)
    {
        QSqlTableModel *mod = new QSqlTableModel(database);

        mod->setTable("postavshik");
        mod->select();
        //qDebug() << dialog->getFirmId();
        int id = dialog->getFirmId();

        mod->setFilter("id = '"+QString::number(id)+"'");
        mod->removeRows(0, mod->rowCount());
        mod->submitAll();

        //удаляем все связи с удаляемой фирмой в таблице "debet"
        mod->setTable("debet");
        mod->select();

        qDebug() << mod->tableName();
        QString str = "parentid="+QString::number(id)+"";
        qDebug() << str;
        mod->setFilter(str);
        qDebug() << mod->rowCount();
        if(!mod->removeRows(0, mod->rowCount()))
        {
            qDebug() << mod->lastError().text();
        }
        mod->submitAll();

        //удаляем все связи с удаляемой фирмой в таблице "credit"
        mod->setTable("credit");
        mod->select();

        mod->setFilter("parentid="+QString::number(id)+"");
        mod->removeRows(0, mod->rowCount());
        mod->submitAll();
    }
    //tableModel->select();
    FillTable();
}
