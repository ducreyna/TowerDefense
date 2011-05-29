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

        /*for(int j = 0; j < this->insectes.size(); j++)
        {
            QObject::connect(insectes.at(j),SIGNAL(supprimerInsecte(Insecte*)),composition[i],SLOT(supprimerInsecte(Insecte*)));
        }*/
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
    }
}

QVector<Insecte *> VagueConcrete::getInsectes(bool onlyOnScene)
{
    return this->insectes;
}

void VagueConcrete::setInsectes(QVector<Insecte *> insectes)
{
    this->insectes += insectes;
}

QVector<Insecte *> VagueCompose::getInsectes(bool onlyOnScene)
{
    /*for(int i = composition.size()-1; i >= 0; i--)
    {
        composition[i]->insectes += composition.at(i)->getInsectes();
    }
    return this->insectes;*/

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
        this->scene->addItem(this->insectes.at(counterInsecte));
        counterInsecte++;
    }
}

void VagueConcrete::supprimerInsecte(Insecte *I, bool vivant)
{
    //std::cout << insectes.size() << std::endl;
    for(int i = 0; i < insectes.size() ; ++i)
    {

        if(insectes.at(i) == I)
        {
            //this->scene->removeItem(I);
            this->scene->removeInsecte(I,vivant);
            insectes.remove(i);
            this->counterInsecte--;
            break;
        }
    }
    emit this->miseAJour();
}

/*void VagueCompose::supprimerInsecte(Insecte *I)
{
    std::cout << "Je rentre" << std::endl;
    for(int i = 0; i < insectes.size() ; ++i)
    {

        if(insectes.at(i) == I)
        {
            insectes.remove(i);
           // QObject::disconnect(ptr);
            this->scene->removeItem(I);
            this->counterInsecte--;
            break;
        }
    }
    emit this->miseAJour();
}*/

}
