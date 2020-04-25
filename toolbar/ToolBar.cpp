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









#include <QTimer>
#include <QDebug>
#include "ToolBar.h"
#include <QDateTime>

ToolBar::ToolBar(QWidget*parent )
    :QDialog(parent)
{
    setupUi(this);

this->setAttribute(Qt::WA_TranslucentBackground); // lo hacemos trasparente



    QTimer *TimerHora = new QTimer(this);
    connect(TimerHora, SIGNAL(timeout()), this, SLOT(UpdateHora())); // temporizaor horario
    TimerHora->start(1000);



}




void ToolBar::UpdateHora()
{
    QDateTime dateTime = QDateTime::currentDateTime();
    QString dateTimeString = dateTime.toString(Qt::SystemLocaleLongDate);
    this->LabelFecha->setText(dateTimeString);

}
