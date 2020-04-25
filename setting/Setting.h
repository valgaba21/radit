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


#ifndef SETTING_H
#define SETTING_H


#include "ui_FrmSetting.h"

class Setting : public QDialog ,private Ui::FrmSetting

{
    Q_OBJECT

    private:
    void AddDispositivo();
    void Establecer();


    public:



       explicit Setting( QWidget *parent = 0);
        virtual ~Setting(){;}



    protected:

    private slots:

    void clickAceptar();

};




#endif // SETTING_H
