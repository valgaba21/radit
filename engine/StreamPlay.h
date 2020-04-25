#ifndef STREAMPLAY_H
#define STREAMPLAY_H



#include <QWidget>

#include "bass.h"
#include "engine/StreamFile.h"
#include "engine/Fader.h"

//class StreamFile;



class StreamPlay: public QObject
{
    Q_OBJECT

    private:

    int Device;
    bool FaderSolapar;
    bool FaderStop;
    int  FaderSeconds;
    Fader *w_Fader;

    void setFader();

    public:
    explicit StreamPlay (QWidget *parent = 0);
    ~StreamPlay();

     HSTREAM stream;


    void setDevice(int device);
    void setUrl(QString url);          //load url
    void isFaderSolapar(bool fadersolapar);
    void isFaderStop(bool faderstop);
    void setFaderSec(int faderseconds);




    private slots:
    void FinalFader();

    public slots:
    void setNext();
    void setStop();


    signals:
    void Finish();
    void FinishStop();


};




#endif // STREAMPLAY_H
