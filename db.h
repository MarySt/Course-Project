#ifndef DB_H
#define DB_H

#include <QtSql/QSql>
#include<QString>
#include<QtSql/QSqlDatabase>
#include <QtSql/qsqlquery.h>
#include <QtSql/QSqlError>
#include <QDebug>
#include <QDate>
#include <QTime>
#include "currentuser.h"
class Db
{

  private:
    const QString dataBaseName = "railway";
    const QString queryCreateTableCashier = "CREATE TABLE IF NOT EXISTS cashier (id INTEGER PRIMARY KEY autoincrement, name varchar(40), experience integer)";
    const QString queryCreateTableClient = "CREATE TABLE IF NOT EXISTS client (id INTEGER PRIMARY KEY autoincrement, name varchar(40),dateOfBirth date)";
    const QString queryCreateTableRoute = "CREATE TABLE IF NOT EXISTS route (id INTEGER PRIMARY KEY autoincrement, name varchar(30), myNumber varchar(30))";
    const QString queryCreateTableTrain = "CREATE TABLE IF NOT EXISTS train (id INTEGER PRIMARY KEY autoincrement, departDate date, route_id integer, foreign key (route_id) references route(id)) ";
    const QString queryCreateTableCarriage = "CREATE TABLE IF NOT EXISTS carriage (id INTEGER PRIMARY KEY autoincrement, type varchar (10), seatsCount integer, train_id integer, foreign key (train_id) references train(id), check(type in(\"coupe\",\"econom\"))) ";
    const QString queryCreateTableLocality = "CREATE TABLE IF NOT EXISTS locality (id INTEGER PRIMARY KEY autoincrement, region varchar (30), city varchar (50))";
    const QString queryCreateTableStation = "CREATE TABLE IF NOT EXISTS station (id INTEGER PRIMARY KEY autoincrement, route_id integer, locality_id integer, arrival_time time, departure_time time, stop_time time, foreign key (route_id) references route(id),foreign key (locality_id) references locality(id))";
    const QString queryCreateTableTicket = "CREATE TABLE IF NOT EXISTS ticket (id INTEGER PRIMARY KEY autoincrement, seatNumber integer, price double, dateOfSale date, carriage_id integer, cashier_id integer, client_id integer,  foreign key (carriage_id) references carriage(id),  foreign key (cashier_id) references cashier(id), foreign key (client_id) references client(id))";
    const QString queryCreateTableJournal = "CREATE TABLE IF NOT EXISTS journal (id INTEGER PRIMARY KEY autoincrement, factDate date, factTime time, factType varchar (40), username varchar (30))";
    const QString queryCreateTableUser = "CREATE TABLE IF NOT EXISTS user (id INTEGER PRIMARY KEY autoincrement, login varchar (30), password varchar (30)) ";
    const QString queryCreateTableProUser = "CREATE TABLE IF NOT EXISTS prouser (id INTEGER PRIMARY KEY autoincrement, login varchar (30), password varchar (30), position varchar (30))";

    QSqlDatabase db;


public:
    QSqlQuery *qry;
    CurrentUser* currentUser;
    Db();
    ~Db();
    bool launch();
    void launchInsert();

    void insertIntoCashier(QString , int );
    void insertIntoClient(QString, QString);
    void insertIntoTrain(QString, int);
    void insertIntoRoute(QString, QString);
    void insertIntoCarriage(bool, int);
    void insertIntoLocality(QString, QString);
    void insertIntoStation(int, int, QString, QString);
    void insertIntoTicket(int, double, QString, int, int, int);

    void insertIntoJournal(QString factType, QString username);
    void insertIntoUser(QString login, QString password);
    void insertIntoProUser(QString, QString, QString);

    bool isUser(QString &login, QString password="");
    bool isProUser(QString &login, QString password="");
    QSqlDatabase getDb() const;

    int findRouteId (QString & name);
};

#endif // DB_H
