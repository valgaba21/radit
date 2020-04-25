/**
 * StreamMath
 * -----------------------------------------
 *
 * - This class supports the mathematical system of the audio file.
 *
 * @author Victor Algaba
 */



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





#ifndef STREAMMATH_H
#define STREAMMATH_H
#include <QTime>
#include <QString>
#include "bass.h"


class StreamMath
{
    private:
        //HSTREAM stream;
        double ToDb(double valor);
        QTime *playTime;

    public:
        StreamMath(HSTREAM stream);
        StreamMath();
       ~StreamMath();
        HSTREAM stream;

        void setStream(HSTREAM stream);
        double Duracion();//get duration in seconds
        double Trascurridos();//get time in progress
        double Contador();//Returns the duration in seconds elapsed minus


        QString SegundoToFormato();
        QString SegundoToFormato(QString Formato);
        QString SegundoToFormato(float Segundos,QString Formato= "hh:mm:ss:z");


        double VumetroDe();//get level of DB of channel right
        double VumetroIz();//get level of DB of channel left

        double FormatoToSegundos(QString Formato);
};
#endif // STREAMMATH_H














