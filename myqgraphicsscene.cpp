#include "myqgraphicsscene.h"

#include <iostream>

MyQGraphicsScene::MyQGraphicsScene(QGraphicsView *parent, Joueur *J):J(J),QGraphicsScene(parent),tourDemandee(""),precedent(0),precedent2(0),tourPortee(0)
{
    QObject::connect(this,SIGNAL(augmenterArgent()),J,SLOT(gagnerArgent()));
    QObject::connect(this,SIGNAL(perdreVie()),J,SLOT(perdreVie()));
}

void MyQGraphicsScene::chargerGraphiques(int **carte)
{
        //--- CHARGEMENT DU TERRAIN ---

        QPixmap cheminHorizontal("data/Chemin/cheminHorizontal.jpg");
        QPixmap cheminVertical("data/Chemin/cheminVertical.jpg");
        QPixmap coinBD("data/Chemin/coinBD.jpg");
        QPixmap coinBG("data/Chemin/coinBG.jpg");
        QPixmap coinHD("data/Chemin/coinHD.jpg");
        QPixmap coinHG("data/Chemin/coinHG.jpg");
        QPixmap herbe("data/herbe.jpg");
        QPixmap but("data/but.png");
        QPixmap boue("data/Chemin/boue.jpg");

        this->setBackgroundBrush(herbe);

        QGraphicsPixmapItem *I;

        for(int i=0;i<16;++i){
            for(int j=0;j<16;++j){
                if(carte[i][j] != 0)
                {
                    if(carte[i][j] == 1)      // vers le NORD
                    {
                        I = this->addPixmap(cheminVertical);
                        I->setData(0,"NORD");
                    }
                    else if(carte[i][j] == 2)   // vers le SUD
                    {
                        I = this->addPixmap(cheminVertical);
                        I->setData(0,"SUD");
                    }
                    else if(carte[i][j] == 4)   // vers l'EST
                    {
                        I = this->addPixmap(cheminHorizontal);
                        I->setData(0,"EST");
                    }
                    else if(carte[i][j] == 8)   // vers l'OUEST
                    {
                        I = this->addPixmap(cheminHorizontal);
                        I->setData(0,"OUEST");
                    }
                    else if(carte[i][j] == 5)   // vers le Nord EST
                    {

                        if(carte[i][j+1] != 1 && carte[i+1][j] != 17) I = this->addPixmap(coinBD);
                        else I = this->addPixmap(coinHG);
                        I->setData(0,"NORD_EST");
                    }
                    else if(carte[i][j] == 6)   // vers le Sud EST
                    {

                        if(carte[i][j-1] != 2 && carte[i-1][j] != 18) I = this->addPixmap(coinHD);
                        else I = this->addPixmap(coinBG);
                        I->setData(0,"SUD_EST");
                    }
                    else if(carte[i][j] == 9)   // vers le Nord OUEST
                    {
                        if(carte[i][j+1] != 1 && carte[i+1][j] != 17) I = this->addPixmap(coinBG);
                        else I = this->addPixmap(coinHD);

                        I->setData(0,"NORD_OUEST");
                    }
                    else if(carte[i][j] == 10)  // vers le Sud OUEST
                    {
                        if(carte[i][j-1] != 2 && carte[i-1][j] != 18) I = this->addPixmap(coinHG);
                        else I = this->addPixmap(coinBD);

                        I->setData(0,"SUD_OUEST");
                    }

                            // TRAITER LES DIFFERENTS DEPARTS

                    else if(carte[i][j] < 32 && carte[i][j] >= 17) // case de DEPART
                    {
                        if(carte[i][j] == 17)      // vers le NORD
                        {
                            I = this->addPixmap(QPixmap("data/Chemin/Depart/cheminVerticalDepartSud.jpg"));
                            I->setData(0,"DEPART_NORD");
                        }
                        else if(carte[i][j] == 18)   // vers le SUD
                        {
                            I = this->addPixmap(QPixmap("data/Chemin/Depart/cheminVerticalDepartNord.jpg"));
                            I->setData(0,"DEPART_SUD");
                        }
                        else if(carte[i][j] == 19)   // vers l'EST
                        {
                            I = this->addPixmap(QPixmap("data/Chemin/Depart/cheminHorizontalDepartOuest.jpg"));
                            I->setData(0,"DEPART_EST");
                        }
                        else if(carte[i][j] == 24)   // vers l'OUEST
                        {
                            I = this->addPixmap(QPixmap("data/Chemin/Depart/cheminHorizontalDepartEst.jpg"));
                            I->setData(0,"DEPART_OUEST");
                        }
                        else if(carte[i][j] == 21)   // vers le Nord EST
                        {
                            if(j == 0) I = this->addPixmap(QPixmap("data/Chemin/Depart/coinBGDepartNordEst.jpg"));
                            else I = this->addPixmap(QPixmap("data/Chemin/Depart/coinHGDepartNordEst.jpg"));
                            I->setData(0,"DEPART_NORD_EST");
                        }
                        else if(carte[i][j] == 22)   // vers le Sud EST
                        {
                            if(i == 0) I = this->addPixmap(QPixmap("data/Chemin/Depart/coinBGDepartSudEst.jpg"));
                            else I = this->addPixmap(QPixmap("data/Chemin/Depart/coinHDDepartSudEst.jpg"));
                            I->setData(0,"DEPART_SUD_EST");
                        }
                        else if(carte[i][j] == 25)   // vers le Nord OUEST
                        {
                            if(j == 15) I = this->addPixmap(QPixmap("data/Chemin/Depart/coinBGDepartNordOuest.jpg"));
                            else I = this->addPixmap(QPixmap("data/Chemin/Depart/coinHDDepartNordOuest.jpg"));
                            I->setData(0,"DEPART_NORD_OUEST");
                        }
                        else if(carte[i][j] == 26)  // vers le Sud OUEST
                        {
                            if(i == 0) I = this->addPixmap(QPixmap("data/Chemin/Depart/coinHDDepartSudOuest.jpg"));
                            else I = this->addPixmap(QPixmap("data/Chemin/Depart/coinHGDepartSudEst.jpg"));
                            I->setData(0,"DEPART_SUD_OUEST");
                        }
                    }
                    else if(carte[i][j] == 32) // le but
                    {
                        I = this->addPixmap(but);
                        float scale1 = (float)32/but.size().width();
                        float scale2 = (float)32/but.size().height();
                        if(scale2 > scale1) scale1 = scale2;
                        I->setScale(scale1);
                        I->setData(0,"BUT");
                    }
                    else if(carte[i][j] == 64) // la boue
                    {
                        I = this->addPixmap(boue);
                        I->setData(0,"BOUE");
                    }
                    I->setPos(i*32,j*32);
                }
                else // de l'herbe
                {
                    // on ajoute un item afin de respecter le quadrillage 16x16
                    this->addRect(i*32,j*32,1*32,1*32,QPen(Qt::NoPen),Qt::transparent)->setData(0,"HERBE");
                }
            }
        }
}

