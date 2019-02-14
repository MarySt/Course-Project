#include "db.h"

QSqlDatabase Db::getDb() const
{
    return db;
}

int Db::findRouteId(QString &name)
{
    qry->prepare("SELECT id from route where name=?");
    qry->addBindValue(name);
    if(qry->exec()){
        qry->next();
        qDebug()<<"findRouteId OK. Name: "<<name<<" id: "<<qry->value(0);
        return (qry->value(0).toInt());
    }
    else{
         qDebug() << "SQLite Error: " << db.lastError().text();
         return -1;
    }
}

Db::Db()
{
    db = QSqlDatabase::addDatabase("QSQLITE");
       db.setDatabaseName(dataBaseName);

    qry= new QSqlQuery (db);
}

Db:: ~Db(){
    if(currentUser){
        delete currentUser;
    }
    delete qry;

}
bool Db::launch() {
    qDebug() << "Launching DB...";
    if (db.open()) {
      if (qry->exec(queryCreateTableCarriage))
        qDebug() << "Carriage OK.";
      else
        qDebug() << "Carriage FAIL.";

      if (qry->exec(queryCreateTableCashier))
        qDebug() << "Cashier OK.";
      else
        qDebug() << "Cashier FAIL.";

      if (qry->exec(queryCreateTableClient))
        qDebug() << "Client OK.";
      else
        qDebug() << "Client FAIL.";
      if (qry->exec(queryCreateTableLocality))
        qDebug() << "Locality OK.";
      else
        qDebug() << "Locality FAIL.";
      if (qry->exec(queryCreateTableStation))
        qDebug() << "Station OK.";
      else
        qDebug() << "Station FAIL.";
      if (qry->exec(queryCreateTableTicket))
        qDebug() << "Ticket OK.";
      else
        qDebug() << "Ticket FAIL.";
      if (qry->exec(queryCreateTableTrain))
        qDebug() << "Train OK.";
      else
        qDebug() << "Train FAIL.";
      if (qry->exec(queryCreateTableRoute))
        qDebug() << "Route OK.";
      else
        qDebug() << "Route FAIL.";
      if (qry->exec(queryCreateTableJournal))
        qDebug() << "Journal OK.";
      else
        qDebug() << "Journal FAIL.";
      if (qry->exec(queryCreateTableUser))
        qDebug() << "User OK.";
      else
        qDebug() << "User FAIL.";
      if (qry->exec(queryCreateTableProUser))
        qDebug() << "ProUser OK.";
      else
        qDebug() << "ProUser FAIL.";
    } else {
      qDebug() << "SQLite Error: " << db.lastError().text();
    }
    qry->clear();
    return true;
  }

