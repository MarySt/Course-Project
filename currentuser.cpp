#include "currentuser.h"

CurrentUser::CurrentUser(QString n, bool p, QString pas) : name(n),pro(p),password(pas) {

}

CurrentUser::~CurrentUser(){

}

void CurrentUser::setName(QString n){
    name=n;
}

void CurrentUser::setPassword(QString pas){
    password=pas;
}

void CurrentUser::setPro(bool p){
    pro=p;
}

QString CurrentUser::getName(){
    return name;
}

QString CurrentUser::getPassword(){
    return password;
}

bool CurrentUser::isPro(){
    return pro;
}
