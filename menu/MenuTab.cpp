
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

#include "menu/MenuTab.h"







MenuTab::MenuTab(QWidget *parent):
                       QMenu(parent)
{

    //createMenu();


}



void MenuTab::setTab(Tab *tab){


    this->tab=tab;

      createMenu();

}




void MenuTab::createMenu(){




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





   /* openAct = new QAction(QIcon(":/images/open.png"), tr("&Open..."), this);
         openAct->setShortcuts(QKeySequence::Open);
         openAct->setStatusTip(tr("Open an existing file"));
         connect(openAct, SIGNAL(triggered()), this, SLOT(open()));

         fileMenu->addAction(openAct);*/

     /*  QAction *actionAdd;
       actionAdd = new QAction("Añadit página",this);
       connect(actionAdd, SIGNAL(triggered()), tab, SLOT(addPage()));
       this->addAction(actionAdd);

       QAction *actionDelete;
       actionDelete = new QAction("Borrar última página",this);
       connect(actionDelete, SIGNAL(triggered()), tab, SLOT(deletePage()));
       this->addAction(actionDelete);

       QAction *actionNew;
       actionNew = new QAction("Eliminar todos los ficheros",this);
       connect(actionNew, SIGNAL(triggered()), tab, SLOT(PageNew()));
       this->addAction(actionNew);*/




       QAction *action;

       action = new QAction("Añadir página",this);
       connect(action, SIGNAL(triggered()), tab, SLOT(addPage()));
       this->addAction(action);


       action = new QAction("Borrar última página",this);
       connect(action, SIGNAL(triggered()), tab, SLOT(deletePage()));
       this->addAction(action);


       action = new QAction("Eliminar página",this);
       connect(action, SIGNAL(triggered()), tab, SLOT(vaciarPage()));
       this->addAction(action);











}












