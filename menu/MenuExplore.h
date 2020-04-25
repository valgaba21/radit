#ifndef MENUEXPLORE_H
#define MENUEXPLORE_H




#include <QTableView>
#include <QMenu>
#include "explore/Explore.h"




class MenuExplore : public QMenu
{
    Q_OBJECT

private:

    void createMenu();
    QTableView *explore;

public:

         MenuExplore (QWidget * parent = 0 );
         virtual ~MenuExplore (){;}
         void setExplore(QTableView *explore);


protected:

private slots:



};












#endif // MENUEXPLORE_H
