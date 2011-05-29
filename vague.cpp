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
        QObject::connect(insecte,SIGNAL(supprimerInsecte(Insecte*)),this,SLOT(supprimerInsecte(Insecte*)));
    }
}

QVector<Insecte *> VagueConcrete::getInsectes(bool onlyOnScene)
{
    return this->insectes;
}

QVector<Insecte *> VagueCompose::getInsectes(bool onlyOnScene)
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

void VagueConcrete::ajouterInsecte()
{
    if(counterInsecte < this->getInsectes().size())
    {
        this->scene->addItem(this->insectes.at(counterInsecte));
        counterInsecte++;
    }
}

void VagueConcrete::supprimerInsecte(Insecte *I)
{
    for(int i = 0; i < insectes.size() ; ++i)
    {
        if(insectes.at(i) == I)
        {
            this->scene->removeItem(I);
            insectes.remove(i);
            this->counterInsecte--;
            break;
        }
    }
}

}
