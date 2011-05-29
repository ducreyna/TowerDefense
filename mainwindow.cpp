#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :

    QMainWindow(parent),
    ui(new Ui::MainWindow) {
    ui->setupUi(this);
    ui->terrain->setMouseTracking(true);
    setWindowTitle("Tower Defense");

    ui->newWave->setEnabled(false);
    ui->pause->setEnabled(false);
    ui->waterTowers->setEnabled(false);
    ui->stoneTowers->setEnabled(false);
    ui->paintTowers->setEnabled(false);
    ui->petanqueTowers->setEnabled(false);
    ui->upButton->setEnabled(false);
    ui->sellButton->setEnabled(false);
    ui->lcdMoney->display(400);
    ui->lcdtLives->display(50);

    S = new MyQGraphicsScene(ui->terrain);
    mainTimer = new QTimer();
    vagueTimer = new QTimer();

    counterVague = 0;

    QObject::connect(S,SIGNAL(ajouterTour(int,int,std::string)),this,SLOT(ajouterTour(int,int,std::string)));
    QObject::connect(S,SIGNAL(tourMouseTracking(int,int,std::string)),this,SLOT(tourMouseTracking(int,int,std::string)));
    QObject::connect(S,SIGNAL(tourSelectionnee(int,int,QGraphicsItem*)),this,SLOT(tourSelectionnee(int,int,QGraphicsItem*)));
    QObject::connect(mainTimer, SIGNAL(timeout()), S, SLOT(advance()));
}

MainWindow::~MainWindow() {
    delete ui;
}

    /*      METHODES        */

void MainWindow::chargerGraphiques() {

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

    S->setBackgroundBrush(herbe);

    QGraphicsPixmapItem *I;

    for(int i=0;i<16;++i){
        for(int j=0;j<16;++j){
            if(carte[i][j] != 0)
            {
                if(carte[i][j] == 1)      // vers le NORD
                {
                    I = S->addPixmap(cheminVertical);
                    I->setData(0,"NORD");
                }
                else if(carte[i][j] == 2)   // vers le SUD
                {
                    I = S->addPixmap(cheminVertical);
                    I->setData(0,"SUD");
                }
                else if(carte[i][j] == 4)   // vers l'EST
                {
                    I = S->addPixmap(cheminHorizontal);
                    I->setData(0,"EST");
                }
                else if(carte[i][j] == 8)   // vers l'OUEST
                {
                    I = S->addPixmap(cheminHorizontal);
                    I->setData(0,"OUEST");
                }
                else if(carte[i][j] == 5)   // vers le Nord EST
                {

                    if(carte[i][j+1] != 1 && carte[i+1][j] != 17) I = S->addPixmap(coinBD);
                    else I = S->addPixmap(coinHG);
                    I->setData(0,"NORD_EST");
                }
                else if(carte[i][j] == 6)   // vers le Sud EST
                {

                    if(carte[i][j-1] != 2 && carte[i-1][j] != 18) I = S->addPixmap(coinHD);
                    else I = S->addPixmap(coinBG);
                    I->setData(0,"SUD_EST");
                }
                else if(carte[i][j] == 9)   // vers le Nord OUEST
                {
                    if(carte[i][j+1] != 1 && carte[i+1][j] != 17) I = S->addPixmap(coinBG);
                    else I = S->addPixmap(coinHD);

                    I->setData(0,"NORD_OUEST");
                }
                else if(carte[i][j] == 10)  // vers le Sud OUEST
                {
                    if(carte[i][j-1] != 2 && carte[i-1][j] != 18) I = S->addPixmap(coinHG);
                    else I = S->addPixmap(coinBD);

                    I->setData(0,"SUD_OUEST");
                }

                        // TRAITER LES DIFFERENTS DEPARTS

                else if(carte[i][j] < 32 && carte[i][j] >= 17) // case de DEPART
                {
                    if(carte[i][j] == 17)      // vers le NORD
                    {
                        I = S->addPixmap(QPixmap("data/Chemin/Depart/cheminVerticalDepartSud.jpg"));
                        I->setData(0,"DEPART_NORD");
                    }
                    else if(carte[i][j] == 18)   // vers le SUD
                    {
                        I = S->addPixmap(QPixmap("data/Chemin/Depart/cheminVerticalDepartNord.jpg"));
                        I->setData(0,"DEPART_SUD");
                    }
                    else if(carte[i][j] == 19)   // vers l'EST
                    {
                        I = S->addPixmap(QPixmap("data/Chemin/Depart/cheminHorizontalDepartOuest.jpg"));
                        I->setData(0,"DEPART_EST");
                    }
                    else if(carte[i][j] == 24)   // vers l'OUEST
                    {
                        I = S->addPixmap(QPixmap("data/Chemin/Depart/cheminHorizontalDepartEst.jpg"));
                        I->setData(0,"DEPART_OUEST");
                    }
                    else if(carte[i][j] == 21)   // vers le Nord EST
                    {
                        if(j == 0) I = S->addPixmap(QPixmap("data/Chemin/Depart/coinBGDepartNordEst.jpg"));
                        else I = S->addPixmap(QPixmap("data/Chemin/Depart/coinHGDepartNordEst.jpg"));
                        I->setData(0,"DEPART_NORD_EST");
                    }
                    else if(carte[i][j] == 22)   // vers le Sud EST
                    {
                        if(i == 0) I = S->addPixmap(QPixmap("data/Chemin/Depart/coinBGDepartSudEst.jpg"));
                        else I = S->addPixmap(QPixmap("data/Chemin/Depart/coinHDDepartSudEst.jpg"));
                        I->setData(0,"DEPART_SUD_EST");
                    }
                    else if(carte[i][j] == 25)   // vers le Nord OUEST
                    {
                        if(j == 15) I = S->addPixmap(QPixmap("data/Chemin/Depart/coinBGDepartNordOuest.jpg"));
                        else I = S->addPixmap(QPixmap("data/Chemin/Depart/coinHDDepartNordOuest.jpg"));
                        I->setData(0,"DEPART_NORD_OUEST");
                    }
                    else if(carte[i][j] == 26)  // vers le Sud OUEST
                    {
                        if(i == 0) I = S->addPixmap(QPixmap("data/Chemin/Depart/coinHDDepartSudOuest.jpg"));
                        else I = S->addPixmap(QPixmap("data/Chemin/Depart/coinHGDepartSudEst.jpg"));
                        I->setData(0,"DEPART_SUD_OUEST");
                    }
                }
                else if(carte[i][j] == 32) // le but
                {
                    I = S->addPixmap(but);
                    float scale1 = (float)32/but.size().width();
                    float scale2 = (float)32/but.size().height();
                    if(scale2 > scale1) scale1 = scale2;
                    I->setScale(scale1);
                    I->setData(0,"BUT");
                }
                else if(carte[i][j] == 64) // la boue
                {
                    I = S->addPixmap(boue);
                    I->setData(0,"BOUE");
                }
                I->setPos(i*32,j*32);
            }
            else // de l'herbe
            {
                // on ajoute un item afin de respecter le quadrillage 16x16
                S->addRect(i*32,j*32,1*32,1*32,QPen(Qt::black),Qt::transparent)->setData(0,"HERBE");
            }
        }
    }
    ui->terrain->setScene(S);
    //ui->terrain->setRenderHint(QPainter::Antialiasing);
    //ui->terrain->setCacheMode(QGraphicsView::CacheBackground);
    //ui->terrain->setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);
    verifierToursConstructibles();
}