void Db::launchInsert(){
    /*
    insertIntoCashier("Ivanov Ivan",5);
    insertIntoCashier("Petrov Petr",2);
    insertIntoCashier("Kovalev Andrew",9);
    insertIntoCashier("Prototenko Kirill",1);
    insertIntoCashier("Chernyakov Igor",7);
    insertIntoCashier("Solodenko Anna",2);
    insertIntoCashier("Semenova Victoriya",3);
    insertIntoCashier("Lemko Olga",3);
    insertIntoCashier("Sinko Olexandr",1);
    insertIntoCashier("Kadylo Ivan",6);

    insertIntoClient("Samko Petr", "1987-10-20");
    insertIntoClient("Bravo Ektor", "1965-06-15");
    insertIntoClient("Esenin Sergey", "1989-09-09");
    insertIntoClient("Block Alexandr", "1980-11-20");
    insertIntoClient("Vasilyev Igor", "1976-06-03");
    insertIntoClient("Krylov Oleg", "1974-02-03");
    insertIntoClient("Smirnov Mykola", "1967-12-19");
    insertIntoClient("Kamorin Andrew", "1990-03-29");

    insertIntoRoute("North","231");
    insertIntoRoute("South","163");
    insertIntoRoute("West","456");
    insertIntoRoute("East","643");
    insertIntoRoute("Chernomorets","123");
    insertIntoRoute("Ivan Franko","647");
    insertIntoRoute("Taras Shevchenko","627");
    insertIntoRoute("Lesya Ukrainka","472");

    insertIntoTrain("2018-11-20",1);
    insertIntoTrain("2018-12-10",1);
    insertIntoTrain("2018-11-16",1);
    insertIntoTrain("2018-11-17",2);
    insertIntoTrain("2018-11-22",2);
    insertIntoTrain("2018-12-25",3);
    insertIntoTrain("2019-01-20",3);
    insertIntoTrain("2019-01-03",4);
    insertIntoTrain("2018-12-01",4);
    insertIntoTrain("2018-11-25",1);
    insertIntoTrain("2018-01-12",5);
    insertIntoTrain("2018-11-18",5);
    insertIntoTrain("2018-12-25",6);
    insertIntoTrain("2018-11-18",6);
    insertIntoTrain("2018-12-17",6);
    insertIntoTrain("2018-12-12",7);
    insertIntoTrain("2018-12-18",7);
    insertIntoTrain("2018-12-19",7);
    insertIntoTrain("2019-01-19",8);
    insertIntoTrain("2019-01-02",8);
    insertIntoTrain("2018-11-27",8);

    insertIntoCarriage(true, 1);
    insertIntoCarriage(false, 1);
    insertIntoCarriage(true, 2);
    insertIntoCarriage(false, 2);
    insertIntoCarriage(true, 3);
    insertIntoCarriage(true, 3);
    insertIntoCarriage(false, 3);
    insertIntoCarriage(false, 3);
    insertIntoCarriage(true, 4);
    insertIntoCarriage(true, 5);
    insertIntoCarriage(false, 4);
    insertIntoCarriage(false, 5);
    insertIntoCarriage(true, 4);
    insertIntoCarriage(true, 5);
    insertIntoCarriage(false,6);
    insertIntoCarriage(false, 6);
    insertIntoCarriage(true, 7);
    insertIntoCarriage(true, 8);
    insertIntoCarriage(false, 9);
    insertIntoCarriage(false, 10);
    insertIntoCarriage(true, 11);
    insertIntoCarriage(true, 12);
    insertIntoCarriage(false, 13);
    insertIntoCarriage(false, 14);
    insertIntoCarriage(true, 15);
    insertIntoCarriage(true, 16);
    insertIntoCarriage(false, 17);
    insertIntoCarriage(false, 18);
    insertIntoCarriage(true, 19);
    insertIntoCarriage(true, 20);
    insertIntoCarriage(false, 21);
    insertIntoCarriage(false, 19);
    insertIntoCarriage(true, 20);
    insertIntoCarriage(true, 15);
    insertIntoCarriage(false, 16);
    insertIntoCarriage(false, 17);
    insertIntoCarriage(true, 17);
    insertIntoCarriage(true, 15);
    insertIntoCarriage(false, 14);
    insertIntoCarriage(false, 13);

    insertIntoLocality("North", "Zhytomyr"); //1
    insertIntoLocality("North", "Chernigov"); //2
    insertIntoLocality("North", "Poltava");   //3
    insertIntoLocality("North", "Kyiv");
    insertIntoLocality("South", "Odessa"); //5
    insertIntoLocality("South", "Mykolaiv");
    insertIntoLocality("South", "Kherson");  //7
    insertIntoLocality("West", "Lviv");
    insertIntoLocality("West", "Ivano-Frankivsk"); //9
    insertIntoLocality("East", "Kharkiv");
    insertIntoLocality("East", "Zaporozhie");    //11
    insertIntoLocality("Center", "Kyiv");
    insertIntoLocality("Center", "Vinnitsa");   //13
    insertIntoLocality("Center", "Dnepr");
    insertIntoLocality("West", "Hmelnitskiy");//15

    insertIntoStation(1,1,"-","12:00:00");
    insertIntoStation(1,2,"14:00:00","14:05:00");
    insertIntoStation(1,3,"16:30:00","16:45:00");
    insertIntoStation(1,4,"18:00:00","-");

    insertIntoStation(2,5,"-","16:00:00");
    insertIntoStation(2,6,"19:20:00","19:35:00");
    insertIntoStation(2,7,"22:00:00","-");

    insertIntoStation(3,8,"-","15:00:00");
    insertIntoStation(3,9,"16:50:00","17:05:00");
    insertIntoStation(3,15,"19:20:00","-");

    insertIntoStation(4,10,"-","10:20:00");
    insertIntoStation(4,11,"12:10:00","12:20:00");
    insertIntoStation(4,14,"14:35:00","-");

    insertIntoStation(5,5,"-","14:20:00");
    insertIntoStation(5,11,"16:00:00","16:15:00");
    insertIntoStation(5,13,"19:35:00","19:50:00");
    insertIntoStation(5,12,"22:10:00","-");

    insertIntoStation(6,5,"-","12:30:00");
    insertIntoStation(6,3,"14:40:00","14:45:00");
    insertIntoStation(6,8,"16:20:00","16:40:00");
    insertIntoStation(6,9,"18:10:00","-");

    insertIntoStation(7,3,"-","15:40:00");
    insertIntoStation(7,2,"17:30:00","17:45:00");
    insertIntoStation(7,13,"19:20:00","19:30:00");
    insertIntoStation(7,4,"21:15:00","-");
    insertIntoStation(8,5,"-","17:25:00");
    insertIntoStation(8,6,"19:25:00","19:45:00");
    insertIntoStation(8,11,"22:10:00","22:20:00");
    insertIntoStation(8,14,"23:55:00","-");
    insertIntoTicket(10,150,"2018-12-08",1,2,3);
    insertIntoTicket(12,120,"2018-12-08",3,2,3);
    insertIntoTicket(8,100,"2018-12-07",4,3,2);
    insertIntoTicket(10,150,"2018-12-07",6,1,4);
    insertIntoTicket(15,100,"2018-12-07",8,1,5);
    insertIntoTicket(20,170,"2018-12-09",9,2,1);
    insertIntoTicket(11,130,"2018-12-06",6,2,1);
    insertIntoTicket(9,110,"2018-12-06",8,4,6);
    insertIntoTicket(18,120,"2018-12-05",10,4,6);
    */
}



