#ifndef VAGUE_H
#define VAGUE_H

#include <string>
#include "insecte.h"
#include "insectefactory.h"
#include <QVector>

using namespace std;

namespace TOWERDEFENSE {

class Vague
{

public:
    Vague();

    virtual void buildVague(int initX,int initY, QList<int> * path) = 0;
    virtual QVector<Insecte *> getInsectes() const = 0;
};

class VagueCompose : public Vague
{

private:
    QVector<Vague *> composition;

public:
    VagueCompose(QVector<Vague *>);
    void buildVague(int initX,int initY, QList<int> * path);
    QVector<Insecte *> getInsectes() const;

};

class VagueConcrete : public Vague
{
private:
    int type;
    int nombre;
    int taille;
    int intervalle;
    string commentaire;
    QVector<Insecte *> insectes;

public:
    VagueConcrete(int type, int nombre, int taille, int intervalle, string commentaire);
    void buildVague(int initX,int initY, QList<int> * path);
    QVector<Insecte *> getInsectes() const;
};

}

#endif // VAGUE_H
