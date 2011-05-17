#include "myqgraphicsscene.h"

#include <iostream>

MyQGraphicsScene::MyQGraphicsScene(QGraphicsView *parent):QGraphicsScene(parent),tourDemandee(""),precedent(0)
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
    else if(I->data(0).toString() == "EAU" || I->data(0).toString() == "PIERRE" || I->data(0).toString() == "PEINTURE" || I->data(0).toString() == "PETANQUE")
    {
        removeItem(I);
    }
}

void MyQGraphicsScene::mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    int x = mouseEvent->scenePos().x();
    int y = mouseEvent->scenePos().y();

    QGraphicsItem * I = itemAt(x,y);

    std::cout << qPrintable(I->data(0).toString()) << std::endl;

    if(I->data(0).toString() == "HERBE")
    {
        if(tourDemandee == "EAU")
        {
            emit tourMouseTracking(x,y,"EAU");
            precedent = itemAt(x,y);
        }
        else if(tourDemandee == "PIERRE")
        {
            emit tourMouseTracking(x,y,"PIERRE");

        }
        else if(tourDemandee == "PEINTURE")
        {
            emit tourMouseTracking(x,y,"PEINTURE");
        }
        else if(tourDemandee == "PETANQUE")
        {
            emit tourMouseTracking(x,y,"PETANQUE");
        }
    }
    else if(I->data(0).toString() == "EAU" || I->data(0).toString() == "PIERRE" || I->data(0).toString() == "PEINTURE" || I->data(0).toString() == "PETANQUE")
    {
        //removeItem(I);
    }
    if(precedent != 0) removeItem(precedent);

    //std::cout << x << " " << y << std::endl;
}

void MyQGraphicsScene::setTourDemandee(std::string tour)
{
    tourDemandee = tour;
}
