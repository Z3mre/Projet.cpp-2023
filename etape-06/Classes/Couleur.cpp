#include "Couleur.h"


#include <string.h>

using namespace std;

const Couleur Couleur::ROUGE(255, 0, 0);
const Couleur Couleur::VERT(0, 255, 0);
const Couleur Couleur::BLEU(0, 0, 255);
const Couleur Couleur::BLANC(255, 255, 255);
const Couleur Couleur::NOIR(0, 0, 0);

//----------------------------------
//-------CONSTRUCTEUR
//----------------------------------

Couleur::Couleur()
{
#ifdef DEBUG
     // cout << ">>> Couleur: constructeur par defaut <<<" << endl;
#endif

    setRouge(0);
    setVert(0);
    setBleu(0);
}

Couleur::Couleur(int r, int v, int b)
{
#ifdef DEBUG
     // cout << ">>> Couleur: constructeur d'initialisation <<<" << endl;
#endif
    setRouge(r);
    setVert(v);
    setBleu(b);
}

Couleur::Couleur(const Couleur &c)
{
#ifdef DEBUG
    // cout << ">>> Couleur: constructeur de copie <<<" << endl;
#endif

    setRouge(c.getRouge());
    setVert(c.getVert());
    setBleu(c.getBleu());
}

//----------------------------------
//-------DESTRUCTEUR
//----------------------------------

Couleur::~Couleur()
{
#ifdef DEBUG
    // cout << ">>> Couleur: Destructeur <<<" << endl;
#endif
}

//----------------------------------
//-------OPERATEURS
//----------------------------------

ostream &operator<<(ostream &s, const Couleur &m)
{
    s << "[rouge : " << m.rouge << " | vert : " << m.vert << " | bleu : " << m.bleu << "]";
    return s;
}

//----------------------------------
//-------SETTERS
//----------------------------------

void Couleur::setRouge(int r) 
{
    if(r<0 || r>255) throw(RGBException(r,"Couleur rouge non valide"));
    rouge = r;


}

void Couleur::setVert(int v) 
{
    if(v<0 || v>255) throw(RGBException(v,"Couleur verte non valide"));
    vert = v;
}

void Couleur::setBleu(int b) 
{
    if(b<0 || b>255) throw(RGBException(b,"Couleur bleue non valide"));
    bleu = b;
}

//----------------------------------
//-------GETTERS
//----------------------------------

int Couleur::getRouge() const
{
    return rouge;
}

int Couleur::getVert() const
{
    return vert;
}

int Couleur::getBleu() const
{
    return bleu;
}

//----------------------------------
//-------METHODES D INSTANCES
//----------------------------------

void Couleur::Affiche() const
{
    cout << (*this) << endl;
}
