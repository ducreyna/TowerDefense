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
        Vague()
{
}

VagueCompose::VagueCompose(QVector<Vague *> vagues) : composition(vagues), Vague()
{
}


void VagueCompose::buildVague(int initX, int initY, QList<int>* path)
{
    for(int i=0; this->composition.size(); i++)
    {
        this->composition[i]->buildVague(initX,initY,path);
    }
}

void VagueConcrete::buildVague(int initX, int initY, QList<int>* path)
{
    Insecte * insecte;

    for(int i=0;i<this->nombre;i++)
    {
        insecte = InsecteFactory::create(this->type,this->taille,path);
        insecte->setX(initX);
        insecte->setY(initY);
        this->insectes.push_back(insecte);
    }
}

QVector<Insecte *> VagueConcrete::getInsectes() const
{
    return this->insectes;
}

QVector<Insecte *> VagueCompose::getInsectes() const
{
    QVector<Insecte *> insectes, temp;
    QList<Insecte *> pouet;

    pouet.toVector();
    int i,j;

    for(i=0; i<composition.size(); i++)
    {
        temp = composition[i]->getInsectes();
        for(j=0;j<temp.size();j++)
        {
            insectes.append(temp[j]);;
        }
    }

    return insectes;
}

}
