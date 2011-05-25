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
    }
}

QVector<Insecte *> VagueConcrete::getInsectes(bool onlyOnScene) const
{
    QVector<Insecte *> tempInsecte;

    if(onlyOnScene)
    {
        for(int i=0; i<this->insectes.size(); i++)
        {
            if(this->scene->items().indexOf(this->insectes[i]) != -1)
                tempInsecte.append(this->insectes[i]);
        }
    }
    else
    {
        tempInsecte = this->insectes;
    }

    return tempInsecte;
}

QVector<Insecte *> VagueCompose::getInsectes(bool onlyOnScene) const
{
    QVector<Insecte *> insectes, temp;


    int i,j;

    for(i=0; i<composition.size(); i++)
    {
        temp = composition[i]->getInsectes(onlyOnScene);
        for(j=0;j<temp.size();j++)
        {
            insectes.append(temp[j]);;
        }
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

void VagueConcrete::display() const
{
    std::cout << type << std::endl;
}

void VagueCompose::display() const
{
    for(int i=0; i<this->composition.size(); i++)
    {
        composition[i]->display();
    }
}

void VagueConcrete::ajouterInsecte()
{
    std::cout << this->getInsectes().size() << std::endl;
    if(counterInsecte < this->getInsectes().size())
    {
        this->scene->addItem(this->getInsectes().at(counterInsecte));
        counterInsecte++;
    }
}

}