void MainWindow::verifierToursConstructibles()
{
    if(ui->lcdMoney->value() >= 15)
    {
        ui->waterTowers->setEnabled(true);
        ui->stoneTowers->setEnabled(true);
        ui->paintTowers->setEnabled(true);
        ui->petanqueTowers->setEnabled(true);
    }
    else if(ui->lcdMoney->value() >= 12)
    {
        ui->waterTowers->setEnabled(true);
        ui->stoneTowers->setEnabled(true);
        ui->paintTowers->setEnabled(true);
        ui->petanqueTowers->setEnabled(false);
    }
    else if(ui->lcdMoney->value() >= 8)
    {
        ui->waterTowers->setEnabled(true);
        ui->stoneTowers->setEnabled(false);
        ui->paintTowers->setEnabled(false);
        ui->petanqueTowers->setEnabled(false);
    }
    else
    {
        ui->waterTowers->setEnabled(false);
        ui->stoneTowers->setEnabled(false);
        ui->paintTowers->setEnabled(false);
        ui->petanqueTowers->setEnabled(false);
    }
}

    /*      BOUTONS     */

void MainWindow::on_loadMap_clicked()
{
    f.chargerCarte("data/map.txt");
    f.chargerVague("data/waves.txt");
    f.chargerPath();

    carte = f.getCarte();
    vagues = f.getVagues();
    ui->loadMap->setEnabled(false);
    ui->newWave->setEnabled(true);

    path = f.getPath();
    chargerGraphiques();
}

void MainWindow::on_newWave_clicked()
{
    int i,j,departX,departY;
    bool found = false;

    for(i=0; i<16 && !found; i++)
    {
        for(j=0; j < 16 && !found; j++)
        {
            if(carte[j][i] < 32 && carte[j][i] >= 17)
            {
                found = true;
            }
        }
    }

    departX = max(0,j-1);
    departY = max(0,i-1);

    mainTimer->start(20);

    if(counterVague+1 == vagues.size())
    {
        // le jeu est fini : WIN \o/
        ui->newWave->setEnabled(false);
    }
    else
    {
        vagues.at(counterVague)->buildVague(departX*32,departY*32,this->path,this->S);
        for(int j=0;j<defenses.size();j++)
        {
            defenses.at(j)->setCurrentWave(vagues.at(counterVague));
        }
        vagues.at(counterVague)->launchVague();       
        counterVague++;
    }
}

