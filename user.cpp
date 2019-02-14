#include "user.h"
#include "ui_user.h"

User::User(Db *d,QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::User)

{
    db=d;
    ui->setupUi(this);
    ui->schedule_widget->setVisible(false);
    ui->addTrain_widget->setVisible(false);
    ui->routes_widget->setVisible(false);
    ui->ticketReport_widget->setVisible(false);
    ui->editTrain_widget->setVisible(false);
    if(!db->currentUser->isPro()){
        ui->addTrain->setVisible(false);
        ui->get_ticketReport->setVisible(false);
    }
}

User::~User()
{
    delete db;
    delete ui;
}

void User::on_getSchedule_clicked()  // Получаем расписание поездов
{
 db->insertIntoJournal("Schedule button",db->currentUser->getName());
ui->widget->setVisible(false);
ui->schedule_widget->setVisible(true);
fillSchedule();
}


void User::on_back_clicked()  //назад из расписания
{
    db->insertIntoJournal("Back button",db->currentUser->getName());
    ui->schedule_table->setRowCount(0);
    ui->schedule_widget->setVisible(false);
    ui->widget->setVisible(true);
}


void User::on_schedule_filter_currentTextChanged(const QString &arg1)  //фильтр расписания на будущие и прошедшие рейсы
{
    ui->schedule_table->setRowCount(0);
     QSqlQuery *qry2 =new QSqlQuery(db->getDb());
    if(arg1=="все"){
        db->qry->prepare("SELECT Train.departDate, route.name FROM Train join route on train.route_id = route.id ORDER BY departDate");  //запрос на получение расписания из бд
        int i=0;
        if (db->qry->exec()){
            while(db->qry->next()) { //заполняем таблицу
                qry2->prepare("SELECT departure_time FROM Station join route on station.route_id = route.id WHERE route.name = ? AND arrival_time=\"-\"");
                qry2->addBindValue(db->qry->value(1).toString());
                qry2->exec();
                qry2->next();
                   ui->schedule_table->insertRow(i);
                   ui->schedule_table->setItem(i,0, new QTableWidgetItem(db->qry->value(0).toString()));
                   ui->schedule_table->setItem(i,1, new QTableWidgetItem(db->qry->value(1).toString()));
                   ui->schedule_table->setItem(i,1, new QTableWidgetItem(db->qry->value(1).toString()));
                   ui->schedule_table->setItem(i,2, new QTableWidgetItem(qry2->value(0).toString()));
                   qry2->clear();
                   qry2->prepare("SELECT arrival_time FROM Station join route on station.route_id = route.id WHERE route.name = ? AND departure_time=\"-\"");
                   qry2->addBindValue(db->qry->value(1));
                   qry2->exec();
                   qry2->next();
                   ui->schedule_table->setItem(i,3, new QTableWidgetItem(qry2->value(0).toString()));
                   qry2->clear();
                   i++;
            }}
    }
    else if (arg1=="Прошедшие"){
        db->qry->prepare("SELECT Train.departDate, route.name FROM Train join route on train.route_id = route.id WHERE departDate < ? ORDER BY departDate");  //запрос на получение расписания из бд
        QDate date=QDate::currentDate();
        db->qry->addBindValue(date);
        int i=0;
        if (db->qry->exec()){
            while(db->qry->next()) { //заполняем таблицу
                qry2->prepare("SELECT departure_time FROM Station join route on station.route_id = route.id WHERE route.name = ? AND arrival_time=\"-\"");
                qry2->addBindValue(db->qry->value(1).toString());
                qry2->exec();
                qry2->next();
                   ui->schedule_table->insertRow(i);
                   ui->schedule_table->setItem(i,0, new QTableWidgetItem(db->qry->value(0).toString()));
                   ui->schedule_table->setItem(i,1, new QTableWidgetItem(db->qry->value(1).toString()));
                   ui->schedule_table->setItem(i,1, new QTableWidgetItem(db->qry->value(1).toString()));
                   ui->schedule_table->setItem(i,2, new QTableWidgetItem(qry2->value(0).toString()));
                   qry2->clear();
                   qry2->prepare("SELECT arrival_time FROM Station join route on station.route_id = route.id WHERE route.name = ? AND departure_time=\"-\"");
                   qry2->addBindValue(db->qry->value(1));
                   qry2->exec();
                   qry2->next();
                   ui->schedule_table->setItem(i,3, new QTableWidgetItem(qry2->value(0).toString()));
                   qry2->clear();
                   i++;
            }
    }
        else {
            qDebug()<<"Schedule error!";
        }

}
    else if (arg1=="Будущие"){
        db->qry->prepare("SELECT Train.departDate, route.name FROM Train join route on train.route_id = route.id where departDate > ? ORDER BY departDate");  //запрос на получение расписания из бд
        QDate date=QDate::currentDate();
        db->qry->addBindValue(date);
        int i=0;
        if (db->qry->exec()){
            while(db->qry->next()) { //заполняем таблицу
                qry2->prepare("SELECT departure_time FROM Station join route on station.route_id = route.id WHERE route.name = ? AND arrival_time=\"-\"");
                qry2->addBindValue(db->qry->value(1).toString());
                qry2->exec();
                qry2->next();
                   ui->schedule_table->insertRow(i);
                   ui->schedule_table->setItem(i,0, new QTableWidgetItem(db->qry->value(0).toString()));
                   ui->schedule_table->setItem(i,1, new QTableWidgetItem(db->qry->value(1).toString()));
                   ui->schedule_table->setItem(i,2, new QTableWidgetItem(qry2->value(0).toString()));
                   qry2->clear();
                   qry2->prepare("SELECT arrival_time FROM Station join route on station.route_id = route.id WHERE route.name = ? AND departure_time=\"-\"");
                   qry2->addBindValue(db->qry->value(1));
                   qry2->exec();
                   qry2->next();
                   ui->schedule_table->setItem(i,3, new QTableWidgetItem(qry2->value(0).toString()));
                   qry2->clear();
                   i++;
            }
    }
        else {
            qDebug()<<"Schedule error!";
        }
    }
}

