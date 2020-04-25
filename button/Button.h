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


#ifndef BUTTON_H
#define BUTTON_H


#include <QPushButton>
#include <QUrl>
#include <QFileInfo>

//#include <QDragEnterEvent>
//#include <QDropEvent>




class Button : public QPushButton
{
    Q_OBJECT

private:





public:
     enum PLAYER_TIPO { PlayerType1 =0, PlayerType2 =1};
         Button(QWidget * parent = 0 );
         virtual ~Button(){;}
         void setPlayer(PLAYER_TIPO tipo);
         void setNumero( QString num);

         void setInfo(QFileInfo file);  //informacón del botón

         QString numero; //numero del boton; para cuando se borre saber cual es

         int tab;
         int botonId;
         int playerTipo;
         QUrl url;

         bool isPlay;   // si esta en reproduccion "rojo" no drag ni vaciar
         bool isEncolar; // saber el siguiente






protected:
   // void resizeEvent( QResizeEvent *event) ;
   void contextMenuEvent(QContextMenuEvent *event);

   void dropEvent(QDropEvent *event);
   void dragEnterEvent(QDragEnterEvent *event);
 // void dragMoveEvent(QDragMoveEvent *event);
   void mousePressEvent(QMouseEvent *event);
 //  void mouseReleaseEvent (QMouseEvent *event );
  // void keyPressEvent (QKeyEvent *event);



private slots:
  void preasignar();


  void copiar();
  void cortar();
  void pegar();

public slots:
  void clickMonitor();
  void encolar();
  void vaciar();

signals:

  void playmonitor();



};




#endif // BUTTON_H
