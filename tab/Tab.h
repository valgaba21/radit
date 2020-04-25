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







#ifndef TAB_H
#define TAB_H

#include "ui_FrmTab.h"

#include "button/Button.h"
#include"iostream/Iostream.h"
#include "player/Player.h"

class Tab : public QDialog ,private Ui::FrmTab

{
    Q_OBJECT

    private:

    struct Boton {
       int ficha;
       QString nombre;
       QString url;
    } boton;

    QList<Button *> allButton;

    void save();
    void load();

    Iostream *iostream;


    public:

      explicit Tab( QWidget *parent = 0);
        ~Tab();

    Player *player1;
    Player *player2;
    Player *monitor;



    protected:

         void contextMenuEvent(QContextMenuEvent *event);
         void resizeEvent( QResizeEvent *event) ;
      //  void dropEvent(QDropEvent *event);
        // void dragEnterEvent(QDragEnterEvent *event);
    // void dragMoveEvent(QDragMoveEvent *event);
       //  void mousePressEvent(QMouseEvent *event);





    private slots:

     void ClickButton();
     void addPage(); //añade una página con botones
     void deletePage();
     void vaciarPage();
     void playMonitor();

    public slots:

     void Final1();
     void Final2();

     void toolMarcarTodos();
     void toolDesMarcarTodos();
     void toolBorrar();
     void toolOcultar();



    void clickExplore(int player,const QList<QString> list);





};




#endif // TAB_H