void User::on_addTrain_clicked() //переход на страницу добавления рейса
{
    db->insertIntoJournal("Add train button",db->currentUser->getName());
    fillCombo();
    ui->schedule_widget->setVisible(false);
    ui->addTrain_widget->setVisible(true);

}

void User::on_addTrain_button_clicked()   // добавление рейса
{
db->insertIntoJournal("Add new train",db->currentUser->getName());
  QString routename =ui->comboRoute->currentText();
    QString trainDate = ui->inputDate->text();
    if(trainDate==""){
         QMessageBox::information(this, "Error", "Заполните поле \"дата\"! ");
    }
    else{
    int res = db->findRouteId(routename);
    db->insertIntoTrain(trainDate, res);
    QMessageBox::information(this, "Train added successfully", "Рейс успешно добавлен в расписание ");
    }
}

void User::fillCombo()   //заполняет выбор названия маршрута в добавлении рейса
{
    db->qry->prepare("SELECT name from route");
    db->qry->exec();
    while(db->qry->next()){
        ui->comboRoute->addItem(db->qry->value(0).toString());
    }
db->qry->clear();
}

void User::showRouteList()   //показать список маршрутов
{
    ui->routeList->clear();
    db->qry->prepare("SELECT name from route");
    db->qry->exec();
    while(db->qry->next()){
        ui->routeList->addItem(db->qry->value(0).toString());
    }
db->qry->clear();
}

void User::on_backToSchedule_clicked()    //кнопка "назад" из добавления рейса в расписание
{
    db->insertIntoJournal("Back button",db->currentUser->getName());
    ui->inputDate->clear();
    ui->addTrain_widget->setVisible(false);
    ui->schedule_widget->setVisible(true);
}


void User::on_get_routeList_clicked()   //кнопка список маршрутов
{
    ui->widget->setVisible(false);
    ui->routes_widget->setVisible(true);
    showRouteList();
}

void User::on_backToBegin_clicked()  //кнопка "назад" из списка маршрутов
{
     db->insertIntoJournal("Back button",db->currentUser->getName());
    ui->routes_widget->setVisible(false);
    ui->widget->setVisible(true);
}

void User::on_routeList_itemSelectionChanged()  // если в списке маршрутов выбран маршрут
{
   ui->routes_table->setRowCount(0);
QString routename = ui->routeList->currentItem()->text();
int route_id = db->findRouteId(routename);
db->qry->prepare ("SELECT locality.city, arrival_time, departure_time FROM locality JOIN Station JOIN route on locality.id = station.locality_id and station.route_id = route.id WHERE route.id=? ORDER BY arrival_time");
db->qry->addBindValue(route_id);
if(db->qry->exec()){
    int i=0;
    while(db->qry->next()){
        ui->routes_table->insertRow(i);
        ui->routes_table->setItem(i,0, new QTableWidgetItem(db->qry->value(0).toString()));
        ui->routes_table->setItem(i,1, new QTableWidgetItem(db->qry->value(1).toString()));
        ui->routes_table->setItem(i,2, new QTableWidgetItem(db->qry->value(2).toString()));
        i++;
    }
}
else{
    qDebug()<<"SQL Error";
}
}

