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
#include <QMessageBox>
#include <QContextMenuEvent>


#include "tab/Tab.h"
#include"button/Button.h"
#include"iostream/Iostream.h"
#include"menu/MenuTab.h"



Tab::Tab(QWidget *parent): QDialog(parent)
{
 setupUi(this);

 //this->setMaximumSize(20000,200);


iostream = new Iostream;


load();

   this->tabWidget->setCurrentIndex(0); //página una por defecto

}


Tab::~Tab(){
    save();
    delete iostream;

}



void Tab::addPage(){

    int page= this->tabWidget->count()+1;

    QString pa;
    pa=pa.setNum(page);
    this->tabWidget->addTab(new QWidget(this),"Page " + pa);
    this->tabWidget->setCurrentIndex(this->tabWidget->count()-1);
    QGridLayout *layout = new QGridLayout(this->tabWidget->currentWidget());

    layout->setHorizontalSpacing(0);
    layout->setVerticalSpacing(0);
    layout->setContentsMargins(0,0,0,0);

     QString numero, nu;
     int linea=1;
     int bottonid=1;

 for(int co=0; co<=5; co++){  //columnas

    for(int c=1;c<=10;c++){  //filas
        nu.setNum(linea);

          if(linea<10)
             numero ="0" + nu;
            else
             numero = nu;

         Button *button = new Button(this);
         connect(button,SIGNAL(clicked()),this, SLOT(ClickButton()));
         connect(button,SIGNAL(playmonitor()),this, SLOT(playMonitor()));



          if(c<6)
              button->setPlayer(Button::PlayerType1);
              else
              button->setPlayer(Button::PlayerType2);

         layout->addWidget(button,co,c);
         button->setText(numero);
         button->setNumero(numero);
         button->tab = this->tabWidget->count()-1;

         button->botonId=bottonid;

         linea++;
         bottonid++;
     }


   }

   allButton = this->findChildren<Button *>();


}


void Tab::deletePage(){

    QMessageBox::StandardButton reply;

    reply = QMessageBox::question(0, "Iradit", "¿Desea borrar la página?",
                                  QMessageBox::Yes|QMessageBox::No);
    if (reply == QMessageBox::No)
        return;



   int  tab = this->tabWidget->count()-1;
  //if(tab==0) //no se puede borrar la pagina 1
    //  return;

  for (int i = 0; i < allButton.size(); ++i){
        if(allButton.at(i)->tab==tab)

           delete allButton.at(i);              //borramos objetos de la ficha
       }

 this->tabWidget->removeTab(tab); //borramos ficha

 allButton = this->findChildren<Button *>();  //creamos tabla


}


void Tab::vaciarPage(){

     QMessageBox::StandardButton reply;

     reply = QMessageBox::question(0, "Iradit", "¿Desea vaciar la página?",
                                   QMessageBox::Yes|QMessageBox::No);
     if (reply == QMessageBox::No)
         return;

    int page=this->tabWidget->currentIndex();

    for (int i = 0; i < allButton.size(); ++i){
           if(allButton.at(i)->tab==page){
               allButton.at(i)->url="";
               allButton.at(i)->setToolTip("");
               allButton.at(i)->setText(allButton.at(i)->numero);

              }


         }

 }


void Tab::ClickButton(){

    QObject* obj = QObject::sender();
    Button *Boton = qobject_cast<Button *>(obj);

    if(Boton->url.isEmpty())// al arrastrar el drag sin esto se para
        return;

    Boton->isEncolar=false;  // si esta encolado lo quita evita de lo contrario sonaria dos veces

    if(Boton->playerTipo==0){
      // player1->streamrender->Stop();
       player1->setButton(Boton);
    }else{
      // player1->streamrender->Stop();
       player2->setButton(Boton);

    }

}


void Tab::playMonitor(){

    QObject* obj = QObject::sender();
    Button *Boton = qobject_cast<Button *>(obj);


    if(Boton->url.isEmpty())// al arrastrar el drag sin esto se para
        return;


     this->monitor->streamrender->setStopNext(Boton->url.toString());

    //colorea el play
     this->monitor->BtnPlay->setStyleSheet(QString::fromUtf8("background-color: qlineargradient(spread:pad, x1:0.994318, y1:1, x2:1, y2:0, stop:0.0113636 rgba(69, 142, 187, 255), stop:0.982955 rgba(95, 179, 241, 255));"));


}


