#include "vague.h"

namespace TOWERDEFENSE {

Vague::Vague()
{
}

VagueConcrete::VagueConcrete(int type, int nombre, int taille, int intervalle, string commentaire) :
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
        QObject::connect(insecte,SIGNAL(supprimerInsecte(Insecte*)),this,SLOT(supprimerInsecte(Insecte*)));
    }
}

QVector<Insecte *> VagueConcrete::getInsectes(bool onlyOnScene)
{
    //std::cout << "Je rentre_1" << std::endl;
    return this->insectes;
}

QVector<Insecte *> VagueCompose::getInsectes(bool onlyOnScene)
{
    for(int i = composition.size()-1; i >= 0; i--)
    {
        insectes += composition.at(i)->getInsectes();
    }

    for(int i=0; i < insectes.size(); i++)
    {
        std::cout << "Je rentre" << std::endl;
        std::cout << qPrintable(insectes.at(i)->data(0).toString()) << std::endl;
    }
    return this->insectes;
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

void VagueConcrete::display() const
{
    //std::cout << type << std::endl;
}

void VagueCompose::display() const
{
    /*for(int i=0; i<this->composition.size(); i++)
    {
        composition[i]->display();
    }*/
}

void VagueConcrete::ajouterInsecte()
{
    if(counterInsecte < this->getInsectes().size())
    {
        this->scene->addItem(this->getInsectes().at(counterInsecte));
        counterInsecte++;
    }
}

void VagueConcrete::supprimerInsecte(Insecte *I)
{
    //std::cout << "Je rentre" << std::endl;
    for(int i = 0; i < insectes.size() ; ++i)
    {

        if(insectes.at(i) == I)
        {
            insectes.remove(i);
           // QObject::disconnect(ptr);
            this->scene->removeItem(I);
            break;
        }
    }
    emit this->miseAJour();
}

}
