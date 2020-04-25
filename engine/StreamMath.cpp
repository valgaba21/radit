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



#include <math.h>
#include <QDebug>
#include "StreamMath.h"

StreamMath::StreamMath(){
    playTime= new QTime();

}

StreamMath::StreamMath(HSTREAM stream)
{
     playTime= new QTime();
    this->stream=stream;
}

StreamMath::~StreamMath(){

    delete playTime;
}


void StreamMath::setStream(HSTREAM stream)
{
    this->stream=stream;
}

double StreamMath::Duracion()
{
    return(BASS_ChannelBytes2Seconds(stream, BASS_ChannelGetLength(stream, BASS_POS_BYTE)));
}


double StreamMath::Trascurridos()
{
    return(BASS_ChannelBytes2Seconds(stream, BASS_ChannelGetPosition(stream, BASS_POS_BYTE)));
}


double StreamMath::Contador()
{
    return(Duracion()-Trascurridos());
}


double StreamMath::VumetroDe()
{
    //double level;
    int level;
    level=BASS_ChannelGetLevel(stream);
    return(ToDb(LOWORD(level)));
}


double StreamMath::VumetroIz()
{
    //double level;
    int level;
    level=BASS_ChannelGetLevel(stream);
    return(ToDb(HIWORD(level)));
}


double StreamMath::ToDb(double valor)
{
    double db=20*log(valor/100); //log esta en <math.h>
    if(db>128)
        db=0;
    return(db);
}


double StreamMath::FormatoToSegundos(QString Formato)
{
    QTime time = QTime::fromString(Formato, "HH:mm:ss"); // invalid
    double Minutos, Segundos;

    Minutos=time.hour()*60;
    Minutos= Minutos + time.minute();
    Segundos=Minutos *60 + time.second();
    return(Segundos);
}


QString StreamMath::SegundoToFormato(float Segundos,QString Formato)
{
   long pos=Segundos*1000;
   long sec = pos/1000;
   long min = sec/60;
   long hour = min/60;
   long msec = pos;

   playTime->setHMS(hour%60, min%60,  sec%60, msec%1000);

    return(playTime->toString("hh:mm:ss.zzz").left(10));

}


QString StreamMath::SegundoToFormato()
{
    float Segundos= Duracion();
    long pos=Segundos*1000;
    long sec = pos/1000;
    long min = sec/60;
    long hour = min/60;
    long msec = pos;
    //QTime *playTime = new QTime((int) hour%60, (int) min%60, (int) sec%60, (int) msec%1000);
   playTime->setHMS((int) hour%60, (int) min%60, (int) sec%60, (int) msec%1000);
    return(playTime->toString("hh:mm:ss:z"));
}


QString StreamMath::SegundoToFormato(QString Formato)
{
    double Segundos=Duracion();

    long pos=Segundos*1000;
    long sec = pos/1000;
    long min = sec/60;
    long hour = min/60;
    long msec = pos;

    playTime->setHMS((int) hour%60, (int) min%60, (int) sec%60, (int) msec%1000);
    return(playTime->toString(Formato));
}

