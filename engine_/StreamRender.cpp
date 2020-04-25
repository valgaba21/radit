/* This file is part of Radit.
   Copyright 2013, Victor Algaba <victor@radit.org>

   Radit is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   Radit is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with Clementine.  If not, see <http://www.gnu.org/licenses/>.
*/


#include "engine/StreamRender.h"
#include "engine/StreamPlay.h"
#include "engine/StreamMath.h"


void CALLBACK StatusProc(const void *buffer, DWORD length, void * /*user*/)
{
    if (buffer && !length)
    {
       qDebug() << buffer; // display connection status
    }
    qDebug() << buffer <<length; // display connection status
}

/////////////////////////////////////////
StreamRender::StreamRender(QWidget *parent):
   QObject(parent)
{

    Timer = new QTimer();
       connect(Timer, SIGNAL(timeout()), this, SLOT(Update())); // temporizaor horario
    Render=10;

    pisador = new Pisador(this);
    PisadorEstado=false;
    isSlider=false;



}

/////////////////////////////////////////

StreamRender::~StreamRender(){

    delete Timer;
    delete pisador;

}

void StreamRender::setStopNext(const QString url){
     Stop();
     setUrl(url);

}

void StreamRender::setNext(const QString url){
    emit next();  //Finish all stream
    setUrl(url);
}


void StreamRender::setUrl(const QString url){

    StreamPlay *streamplay= new StreamPlay;
    connect(this, SIGNAL(next()),streamplay, SLOT(setNext()));
    connect(this, SIGNAL(stop()),streamplay, SLOT(setStop()));

    connect(streamplay, SIGNAL(Finish()),this, SLOT(StreamFree()));



    streamplay->isFaderSolapar(FundirSolapar);
    streamplay->isFaderStop(FundirParar);
    streamplay->setFaderSec(Fundir);
    streamplay->setDevice(Device);
    streamplay->setUrl(url);

    stream = streamplay->stream;


     StreamMath *streammath = new StreamMath(stream);
     segundos = streammath->Duracion();
     Slider->setMaximum(segundos);
     delete streammath;
     Timer->start(Render);




}

/////////////////////////////////////////
 void StreamRender::Update(){


     QTimer::singleShot(30, this, SLOT(render())); // el consumo de cpu es 0

    if (isFinal())
    {
        // if(Timer->isActive ())
        // {
            Timer->stop();
             emit  Finish();
        // }
     }


}

////////////////////////////////////
void StreamRender::render(){


    StreamMath *w_StreamMath = new StreamMath(stream);
    Label->setText(w_StreamMath->SegundoToFormato(segundos-w_StreamMath->Trascurridos()));

    Vumeter->setLeftValue(w_StreamMath->VumetroDe());
    Vumeter->setRightValue(w_StreamMath->VumetroIz());

    if(!isSlider)
    Slider->setValue((int)w_StreamMath->Trascurridos());

    delete w_StreamMath;

    if(!Timer->isActive ())// si esta el timer off apagamos los indicadores, a
        PuestaCero();//  a velocidades de render de 10 tics  se suelen quedar activos


}
//////////////////////////////////
void StreamRender::PuestaCero()
{
    Slider->setValue(0);
    Vumeter->setLeftValue(0);
    Vumeter->setRightValue(0);

    StreamMath *w_StreamMath = new StreamMath;
    Label->setText(w_StreamMath->SegundoToFormato(0));
    delete w_StreamMath;
}

///////////////////////////////////
 bool StreamRender::isFinal(){

     StreamMath *streammath = new StreamMath(stream);

     int tmp;
     int Nivel;
 //-----------------------------------------
     if((int) streammath->Duracion()<=Descartar)// si es descartable
         tmp=0; // lo ponemos 0 para descartarlo
     else
         tmp=Solapar;//no es asignamos el final

//---------------------------------------------

     if(Solapar==0)
         tmp=0;         //si solapar=0 corte real
//---------------------------------------------

     if(Detector)// si el detector esta activado/ o no
         Nivel=DetectorNivel;
     else
         Nivel=120;//al maximo como si no hubiese detector

//-------------------------------------------------
     //if(isTanda)
       //  tmp=0;// si es tanda corte real



      /// detector************************************************************

     if(tmp!=0) //si solapar es cero no hace falta el detector corte por final real
     {
         if(streammath->Contador()<=tmp) //esta dentro del rango y el detecto activado
         {
             tmp=0;  // ponemos a cero por si falla el detector o no lo detecta

             if((int) streammath->VumetroDe()<=Nivel)  // es detectatdo por el detector
             {
                delete streammath;
                 return(true);
             }
         }
     }

      delete streammath;

     /// corte por final real***********************************************************

     if(BASS_ChannelIsActive(stream)!=BASS_ACTIVE_PLAYING)
         return(true);
     else
         return(false);

 }
 //////////////////////////////////////////////////////
