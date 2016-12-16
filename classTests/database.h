#ifndef DATABASE_H
#define DATABASE_H

#include <QObject>
#include <QtSql>

class DataBase : public QObject
{
    Q_OBJECT
public:
    explicit DataBase(QObject *parent=0, QString dbname="");
    ~DataBase();

    QSqlDatabase *db;

    QString DBConnect();

};

#endif // DATABASE_H
