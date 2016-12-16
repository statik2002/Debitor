#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "database.h"

#include <QMainWindow>
#include <QtSql>



namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    QSqlRelationalTableModel *tableModel;
    DataBase *database;

    int calcDebitor(int firmid);
    int calcCredit(int firmid);
    int calcDolg(int firmid);
    int calcAllDebet();
    int calcAllCredit();
    void repaintTableAfterCalc();
    void FillTable();
    QString IntToMoney(long summa, QString delitel, QString moneysign);

private:
    Ui::MainWindow *ui;

private slots:
    void slotEditFirmDebitor();
    void slotEditFirmsDialog();
    void slotAddCredit();
    void slotAddDebet();
    void slotDeleteFirm();
};

#endif // MAINWINDOW_H