void MyQGraphicsScene::mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    int x = mouseEvent->scenePos().x();
    int y = mouseEvent->scenePos().y();

    if(tourPortee != 0)
    {
        this->removeItem(tourPortee);
        tourPortee = 0;
        emit this->tourSelectionnee(0,0,0);
    }

    QGraphicsItem * I = itemAt(x,y);

    if(mouseEvent->button() == Qt::RightButton)
    {
        /*this->removeItem(I);
        I = this->itemAt(x,y);
        this->removeItem(I);*/
        this->removeItem(getPrecedent());
        this->removeItem(getPrecedent2());
        this->tourDemandee = "";
    }

    if(tourDemandee != "")
    {
        this->removeItem(getPrecedent());
        this->removeItem(getPrecedent2());
        I = this->itemAt(x,y);

        if(tourDemandee == "EAU" && I->data(0).toString() == "HERBE")
        {
            emit this->ajouterTour(x,y,"EAU");
        }
        else if(tourDemandee == "PIERRE" && I->data(0).toString() == "HERBE")
        {
            emit this->ajouterTour(x,y,"PIERRE");
        }
        else if(tourDemandee == "PEINTURE" && I->data(0).toString() == "HERBE")
        {
            emit this->ajouterTour(x,y,"PEINTURE");
        }
        else if(tourDemandee == "PETANQUE" && I->data(0).toString() == "HERBE")
        {
            emit this->ajouterTour(x,y,"PETANQUE");
        }
        else if(tourDemandee == "MUSICIEN" && I->data(0).toString() == "HERBE")
        {
            emit this->ajouterTour(x,y,"MUSICIEN");
        }
     }
    if(I->data(0).toString() == "EAU" || I->data(0).toString() == "PIERRE" || I->data(0).toString() == "PEINTURE" || I->data(0).toString() == "PETANQUE" || I->data(0).toString() == "MUSICIEN")
    {
        emit this->tourSelectionnee(x,y,I);
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
        else if(tourDemandee == "MUSICIEN")
        {
            emit tourMouseTracking(x,y,"MUSICIEN");
            precedent = itemAt((x/32)*32+32/2,(y/32)*32+32/2);
        }
    }
}



void MyQGraphicsScene::removeInsecte(QGraphicsItem *insecte, bool vivant)
{
    QGraphicsScene::removeItem(insecte);
    if(!vivant)
    {
        emit this->augmenterArgent();
    }
    else emit this->perdreVie();
}

void MyQGraphicsScene::setTourDemandee(std::string tour)
{
    tourDemandee = tour;
}

QGraphicsItem* MyQGraphicsScene::getPrecedent()const { return precedent; }
QGraphicsItem* MyQGraphicsScene::getPrecedent2()const { return precedent2; }
QGraphicsItem* MyQGraphicsScene::getTourPortee()const { return tourPortee; }
QGraphicsItem* MyQGraphicsScene::getTourAmelioration()const { return tourAmelioration; }


void MyQGraphicsScene::setPrecedent2(QGraphicsItem *I)
{
    precedent2 = I;
}

void MyQGraphicsScene::setTourPortee(QGraphicsItem *I)
{
    this->tourPortee = I;
}

void MyQGraphicsScene::setTourAmelioration(QGraphicsItem *I)
{
    this->tourAmelioration = I;
}
