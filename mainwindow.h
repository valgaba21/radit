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


#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDockWidget>
#include <QToolBar>

#include "player/Player.h"
#include "micelanea/Dock/Dock.h"
#include "toolbar/ToolBar.h"
#include "tab/Tab.h"
#include "explore/Explore.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    
private:
    Ui::MainWindow *ui;

    Player *player1;
    Player *player2;
    Player *playermonitor;

    Tab * tab;

    Dock *Dock1;
    Dock *Dock2;
    Dock *DockMonitor;

    QToolBar *toolbar;
    ToolBar *frmtoolbar;

    Explore *explore;

    void setConfig();
    void bassConfig();


protected:
    void resizeEvent( QResizeEvent *event) ;



private slots:

   void ClickSetting();
   void ClickAbout();
   void ClickExplore();





};

#endif // MAINWINDOW_H