void Db::insertIntoCashier(QString n, int exp){
    qry->prepare( "INSERT INTO cashier(name, experience) VALUES(?, ?)");
    qry->addBindValue(n);
    qry->addBindValue(exp);
    if (qry->exec()) {
          qDebug() << " Cashier Inserted Succesfully!";
        } else
        qDebug() << "Cashier Error: " << qry->lastError();
    qry->clear();
}

void Db::insertIntoClient(QString n, QString dateOfBirth){
    qry->prepare( "INSERT INTO client(name, dateOfBirth) VALUES(?, ?)");
    qry->addBindValue(n);
    qry->addBindValue(dateOfBirth);
    if (qry->exec()) {
          qDebug() << " Client Inserted Succesfully!";
        } else
        qDebug() << "Client Error: " << qry->lastError();
    qry->clear();
}


void Db::insertIntoRoute(QString name, QString myNumber){
    qry->prepare( "INSERT INTO route(name, myNumber) VALUES(?,?)");
  qry->addBindValue(name);
    qry->addBindValue(myNumber);
    if (qry->exec()) {
          qDebug() << "Route Inserted Succesfully!";
        } else
        qDebug() << "Route Error: " << qry->lastError();
    qry->clear();
}


void Db::insertIntoTrain(QString date, int route){
    qry->prepare( "INSERT INTO train( departDate, route_id ) VALUES(?,?)");
    qry->addBindValue(date);
    qry->addBindValue(route);
    if (qry->exec()) {
          qDebug() << "Train Inserted Succesfully!";
        } else
        qDebug() << "Train Error: " << qry->lastError();
    qry->clear();
}



void Db::insertIntoCarriage(bool isCoupe, int train){
    if(isCoupe)
        qry->prepare( "INSERT INTO Carriage(type,seatsCount, train_id) VALUES(\"coupe\",36, ?)");
    if(!isCoupe)
         qry->prepare( "INSERT INTO Carriage(type,seatsCount, train_id) VALUES(\"econom\",54, ?)");
    qry->addBindValue(train);
    if (qry->exec()) {
          qDebug() << "Carriage Inserted Succesfully!";
        } else
        qDebug() << "Carriage Error: " << qry->lastError();
    qry->clear();
}

void Db::insertIntoLocality(QString region, QString city){
    qry->prepare( "INSERT INTO locality(region, city ) VALUES(?,?)");
    qry->addBindValue(region);
    qry->addBindValue(city);
    if (qry->exec()) {
          qDebug() << "Locality Inserted Succesfully!";
        } else
        qDebug() << "Locality Error: " << qry->lastError();
    qry->clear();
}