//////////////////////////////////////////////tools///////////////////////////////////////////////
void Tab::toolMarcarTodos(){




    QObject* obj = QObject::sender();
    QPushButton *Boton = qobject_cast<QPushButton *>(obj);


    int player;
    int play=0;

    if(Boton==this->player1->BtnMarcar)
        player=0;
        else
        player=1;


     for (int ii = 0; ii < allButton.size(); ++ii){
              if(allButton.at(ii)->isPlay && allButton.at(ii)->tab == this->tabWidget->currentIndex() &&allButton.at(ii)->playerTipo==player)
                   play=allButton.at(ii)->botonId; //obtenemos el que esta en play para marcar los verdes que van despues

         }




    for (int i=0; i < allButton.size(); ++i){
           if(allButton.at(i)->playerTipo==player && allButton.at(i)->tab == this->tabWidget->currentIndex() && !allButton.at(i)->isPlay && allButton.at(i)->botonId>play && !allButton.at(i)->url.isEmpty()){
               allButton.at(i)->isEncolar=true;
               allButton.at(i)->setStyleSheet(QString::fromUtf8("background-color: qlineargradient(spread:pad, x1:0.994318, y1:1, x2:1, y2:0, stop:0.0113636 rgba(75, 141, 64, 255), stop:0.982955 rgba(149, 254, 92, 255));"));
             }

       }


 }

void Tab::toolDesMarcarTodos(){



    QObject* obj = QObject::sender();
    QPushButton *Boton = qobject_cast<QPushButton *>(obj);


    int player;

    if(Boton==this->player1->BtnDesMarcar)
        player=0;
        else
        player=1;



    for (int i = 0; i < allButton.size(); ++i){
           if(allButton.at(i)->playerTipo==player && allButton.at(i)->tab == this->tabWidget->currentIndex()&& !allButton.at(i)->isPlay){
               allButton.at(i)->isEncolar=false;

                     if(player==0){
                       allButton.at(i)->setPlayer(allButton.at(i)->PlayerType1);
                       }else{
                       allButton.at(i)->setPlayer(allButton.at(i)->PlayerType2);
                     }


             }

       }







}



 void Tab::toolBorrar(){

     QMessageBox::StandardButton reply;
     reply = QMessageBox::question(0, "Iradit", "¿Desea vaciar el player?",
                                   QMessageBox::Yes|QMessageBox::No);
     if (reply == QMessageBox::No)
         return;





     QObject* obj = QObject::sender();
     QPushButton *Boton = qobject_cast<QPushButton *>(obj);


     int player;

     if(Boton==this->player1->BtnBorrar)
         player=0;
         else
         player=1;

     for (int i = 0; i < allButton.size(); ++i){
            if(allButton.at(i)->playerTipo==player && allButton.at(i)->tab == this->tabWidget->currentIndex()){
                allButton.at(i)->vaciar();
              }

        }


 }


  void Tab::toolOcultar(){


      QObject* obj = QObject::sender();
      QPushButton *Boton = qobject_cast<QPushButton *>(obj);


      int player;
      bool estado;


       estado=Boton->isChecked();

      if(Boton==this->player1->BtnOcultar)
          player=0;
          else
          player=1;

      for (int i = 0; i < allButton.size(); ++i){
          if(allButton.at(i)->playerTipo==player && allButton.at(i)->tab == this->tabWidget->currentIndex() &&allButton.at(i)->url.isEmpty()){
                allButton.at(i)->setVisible(estado);
               }

         }



  }




void Tab::clickExplore(int player, const QList<QString> list){


    for (int ii = 0; ii < list.size(); ++ii){

        for (int i = 0; i < allButton.size(); ++i){
               if(allButton.at(i)->playerTipo==player && allButton.at(i)->tab == this->tabWidget->currentIndex() && allButton.at(i)->url.isEmpty() && allButton.at(i)->isVisible()){
                   allButton.at(i)->url=list.at(ii);
                   allButton.at(i)->setInfo(list.at(ii));
                   break;
                 }

           }


        }


}





void Tab::Final1(){

    for (int i = 0; i < allButton.size(); ++i){

           if(allButton.at(i)->isEncolar && allButton.at(i)->playerTipo==0){
               allButton.at(i)->isEncolar=false;
               player1->setButton(allButton.at(i));
               return;
               }
    }



 }


void Tab::Final2(){

    for (int i = 0; i < allButton.size(); ++i){

           if(allButton.at(i)->isEncolar && allButton.at(i)->playerTipo==1){
               allButton.at(i)->isEncolar=false;
               player2->setButton(allButton.at(i));
               return;
               }
    }




}




void Tab::save(){

     this->setCursor(Qt::BusyCursor);

 //Iostream *iostream = new Iostream;

 iostream->setAllButton(allButton);
 iostream->setTabwidget(this->tabWidget);
 iostream->save();


 //delete iostream;

  this->setCursor(Qt::ArrowCursor);


}

void Tab::load(){


    this->setCursor(Qt::BusyCursor);


iostream->createPestanas();

for (int i = 0; i < iostream->Pestanas; ++i)
addPage(); //añadimos las pàginas

iostream->setAllButton(allButton);

iostream->load();



//delete iostream;

 this->setCursor(Qt::ArrowCursor);

}

void Tab::contextMenuEvent(QContextMenuEvent *event)
 {
    MenuTab *menu = new MenuTab();
    menu->setTab(this);
    menu->exec(event->globalPos());
   delete menu;

}



void Tab::resizeEvent( QResizeEvent *event)
{



}






