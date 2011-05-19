#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :

    QMainWindow(parent),
    ui(new Ui::MainWindow) {
    ui->setupUi(this);
    ui->terrain->setMouseTracking(true);
    setWindowTitle("Tower Defense");

    S = new MyQGraphicsScene(ui->terrain);
    timer = new QTimer();

    QObject::connect(S,SIGNAL(ajouterTour(int,int,std::string)),this,SLOT(ajouterTour(int,int,std::string)));
    QObject::connect(S,SIGNAL(tourMouseTracking(int,int,std::string)),this,SLOT(tourMouseTracking(int,int,std::string)));
    QObject::connect(timer, SIGNAL(timeout()), S, SLOT(advance()));
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::ChargerGraphiques() {

    //--- CHARGEMENT DU TERRAIN ---

    QPixmap cheminHorizontal("data/Chemin/cheminHorizontal.jpg");
    QPixmap cheminVertical("data/Chemin/cheminVertical.jpg");
    QPixmap coinBD("data/Chemin/coinBD.jpg");
    QPixmap coinBG("data/Chemin/coinBG.jpg");
    QPixmap coinHD("data/Chemin/coinHD.jpg");
    QPixmap coinHG("data/Chemin/coinHG.jpg");
    QPixmap herbe = QPixmap("data/herbe.jpg");
    QPixmap but = QPixmap("data/but.png");
    QPixmap boue = QPixmap("data/Chemin/boue.jpg");

    S->setBackgroundBrush(herbe);

    QGraphicsPixmapItem *I;

    for(int i=0;i<16;++i){
        for(int j=0;j<16;++j){
            if(carte[i][j] != 0)
            {
                if(carte[i][j] == 1)      // vers le NORD
                {
                    //S->addRect(j*32,i*32,1*32,1*32,QPen(Qt::transparent),Qt::green)->setData(0,"NORD");
                    I = S->addPixmap(cheminVertical);
                    I->setPos(j*32,i*32);
                    I->setData(0,"NORD");
                }
                else if(carte[i][j] == 2)   // vers le SUD
                {
                    //S->addRect(j*32,i*32,1*32,1*32,QPen(Qt::transparent),Qt::green)->setData(0,"SUD");
                    I = S->addPixmap(cheminVertical);
                    I->setPos(j*32,i*32);
                    I->setData(0,"SUD");
                }
                else if(carte[i][j] == 4)   // vers l'EST
                {
                    //S->addRect(j*32,i*32,1*32,1*32,QPen(Qt::transparent),Qt::green)->setData(0,"EST");
                    I = S->addPixmap(cheminHorizontal);
                    I->setPos(j*32,i*32);
                    I->setData(0,"EST");
                }
                else if(carte[i][j] == 8)   // vers l'OUEST
                {
                    //S->addRect(j*32,i*32,1*32,1*32,QPen(Qt::transparent),Qt::green)->setData(0,"OUEST");
                    I = S->addPixmap(cheminHorizontal);
                    I->setPos(j*32,i*32);
                    I->setData(0,"OUEST");
                }
                else if(carte[i][j] == 5)   // vers le Nord EST
                {
                    //S->addRect(j*32,i*32,1*32,1*32,QPen(Qt::transparent),Qt::green)->setData(0,"NORD_EST");
                    I = S->addPixmap(coinBD);
                    I->setPos(j*32,i*32);
                    I->setData(0,"NORD_EST");
                }
                else if(carte[i][j] == 6)   // vers le Sud EST
                {
                    //S->addRect(j*32,i*32,1*32,1*32,QPen(Qt::transparent),Qt::green)->setData(0,"SUD_EST");
                    if(carte[i-1][j] != 2) I = S->addPixmap(coinHD);
                    else I = S->addPixmap(coinBG);
                    I->setPos(j*32,i*32);
                    I->setData(0,"SUD_EST");
                }
                else if(carte[i][j] == 9)   // vers le Nord OUEST
                {
                    //S->addRect(j*32,i*32,1*32,1*32,QPen(Qt::transparent),Qt::green)->setData(0,"NORD_OUEST");
                    I = S->addPixmap(coinBG);
                    I->setPos(j*32,i*32);
                    I->setData(0,"NORD_OUEST");
                }
                else if(carte[i][j] == 10)  // vers le Sud OUEST
                {
                    //S->addRect(j*32,i*32,1*32,1*32,QPen(Qt::transparent),Qt::green)->setData(0,"SUD_OUEST");
                    if(carte[i-1][j] != 2) I = S->addPixmap(coinHG);
                    else I = S->addPixmap(coinBD);
                    I->setPos(j*32,i*32);
                    I->setData(0,"SUD_OUEST");
                }

                        // TRAITER LES DIFFERENTS DEPARTS

                else if(carte[i][j] < 32 && carte[i][j] >= 17) // case de DEPART
                {
                    if(carte[i][j] == 17)      // vers le NORD
                    {
                        S->addRect(j*32,i*32,1*32,1*32,QPen(Qt::transparent),Qt::red)->setData(0,"DEPART_NORD");
                    }
                    else if(carte[i][j] == 18)   // vers le SUD
                    {
                        S->addRect(j*32,i*32,1*32,1*32,QPen(Qt::transparent),Qt::red)->setData(0,"DEPART_SUD");
                    }
                    else if(carte[i][j] == 19)   // vers l'EST
                    {
                        S->addRect(j*32,i*32,1*32,1*32,QPen(Qt::transparent),Qt::red)->setData(0,"DEPART_EST");
                    }
                    else if(carte[i][j] == 24)   // vers l'OUEST
                    {
                        S->addRect(j*32,i*32,1*32,1*32,QPen(Qt::transparent),Qt::red)->setData(0,"DEPART_OUEST");
                    }
                    else if(carte[i][j] == 21)   // vers le Nord EST
                    {
                        S->addRect(j*32,i*32,1*32,1*32,QPen(Qt::transparent),Qt::red)->setData(0,"DEPART_NORD_EST");
                    }
                    else if(carte[i][j] == 22)   // vers le Sud EST
                    {
                        S->addRect(j*32,i*32,1*32,1*32,QPen(Qt::transparent),Qt::red)->setData(0,"DEPART_SUD_EST");
                    }
                    else if(carte[i][j] == 25)   // vers le Nord OUEST
                    {
                        S->addRect(j*32,i*32,1*32,1*32,QPen(Qt::transparent),Qt::red)->setData(0,"DEPART_NORD_OUEST");
                    }
                    else if(carte[i][j] == 26)  // vers le Sud OUEST
                    {
                        S->addRect(j*32,i*32,1*32,1*32,QPen(Qt::transparent),Qt::red)->setData(0,"DEPART_SUD_OUEST");
                    }
                }
                else if(carte[i][j] == 32) // le but
                {
                    QGraphicsPixmapItem *I = S->addPixmap(but);
                    float scale1 = (float)32/but.size().width();
                    float scale2 = (float)32/but.size().height();
                    if(scale2 > scale1) scale1 = scale2;
                    I->setScale(scale1);
                    I->setPos(j*32,i*32);
                    I->setData(0,"BUT");
                }
                else if(carte[i][j] == 64) // la boue
                {
                    //S->addRect(j*32,i*32,1*32,1*32,QPen(Qt::transparent),Qt::darkGreen)->setData(0,"BOUE");
                    I = S->addPixmap(boue);
                    I->setPos(j*32,i*32);
                    I->setData(0,"BOUE");
                }
            }
            else // de l'herbe
            {
                // on ajoute un item afin de respecter le quadrillage 16x16
                S->addRect(j*32,i*32,1*32,1*32,QPen(Qt::black),Qt::transparent)->setData(0,"HERBE");
            }
        }
    }
    ui->terrain->setScene(S);
}

void MainWindow::on_loadMap_clicked()
{
    f.chargerCarte("data/map.txt");
    f.chargerVague("data/waves.txt");
    carte = f.getCarte();
    vague = f.getVague();
    ChargerGraphiques();
}

void MainWindow::on_newWave_clicked()
{
    Cafard *c = new Cafard(1,0,0,0);
    Fourmi *f = new Fourmi(1.7,0,0,0);
    S->addItem(c);
    S->addItem(f);
    timer->start(1000 / 20);
}

void MainWindow::on_waterTowers_clicked()
{
    ui->choice->setText("Vous avez choisi: ");
    S->setTourDemandee("EAU");
    ui->choice->setText(ui->choice->text()+"EAU");
}

void MainWindow::on_stoneTowers_clicked()
{
    ui->choice->setText("Vous avez choisi: ");
    S->setTourDemandee("PIERRE");
    ui->choice->setText(ui->choice->text()+"PIERRE");
}

void MainWindow::on_paintTowers_clicked()
{
    ui->choice->setText("Vous avez choisi: ");
    S->setTourDemandee("PEINTURE");
    ui->choice->setText(ui->choice->text()+"PEINTURE");
}

void MainWindow::on_petanqueTowers_clicked()
{
    ui->choice->setText("Vous avez choisi: ");
    S->setTourDemandee("PETANQUE");
    ui->choice->setText(ui->choice->text()+"PETANQUE");
}

void MainWindow::ajouterTour(int x, int y, std::string type)
{
    if(type == "EAU")
    {
        Eau *e = new Eau(1,(x/32)*32,(y/32)*32,0);
        S->addItem(e);
        S->setTourDemandee("");
        ui->choice->setText("Vous avez choisi: ");
    }
    else if(type == "PIERRE")
    {
        Pierre *p = new Pierre(1,(x/32)*32,(y/32)*32,0);
        S->addItem(p);
        S->setTourDemandee("");
        ui->choice->setText("Vous avez choisi: ");
    }
    else if(type == "PEINTURE")
    {
        Peinture *p = new Peinture(1,(x/32)*32,(y/32)*32,0);
        S->addItem(p);
        S->setTourDemandee("");
        ui->choice->setText("Vous avez choisi: ");
    }
    else
    {
        Petanque *p = new Petanque(1,(x/32)*32,(y/32)*32,0);
        S->addItem(p);
        S->setTourDemandee("");
        ui->choice->setText("Vous avez choisi: ");
    }
}

void MainWindow::tourMouseTracking(int x, int y,std::string type)
{
    if(type == "EAU")
    {
        Eau *e = new Eau(1,(x/32)*32,(y/32)*32,0);
        QGraphicsItem *I = S->addEllipse((x/32)*32-(e->getPortee()-1)*32/2,(y/32)*32-(e->getPortee()-1)*32/2,32*e->getPortee(),32*e->getPortee(),QPen(Qt::white),Qt::transparent);
        I->setData(0,"HERBE");
        S->addItem(e);

        if(S->getPrecedent() != 0 && S->getPrecedent2() != 0)
        {
            S->removeItem(S->getPrecedent());
            S->removeItem(S->getPrecedent2());
        }
        S->setPrecedent2(I);
    }
    else if(type == "PIERRE")
    {
        Pierre *p = new Pierre(1,(x/32)*32,(y/32)*32,0);
        QGraphicsItem *I = S->addEllipse((x/32)*32-(p->getPortee()-1)*32/2,(y/32)*32-(p->getPortee()-1)*32/2,32*p->getPortee(),32*p->getPortee(),QPen(Qt::white),Qt::transparent);
        I->setData(0,"HERBE");
        S->addItem(p);

        if(S->getPrecedent() != 0 && S->getPrecedent2() != 0)
        {
            S->removeItem(S->getPrecedent());
            S->removeItem(S->getPrecedent2());
        }
        S->setPrecedent2(I);
    }
    else if(type == "PEINTURE")
    {
        Peinture *p = new Peinture(1,(x/32)*32,(y/32)*32,0);
        QGraphicsItem *I = S->addEllipse((x/32)*32-(p->getPortee()-1)*32/2,(y/32)*32-(p->getPortee()-1)*32/2,32*p->getPortee(),32*p->getPortee(),QPen(Qt::white),Qt::transparent);
        I->setData(0,"HERBE");
        S->addItem(p);

        if(S->getPrecedent() != 0 && S->getPrecedent2() != 0)
        {
            S->removeItem(S->getPrecedent());
            S->removeItem(S->getPrecedent2());
        }
        S->setPrecedent2(I);
    }
    else
    {
        Petanque *p = new Petanque(1,(x/32)*32,(y/32)*32,0);
        QGraphicsItem *I = S->addEllipse((x/32)*32-(p->getPortee()-1)*32/2,(y/32)*32-(p->getPortee()-1)*32/2,32*p->getPortee(),32*p->getPortee(),QPen(Qt::white),Qt::transparent);
        I->setData(0,"HERBE");
        S->addItem(p);

        if(S->getPrecedent() != 0 && S->getPrecedent2() != 0)
        {
            S->removeItem(S->getPrecedent());
            S->removeItem(S->getPrecedent2());
        }
        S->setPrecedent2(I);
    }
}
