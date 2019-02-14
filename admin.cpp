#include "admin.h"
#include "ui_admin.h"

Admin::Admin(Db* d,QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Admin)
{
    db=d;
    ui->setupUi(this);
    ui->widget_journal->setVisible(false);
    ui->widget_user->setVisible(false);
    ui->widget_pro->setVisible(false);
}

Admin::~Admin()
{
    delete db;
    delete ui;
}

void Admin::fillJournalTable()  //заполнение журнала из таблицы бд
{
    ui->journalTable->setRowCount(0);
    if(db->qry->exec("SELECT * FROM journal")){
    int i=0;
    while(db->qry->next()){
        ui->journalTable->insertRow(i);
        ui->journalTable->setItem(i,0, new QTableWidgetItem(db->qry->value(1).toString()));
        ui->journalTable->setItem(i,1, new QTableWidgetItem(db->qry->value(2).toString()));
        ui->journalTable->setItem(i,2, new QTableWidgetItem(db->qry->value(3).toString()));
        ui->journalTable->setItem(i,3, new QTableWidgetItem(db->qry->value(4).toString()));
        i++;
    }
    }
    else{
        qDebug() << "Journal query error! " << db->qry->lastError();
    }
}

void Admin::fillUserTable()  //
{
    ui->userTable->setRowCount(0);
    if(db->qry->exec("SELECT * FROM user")){
    int i=0;
    while(db->qry->next()){
        ui->userTable->insertRow(i);
        ui->userTable->setItem(i,0, new QTableWidgetItem(db->qry->value(1).toString()));
        ui->userTable->setItem(i,1, new QTableWidgetItem(db->qry->value(2).toString()));
        i++;
    }
    }
    else{
        qDebug() << "User query error! " << db->qry->lastError();
    }
}

void Admin::fillProTable()
{
    ui->proTable->setRowCount(0);
    if(db->qry->exec("SELECT * FROM prouser")){
    int i=0;
    while(db->qry->next()){
        ui->proTable->insertRow(i);
        ui->proTable->setItem(i,0, new QTableWidgetItem(db->qry->value(1).toString()));
        ui->proTable->setItem(i,1, new QTableWidgetItem(db->qry->value(2).toString()));
        ui->proTable->setItem(i,2, new QTableWidgetItem(db->qry->value(3).toString()));
        i++;
    }
    }
    else{
        qDebug() << "User query error! " << db->qry->lastError();
    }
}

void Admin::on_journalButton_clicked()
{
     db->insertIntoJournal("Click Journal view","admin");
    ui->main_widget->setVisible(false);
    ui->widget_journal->setVisible(true);
    fillJournalTable();
}

void Admin::on_userList_button_clicked()
{
    db->insertIntoJournal("Click User view","admin");
    ui->main_widget->setVisible(false);
    ui->widget_user->setVisible(true);
    fillUserTable();
}

void Admin::on_backFromJournal_clicked()
{
    db->insertIntoJournal("Click back button","admin");
    ui->widget_journal->setVisible(false);
    ui->main_widget->setVisible(true);
}

void Admin::on_backFromUser_clicked()
{
    db->insertIntoJournal("Click back button","admin");
    ui->widget_user->setVisible(false);
    ui->main_widget->setVisible(true);
}

void Admin::on_proList_button_clicked()
{
    db->insertIntoJournal("Click Pro view","admin");
    ui->main_widget->setVisible(false);
    ui->widget_pro->setVisible(true);
    fillProTable();
}

void Admin::on_backFromPro_clicked()
{
    db->insertIntoJournal("Click back button","admin");
    ui->main_widget->setVisible(true);
    ui->widget_pro->setVisible(false);
}
