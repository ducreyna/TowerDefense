#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :QMainWindow(parent),ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->terrain->setMouseTracking(true);
    setWindowTitle("Tower Defense");

    J = new Joueur(10,400);
    S = new MyQGraphicsScene(ui->terrain,J);
    mainTimer = new QTimer();
    vagueTimer = new QTimer();

    counterVague = 0;

    ui->lcdMoney->display(J->getArgent());
    ui->lcdtLives->display(J->getVies());
    QObject::connect(J,SIGNAL(argentModifie(int)),ui->lcdMoney,SLOT(display(int)));
    QObject::connect(J,SIGNAL(viesModifiees(int)),ui->lcdtLives,SLOT(display(int)));
    QObject::connect(this,SIGNAL(achatTour(int)),J,SLOT(achatTour(int)));
    QObject::connect(this,SIGNAL(venteTour(int)),J,SLOT(venteTour(int)));

    QObject::connect(S,SIGNAL(ajouterTour(int,int,std::string)),this,SLOT(ajouterTour(int,int,std::string)));
    QObject::connect(S,SIGNAL(tourMouseTracking(int,int,std::string)),this,SLOT(tourMouseTracking(int,int,std::string)));
    QObject::connect(S,SIGNAL(tourSelectionnee(int,int,QGraphicsItem*)),this,SLOT(tourSelectionnee(int,int,QGraphicsItem*)));
    QObject::connect(J,SIGNAL(finDuJeu()),this,SLOT(finDuJeu()));
    QObject::connect(mainTimer, SIGNAL(timeout()), S, SLOT(advance()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

    /*      METHODES        */

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
    S->chargerGraphiques(carte);
    ui->terrain->setScene(S);
    this->verifierToursConstructibles();
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
    ui->pause->setEnabled(true);

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
        S->removeItem(S->getTourPortee());
        if(D->getNiveau() == 1 && D->getAmelioration_1() <= ui->lcdMoney->value())
        {
            D->ameliorer();
            QGraphicsItem *I = S->addEllipse((D->x()/32)*32-(D->getPortee()-0.5)*32,(D->y()/32)*32-(D->getPortee()-0.5)*32,64*D->getPortee(),64*D->getPortee(),QPen(Qt::NoPen),Qt::white);
            I->setOpacity(0.5f);
            S->setTourPortee(I);
            emit this->achatTour(D->getAmelioration_1());
            ui->level->setText("Level: "+QString::number(D->getNiveau()));

        }
        else if(D->getAmelioration_2() <= ui->lcdMoney->value())
        {
            bool ok = D->ameliorer();
            QGraphicsItem *I = S->addEllipse((D->x()/32)*32-(D->getPortee()-0.5)*32,(D->y()/32)*32-(D->getPortee()-0.5)*32,64*D->getPortee(),64*D->getPortee(),QPen(Qt::NoPen),Qt::white);
            I->setOpacity(0.5f);
            S->setTourPortee(I);
            ui->level->setText("Level: "+QString::number(D->getNiveau()));
            if(ok) emit this->achatTour(D->getAmelioration_2());
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
    emit this->venteTour(D->getCout()/2);
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

        if(counterVague != 0)
        {
            e->setCurrentWave(vagues.at(counterVague-1));
        }

        emit this->achatTour(8);
    }

    else if(type == "PIERRE")
    {
        Pierre *p = new Pierre(1,(x/32)*32,(y/32)*32,0);
        defenses.push_back(p);
        S->addItem(p);

        if(counterVague != 0)
        {
            p->setCurrentWave(vagues.at(counterVague-1));
        }

        emit this->achatTour(12);
    }

    else if(type == "PEINTURE")
    {
        Peinture *p = new Peinture(1,(x/32)*32,(y/32)*32,0);
        defenses.push_back(p);
        S->addItem(p);

        if(counterVague != 0)
        {
            p->setCurrentWave(vagues.at(counterVague-1));
        }

        emit this->achatTour(12);
    }

    else
    {
        Petanque *p = new Petanque(1,(x/32)*32,(y/32)*32,0);
        defenses.push_back(p);
        S->addItem(p);

        if(counterVague != 0)
        {
            p->setCurrentWave(vagues.at(counterVague-1));
        }

        emit this->achatTour(15);
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
        ui->pause->setText("REPRENDRE");
    }
    else
    {
        mainTimer->start();
        ui->pause->setText("PAUSE");
    }
}

void MainWindow::tourMouseTracking(int x, int y,std::string type)
{
    QGraphicsItem *I;
    if(type == "EAU")
    {
        Eau *e = new Eau(1,(x/32)*32,(y/32)*32,0);
        I = S->addEllipse((x/32)*32-(e->getPortee()-0.5)*32,(y/32)*32-(e->getPortee()-0.5)*32,64*e->getPortee(),64*e->getPortee(),QPen(Qt::NoPen),Qt::white);
        I->setOpacity(0.5f);
        S->addItem(e);
    }
    else if(type == "PIERRE")
    {
        Pierre *p = new Pierre(1,(x/32)*32,(y/32)*32,0);
        I = S->addEllipse((x/32)*32-(p->getPortee()-0.5)*32,(y/32)*32-(p->getPortee()-0.5)*32,64*p->getPortee(),64*p->getPortee(),QPen(Qt::NoPen),Qt::white);
        I->setOpacity(0.5f);
        S->addItem(p);
    }
    else if(type == "PEINTURE")
    {
        Peinture *p = new Peinture(1,(x/32)*32,(y/32)*32,0);
        I = S->addEllipse((x/32)*32-(p->getPortee()-0.5)*32,(y/32)*32-(p->getPortee()-0.5)*32,64*p->getPortee(),64*p->getPortee(),QPen(Qt::NoPen),Qt::white);
        I->setOpacity(0.5f);
        S->addItem(p);
    }
    else
    {
        Petanque *p = new Petanque(1,(x/32)*32,(y/32)*32,0);
        I = S->addEllipse((x/32)*32-(p->getPortee()-0.5)*32,(y/32)*32-(p->getPortee()-0.5)*32,64*p->getPortee(),64*p->getPortee(),QPen(Qt::NoPen),Qt::white);
        I->setOpacity(0.5f);
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
        QGraphicsItem *I = S->addEllipse((x/32)*32-(D->getPortee()-0.5)*32,(y/32)*32-(D->getPortee()-0.5)*32,64*D->getPortee(),64*D->getPortee(),QPen(Qt::NoPen),Qt::white);
        I->setOpacity(0.5f);
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

void MainWindow::finDuJeu()
{
    this->mainTimer->stop();
    QMessageBox(QMessageBox::Critical,"Fin du jeu","GAME OVER ! ! !").exec();
    this->close();
}
