#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->registration1->setVisible(false);
    ui->registration_guest->setVisible(false);
    ui->registration_pro->setVisible(false);
    db=new Db();
    db->launch();
    db->launchInsert();

}

MainWindow::~MainWindow()
{
    delete ui;
    if (window) delete window;
}

void MainWindow::on_registr_clicked()  //кнопка "зарегистрироваться"
{
    db->insertIntoJournal("Click to sign up","guest");

    ui->log_in->setVisible(false);
    ui->registration1->setVisible(true);

}

void MainWindow::on_entry_clicked() //вход
{
     db->insertIntoJournal("Click SignIn",ui->login->text());
    QString login = ui->login->text();
    QString password = ui->pasword->text();
    if(login=="admin" && password=="admin"){
        hide();
        window2=new Admin(db);
        window2->show();
    }
    else if (db->isUser(login,password)){
        QMessageBox::information(this, "Sign in successful", "Вы вошли в систему как "+login);
        db->currentUser=new  CurrentUser (login, false, password);
        hide();
        window=new User(db);
        window->show();
    }
    else if (db->isProUser(login,password)){
        QMessageBox::information(this, "Sign in successful", "Вы вошли в систему как "+login);
        db->currentUser=new  CurrentUser (login, true, password);        
        hide();
        window=new User(db);
        window->show();
    }
    else  QMessageBox::information(this, "Sign in error", "Вы ввели неверный пароль ");

}

void MainWindow::on_as_guest_clicked() //кнопка зарегистрироваться как пользователь
{
     db->insertIntoJournal("Click SignUp as user","guest");
    ui->registration1->setVisible(false);
    ui->registration_guest->setVisible(true);

}


void MainWindow::on_as_worker_clicked() //зарегистрироваться как работник
{
    db->insertIntoJournal("Click SignUp as worker","guest");
ui->registration1->setVisible(false);
ui->registration_pro->setVisible(true);
}

void MainWindow::on_signup_guest_clicked()     //регистрация обычного пользователя
{
    db->insertIntoJournal("Click guest registration", "guest");
    QString login=ui->login_guest->text();
    QString pas=ui->pas_guest->text();
    QString again=ui->again_guest->text();

    if(login!="" && pas!="" && again!=""){
    if(pas==again){
        if((db->isUser(login)) || (db->isProUser(login))){
            QMessageBox::information(this, "Registration error", "Пользователь с таким именем уже зарегистрирован");
        }
        else{
        db->insertIntoUser(login,pas);
        db->currentUser=new CurrentUser(login, false, pas);
         QMessageBox::information(this, "Registration successful", "Регистрация прошла успешно ");
         hide();
         window=new User(db);
         window->show();

    }}
    else {
        QMessageBox::information(this, "Password error", "Пароли не совпадают!");
        ui->again_guest->clear();
    }

   }
    else{
        QMessageBox::information(this, "Registration error", "Вы заполнили не все поля! ");
    }
}



void MainWindow::on_signup_pro_clicked()        //регистрация работника
{
    db->insertIntoJournal("Click pro registration", "pro");
    QString login=ui->login_pro->text();
    QString pas=ui->pas_pro->text();
    QString again=ui->again_pro->text();
    QString position=ui->position_pro->text();

    if(login!="" && pas!="" && again!="" && position!=""){
    if(pas==again){
        if((db->isUser(login)) || (db->isProUser(login))){
            QMessageBox::information(this, "Registration error", "Пользователь с таким именем уже зарегистрирован");
        }
        else{
        db->insertIntoProUser(login,pas,position);
        db->currentUser=new CurrentUser(login, true, pas);
        QMessageBox::information(this, "Registration successful", "Регистрация прошла успешно ");
        hide();
        window=new User(db);
        window->show();
    }}
    else {
        QMessageBox::information(this, "Password error", "Пароли не совпадают!");
        ui->again_pro->clear();
    }
   }
    else{
        QMessageBox::information(this, "Registration error", "Вы заполнили не все поля! ");
    }
}
