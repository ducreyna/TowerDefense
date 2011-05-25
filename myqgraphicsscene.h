#ifndef MYQGRAPHICSSCENE_H
#define MYQGRAPHICSSCENE_H

#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsItem>
#include <QList>

#include <iostream>
#include "insecte.h"

using namespace TOWERDEFENSE;

class MyQGraphicsScene : public QGraphicsScene
{
    Q_OBJECT

private:
    std::string tourDemandee;
    QGraphicsItem *precedent;
    QGraphicsItem *precedent2;
    QGraphicsItem *tourPortee;
    QGraphicsItem *tourAmelioration;
    QList<Insecte*> insectes;

public:
    // Constructeur
    MyQGraphicsScene(QGraphicsView *parent);

    /*!
      * Methode gerant les cliques de la souris sur la scene
      * \param mouseEvent l'evenement de la souris
      */
    void mousePressEvent ( QGraphicsSceneMouseEvent * mouseEvent );

    /*!
      * Methode gerant les mouvements de la souris sur la scene
      * \param mouseEvent l'evenement de la souris
      */
    void mouseMoveEvent ( QGraphicsSceneMouseEvent * mouseEvent );

    void addInsecte(Insecte *item);
    void removeItem(QGraphicsItem *item);

    void setTourDemandee(std::string tour);

    QGraphicsItem* getPrecedent()const;
    QGraphicsItem* getPrecedent2()const;
    QGraphicsItem* getTourPortee()const;
    QGraphicsItem* getTourAmelioration()const;
    QList<Insecte*> getInsectes()const;

    void setPrecedent2(QGraphicsItem *I);
    void setTourPortee(QGraphicsItem *I);
    void setTourAmelioration(QGraphicsItem *I);

signals:
    void ajouterTour(int x, int y, std::string type);
    void tourMouseTracking(int x, int y,std::string type);
    void tourSelectionnee(int x, int y, QGraphicsItem *tour);

};

#endif // MYQGRAPHICSSCENE_H
