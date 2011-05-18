#include "myqgraphicsscene.h"

#include <iostream>

MyQGraphicsScene::MyQGraphicsScene(QGraphicsView *parent):QGraphicsScene(parent),tourDemandee(""),precedent(0),precedent2(0)
{}

void MyQGraphicsScene::mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    int x = mouseEvent->scenePos().x();
    int y = mouseEvent->scenePos().y();

    QGraphicsItem * I = itemAt(x,y);

    if(tourDemandee == "EAU")
    {
        removeItem(getPrecedent());
        removeItem(getPrecedent2());
        I = itemAt(x,y);
        if(I->data(0).toString() == "HERBE") emit ajouterTour(x,y,"EAU");
    }
    else if(tourDemandee == "PIERRE")
    {
        removeItem(getPrecedent());
        removeItem(getPrecedent2());
        I = itemAt(x,y);
        if(I->data(0).toString() == "HERBE") emit ajouterTour(x,y,"PIERRE");
    }
    else if(tourDemandee == "PEINTURE")
    {
        removeItem(getPrecedent());
        removeItem(getPrecedent2());
        I = itemAt(x,y);
        if(I->data(0).toString() == "HERBE") emit ajouterTour(x,y,"PEINTURE");
    }
    else if(tourDemandee == "PETANQUE")
    {
        removeItem(getPrecedent());
        removeItem(getPrecedent2());
        I = itemAt(x,y);
        if(I->data(0).toString() == "HERBE") emit ajouterTour(x,y,"PETANQUE");
    }

     if(I->data(0).toString() == "EAU" || I->data(0).toString() == "PIERRE" || I->data(0).toString() == "PEINTURE" || I->data(0).toString() == "PETANQUE")
    {
        removeItem(I);
    }
     precedent = 0;
     precedent2 = 0;
}

void MyQGraphicsScene::mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    int x = mouseEvent->scenePos().x();
    int y = mouseEvent->scenePos().y();

    QGraphicsItem * I = itemAt(x,y);

    if(I->data(0).toString() == "HERBE")
    {
        if(tourDemandee == "EAU")
        {
            emit tourMouseTracking(x,y,"EAU");
            precedent = itemAt((x/32)*32+32/2,(y/32)*32+32/2);
        }
        else if(tourDemandee == "PIERRE")
        {
            emit tourMouseTracking(x,y,"PIERRE");
            precedent = itemAt((x/32)*32+32/2,(y/32)*32+32/2);
        }
        else if(tourDemandee == "PEINTURE")
        {
            emit tourMouseTracking(x,y,"PEINTURE");
            precedent = itemAt((x/32)*32+32/2,(y/32)*32+32/2);
        }
        else if(tourDemandee == "PETANQUE")
        {
            emit tourMouseTracking(x,y,"PETANQUE");
            precedent = itemAt((x/32)*32+32/2,(y/32)*32+32/2);
        }
    }
}

void MyQGraphicsScene::removeItem(QGraphicsItem *item)
{
    QGraphicsScene::removeItem(item);
    delete item;
}

void MyQGraphicsScene::setTourDemandee(std::string tour)
{
    tourDemandee = tour;
}

QGraphicsItem* MyQGraphicsScene::getPrecedent()const { return precedent;}
QGraphicsItem* MyQGraphicsScene::getPrecedent2()const { return precedent2;}

void MyQGraphicsScene::setPrecedent2(QGraphicsItem *I)
{
    precedent2 = I;
}
