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

#include <QDesktopWidget>
#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "setting/Setting.h"
#include "about/About.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);



    explore = new Explore(this);

    frmtoolbar = new ToolBar(this) ;
    toolbar= new QToolBar(this);
    toolbar->setMovable(false);


    toolbar->setStyleSheet(QString::fromUtf8("background-color: qlineargradient(spread:pad, x1:0.994318, y1:1, x2:1, y2:0, stop:0.0113636 rgba(125, 135, 147, 255), stop:0.982955 rgba(201, 206, 212, 255));\n"
   "\n"
   "	\n"
   "	\n"
   "\n"
   ""));

    toolbar->addWidget(frmtoolbar);

    //botonera barra de herramientas
        connect(frmtoolbar->BtnExplore,SIGNAL(clicked()),this, SLOT(ClickExplore()));  //exit
        connect(frmtoolbar->BtnSetting,SIGNAL(clicked()),this, SLOT(ClickSetting()));  //Setting
        connect(frmtoolbar->BtnAcerca,SIGNAL(clicked()),this, SLOT(ClickAbout()));  //About
        connect(frmtoolbar->BtnSalir,SIGNAL(clicked()),this, SLOT(close()));  //exit




   Dock1= new Dock(this);
   Dock2= new Dock(this);
   DockMonitor= new Dock(this);


   player1 =new Player(this);
   player2 =new Player(this);
   playermonitor =new Player(this);

   player1->setObjectName("Player1");
   player2->setObjectName("Player2");
   playermonitor->setObjectName("Monitor");

   player1->setTipo(Player::PlayerType1);
   player2->setTipo(Player::PlayerType2);
   playermonitor->setTipo(Player::PlayerTypeMonitor);

//ocultar en monitor
   playermonitor->BtnMarcar->setVisible(false);
   playermonitor->BtnDesMarcar->setVisible(false);
   playermonitor->BtnBorrar->setVisible(false);
   playermonitor->BtnOcultar->setVisible(false);
   playermonitor->BtnEncadenar->setVisible(false);

    setConfig();// configuramos los dispositivos
    bassConfig(); // configuramos las lib bass y plug-in

   tab = new Tab();
   tab->player1=player1;
   tab->player2=player2;
   tab->monitor=playermonitor;

   explore->setPlayer(playermonitor);


   connect(player1->streamrender,SIGNAL(Finish()),tab, SLOT(Final1()));  //para los encolados
   connect(player2->streamrender,SIGNAL(Finish()),tab, SLOT(Final2()));  //para los encolados



    //tools de los player
    connect(player1->BtnMarcar,SIGNAL(clicked()),tab, SLOT(toolMarcarTodos()));  //para los encolados
    connect(player2->BtnMarcar,SIGNAL(clicked()),tab, SLOT(toolMarcarTodos()));  //para los encolados

   connect(player1->BtnDesMarcar,SIGNAL(clicked()),tab, SLOT(toolDesMarcarTodos()));  //para los encolados
   connect(player2->BtnDesMarcar,SIGNAL(clicked()),tab, SLOT(toolDesMarcarTodos()));  //para los encolados



   connect(player1->BtnBorrar,SIGNAL(clicked()),tab, SLOT(toolBorrar()));
   connect(player2->BtnBorrar,SIGNAL(clicked()),tab, SLOT(toolBorrar()));

   connect(player1->BtnOcultar,SIGNAL(clicked()),tab, SLOT(toolOcultar()));
   connect(player2->BtnOcultar,SIGNAL(clicked()),tab, SLOT(toolOcultar()));





   connect(this->explore, SIGNAL(ficheros(int,const QList<QString>)),tab,SLOT(clickExplore(int,const QList<QString>))); //reenvio




   Dock1->setWidget(player1);
   Dock2->setWidget(player2);
   DockMonitor->setWidget(playermonitor);




 this->addDockWidget(Qt::TopDockWidgetArea, Dock1,Qt::Horizontal);
 this->addDockWidget(Qt::TopDockWidgetArea, Dock2,Qt::Horizontal);
 this->addDockWidget(Qt::TopDockWidgetArea, DockMonitor,Qt::Horizontal);


 this->setCentralWidget(tab);
 this->addToolBar(toolbar);



}

MainWindow::~MainWindow()
{
   // delete player1;
   // delete explore;
    delete ui;
}



void MainWindow::ClickExplore(){

    explore->show();

}





///////////////////////////////////////////
void MainWindow::ClickSetting(){

    Setting *setting = new Setting();
    setting->exec();
    setConfig();
    delete setting;



}

void MainWindow::setConfig(){

    player1->streamrender->setConfig(player1->objectName());
    player2->streamrender->setConfig(player2->objectName());
    playermonitor->streamrender->setConfig(playermonitor->objectName());


    QSettings RaditIni("IRadit.ini", QSettings::IniFormat);


    Qt::CheckState checkState;

    checkState =  static_cast<Qt::CheckState>(RaditIni.value("General/vumetros", Qt::Unchecked).toInt());
   player1->vumeter->setVisible(checkState);
   player2->vumeter->setVisible(checkState);
   playermonitor->vumeter->setVisible(checkState);


}


void MainWindow::bassConfig(){


    //bass configuration
    BASS_SetConfig(BASS_CONFIG_BUFFER, 5000 );
    // BASS_SetConfig(BASS_CONFIG_UPDATEPERIOD, 10);
    BASS_SetConfig(BASS_CONFIG_NET_PLAYLIST,1); // enable playlist processing

    // plugin

    BASS_PluginFree(0);
    QString Path=QCoreApplication::applicationDirPath().toLatin1();

    #ifdef _WIN32
        BASS_PluginLoad(Path.toLatin1() + "/Plugin/bass_aac.dll",0);
        BASS_PluginLoad(Path.toLatin1() + "/Plugin/bassflac.dll",0);
        BASS_PluginLoad(Path.toLatin1() + "/Plugin/basswma.dll",0);
    #endif


    #ifdef Q_OS_UNIX
        BASS_PluginLoad(Path.toLatin1() + "/Plugin/libbass_aac.so",0);
        BASS_PluginLoad(Path.toLatin1() + "/Plugin/libbassflac.so",0);
    #endif


}


void MainWindow::ClickAbout(){

    About *about = new About(this);
    about->exec();



}


void MainWindow::resizeEvent( QResizeEvent *event)
{

    tab->setMaximumSize(this->size()); //limita el ancho

}




