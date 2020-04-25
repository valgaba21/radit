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



//promoted

#include <QDebug>
#include "explore/TableView/TableView.h"   //promoted
#include "menu/MenuExplore.h"



TableView::TableView(QWidget *parent): QTableView(parent){



}




void TableView::resizeEvent( QResizeEvent *event){

    int ancho = this->width();
    this->setColumnWidth(2,100);
    this->setColumnWidth(0,ancho- 120);



}


void TableView::contextMenuEvent(QContextMenuEvent *event)
 {
    MenuExplore *menu = new MenuExplore();
    menu->setExplore(this);
    menu->exec(event->globalPos());
   delete menu;

}



void TableView::clickAsignar(){

    QObject* obj = QObject::sender();
    QAction *opcion = qobject_cast<QAction *>(obj);

    int player;

    QList<QString> list;

    if(opcion->objectName()=="1")
        player=0;
       else
        player=1;



    QModelIndexList indexList = this->selectedIndexes();



      for (int i = 0; i < indexList.size(); ++i){

          if(indexList.at(i).column()==0){ //evita repeticiones de los ficheros
                // qDebug() <<filemodel->filePath(indexList.at(i));

              list <<filemodel->filePath(indexList.at(i));

             }

           }


       emit ficheros(player,list);


  }






