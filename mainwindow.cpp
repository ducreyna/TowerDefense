#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :

    QMainWindow(parent),
    ui(new Ui::MainWindow) {
    ui->setupUi(this);
    ui->terrain->setMouseTracking(true);
    setWindowTitle("Tower Defense");

    S = new MyQGraphicsScene(ui->terrain);

    QObject::connect(S,SIGNAL(ajouterTour(int,int,std::string)),this,SLOT(ajouterTour(int,int,std::string)));
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::ChargerGraphiques() {

    //--- CHARGEMENT DU TERRAIN ---

    QPixmap herbe = QPixmap("data/herbe.jpg");
    QPixmap but = QPixmap("data/but.png");

    S->setBackgroundBrush(herbe);

    for(int i=0;i<16;++i){
        for(int j=0;j<16;++j){
            if(carte[i][j] != 0)
            {
                if(carte[i][j] == 1)      // vers le NORD
                {
                    S->addRect(j*32,i*32,1*32,1*32,QPen(Qt::transparent),Qt::green)->setData(0,"NORD");
                }
                else if(carte[i][j] == 2)   // vers le SUD
                {
                    S->addRect(j*32,i*32,1*32,1*32,QPen(Qt::transparent),Qt::green)->setData(0,"SUD");
                }
                else if(carte[i][j] == 4)   // vers l'EST
                {
                    S->addRect(j*32,i*32,1*32,1*32,QPen(Qt::transparent),Qt::green)->setData(0,"EST");
                }
                else if(carte[i][j] == 8)   // vers l'OUEST
                {
                    S->addRect(j*32,i*32,1*32,1*32,QPen(Qt::transparent),Qt::green)->setData(0,"OUEST");
                }
                else if(carte[i][j] == 5)   // vers le Nord EST
                {
                    S->addRect(j*32,i*32,1*32,1*32,QPen(Qt::transparent),Qt::green)->setData(0,"NORD_EST");
                }
                else if(carte[i][j] == 6)   // vers le Sud EST
                {
                    S->addRect(j*32,i*32,1*32,1*32,QPen(Qt::transparent),Qt::green)->setData(0,"SUD_EST");
                }
                else if(carte[i][j] == 9)   // vers le Nord OUEST
                {
                    S->addRect(j*32,i*32,1*32,1*32,QPen(Qt::transparent),Qt::green)->setData(0,"NORD_OUEST");
                }
                else if(carte[i][j] == 10)  // vers le Sud OUEST
                {
                    S->addRect(j*32,i*32,1*32,1*32,QPen(Qt::transparent),Qt::green)->setData(0,"SUD_OUEST");
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
                    S->addRect(j*32,i*32,1*32,1*32,QPen(Qt::transparent),Qt::darkGreen)->setData(0,"BOUE");
                }
            }
            else // de l'herbe
            {
                // on ajoute un item afin de respecter le quadrillage 16x16
                S->addRect(j*32,i*32,1*32,1*32,QPen(Qt::transparent),Qt::transparent)->setData(0,"HERBE");
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
    std::cout << S->itemAt(2*32,3*32) << std::endl;
}

void MainWindow::on_waterTowers_clicked()
{
    S->setTourDemandee("EAU");
    ui->choice->setText(ui->choice->text()+"EAU");
}

void MainWindow::on_stoneTowers_clicked()
{
    S->setTourDemandee("PIERRE");
    ui->choice->setText(ui->choice->text()+"EAU");
}

void MainWindow::on_paintTowers_clicked()
{
    S->setTourDemandee("PEINTURE");
    ui->choice->setText(ui->choice->text()+"EAU");
}

void MainWindow::on_petanqueTowers_clicked()
{
    S->setTourDemandee("PETANQUE");
    ui->choice->setText(ui->choice->text()+"EAU");
}

void MainWindow::ajouterTour(int x, int y, std::string type)
{
    if(type == "EAU")
    {
        S->addEllipse((x/32)*32,(y/32)*32,32,32,QPen(Qt::transparent),Qt::blue)->setData(0,type.c_str());
        S->setTourDemandee("");
    }
    else if(type == "PIERRE")
    {
        S->addEllipse((x/32)*32,(y/32)*32,32,32,QPen(Qt::transparent),Qt::lightGray)->setData(0,type.c_str());
        S->setTourDemandee("");
    }
    else if(type == "PEINTURE")
    {
        S->addEllipse((x/32)*32,(y/32)*32,32,32,QPen(Qt::transparent),Qt::magenta)->setData(0,type.c_str());
        S->setTourDemandee("");
    }
    else
    {
        S->addEllipse((x/32)*32,(y/32)*32,32,32,QPen(Qt::transparent),Qt::darkGray)->setData(0,type.c_str());
        S->setTourDemandee("");
    }
}
