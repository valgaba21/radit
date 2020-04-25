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

#include"menu/MenuButton.h"







MenuButton::MenuButton(QWidget *parent):
                       QMenu(parent)
{




}



void MenuButton::setButton(Button *button){


    this->button=button;

     createMenu();
}




void MenuButton::createMenu(){

   /* this->setStyleSheet(QString::fromUtf8("QMenu {\n"
                                          "\n"
                                          "background-color: qlineargradient(spread:pad, x1:0.994318, y1:1, x2:1, y2:0, stop:0.0113636 rgba(146, 169, 211, 255), stop:0.982955 rgba(174, 199, 230, 255));\n"
                                          "border-color: rgb(0, 0, 0);\n"
                                          "}\n"
                                          "QMenu::item {\n"
                                          "background-color: rgb(255, 255, 255);\n"
                                          "}\n"
                                          "QMenu::item:selected {\n"
                                          "background-color: qlineargradient(spread:pad, x1:1, y1:1, x2:1, y2:0, stop:0 rgba(129, 166, 226, 255), stop:1 rgba(93, 131, 190, 255));\n"
                                          "}"));*/


   // QAction *actionAdd;
   // actionAdd = new QAction("Preasignar reproductor",this);
   // connect(actionAdd, SIGNAL(triggered()), button, SLOT(addPage()));



    QMenu* preasignar = this->addMenu("Preasignar reproductor");

           QAction *action;



           action = new QAction("Reproductor 1",this);
           action->setObjectName("1"); //para identificar en es cast
           connect(action, SIGNAL(triggered()), button, SLOT (preasignar()));
           preasignar->addAction(action);

           action = new QAction("Reproductor 2",this);
           action->setObjectName("2");
           connect(action, SIGNAL(triggered()), button, SLOT (preasignar()));
           preasignar->addAction(action);

          action = new QAction("Reproducir por monitores",this);
          connect(action, SIGNAL(triggered()), button, SLOT(clickMonitor()));
          this->addAction(action);

 this->addSeparator();


          action = new QAction("Cortar",this);
         connect(action, SIGNAL(triggered()), button, SLOT(cortar()));
         this->addAction(action);

          action = new QAction("Copiar",this);
          connect(action, SIGNAL(triggered()), button, SLOT(copiar()));
         this->addAction(action);

          action = new QAction("Pegar",this);
         connect(action, SIGNAL(triggered()), button, SLOT(pegar()));
         this->addAction(action);

this->addSeparator();
          action = new QAction("Eliminar",this);
          connect(action, SIGNAL(triggered()), button, SLOT(vaciar()));
          this->addAction(action);


 this->addSeparator();

          action = new QAction("Siguiente",this);
          connect(action, SIGNAL(triggered()), button, SLOT(encolar()));
          this->addAction(action);


}












