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
#include <QApplication>
#include <QSettings>
#include "setting/Setting.h"

#include "bass.h"



Setting::Setting(QWidget *parent): QDialog(parent)
{
 setupUi(this);

 //setModal(true);

 #ifdef Q_OS_WIN32
    // setWindowFlags( Qt::Tool);
 #endif

 //define size of form
 QSize fixedSize(this->width(),this->height());
 setMinimumSize(fixedSize);
 setMaximumSize(fixedSize);
 setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);



 //aceptar/cancelar
   connect(this->BtnCancelar,SIGNAL(clicked()),this, SLOT(close()));  //cancelar
   connect(this->BtnAceptar,SIGNAL(clicked()),this, SLOT(clickAceptar()));  //cancelar

AddDispositivo();
Establecer();

}



void Setting::AddDispositivo(){

    BASS_DEVICEINFO i;
        QString nombre;

        QString nulo(tr("Sin Sonido")); //añadimos nulo
        this->Dispositivo1->addItem(nulo);
        this->Dispositivo2->addItem(nulo);
        this->Dispositivo3->addItem(nulo);

        #ifdef Q_OS_UNIX
          //  QString def(tr("Defecto")); //en linux añadimos otro el default
          //  this->Dispositivo->addItem(def);
        #endif


     //****************** añadimos las tarjetas de audio *****************************
        for (int c=1;BASS_GetDeviceInfo(c,&i);c++)// device 1 = el primer dispositivo
        {
           if (i.flags&BASS_DEVICE_ENABLED){
                    this->Dispositivo1->addItem(nombre.fromAscii(i.name));
                    this->Dispositivo2->addItem(nombre.fromAscii(i.name));
                    this->Dispositivo3->addItem(nombre.fromAscii(i.name));

              }
        }


}



void Setting::Establecer(){

    Qt::CheckState checkState;

    QSettings RaditIni("IRadit.ini", QSettings::IniFormat);

        Dispositivo1->setCurrentIndex(RaditIni.value("Player1/Dispositivo").toInt());
        Dispositivo2->setCurrentIndex(RaditIni.value("Player2/Dispositivo").toInt());
        Dispositivo3->setCurrentIndex(RaditIni.value("Monitor/Dispositivo").toInt());


        checkState =  static_cast<Qt::CheckState>(RaditIni.value("General/Vumetros", Qt::Unchecked).toInt());
        this->checkVumeter->setCheckState(checkState);



}



void Setting::clickAceptar(){

    QSettings IRaditIni("IRadit.ini", QSettings::IniFormat);

        IRaditIni.setValue("Player1/Dispositivo",this->Dispositivo1->currentIndex());
        IRaditIni.setValue("Player2/Dispositivo",this->Dispositivo2->currentIndex());
        IRaditIni.setValue("Monitor/Dispositivo",this->Dispositivo3->currentIndex());


        IRaditIni.setValue("General/Vumetros",this->checkVumeter->checkState());

     close();

 }















