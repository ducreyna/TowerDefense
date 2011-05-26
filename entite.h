#ifndef ENTITE_H
#define ENTITE_H

#include <QGraphicsPixmapItem>

class Entite :public QGraphicsPixmapItem, public QObject
{
public:
    Entite();
};

#endif // ENTITE_H