void MainWindow::on_waterTowers_clicked()
{
    ui->choice->setText("Vous avez choisi: ");
    S->setTourDemandee("EAU");
    ui->choice->setText(ui->choice->text()+"EAU");
    if(S->getTourPortee() != 0)
    {
        S->removeItem(S->getTourPortee());
        S->setTourPortee(0);
        ui->upButton->setEnabled(false);
        ui->sellButton->setEnabled(false);
    }
    ui->type->setText("Type: ");
    ui->level->setText("Level: ");
}

void MainWindow::on_stoneTowers_clicked()
{
    ui->choice->setText("Vous avez choisi: ");
    S->setTourDemandee("PIERRE");
    ui->choice->setText(ui->choice->text()+"PIERRE");
    if(S->getTourPortee() != 0)
    {
        S->removeItem(S->getTourPortee());
        S->setTourPortee(0);
        ui->upButton->setEnabled(false);
        ui->sellButton->setEnabled(false);
    }
    ui->type->setText("Type: ");
    ui->level->setText("Level: ");
}

void MainWindow::on_paintTowers_clicked()
{
    ui->choice->setText("Vous avez choisi: ");
    S->setTourDemandee("PEINTURE");
    ui->choice->setText(ui->choice->text()+"PEINTURE");
    if(S->getTourPortee() != 0)
    {
        S->removeItem(S->getTourPortee());
        S->setTourPortee(0);
        ui->upButton->setEnabled(false);
        ui->sellButton->setEnabled(false);
    }
    ui->type->setText("Type: ");
    ui->level->setText("Level: ");
}

void MainWindow::on_petanqueTowers_clicked()
{
    ui->choice->setText("Vous avez choisi: ");
    S->setTourDemandee("PETANQUE");
    ui->choice->setText(ui->choice->text()+"PETANQUE");
    if(S->getTourPortee() != 0)
    {
        S->removeItem(S->getTourPortee());
        S->setTourPortee(0);
        ui->upButton->setEnabled(false);
        ui->sellButton->setEnabled(false);
    }
    ui->type->setText("Type: ");
    ui->level->setText("Level: ");
}

void MainWindow::on_upButton_clicked()
{
    try
    {
        Defense *D = dynamic_cast<Defense*>(S->getTourAmelioration());
        if(D->getNiveau() == 1 && D->getAmelioration_1() <= ui->lcdMoney->value())
        {
            S->removeItem(S->getTourPortee());
            D->ameliorer();
            QGraphicsItem *I = S->addEllipse((D->x()/32)*32-(D->getPortee()-0.5)*32,(D->y()/32)*32-(D->getPortee()-0.5)*32,64*D->getPortee(),64*D->getPortee(),QPen(Qt::white),Qt::transparent);
            S->setTourPortee(I);
            ui->lcdMoney->display(ui->lcdMoney->value() - D->getAmelioration_1());
            ui->level->setText("Level: "+QString::number(D->getNiveau()));

        }
        else if(D->getAmelioration_2() <= ui->lcdMoney->value())
        {
            S->removeItem(S->getTourPortee());
            bool ok = D->ameliorer();
            QGraphicsItem *I = S->addEllipse((D->x()/32)*32-(D->getPortee()-0.5)*32,(D->y()/32)*32-(D->getPortee()-0.5)*32,64*D->getPortee(),64*D->getPortee(),QPen(Qt::white),Qt::transparent);
            S->setTourPortee(I);
            ui->level->setText("Level: "+QString::number(D->getNiveau()));
            if(ok) ui->lcdMoney->display(ui->lcdMoney->value() - D->getAmelioration_2());
        }
        else throw std::exception();
    }
    catch(std::exception e)
    {
        QMessageBox(QMessageBox::Warning,"Amelioration impossible","Credits insuffisants ! ! !").exec();
    }
    this->verifierToursConstructibles();
}

void MainWindow::on_sellButton_clicked()
{
    Defense *D = dynamic_cast<Defense*>(S->getTourAmelioration());
    ui->lcdMoney->display(ui->lcdMoney->value() + (D->getCout()/2));
    S->removeItem(D);
    S->removeItem(S->getTourPortee());
    S->setTourPortee(0);
    S->setTourAmelioration(0);
    ui->upButton->setEnabled(false);
    ui->sellButton->setEnabled(false);
    this->verifierToursConstructibles();
    ui->type->setText("Type: ");
    ui->level->setText("Level: ");
}

    /*      SLOTS       */

