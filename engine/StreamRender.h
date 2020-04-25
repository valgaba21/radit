#ifndef STREAMRENDER_H
#define STREAMRENDER_H


#include <QWidget>

#include <QTimer>
#include <QString>
#include <QLabel>
#include <qvumeter.h>
#include <QSlider>


#include "bass.h"

#include "render/Render.h"





class StreamRender: public QObject

{
    Q_OBJECT

    private:

RenderThread * renderthread;

    //configurations

    int      Descartar;
    int      Fundir;
    bool     FundirSolapar;
    bool     FundirParar;
    bool     Detector;
    int      DetectorNivel;
    int      Solapar;
    bool     isTanda;

    int      Miliseconds;
    float    Locucion;

    bool Encadenar;

    int Render; //update rate timers




    QLabel   *Label;
    QVUMeter *Vumeter;
    QSlider  *Slider;

    QTimer *Timer;





    double segundos;        // duración en segundos del stream;
    double segungosTrascurridos;

    bool isFinal();//checks if is the end song
    void PuestaCero();

    bool isSlider;



    QThread* somethread;

    public:
    explicit StreamRender (QWidget *parent = 0);
    ~StreamRender();

     HSTREAM stream;

     void Play();
     void PlayNext();
     void Pause();
     void Stop();

            //load url
    void setNext(const QString url);
    void setStopNext(const QString url);

    void setLabel(QLabel *w_Label);
    void setTitulo(QLabel *w_Titulo);
    void setVumeter(QVUMeter *w_Vumeter);
    void setSlider(QSlider *w_Slider);

    void setConfig(const QString Player);

    int      Device;

    void setUrl(const QString url);

    private slots:

     void SlideMove(int pos);
     void SlideSuelta();
     void Update();
     void StreamFree();
     void StreamFreeStop();
     void render();
     void renderVu();

    public slots:
     void SlideBack();
     void SlideForward();
     void setEncadenar(bool encadenar);

    signals:

    void next();
    void stop();
    void Finish();//when playback ends

};










#endif // STREAMRENDER_H
