/* This file is part of IRadit.
   Copyright 2014, Victor Algaba <victor@radit.org> www.radit.org

   IRadit is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   Iradit is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with Iradit.  If not, see <http://www.gnu.org/licenses/>.
*/

#include <QDebug>
#include <QSqlRecord>
#include <QSqlQuery>
#include <QVariant>
#include <QFileInfo>
#include "iostream/Iostream.h"




Iostream::Iostream (){

    QFileInfo file("default/default.dat");

    if(file.exists())
        setBase();
    else
        setCreateBase();//if dont has file creat tables of database

}


Iostream::~Iostream (){


}



void Iostream::setAllButton(QList<Button *> allbutton){

    allButton=allbutton;

}



void Iostream::setTabwidget(QTabWidget *tabwidget){

    Tabwidget=tabwidget;
}




void Iostream::save(){


    QSqlQuery query(db);
    query.prepare("DELETE FROM PESTANA");
    query.exec();

    query.prepare("DELETE FROM BOTONES");
    query.exec();


    query.prepare("REPLACE INTO PESTANA"
                  "(ID) VALUES"
                  "(?)"
                 );

    query.addBindValue(Tabwidget->count());

     query.exec();

 QSqlDatabase::database().transaction();

           query.prepare("REPLACE INTO BOTONES"
                         "(ID,PLAYERTIPO, BOTONID, NOMBRE, URL) VALUES"
                         "(?,?,?,?,?)"
                         );

            for (int i = 0; i < allButton.size(); ++i) {

            query.addBindValue(allButton.at(i)->tab);
            query.addBindValue(allButton.at(i)->playerTipo);
            query.addBindValue(allButton.at(i)->botonId);

            query.addBindValue(allButton.at(i)->text());
            query.addBindValue(allButton.at(i)->url);
            query.exec();

                }

 QSqlDatabase::database().commit();


}

 void Iostream::createPestanas(){

     QSqlQuery query(db);
     query.prepare("SELECT * FROM PESTANA");
     query.exec();

     query.first();
     QSqlRecord rec =  query.record();
     Pestanas=rec.value("ID").toInt();


 }


void Iostream::load(){

    QSqlQuery query(db);
    query.prepare("SELECT * FROM BOTONES ORDER BY ID, BOTONID ASC");
    query.exec();

   // query.first();


    int i=0;
    while (query.next()) {
            QSqlRecord rec =  query.record();
            allButton.at(i)->tab=rec.value("ID").toInt();
            allButton.at(i)->playerTipo=rec.value("PLAYERTIPO").toInt();
            allButton.at(i)->botonId=rec.value("BOTONID").toInt();
            allButton.at(i)->setText(rec.value("NOMBRE").toString());
            allButton.at(i)->url=rec.value("URL").toString();
            allButton.at(i)->setToolTip(rec.value("NOMBRE").toString());

            if(allButton.at(i)->playerTipo==0)
                allButton.at(i)->setPlayer(allButton.at(i)->PlayerType1);
               else
                allButton.at(i)->setPlayer(allButton.at(i)->PlayerType2);




             i++;

         }

}


void Iostream::setBase(){

//db.close();
    db = QSqlDatabase::addDatabase("QSQLITE");

    db.setDatabaseName("default/default.dat");
    db.open();

}

void Iostream::setCreateBase(){

    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("default/default.dat");
    db.open();

    QSqlQuery query(db);


    query.exec("create table PESTANA (ID int primary key)");

    query.exec("create table BOTONES (ID int,"
               "PLAYERTIPO int,"
               "BOTONID int,"
               "NOMBRE text,"
               "URL tex)");


}
