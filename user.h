#ifndef USER_H
#define USER_H

#include <QMainWindow>
#include "db.h"
#include <memory>
#include <QDate>
#include <QtSql/QSql>
#include<QString>
#include<QtSql/QSqlDatabase>
#include <QtSql/qsqlquery.h>
#include <QtSql/QSqlError>
#include <QMessageBox>
#include <QDateTime>

#include <QtPrintSupport/QPrinter>
#include <QPainter>

namespace Ui {
class User;
}

class User : public QMainWindow
{
    Q_OBJECT

public:
    Db *db;
    explicit User(Db* d,QWidget *parent = nullptr);
    ~User();

private slots:
    void on_getSchedule_clicked();

    void on_back_clicked();

    void on_schedule_filter_currentTextChanged(const QString &arg1);

    void on_addTrain_clicked();

    void on_addTrain_button_clicked();

    void fillCombo();

    void showRouteList();

    void on_backToSchedule_clicked();


    void on_get_routeList_clicked();

    void on_backToBegin_clicked();

    void on_routeList_itemSelectionChanged();

    void on_get_ticketReport_clicked();

    void fillCashierList();

    void fillDateList();
    void on_back_fromReport_clicked();

    void on_cashierList_itemSelectionChanged();

    void on_dateList_itemSelectionChanged();

    void on_deleteTrain_clicked();

    void on_deleteRoute_clicked();

    void on_editTrain_clicked();

    void on_editTrain_button_clicked();

    void fillSchedule();

    void on_reportButton_clicked();

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::User *ui;
};

#endif // USER_H
