#ifndef ADMIN_H
#define ADMIN_H

#include <QMainWindow>
#include "db.h"
#include <QDate>
#include <QtSql/QSql>
#include<QString>
#include<QtSql/QSqlDatabase>
#include <QtSql/qsqlquery.h>
#include <QtSql/QSqlError>
#include <QMessageBox>

namespace Ui {
class Admin;
}

class Admin : public QMainWindow
{
    Q_OBJECT

public:
    Db *db;
    explicit Admin(Db* d,QWidget *parent = nullptr);
    ~Admin();
    void fillJournalTable();
    void fillUserTable();
    void fillProTable();

private slots:
    void on_journalButton_clicked();

    void on_userList_button_clicked();

    void on_backFromJournal_clicked();

    void on_backFromUser_clicked();

    void on_proList_button_clicked();

    void on_backFromPro_clicked();

private:
    Ui::Admin *ui;
};

#endif // ADMIN_H
