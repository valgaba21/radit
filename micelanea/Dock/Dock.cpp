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






#include<QCloseEvent>
#include"Dock.h"



Dock::Dock(QWidget *parent) :
           QDockWidget(parent)
{

    setFeatures(QDockWidget::NoDockWidgetFeatures);
    setAllowedAreas(Qt::LeftDockWidgetArea |Qt::RightDockWidgetArea);

    QWidget* titleWidget = new QWidget(this); /* Quitamos la barra de titulos del dockwidget */
    this->setTitleBarWidget( titleWidget );


    setStyleSheet(QString::fromUtf8("/* background-color: rgb(33, 48, 58);*/\n"
    "\n"
    " QDockWidget {\n"
    "	color: rgb(255, 255, 255);\n"
    "     \n"
    " }\n"
    "\n"
    " QDockWidget::title {\n"
    "   \n"
    "    \n"
    "	background-color: rgb(33, 135, 207);\n"
    "	\n"
    "	\n"
    "   \n"
    " }\n"
    "\n"
    ""));

}

void Dock::closeEvent(QCloseEvent *e)
{
    e->ignore();
    //e->accept();
}
