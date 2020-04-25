


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
   along with Iradit.  If not, see <http://www.gnu.org/licenses/>.
*/





#include<QDebug>

#include "engine/StreamPlay.h"
#include "engine/StreamMath.h"

/////////////////////////////////////////
StreamPlay::StreamPlay(QWidget *parent):
   QObject(parent)
{

   w_Fader = new Fader();

}

/////////////////////////////////////////

StreamPlay::~StreamPlay(){

    // BASS_StreamFree(stream); //free stream

}
/////////////////////////////////////////////
void StreamPlay::setNext(){
    if(!FaderSolapar){
        emit  Finish();
      }else{
        setFader();
    }

}

void StreamPlay::setStop(){

    if(!FaderStop){
        BASS_ChannelStop(stream);
    //  emit  Finish();
      emit FinishStop();
      }else{
        setFader();
    }

}



////////////////////////////////////////
void StreamPlay::setUrl(QString url){

    BASS_SetDevice(Device);//dispositivo
    StreamFile *streamFile = new StreamFile ;
    streamFile->setDevice(Device);
    streamFile->setUrl(url);

    stream= streamFile->stream;
    delete streamFile;
    BASS_ChannelPlay(stream,false);



}
////////////////////////////////////////////////////////////////////////////
void StreamPlay::isFaderSolapar(bool fadersolapar){FaderSolapar=fadersolapar;}
void StreamPlay::isFaderStop(bool faderstop){FaderStop=faderstop;}
void StreamPlay::setFaderSec(int faderseconds){FaderSeconds=faderseconds;}



//////////////////////////////////////
void StreamPlay::setDevice(int device){Device=device;}


///////////////////////////////////////////////////////
void StreamPlay::setFader(){


   //Fader *w_Fader = new Fader();
   w_Fader->setStream(stream);
   w_Fader->setFundir(FaderSeconds);
   w_Fader->start();


}

/////////////////////////////////////////////////////
void StreamPlay::FinalFader(){

    QObject* obj = QObject::sender();
    Fader *objeto = qobject_cast<Fader *>(obj);
    delete objeto;
    BASS_StreamFree(stream); //free stream


}







