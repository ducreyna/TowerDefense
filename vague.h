#ifndef VAGUE_H
#define VAGUE_H

#include <string>
#include "insecte.h"
#include "insectefactory.h"
#include <QVector>
#include <QTimer>
#include "myqgraphicsscene.h"

using namespace std;

namespace TOWERDEFENSE {

 class Vague : public QObject
{
     Q_OBJECT
public:
    Vague();
    virtual void buildVague(int initX,int initY, QList<int> * path, MyQGraphicsScene* scene) = 0;
    virtual QVector<Insecte *> getInsectes(bool onlyOnScene = false) = 0;
    virtual void launchVague() = 0;

signals:
    void miseAJour();

};

class VagueCompose : public Vague
{
Q_OBJECT
private:
    QVector<Vague *> composition;

public:
    VagueCompose(QVector<Vague *>);
    void buildVague(int initX,int initY, QList<int> * path, MyQGraphicsScene * scene);
    QVector<Insecte *> getInsectes(bool onlyOnScene = false);
    void launchVague();
};

class VagueConcrete : public Vague
{ Q_OBJECT
private:
    int type;
    int nombre;
    double taille;
    int intervalle;
    int counterInsecte;
    QTimer * timer;
    string commentaire;
    QVector<Insecte *> insectes;
    MyQGraphicsScene * scene;

public:
    VagueConcrete(int type, int nombre, double taille, int intervalle, string commentaire);
    void buildVague(int initX,int initY, QList<int> * path, MyQGraphicsScene * scene);
    QVector<Insecte *> getInsectes(bool onlyOnScene = false);
    void launchVague();

public slots:
    void ajouterInsecte();
    void supprimerInsecte(Insecte* I);

signals:
    void ajouterInsecteSurScene(Insecte * i);
};

}

#endif // VAGUE_H
