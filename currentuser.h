#ifndef CURRENTUSER_H
#define CURRENTUSER_H
#include <QString>

class CurrentUser{
private:
QString name;
bool pro;
QString password;

public:

CurrentUser(QString n, bool p, QString pas="");
~CurrentUser();
void setPassword(QString pas);
void setName(QString n);
void setPro(bool p);

QString getName();
QString getPassword();
bool isPro();


};


#endif


