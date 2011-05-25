#include "fichier.h"

namespace TOWERDEFENSE{

Fichier::Fichier()
{
    carte = new int*[16];
    //vague = new double*[20];

    //initialisation de la carte
    for(int i = 0; i < 16; ++i)
    {
        carte[i] = new int[16];
        for(int j = 0; j < 16; ++j)
        {
            carte[i][j] = 0;
        }
    }
}

Fichier::~Fichier()
{
    delete[] carte;
}

int** Fichier::getCarte()const { return carte; }

QVector<Vague *> Fichier::getVagues() const { return vagues; }

QList<int> * Fichier::getPath() const { return path; }

bool Fichier::chargerCarte(const std::string & chemin)
{
    std::ifstream fichier(chemin.c_str(), std::ios::in);  // on ouvre le fichier en lecture

        if(fichier)  // si l'ouverture a réussi
        {
            int i(0),j(0);

            while(!fichier.eof())
            {
                if(i == 16)
                {
                    ++j;
                    i = 0;
                }
                fichier >> carte[i][j];
                ++i;
            }

            fichier.close();  // on ferme le fichier
            return true;
        }
        else  return false;
}

bool Fichier::chargerPath()
{
    int departX,departY,i,j;

    this->path = new QList<int>();

    // recherche du départ, détermination de la direction du départ.
    bool found = false;
    for(i=0; i<16 && !found; i++)
    {
        for(j=0; j < 16 && !found; j++)
        {
            if(carte[j][i] < 32 && carte[j][i] >= 17)
            {
                found = true;
            }
        }
    }

    departX = max(0,j-1);
    departY = max(0,i-1);

    this->path->push_back(carte[departX][departY] % 16);

    this->path->append(buildPathRecursively(departX,departY,departX,departY));

    return true;
}

QList<int> Fichier::buildPathRecursively(int currX, int currY, int prevX, int prevY)
{

    QList<int> temp;
    int newX, newY;

    if(currX-1 >= 0 && currX-1 != prevX && carte[currX-1][currY] >= 1 && carte[currX-1][currY] <= 10)
    {
        newX = currX-1;
        newY = currY;
    }
    else if(currX+1 <= 16 && currX+1 != prevX && carte[currX+1][currY] >= 1 && carte[currX+1][currY] <= 10)
    {
        newX = currX+1;
        newY = currY;
    }
    else if(currY-1 >= 0 && currY-1 != prevY && carte[currX][currY-1] >= 1 && carte[currX][currY-1] <= 10)
    {
        newX = currX;
        newY = currY-1;
    }
    else if(currY+1 <= 16 && currY+1 != prevY && carte[currX][currY+1] >= 1 && carte[currX][currY+1] <= 10)
    {
        newX = currX;
        newY = currY+1;
    }
    else
    {
        return temp;
    }

    temp.push_back(carte[newX][newY]);

    temp.append(buildPathRecursively(newX,newY,currX,currY));

    return temp;
}

bool Fichier::chargerVague(const std::string &chemin)
{

    QFile descripteurFichier(chemin.c_str());
    if(descripteurFichier.open(QIODevice::ReadOnly))
    {
        // Le fichier a ete ouvert correctement
        QString contenu = descripteurFichier.readAll();
        QStringList lignes = contenu.split("\n");
        QStringList vagueParse;
        QStringList parameters;
        string commentaire;
        float taille;
        int type;
        int nombre;
        int intervalle;

        QVector<Vague *> composition, vagueContainer;
        Vague * tempVague;

        for(int i=0; i<lignes.size(); i++)
        {
            vagueParse = lignes.at(i).split(";");
            composition.clear();

            for(int j=0; j<vagueParse.size(); j++)
            {
                if(j == 0)
                {
                    commentaire = vagueParse.at(j).toStdString();
                }
                else
                {
                    parameters = vagueParse.at(j).split(":");

                    for(int k=0; k<parameters.size(); k++)
                    {
                        if(k == 0)
                        {
                            if(parameters.at(k).compare("fourmi") == 0)
                            {
                                type = InsecteFactory::TYPE_FOURMI;
                            }
                            else if(parameters.at(k).compare("guepe") == 0)
                            {
                                type = InsecteFactory::TYPE_GUEPE;
                            }
                            else if(parameters.at(k).compare("cafard") == 0)
                            {
                                type = InsecteFactory::TYPE_CAFARD;
                            }
                            else if(parameters.at(k).compare("moustique") == 0)
                            {
                                type = InsecteFactory::TYPE_MOUSTIQUE;
                            }
                            else
                            {
                                throw runtime_error(0);
                            }
                        }
                        else if(k == 1)
                        {
                            taille = parameters.at(k).toFloat();
                        }
                        else if(k == 2)
                        {
                            nombre = parameters.at(k).toInt();
                        }
                        else if(k == 3)
                        {
                            intervalle = parameters.at(k).toInt();
                        }
                    }

                    tempVague = new VagueConcrete(type,nombre,taille,intervalle,commentaire);
                    composition.append(tempVague);
                }
            }

            if(composition.size() > 1)
            {
                tempVague = new VagueCompose(composition);
            }

            vagueContainer.append(tempVague);
        }

        this->vagues = vagueContainer;
        return true;
    }
    else
    {
        return false;
    }

    /*std::ifstream fichier(chemin.c_str(), std::ios::in);  // on ouvre le fichier en lecture

        if(fichier)  // si l'ouverture a réussi
        {

            int j(0);
            std::string ligne;
            QString commentaire;
            QString typeInsecte;
            int type;
            QString taille;
            QString nombre;
            QString intervalle;
            Vague * vague;

            QVector<Vague*> composition;
            QVector<Vague*> vagues;



            while(getline(fichier, ligne))
            {
                j = 0;

                // récupération du commentaire
                commentaire.clear();
                while(ligne[j] != ';')
                {
                    commentaire.push_back(QChar(ligne[j]));
                    j++;
                }

                j++;

                //composition.clear(); // on vide le vecteur temporaire de composition

                while(ligne[j] != '\n' && ligne[j] != '\r')
                {
                    typeInsecte.clear();
                    while(ligne[j] != ':')
                    {
                        typeInsecte.push_back(QChar(ligne[j]));
                        j++;
                    }

                    j++;

                    if(typeInsecte.compare("fourmi"))
                    {
                        type = InsecteFactory::TYPE_FOURMI;
                    }
                    else if(typeInsecte.compare("guepe"))
                    {
                        type = InsecteFactory::TYPE_GUEPE;
                    }
                    else if(typeInsecte.compare("cafard"))
                    {
                        type = InsecteFactory::TYPE_CAFARD;
                    }
                    else if(typeInsecte.compare("moustique"))
                    {
                        type = InsecteFactory::TYPE_MOUSTIQUE;
                    }
                    else
                    {
                        throw runtime_error(0);
                    }

                    taille.clear();
                    while(ligne[j] != ':')
                    {
                        taille.push_back(QChar(ligne[j]));
                        j++;
                    }

                    j++;

                    nombre.clear();
                    while(ligne[j] != ':')
                    {
                        nombre.push_back(QChar(ligne[j]));
                        j++;
                    }

                    j++;

                    intervalle.clear();
                    while(ligne[j] != ';' && ligne[j] != '\n')
                    {
                        intervalle.push_back(QChar(ligne[j]));
                        j++;
                    }

                    vague = new VagueConcrete(type,nombre.toInt(),taille.toInt(),intervalle.toInt(),commentaire.toStdString());
                    composition.push_back(vague);


                    j++;
                    std::cout << ligne[j] << endl;
                }

                // si on a une vague composée
                if(composition.size() > 1)
                {
                    vague = new VagueCompose(composition);
                }

                vagues.push_back(vague);
            }

            this->vagues = vagues;
            return true;
        }
        else
        {
            return false;
        }*/

}

}
