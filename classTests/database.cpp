#include "database.h"


DataBase::DataBase(QObject *parent, QString dbname) : QObject(parent)
{
    db = new QSqlDatabase(QSqlDatabase::addDatabase("QSQLITE"));
    db->setDatabaseName(dbname);
}

DataBase::~DataBase()
{
    delete db;
}

QString DataBase::DBConnect()
{

    qDebug() << db->databaseName();

    bool connected = db->open();
    if(!connected)
    {
        return (db->lastError().text());
    }

    return ("Ok");
}
