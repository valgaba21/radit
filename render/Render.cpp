



#include <QDebug>
#include "render/Render.h"

RenderThread::RenderThread(QObject *parent): QThread(parent){

    stop=false;

}



void RenderThread::run(){


    forever{
         //  qDebug() <<"ss";
        mutex.lock();
        this->thread->msleep(10);
        emit tic();
        mutex.unlock();

    }



}


