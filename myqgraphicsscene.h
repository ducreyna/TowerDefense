#ifndef MYQGRAPHICSSCENE_H
#define MYQGRAPHICSSCENE_H

#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsItem>

#include <iostream>

class MyQGraphicsScene : public QGraphicsScene
{
    Q_OBJECT

private:
    std::string tourDemandee;
    QGraphicsItem *precedent;

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

    void setTourDemandee(std::string tour);

signals:
    void ajouterTour(int x, int y, std::string type);
    void tourMouseTracking(int x, int y,std::string type);
};

#endif // MYQGRAPHICSSCENE_H
