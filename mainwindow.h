#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLineEdit>
#include <QPushButton>
#include <QDebug>
#include <QMessageBox>
#include<memory>
#include <QMenuBar>
#include <QMenu>
#include "user.h"
#include "admin.h"
#include "db.h"
#include "currentuser.h"


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    Db *db;
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:

    void on_registr_clicked();

    void on_entry_clicked();

    void on_as_guest_clicked();

    void on_as_worker_clicked();

    void on_signup_guest_clicked();

    void on_signup_pro_clicked();

private:
    Ui::MainWindow *ui;
    User *window;
    Admin *window2;
};

#endif // MAINWINDOW_H
