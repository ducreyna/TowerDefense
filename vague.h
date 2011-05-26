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
protected:
     QVector<Insecte*> insectes;

public:
    Vague();
    virtual void buildVague(int initX,int initY, QList<int> * path, MyQGraphicsScene* scene) = 0;
    virtual QVector<Insecte *> getInsectes(bool onlyOnScene = false) const = 0;
    virtual void launchVague() = 0;
    virtual void display() const = 0;
};

class VagueCompose : public Vague
{

private:
    QVector<Vague *> composition;

public:
    VagueCompose(QVector<Vague *>);
    void buildVague(int initX,int initY, QList<int> * path, MyQGraphicsScene * scene);
    QVector<Insecte *> getInsectes(bool onlyOnScene = false) const;
    void launchVague();
    void display() const;
};

class VagueConcrete : public Vague
{ Q_OBJECT
private:
    int type;
    int nombre;
    int taille;
    int intervalle;
    int counterInsecte;
    QTimer * timer;
    string commentaire;
    //QVector<Insecte *> insectes;
    MyQGraphicsScene * scene;

public:
    VagueConcrete(int type, int nombre, int taille, int intervalle, string commentaire);
    void buildVague(int initX,int initY, QList<int> * path, MyQGraphicsScene * scene);
    QVector<Insecte *> getInsectes(bool onlyOnScene = false) const;
    void launchVague();
    void display() const;

public slots:
    void ajouterInsecte();

signals:
    void ajouterInsecteSurScene(Insecte * i);
};

}

#endif // VAGUE_H
