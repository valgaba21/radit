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


#ifndef STREAMFILE_H
#define STREAMFILE_H



#include <QFileInfo>
#include <QString>
#include "bass.h"


class StreamFile
{
    private:
     int device;


    public:
        StreamFile();
        StreamFile(const QString url);
        void setDevice(int Device);
        void setUrl(const QString url);
        HSTREAM stream;
        virtual ~StreamFile(){;}


};


















#endif // STREAMFILE_H
