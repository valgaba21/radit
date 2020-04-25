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
#include <QDir>
#include "engine/StreamFile.h"




StreamFile::StreamFile(){

}


StreamFile::StreamFile(const QString url){

    setUrl(url);

}


void StreamFile::setDevice(int Device){


    device=Device;

}

void StreamFile::setUrl(const QString url){



     BASS_SetDevice(device);

    QString w_url;

        w_url=QDir::toNativeSeparators(url);

        #ifdef Q_WS_X11
           w_url=QDir::toNativeSeparators(url.toUtf8());
        #endif

        stream=BASS_StreamCreateFile(FALSE, w_url.toLatin1(), 0, 0, BASS_STREAM_AUTOFREE);

}