void Db::insertIntoStation(int route, int locality, QString arrive, QString depart){
    qry->prepare( "INSERT INTO Station(route_id,locality_id, arrival_time, departure_time) VALUES(?,?,?,?)");
    qry->addBindValue(route);
    qry->addBindValue(locality);
    qry->addBindValue(arrive);
    qry->addBindValue(depart);
    if (qry->exec()) {
          qDebug() << "Station Inserted Succesfully!";
        } else
        qDebug() << "Station Error: " << qry->lastError();
    qry->clear();
}

void Db::insertIntoTicket(int seat, double price, QString dateOfSale, int carriage_id, int cashier_id, int client_id){
   // QSqlQuery qry(db);
    qry->prepare( "INSERT INTO ticket(seatNumber, price, dateOfSale, carriage_id, cashier_id, client_id) VALUES(?,?,?,?,?, ?)");
    qry->addBindValue(seat);
    qry->addBindValue(price);
    qry->addBindValue(dateOfSale);
    qry->addBindValue(carriage_id);
    qry->addBindValue(cashier_id);
    qry->addBindValue(client_id);
    if (qry->exec()) {
          qDebug() << "Ticket Inserted Succesfully!";
        } else
        qDebug() << "Ticket Error: " << qry->lastError();
    qry->clear();
}

void Db::insertIntoJournal(QString factType, QString username){
    QDate date= QDate::currentDate();
    QString strDate= date.toString("yyyy-MM-dd");
    QTime time= QTime::currentTime();
    QString strTime=time.toString("hh:mm:ss");
    qry->prepare( "INSERT INTO Journal(factDate, factTime, factType, username) VALUES(?,?,?,?)");
    qry->addBindValue(strDate);
    qry->addBindValue(strTime);
    qry->addBindValue(factType);
    qry->addBindValue(username);
    if (qry->exec()) {
          qDebug() << "Journal Inserted Succesfully!";
        } else
        qDebug() << "Journal Error: " << qry->lastError();
    qry->clear();
}

void Db::insertIntoUser(QString login, QString password){
    qry->prepare( "INSERT INTO User(login, password) VALUES(?,?)");
    qry->addBindValue(login);
    qry->addBindValue(password);
    if (qry->exec()) {
          qDebug() << "User Inserted Succesfully!"<<login<<" "<<password<<endl;
        } else
        qDebug() << "User Error: " << qry->lastError();
    qry->clear();
}

void Db::insertIntoProUser(QString login, QString password, QString position){
    qry->prepare( "INSERT INTO proUser(login, password, position) VALUES(?,?,?)");
    qry->addBindValue(login);
    qry->addBindValue(password);
    qry->addBindValue(position);
    if (qry->exec()) {
          qDebug() << "Pro Inserted Succesfully!";

        } else
        qDebug() << "Pro Error: " << qry->lastError();
    qry->clear();
}

bool Db::isUser(QString &login, QString password){
    if(password!=""){
    qry->prepare("SELECT * FROM user WHERE login=? AND password=?");
    qry->addBindValue(login);
    qry->addBindValue(password);
    if(qry->exec()){
        if(qry->next()){
            return true;
        }
    }
    else
    qDebug() << "isUser error: " << qry->lastError();
    }
    else{
        qry->prepare("SELECT * FROM user WHERE login=?");
        qry->addBindValue(login);
        if(qry->exec()){
            if(qry->next()){
                return true;
            }
        }
        else
        qDebug() << "isUser error: " << qry->lastError();
    }
    qry->clear();
    return false;
}

bool Db::isProUser(QString &login, QString password){
     if(password!=""){
    qry->prepare("SELECT * FROM prouser WHERE login=? AND password=?");
    qry->addBindValue(login);
    qry->addBindValue(password);
    if(qry->exec()){
        if(qry->next()){
            return true;
        }
    }
    else
    qDebug() << "isProUser error: " << qry->lastError();

     }
     else {
         qry->prepare("SELECT * FROM prouser WHERE login=?");
         qry->addBindValue(login);
         if(qry->exec()){
             if(qry->next()){
                 return true;
             }
         }
         else
         qDebug() << "isProUser error: " << qry->lastError();
     }
    qry->clear();
    return false;
}


