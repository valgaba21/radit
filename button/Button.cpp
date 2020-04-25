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



#include <QMenu>
#include <QDebug>
#include <QContextMenuEvent>

#include <QDrag>
#include <QClipboard>
#include <QApplication>

#include "button/Button.h"
#include "menu/MenuButton.h"

#include "engine/StreamFile.h"
#include "engine/StreamMath.h"



Button::Button(QWidget *parent): QPushButton(parent)
{

  this->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Expanding);
  //  this->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Expanding);
    this->setText(" Nombre del fichero\n"
                  "\n"
                  "00:00:00");



    this->setCursor(QCursor(Qt::PointingHandCursor));
    this->setAcceptDrops(true);

    this->isEncolar=false;
    this->isPlay=false;


}



void Button::mousePressEvent(QMouseEvent *event){






if ((event->button() == Qt::LeftButton) && (event->modifiers() == Qt::ShiftModifier)){

    QDrag *drag = new QDrag(this);
    QMimeData *mimeData = new QMimeData;
    mimeData->setText(this->url.toString());
    drag->setMimeData(mimeData);
    drag->exec(Qt::MoveAction);
    return;

 }
   if (event->button() == Qt::LeftButton)
           emit clicked();




}




void Button::dragEnterEvent(QDragEnterEvent *event){


    if (event->mimeData()->hasFormat("text/uri-list"))
        event->acceptProposedAction();

    if (event->mimeData()->hasFormat("text/plain"))
         event->acceptProposedAction();



}


void Button::dropEvent(QDropEvent *event){

     QList<QUrl> urls = event->mimeData()->urls();
    if (!urls.isEmpty()){
         url=urls.first().toLocalFile();
         setInfo(urls.first().toLocalFile());
        return;
    }

    Button* source = qobject_cast<Button*>(event->source());

   // if(source==this)  //  solo reproduce cuando ambos son iguales evita ciertas cosas
     //  emit clicked();

     if(source->isPlay || this->isPlay) // en play no es posible drag drop
         return;



   if(source==this) //revisar
       return;

        url=event->mimeData()->text();

        if(url.isEmpty())
           return;



       //setInfo(event->mimeData()->text());
       this->setText(source->text());
       this->setToolTip(source->toolTip());
       this->url=source->url;

        if(source->isEncolar){
            this->isEncolar=true;
            this->setStyleSheet(source->styleSheet());
            source->isEncolar=false;

        }


        source->url="";
        source->setText("");
        source->setText(source->numero);

        if(source->playerTipo==0){
           source->setPlayer(PlayerType1);
           }else{
           source->setPlayer(PlayerType2);

        }




}



void Button::setInfo(QFileInfo file){

    StreamFile *streamfile =new StreamFile;
    streamfile->setUrl(file.absoluteFilePath());

    StreamMath *streammath = new StreamMath(streamfile->stream);




    //QString L2=file.baseName().mid(13);
    this->setToolTip(file.completeBaseName());

    this->setText(" " +file.completeBaseName()+"\n"
                  "\n"+
                  streammath->SegundoToFormato("hh:mm:ss"));

    delete streamfile;
    delete streammath;

}


void Button::setNumero(QString num){
    this->numero=num;
}



 void Button::preasignar(){

     QObject* obj = QObject::sender();
     QAction *opcion = qobject_cast<QAction *>(obj);


     if(opcion->objectName()=="1")
         setPlayer(PlayerType1);
        else
         setPlayer(PlayerType2);


}

void Button::vaciar(){

    if(this->isPlay || this->isEncolar)
        return;

    this->url="";
    this->setText("");
    this->setText(this->numero);
    this->setToolTip("");

}


void Button::encolar(){

    if(this->url.isEmpty()) // no es posible vacio
        return;

    if(this->isPlay) // en play no es posible
        return;

    if(isEncolar){  // ya esta encolado lo quitamos

        isEncolar=false;

        if(this->playerTipo==0){

            setPlayer(PlayerType1);
           }else{
            setPlayer(PlayerType2);

        }

        return;
    }


    this->setStyleSheet(QString::fromUtf8("background-color: qlineargradient(spread:pad, x1:0.994318, y1:1, x2:1, y2:0, stop:0.0113636 rgba(75, 141, 64, 255), stop:0.982955 rgba(149, 254, 92, 255));"));
    this->isEncolar=true;

}







void Button::clickMonitor(){  // llega de la opcion del menu
   emit playmonitor(); //hacia el tab para reproducir
 }


void Button::cortar(){
    QClipboard *clipboard = QApplication::clipboard();
    QMimeData *mimeData = new QMimeData;

    mimeData->setText(this->url.toString());
    clipboard->setMimeData(mimeData);

    vaciar();

 }



void Button::copiar(){

     QClipboard *clipboard = QApplication::clipboard();
     QMimeData *mimeData = new QMimeData;

     mimeData->setText(this->url.toString());
     clipboard->setMimeData(mimeData);

}


void Button::pegar(){

     QClipboard *clipboard = QApplication::clipboard();

     QList<QUrl>urls = clipboard->mimeData()->urls();
     if (!urls.isEmpty()){
          url=urls.first().toLocalFile();
          setInfo(urls.first().toLocalFile());
         return;
     }

     url=clipboard->mimeData()->text();
     setInfo(QFileInfo(clipboard->mimeData()->text()));
}


///
void Button::setPlayer(PLAYER_TIPO tipo){

isEncolar=false;

    switch(tipo) {
            case 0 :
                  playerTipo= tipo;
                  this->setStyleSheet(QString::fromUtf8("QPushButton {\n"
                                                        "\n"
                                                        "background-color: qlineargradient(spread:pad, x1:0.994318, y1:1, x2:1, y2:0, stop:0.0113636 rgba(146, 169, 211, 255), stop:0.982955 rgba(174, 199, 230, 255));\n"
                                                        "border-color: rgb(0, 0, 0);\n"
                                                        "\n"
                                                        "}\n"
                                                        "\n"
                                                        "QPushButton:hover {\n"
                                                        "background-color: rgb(255, 255, 255);\n"
                                                        "\n"
                                                        "\n"
                                                        "}"));
               break;
             case 1 :
                  playerTipo=tipo;
                  this->setStyleSheet(QString::fromUtf8("QPushButton {\n"
                                                        "\n"
                                                        "background-color: qlineargradient(spread:pad, x1:0.994318, y1:1, x2:1, y2:0, stop:0.00568182 rgba(209, 160, 131, 255), stop:0.0113636 rgba(138, 106, 93, 255), stop:0.982955 rgba(223, 190, 166, 255));\n"
                                                        "border-color: rgb(0, 0, 0);\n"
                                                        "\n"
                                                        "}\n"
                                                        "\n"
                                                        "QPushButton:hover {\n"
                                                        "background-color: rgb(255, 255, 255);\n"
                                                        "\n"
                                                        "\n"
                                                        "}"));
                break;


    }





 }


void Button::contextMenuEvent(QContextMenuEvent *event)
 {

    MenuButton *menu =new MenuButton();
     menu->setButton(this);
    menu->exec(event->globalPos());
   delete menu;

}