void User::on_get_ticketReport_clicked()   // учет проданных билетов (для пользователей с расширенными правами)
{
     db->insertIntoJournal("Click get report",db->currentUser->getName());
ui->widget->setVisible(false);
ui->ticketReport_widget->setVisible(true);
fillDateList();
fillCashierList();  //Не продали билетов:

if(db->qry->exec("SELECT name FROM Cashier  WHERE Cashier.id NOT IN (SELECT cashier_id FROM ticket)")){
    if(db->qry->next())
        ui->bad->setText(db->qry->value(0).toString());
  while(db->qry->next()){
ui->bad->setText(ui->bad->text()+", " +db->qry->value(0).toString());

}
}
else{
    qDebug()<<"OSHIBKA"<<db->qry->lastError().text()<<endl;
}
// QSqlQuery *qry2 =new QSqlQuery(db->getDb()); //НЕ РАБОТАЕТ
/*qry2->prepare("SELECT * from ticket group by dateOfSale having COUNT(*) > ANY (SELECT count(*) FROM ticket GROUP BY dateOfSale)");
if (qry2->exec("SELECT * from cashier join ticket on cashier.id = ticket.cashier_id group by cashier_id where count(*) >= (SELECT MAX(COUNT(*)) from ticket GROUP BY cashier_id)")){
   qry2->next();
    ui->best->setText(qry2->value(1).toString());
}
        else{
    qDebug()<<"OSHIBKA"<<qry2->lastError().text()<<endl;
}
*/
}

void User::fillCashierList() //список кассиров
{
    db->qry->exec("SELECT name from cashier");
    while(db->qry->next()){
        ui->cashierList->addItem(db->qry->value(0).toString());
    }
    db->qry->clear();

}

void User::fillDateList() //список дат, в которые были проданы билеты
{
    db->qry->exec("SELECT DISTINCT dateOfSale from ticket order by dateOfSale");
    while(db->qry->next()){
        ui->dateList->addItem(db->qry->value(0).toString());
    }
    db->qry->clear();
}

void User::on_back_fromReport_clicked()  //возврат назад с учета билетов
{
    db->insertIntoJournal("Back button",db->currentUser->getName());
    ui->ticketReport_widget->setVisible(false);
    ui->widget->setVisible(true);
}

void User::on_cashierList_itemSelectionChanged() //когда выбран кассир
{
    QString cashier = ui->cashierList->currentItem()->text();
    db->qry->prepare("SELECT COUNT (*), experience FROM Ticket JOIN Cashier ON Ticket.Cashier_id = Cashier.id where cashier.name=? Group by Cashier_id");
    db->qry->addBindValue(cashier);
    db->qry->exec();
    if(db->qry->next()){
    ui->cashierInfo->setText("Кассир "+cashier+"\nПродано билетов: "+db->qry->value(0).toString()+"\nСтаж:"+db->qry->value(1).toString());
    }
    else{
        db->qry->prepare("SELECT experience from cashier where cashier.name=?");
        db->qry->addBindValue(cashier);
        db->qry->exec();
        db->qry->next();
        ui->cashierInfo->setText("Кассир "+cashier+"\n Продано билетов: 0\nСтаж:"+db->qry->value(0).toString());
    }
}

void User::on_dateList_itemSelectionChanged() //когда выбрана дата
{
    QString date = ui->dateList->currentItem()->text();
    db->qry->prepare("SELECT COUNT (*) FROM Ticket  where dateofsale=? Group by dateofsale");
    db->qry->addBindValue(date);
    db->qry->exec();
    QString result="";
    if(db->qry->next()){
    result+="Билетов продано: "+ db->qry->value(0).toString();
    }
    db->qry->prepare("SELECT COUNT (*) FROM Carriage JOIN Ticket ON Carriage.id = Ticket.Carriage_id  where ticket.dateOfSale=? GROUP BY Carriage.type");
    db->qry->addBindValue(date);
    db->qry->exec();
    db->qry->next();
    result+="\nИз них купе:"+db->qry->value(0).toString();
   if(db->qry->next()){
    result+="\nПлацкарт"+db->qry->value(0).toString();
   }
   else  result+="\nПлацкарт: 0";
    ui->dateInfo->setText(result);

}

