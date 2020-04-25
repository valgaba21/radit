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







#ifndef TOOLBAR_H
#define TOOLBAR_H
#include "ui_FrmToolBar.h"
#include <QTableWidget>
#include <QString>


class ToolBar : public QDialog, public Ui::FrmToolBar
{
    Q_OBJECT

    private:


    public:
        explicit ToolBar(QWidget *parent = 0);
        virtual ~ToolBar(){;}

    private slots:
        void UpdateHora();   //Procesa la hora

};
#endif // TOOLBAR_H
