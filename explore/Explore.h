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


#ifndef EXPLORE_H
#define EXPLORE_H

#include <QDirModel>
#include <QFileSystemModel>
#include <QModelIndex>

#include "player/Player.h"

#include "ui_FrmExplore.h"

class Explore : public QDialog ,public Ui::FrmExplore

{
    Q_OBJECT

    private:

  QFileSystemModel *filemodel;

    Player *player;

    public:


       explicit Explore ( QWidget *parent = 0);
       virtual ~Explore (){;}
       void setPlayer(Player *player);



 protected:
    void keyPressEvent (QKeyEvent *event);






    private slots:
    void clickDirectorio(const QModelIndex & index);
    void clickFile(const QModelIndex & index);
    void clickAnterior();
    void clickRed();
    void Play();

    public slots:


    signals:
    void ficheros(int player,const QList<QString> list);



};












#endif // EXPLORE_H
