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



#include "player/Player.h"




Player::Player(QWidget *parent): QDialog(parent)
{
 setupUi(this);

 this->setMaximumSize(20000,200);
 //this->setMinimumSize(0,200);

 streamrender = new  StreamRender(this);

  connect(streamrender, SIGNAL(Finish()),this, SLOT(Final()));

   streamrender->setVumeter(this->vumeter);
   streamrender->setSlider(this->slider);
   streamrender->setLabel(this->label);

  connect(BtnPlay,SIGNAL(clicked()),this, SLOT(Play()));
  connect(BtnPause,SIGNAL(clicked()),this, SLOT(Pause()));
  connect(BtnStop,SIGNAL(clicked()),this, SLOT(Stop()));

  connect(BtnAtras,SIGNAL(clicked()),streamrender, SLOT(SlideBack()));
  connect(BtnAlante,SIGNAL(clicked()),streamrender, SLOT(SlideForward()));

  connect(BtnEncadenar,SIGNAL(clicked(bool)),streamrender, SLOT(setEncadenar(bool)));


  this->button= new Button(this); // temporal para los colores
  this->button->setVisible(false);
}


void Player::setButton(Button *button){

    streamrender->setStopNext(button->url.toString());
    this->LabelCancion->setText(button->text());
    setColor(button);


}


void Player::Play(){
    this->BtnPause->setStyleSheet(this->BtnStop->styleSheet());
    streamrender->Play();

}

void Player::Pause(){
    button->isPlay=true;
    this->BtnPause->setStyleSheet(QString::fromUtf8("background-color: qlineargradient(spread:pad, x1:0.994318, y1:1, x2:1, y2:0, stop:0.0113636 rgba(69, 142, 187, 255), stop:0.982955 rgba(95, 179, 241, 255));"));


 streamrender->Pause();
}


void Player::Stop(){

    streamrender->Stop();
    this->LabelCancion->setText("");
     borrarColor();
}



void Player::setColor(Button *button ){

    borrarColor();
    button->setStyleSheet(QString::fromUtf8("background-color: qlineargradient(spread:pad, x1:0.994318, y1:1, x2:1, y2:0, stop:0.0113636 rgba(138, 106, 93, 255), stop:0.0113636 rgba(249, 36, 16, 255), stop:0.982955 rgba(255, 143, 123, 255));"));
    this->button=button;
    this->button->isPlay=true;
    this->BtnPlay->setStyleSheet(QString::fromUtf8("background-color: qlineargradient(spread:pad, x1:0.994318, y1:1, x2:1, y2:0, stop:0.0113636 rgba(69, 142, 187, 255), stop:0.982955 rgba(95, 179, 241, 255));"));

}



void Player::borrarColor(){

    if(this->button->playerTipo==0)
       this->button->setPlayer(Button::PlayerType1);

    if(this->button->playerTipo==1)
       this->button->setPlayer(Button::PlayerType2);

  button->isPlay=false;
  this->BtnPause->setStyleSheet(this->BtnStop->styleSheet()); //borrar color pause
  this->BtnPlay->setStyleSheet(this->BtnPause->styleSheet()); //borrar color play

}


void Player::Final(){ // llega de streamRender

     this->LabelCancion->setText("");
     borrarColor();
}



void Player::setTipo(PLAYER_TIPO tipo){


    switch(tipo) {
            case 0 :
               LabelTitulo->setStyleSheet(QString::fromUtf8("background-color: qlineargradient(spread:pad, x1:0.994318, y1:1, x2:1, y2:0, stop:0.0113636 rgba(0, 71, 161, 255), stop:0.982955 rgba(59, 145, 246, 255));\n"
                                                            "color: rgb(255, 255, 255);"));
               LabelTitulo->setText(" Player 1");
               break;
            case 1 :

                 LabelTitulo->setStyleSheet(QString::fromUtf8("background-color: qlineargradient(spread:pad, x1:0.994318, y1:1, x2:1, y2:0, stop:0.0113636 rgba(109, 40, 9, 255), stop:0.982955 rgba(214, 109, 18, 255));\n"
                                                              "color: rgb(255, 255, 255);"));
                 LabelTitulo->setText(" Player 2");
                break;
            case 2 :
                 LabelTitulo->setStyleSheet(QString::fromUtf8("background-color: qlineargradient(spread:pad, x1:0.994318, y1:1, x2:1, y2:0, stop:0.0113636 rgba(43, 75, 10, 255), stop:0.982955 rgba(92, 174, 4, 255));\n"
                                                              "color: rgb(255, 255, 255);"));
                 LabelTitulo->setText(" Monitor");
                break;


    }



}

void Player::resizeEvent( QResizeEvent *event)
{
   // this->setMaximumSize(20000,150);


}