void StreamRender::Play(){

      BASS_ChannelPlay(stream,false);
      Timer->start(Render);
 }


void StreamRender::Pause(){
     Timer->stop();
     BASS_ChannelPause(stream);
     Vumeter->setLeftValue(0);
     Vumeter->setRightValue(0);

 }

void StreamRender::Stop(){

     Timer->stop();
     emit stop();
 }

void  StreamRender::setPisador(){

    pisador->setStream(stream);
    pisador->setTime(Miliseconds);
    pisador->setLocucion(Locucion);


    if(PisadorEstado)
         PisadorEstado=false;
       else
        PisadorEstado=true;

   pisador->setEstado(PisadorEstado);
   pisador->start();

 }


//////////////////////////////////////////////////////////////////////////////
void StreamRender::setLabel(QLabel *w_Label){Label =  w_Label;}
void StreamRender::setVumeter(QVUMeter *w_Vumeter){Vumeter = w_Vumeter;}
void StreamRender::setSlider(QSlider *w_Slider)
{
    Slider = w_Slider;
    connect(Slider, SIGNAL(sliderMoved(int)),this, SLOT(SlideMove(int)));
    connect(Slider, SIGNAL(sliderReleased()),this, SLOT(SlideSuelta()));
    //connect(Slider, SIGNAL(valueChanged(int)),this, SLOT(slot_Barra(int)));
}


/////////////////////////////////////////////
void StreamRender::SlideMove(int pos){

    //Timer->stop();
    isSlider=true;
    //double posx = BASS_ChannelSeconds2Bytes( stream,  pos);
    segungosTrascurridos= BASS_ChannelSeconds2Bytes( stream,  pos);
    //BASS_ChannelSetPosition(stream, posx, BASS_POS_BYTE);
    return;

}
void StreamRender::SlideSuelta(){

    //Timer->start(Render);
    isSlider=false;
     BASS_ChannelSetPosition(stream, segungosTrascurridos, BASS_POS_BYTE);

}


void StreamRender::SlideForward(){

    StreamMath *w_StreamMath = new StreamMath(stream);
    double pos= w_StreamMath ->Trascurridos()+3;
    QWORD posx =BASS_ChannelSeconds2Bytes( stream,  pos);
    BASS_ChannelSetPosition(stream, posx, BASS_POS_BYTE);
    delete w_StreamMath;
}


void StreamRender::SlideBack()
{
    StreamMath *w_StreamMath = new StreamMath(stream);
    double pos = w_StreamMath ->Trascurridos()-3;
    QWORD posx = BASS_ChannelSeconds2Bytes(stream,pos);
    BASS_ChannelSetPosition(stream, posx, BASS_POS_BYTE);
    delete w_StreamMath;
}



/////////////////////////////////////////////////
void StreamRender::StreamFree(){

    QObject* obj = QObject::sender();
    StreamPlay *objeto = qobject_cast<StreamPlay *>(obj);
    delete objeto;
 }


////////////////////////////////////////////////
void StreamRender::setConfig(const QString Player)
{


    QSettings RaditIni("Radit.ini", QSettings::IniFormat);

    Device=RaditIni.value(Player + "/Dispositivo").toInt();
    Solapar=RaditIni.value(Player + "/Solapar").toInt();
    Descartar=RaditIni.value(Player + "/Descartar").toInt();
    Fundir=RaditIni.value(Player + "/Fundir").toInt();

    Qt::CheckState checkState;

    checkState =  static_cast<Qt::CheckState>(RaditIni.value(Player + "/FundirSolapar", Qt::Unchecked).toInt());
    FundirSolapar=checkState ;

    checkState =  static_cast<Qt::CheckState>(RaditIni.value(Player + "/FundirParar", Qt::Unchecked).toInt());
    FundirParar=checkState ;

    checkState =  static_cast<Qt::CheckState>(RaditIni.value(Player + "/Detector", Qt::Unchecked).toInt());
    Detector=checkState ;

    DetectorNivel=RaditIni.value(Player + "/DetectorNivel").toInt();


    Miliseconds=RaditIni.value(Player + "/Transicion").toInt();
    Locucion=RaditIni.value(Player + "/Locucion").toFloat();

    BASS_Init(Device, 44100,0, 0, NULL);



}
























