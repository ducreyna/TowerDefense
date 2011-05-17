#include "myqgraphicsscene.h"

#include <iostream>

MyQGraphicsScene::MyQGraphicsScene(QGraphicsView *parent):QGraphicsScene(parent),tourDemandee("")
{}

void MyQGraphicsScene::mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    int x = mouseEvent->scenePos().x();
    int y = mouseEvent->scenePos().y();

    QGraphicsItem * I = itemAt(x,y);

    if(I->data(0).toString() == "HERBE")
    {
        if(tourDemandee == "EAU")
        {
            emit ajouterTour(x,y,"EAU");
        }
        else if(tourDemandee == "PIERRE")
        {
            emit ajouterTour(x,y,"PIERRE");
        }
        else if(tourDemandee == "PEINTURE")
        {
            emit ajouterTour(x,y,"PEINTURE");
        }
        else if(tourDemandee == "PETANQUE")
        {
            emit ajouterTour(x,y,"PETANQUE");
        }
    }
    else if(I->data(0).toString() == "EAU")
    {
        removeItem(I);
    }
}

void MyQGraphicsScene::mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    /*int x = mouseEvent->scenePos().x();
    int y = mouseEvent->scenePos().y();

    std::cout << x << " " << y << std::endl;*/
}

void MyQGraphicsScene::setTourDemandee(std::string tour)
{
    tourDemandee = tour;
}