void MainWindow::ajouterTour(int x, int y, std::string type)
{
    if(type == "EAU")
    {
        Eau *e = new Eau(1,(x/32)*32,(y/32)*32,0);
        defenses.push_back(e);
        S->addItem(e);
        ui->lcdMoney->display(ui->lcdMoney->value() - 8);

        if(counterVague != 0)
        {
            e->setCurrentWave(vagues.at(counterVague-1));
        }
    }

    else if(type == "PIERRE")
    {
        Pierre *p = new Pierre(1,(x/32)*32,(y/32)*32,0);
        defenses.push_back(p);
        S->addItem(p);
        ui->lcdMoney->display(ui->lcdMoney->value() - 12);

        if(counterVague != 0)
        {
            p->setCurrentWave(vagues.at(counterVague-1));
        }
    }

    else if(type == "PEINTURE")
    {
        Peinture *p = new Peinture(1,(x/32)*32,(y/32)*32,0);
        defenses.push_back(p);
        S->addItem(p);
        ui->lcdMoney->display(ui->lcdMoney->value() - 12);

        if(counterVague != 0)
        {
            p->setCurrentWave(vagues.at(counterVague-1));
        }
    }

    else
    {
        Petanque *p = new Petanque(1,(x/32)*32,(y/32)*32,0);
        defenses.push_back(p);
        S->addItem(p);
        ui->lcdMoney->display(ui->lcdMoney->value() - 15);

        if(counterVague != 0)
        {
            p->setCurrentWave(vagues.at(counterVague-1));
        }
    }

    S->setTourDemandee("");
    ui->choice->setText("Vous avez choisi: ");
    verifierToursConstructibles();
}

void MainWindow::on_pause_clicked()
{
    if(mainTimer->isActive())
    {
        mainTimer->stop();
        ui->pause->setText("Reprendre");
    }
    else
    {
        mainTimer->start();
        ui->pause->setText("Pause");
    }
}

void MainWindow::tourMouseTracking(int x, int y,std::string type)
{
    QGraphicsItem *I;
    if(type == "EAU")
    {
        Eau *e = new Eau(1,(x/32)*32,(y/32)*32,0);
        I = S->addEllipse((x/32)*32-(e->getPortee()-0.5)*32,(y/32)*32-(e->getPortee()-0.5)*32,64*e->getPortee(),64*e->getPortee(),QPen(Qt::white),Qt::transparent);
        S->addItem(e);
    }
    else if(type == "PIERRE")
    {
        Pierre *p = new Pierre(1,(x/32)*32,(y/32)*32,0);
        I = S->addEllipse((x/32)*32-(p->getPortee()-0.5)*32,(y/32)*32-(p->getPortee()-0.5)*32,64*p->getPortee(),64*p->getPortee(),QPen(Qt::white),Qt::transparent);
        S->addItem(p);
    }
    else if(type == "PEINTURE")
    {
        Peinture *p = new Peinture(1,(x/32)*32,(y/32)*32,0);
        I = S->addEllipse((x/32)*32-(p->getPortee()-0.5)*32,(y/32)*32-(p->getPortee()-0.5)*32,64*p->getPortee(),64*p->getPortee(),QPen(Qt::white),Qt::transparent);
        S->addItem(p);
    }
    else
    {
        Petanque *p = new Petanque(1,(x/32)*32,(y/32)*32,0);
        I = S->addEllipse((x/32)*32-(p->getPortee()-0.5)*32,(y/32)*32-(p->getPortee()-0.5)*32,64*p->getPortee(),64*p->getPortee(),QPen(Qt::white),Qt::transparent);
        S->addItem(p);
    }

    I->setData(0,"HERBE");
    if(S->getPrecedent() != 0 && S->getPrecedent2() != 0)
    {
        S->removeItem(S->getPrecedent());
        S->removeItem(S->getPrecedent2());
    }
    S->setPrecedent2(I);
}

void MainWindow::tourSelectionnee(int x, int y, QGraphicsItem *tour)
{
    if(tour != 0)
    {
        Defense *D = dynamic_cast<Defense*>(tour);
        S->setTourAmelioration(D);
        QGraphicsItem *I = S->addEllipse((x/32)*32-(D->getPortee()-0.5)*32,(y/32)*32-(D->getPortee()-0.5)*32,64*D->getPortee(),64*D->getPortee(),QPen(Qt::white),Qt::transparent);
        S->setTourPortee(I);
        ui->upButton->setEnabled(true);
        ui->sellButton->setEnabled(true);
        ui->type->setText(ui->type->text()+D->data(0).toString());
        ui->level->setText(ui->level->text()+QString::number(D->getNiveau()));
    }
    else
    {
        ui->upButton->setEnabled(false);
        ui->sellButton->setEnabled(false);
        ui->type->setText("Type: ");
        ui->level->setText("Level: ");
    }
}
