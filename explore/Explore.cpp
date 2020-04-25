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

#include <QFileInfo>
#include <QDesktopServices>
#include "explore/Explore.h"

Explore::Explore(QWidget *parent): QDialog(parent){

 setupUi(this);

 //QDirModel *model = new QDirModel();

 this->tableView->setSelectionMode(QAbstractItemView::ExtendedSelection);
 this->tableView->setSortingEnabled(true);
 filemodel = new QFileSystemModel(this);


 QStringList filters;
 filters << "*.mp3" << "*.mp2" << "*.mp1" << "*.ogg" << "*.wav" << "*.aif" <<"*.wma" <<"*.flac" <<"*.seq" <<"*.rsc";
 filemodel->setNameFilters ( filters );
 filemodel->setNameFilterDisables(false);




connect(this->treeView, SIGNAL(clicked (const QModelIndex & )), this, SLOT(clickDirectorio( const QModelIndex & ))); //click en los directorios
connect(this->tableView, SIGNAL(doubleClicked (const QModelIndex & )), this, SLOT(clickFile( const QModelIndex & ))); //click en los directorios

connect(this->BtnAtras, SIGNAL(clicked()), this, SLOT(clickAnterior()));
connect(this->BtnSalir, SIGNAL(clicked()), this, SLOT(close()));


//botonera
connect(this->BtnPlay, SIGNAL(clicked()), this, SLOT(Play()));

//red
connect(this->BtnRed, SIGNAL(clicked()), this, SLOT(clickRed()));
connect(this->LinePath, SIGNAL(returnPressed()),this->BtnRed,SIGNAL(clicked()));  //pulsamos intro


connect(this->tableView, SIGNAL(ficheros(int,const QList<QString>)),this,SIGNAL(ficheros(int,const QList<QString>))); //reenvio


     //dirmodel->setFilter(QDir::Dirs | QDir::NoDotAndDotDot);
     //dirmodel->setRootPath(QDir::currentPath());
filemodel->setRootPath("");

this->treeView->setModel(filemodel);
this->tableView->setModel(filemodel);


QString dir = QDesktopServices::storageLocation(QDesktopServices::DesktopLocation);




     this->treeView->setRootIndex(filemodel->setRootPath(dir));
     this->tableView->setRootIndex(filemodel->setRootPath(dir));


     this->treeView->setColumnHidden(1, 1);  //ocultamos columnas
     this->treeView->setColumnHidden(2, 1);
     this->treeView->setColumnHidden(3, 1);

     this->tableView->setColumnHidden(1,1);
     this->tableView->setColumnHidden(2,1);

    this->tableView->filemodel=this->filemodel;

}

void Explore::clickAnterior(){

      clickFile(this->tableView->rootIndex().parent());



}




void Explore::clickDirectorio(const QModelIndex & index){

    if(!filemodel->isDir(index)) //click en un fichero esto evita dejar en blanco la lista
        return;

  this->tableView->setRootIndex(index);
  LinePath->setText(filemodel->filePath(index));



}

void Explore::clickFile(const QModelIndex & index){

if(!filemodel->isDir(index)){
    Play();
    return;
}


  this->tableView->setRootIndex(index);
  LinePath->setText(filemodel->filePath(index));
  treeView->setCurrentIndex(index);
  tableView->setCurrentIndex(index);

}


void Explore::clickRed(){

QFileInfo fileinfo = LinePath->text();


     this->tableView->setRootIndex(filemodel->setRootPath(fileinfo.absolutePath()));

     this->treeView->setRootIndex(filemodel->setRootPath(LinePath->text()));
}



void Explore::setPlayer(Player *player){

    this->player=player;

    connect(this->BtnStop, SIGNAL(clicked()), this->player, SLOT(Stop()));
    connect(this->BtnPause, SIGNAL(clicked()), this->player, SLOT(Pause()));

}


void Explore::Play(){


   // this->monitor->streamrender->setStopNext(Boton->url.toString());

    this->player->streamrender->setStopNext(filemodel->filePath(tableView->currentIndex()));

   //colorea el play
    this->player->BtnPlay->setStyleSheet(QString::fromUtf8("background-color: qlineargradient(spread:pad, x1:0.994318, y1:1, x2:1, y2:0, stop:0.0113636 rgba(69, 142, 187, 255), stop:0.982955 rgba(95, 179, 241, 255));"));




}



void Explore::keyPressEvent (QKeyEvent *event){

    if( event->key() == Qt::Key_Return ){



       }

}













