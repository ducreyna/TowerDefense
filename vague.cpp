#include "vague.h"

namespace TOWERDEFENSE {

Vague::Vague()
{
}

VagueConcrete::VagueConcrete(int type, int nombre, double taille, int intervalle, string commentaire) :
        type(type),
        nombre(nombre),
        taille(taille),
        intervalle(intervalle),
        commentaire(commentaire),
        counterInsecte(0),
        Vague()
{
    this->timer = new QTimer();

    QObject::connect(timer, SIGNAL(timeout()), this, SLOT(ajouterInsecte()));
}

VagueCompose::VagueCompose(QVector<Vague *> vagues) : composition(vagues), Vague()
{
}

void VagueCompose::buildVague(int initX, int initY, QList<int>* path, MyQGraphicsScene * scene)
{
    for(int i=0; i<this->composition.size(); i++)
    {
        this->composition[i]->buildVague(initX,initY,path, scene);
    }
}

void VagueConcrete::buildVague(int initX, int initY, QList<int>* path, MyQGraphicsScene * scene)
{
    this->scene = scene;

    Insecte * insecte;

    for(int i=0;i<this->nombre;i++)
    {
        insecte = InsecteFactory::create(this->type,this->taille,path);
        insecte->setX(initX);
        insecte->setY(initY);
        this->insectes.push_back(insecte);
        QObject::connect(insecte,SIGNAL(supprimerInsecte(Insecte*,bool)),this,SLOT(supprimerInsecte(Insecte*,bool)));
        if(dynamic_cast<Cafard*>(insecte) != 0) QObject::connect(insecte,SIGNAL(ajouterInsecteEnfant(int,double,int,int,QList<int>*,int,int)),this,SLOT(ajouterInsecteEnfant(int,double,int,int,QList<int>*,int,int)));
    }
}

QVector<Insecte *> VagueConcrete::getInsectes(bool onlyOnScene)
{
    return this->insectes;
}

QVector<Insecte *> VagueCompose::getInsectes(bool onlyOnScene)
{
    QVector<Insecte*> insectes;
    for(int i = composition.size()-1; i>= 0; --i)
    {
        insectes += composition[i]->getInsectes();
    }
    return insectes;
}

void VagueConcrete::launchVague()
{
    this->timer->start(this->intervalle*20);
}

void VagueCompose::launchVague()
{
    for(int i=0; i<this->composition.size(); i++)
    {
        composition[i]->launchVague();
    }
}

void VagueConcrete::stopVague()
{
    this->timer->stop();
}

void VagueCompose::stopVague()
{
    for(int i=0; i<this->composition.size(); i++)
    {
        composition[i]->stopVague();
    }
}

void VagueConcrete::ajouterInsecte()
{
    if(counterInsecte < this->getInsectes().size())
    {
        this->scene->addItem(this->insectes.at(counterInsecte));
        counterInsecte++;
    }
}

void VagueConcrete::ajouterInsecteEnfant(int type, double taille, int x, int y, QList<int> *path, int counter, int numEnfant)
{
    Insecte *insecte;
    insecte = InsecteFactory::create(type,taille,path);
    insecte->setX(x);
    insecte->setY(y);
    insecte->setCounter(counter);
    this->insectes.push_back(insecte);
    QObject::connect(insecte,SIGNAL(supprimerInsecte(Insecte*,bool)),this,SLOT(supprimerInsecte(Insecte*,bool)));
    this->scene->addItem(insecte);
    counterInsecte++;
    if(numEnfant == 1) for(int i = 0 ; i < 8 ; ++i) insecte->advance(1);
    emit this->miseAJour();
}

void VagueConcrete::supprimerInsecte(Insecte *I, bool vivant)
{
    for(int i = 0; i < insectes.size() ; ++i)
    {
        if(insectes.at(i) == I)
        {
            this->scene->removeInsecte(I,vivant);
            insectes.remove(i);
            this->counterInsecte--;
            break;
        }
    }
}

}
