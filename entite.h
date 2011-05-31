#ifndef ENTITE_H
#define ENTITE_H

#include <QGraphicsPixmapItem>

class Entite :public QGraphicsPixmapItem, public QObject
{
public:
    /*!
      * Constructeur par defaut
      */
    Entite();
};

#endif // ENTITE_H