void User::on_deleteTrain_clicked()
{
    int row=ui->schedule_table->currentRow();

QString  date = ui->schedule_table->item(row, 0)->text();
QString route = ui->schedule_table->item(row,1)->text();
int routeid = db->findRouteId(route);
db->qry->prepare ("DELETE FROM train WHERE departDate = ? AND route_id = ?");
db->qry->addBindValue(date);
db->qry->addBindValue(routeid);
if (db->qry->exec()){
    db->qry->clear();
    ui->schedule_table->setRowCount(0);
    db->qry->prepare("SELECT Train.departDate, route.name FROM Train join route on train.route_id = route.id ORDER BY departDate");  //запрос на получение расписания из бд
    int i=0;
    if (db->qry->exec()){  //обновляем расписание
 QMessageBox::information(this, "Success", "Рейс успешно удален!");
         QSqlQuery *qry2 =new QSqlQuery(db->getDb());
        while(db->qry->next()) {           //заполняем таблицу

                    qry2->prepare("SELECT departure_time FROM Station join route on station.route_id = route.id WHERE route.name = ? AND arrival_time=\"-\"");
                    qry2->addBindValue(db->qry->value(1).toString());
                    qry2->exec();
                    qry2->next();
               ui->schedule_table->insertRow(i);
               ui->schedule_table->setItem(i,0, new QTableWidgetItem(db->qry->value(0).toString()));
               ui->schedule_table->setItem(i,1, new QTableWidgetItem(db->qry->value(1).toString()));
               ui->schedule_table->setItem(i,2, new QTableWidgetItem(qry2->value(0).toString()));
               qry2->clear();
               qry2->prepare("SELECT arrival_time FROM Station join route on station.route_id = route.id WHERE route.name = ? AND departure_time=\"-\"");
               qry2->addBindValue(db->qry->value(1));
               qry2->exec();
               qry2->next();
               ui->schedule_table->setItem(i,3, new QTableWidgetItem(qry2->value(0).toString()));
               qry2->clear();
               i++;
        }
}
}}

void User::on_deleteRoute_clicked()  //удаление маршрута
{
    QString route=ui->routeList->currentItem()->text();
    int res = db->findRouteId(route);
    db->qry->prepare("DELETE FROM route where id = ?");
    db->qry->addBindValue(res);
    if(db->qry->exec()){
        ui->routeList->clear();
        db->qry->clear();
        db->qry->prepare("SELECT name from route");
        db->qry->exec();
        while(db->qry->next()){
            ui->routeList->addItem(db->qry->value(0).toString());
        }
    db->qry->clear();
    db->qry->prepare("DELETE from Train WHERE route_id = ?");
    db->qry->addBindValue(res);
    db->qry->exec();
    }
    else{
        qDebug()<<"Route not deleted";
    }
}

void User::on_editTrain_clicked()  //редактирование маршрута
{

    int row=ui->schedule_table->currentRow();

QString  date = ui->schedule_table->item(row, 0)->text();
QString route = ui->schedule_table->item(row,1)->text();
int routeid = db->findRouteId(route);
db->qry->prepare ("DELETE FROM train WHERE departDate = ? AND route_id = ?");
db->qry->addBindValue(date);
db->qry->addBindValue(routeid);
if(db->qry->exec()){

    ui->schedule_widget->setVisible(false);
    ui->editTrain_widget->setVisible(true);
    ui->inputDate_edit->setText(date);
    db->qry->prepare("SELECT name from route");
    db->qry->exec();
    while(db->qry->next()){
        ui->comboRoute_edit->addItem(db->qry->value(0).toString());
    }
db->qry->clear();
  }
ui->comboRoute_edit->setCurrentText(route);

}

void User::on_editTrain_button_clicked()
{
    db->insertIntoJournal("Edit train",db->currentUser->getName());
      QString routename =ui->comboRoute_edit->currentText();
        QString trainDate = ui->inputDate_edit->text();
        if(trainDate==""){
             QMessageBox::information(this, "Error", "Заполните поле \"дата\"! ");
        }
        else{
        int res = db->findRouteId(routename);
        db->insertIntoTrain(trainDate, res);
        QMessageBox::information(this, "Train added successfully", "Рейс успешно отредактирован ");
        }
        ui->editTrain_widget->setVisible(false);
        ui->schedule_widget->setVisible(true);
        fillSchedule();
}

