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



#ifndef PLAYER_H
#define PLAYER_H


#include "ui_FrmPlayer.h"
#include "engine/StreamRender.h"
#include "button/Button.h"

class Player : public QDialog ,public Ui::FrmPlayer

{
    Q_OBJECT

    private:
    const QString nombre;
    void setColor(Button *button );
    void borrarColor();

    Button *button;
    public:

    enum PLAYER_TIPO { PlayerType1 =0, PlayerType2 =1, PlayerTypeMonitor =2};

       explicit Player( QWidget *parent = 0);
       virtual ~Player(){;}
       void setTipo(PLAYER_TIPO tipo);
       StreamRender *streamrender;

       void setNombre(const QString nombre); //configuraciones
       void setButton(Button *button);

protected:
    void resizeEvent( QResizeEvent *event) ;

    private slots:

    void Play();
    void Pause();
    void Stop();

    void Final();


};






#endif // PLAYER_H