void User::fillSchedule()  //заполнение расписания
{
    ui->schedule_table->setRowCount(0);
    db->qry->prepare("SELECT Train.departDate, route.name FROM Train join route on train.route_id = route.id ORDER BY departDate");  //запрос на получение расписания из бд
    int i=0;
    if (db->qry->exec()){
         QSqlQuery *qry2 =new QSqlQuery(db->getDb());
        while(db->qry->next()) {           //заполняем таблицу
                    qry2->prepare("SELECT departure_time FROM Station join route on station.route_id = route.id WHERE route.name = ? AND arrival_time=\"-\"");
                    qry2->addBindValue(db->qry->value(1).toString());
                    qry2->exec();
                    qry2->next();
               ui->schedule_table->insertRow(i);
               ui->schedule_table->setItem(i,0, new QTableWidgetItem(db->qry->value(0).toString()));
               ui->schedule_table->setItem(i,1, new QTableWidgetItem(db->qry->value(1).toString()));
               ui->schedule_table->setItem(i,2, new QTableWidgetItem(qry2->value(0).toString()));
               qry2->clear();
               qry2->prepare("SELECT arrival_time FROM Station join route on station.route_id = route.id WHERE route.name = ? AND departure_time=\"-\"");
               qry2->addBindValue(db->qry->value(1));
               qry2->exec();
               qry2->next();
               ui->schedule_table->setItem(i,3, new QTableWidgetItem(qry2->value(0).toString()));
               qry2->clear();
               i++;
        }}
}

void User::on_reportButton_clicked()
{

    QDateTime datetime = QDateTime::currentDateTime();
        QString fileName = "report " + datetime.toString();
    QPrinter printer;
   printer.setOutputFormat(QPrinter::PdfFormat);

    printer.setOutputFileName("D:/report.pdf");
    QPainter p(&printer);
        QString report =""+fileName+"\n ";
        QSqlQuery *qry2 =new QSqlQuery(db->getDb());

    db->qry->exec("SELECT city FROM locality");
    while(db->qry->next()){
        qry2->prepare("select name from route WHERE ? IN (SELECT city FROM Locality JOIN STATION ON Locality.id = Station.locality_id WHERE station.route_id = route.id)");
        qry2->addBindValue(db->qry->value(0));
        qry2->exec();
        report+="Город "+db->qry->value(0).toString()+"\n";
        report+="Маршруты, проходящие через этот город: ";
        while(qry2->next()){
            report+=qry2->value(0).toString()+", ";
        }
        report+= "\n\n";
    }

    p.drawText(p.window(),report);
  //  doc.print(&printer);
   p.end();
   QMessageBox::information(this, "report", "Отчет получен ");

}

void User::on_pushButton_clicked()  //поиск по дате
{
    QString from = ui->dateFrom->text();
    QString to = ui->dateTo->text();
    ui->schedule_table->setRowCount(0);
    db->qry->prepare("SELECT Train.departDate, route.name FROM Train join route on train.route_id = route.id WHERE DepartDate BETWEEN ? AND ? ORDER BY departDate");  //между датами
    db->qry->addBindValue(from);
    db->qry->addBindValue(to);
    int i=0;
    if (db->qry->exec()){
         QSqlQuery *qry2 =new QSqlQuery(db->getDb());
        while(db->qry->next()) {           //заполняем таблицу
                    qry2->prepare("SELECT departure_time FROM Station join route on station.route_id = route.id WHERE route.name = ? AND arrival_time=\"-\"");
                    qry2->addBindValue(db->qry->value(1).toString());
                    qry2->exec();
                    qry2->next();
               ui->schedule_table->insertRow(i);
               ui->schedule_table->setItem(i,0, new QTableWidgetItem(db->qry->value(0).toString()));
               ui->schedule_table->setItem(i,1, new QTableWidgetItem(db->qry->value(1).toString()));
               ui->schedule_table->setItem(i,2, new QTableWidgetItem(qry2->value(0).toString()));
               qry2->clear();
               qry2->prepare("SELECT arrival_time FROM Station join route on station.route_id = route.id WHERE route.name = ? AND departure_time=\"-\"");
               qry2->addBindValue(db->qry->value(1));
               qry2->exec();
               qry2->next();
               ui->schedule_table->setItem(i,3, new QTableWidgetItem(qry2->value(0).toString()));
               qry2->clear();
               i++;
        }}


}

void User::on_pushButton_2_clicked() //Только на букву С
{
db->qry->prepare("SELECT name FROM Cashier WHERE name LIKE 'S%'");
if(db->qry->exec()){
    ui->cashierList->clear();
    while(db->qry->next()){
        ui->cashierList->addItem(db->qry->value(0).toString());
    }
    db->qry->clear();
}
else{
    qDebug()<<db->qry->lastError().text();
}
}
