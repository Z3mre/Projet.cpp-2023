#include "ArrayList.h"

//----------------------------------
//-------CONSTRUCTEURS
//----------------------------------
template<class T>
ArrayList<T>::ArrayList() : ptete(NULL)
{
#ifdef DEBUG
    cout << ">>> ArrayList : constructeur par defaut  <<<" << endl;
#endif
}

template<class T>
ArrayList<T>::ArrayList(const ArrayList<T> &a)
{
#ifdef DEBUG
    cout << ">>> ArrayList : constructeur de copie  <<<" << endl;
#endif

    ptete = NULL;

    Cellule<T> *pt = NULL;
    Cellule<T> *pa = a.ptete;

    while (pa)
    {
        if (!ptete)
        {
            // Si la liste est vide, crée le premier élément
            ptete = new Cellule<T>{pa->valeur, NULL};
            pt = ptete;
        }
        else
        {
            // Ajoute un nouvel élément à la liste
            pt->suivant = new Cellule<T>{pa->valeur, NULL};
            pt = pt->suivant;
        }

        pa = pa->suivant;
    }
}

//----------------------------------
//-------DESTRUCTEUR
//----------------------------------
template<class T>
ArrayList<T>::~ArrayList()
{
#ifdef DEBUG
    cout << ">>> ArrayList : destructeur  <<<" << endl;
#endif

    Cellule<T> *pCur = ptete;
    Cellule<T> *pPrec = NULL;

    while (pCur)
    {
        pPrec = pCur;
        pCur = pCur->suivant;
        delete pPrec;
    }
}

//----------------------------------
//-------OPERATEURS
//----------------------------------
template<class T>
ArrayList<T> &ArrayList<T>::operator=(const ArrayList<T> &a)
{
    if (this != &a)
    {
        // Libère la mémoire occupée par l'objet actuel
        while (ptete)
        {
            Cellule<T> *temp = ptete;
            ptete = ptete->suivant;
            delete temp;
        }

        // Copie les éléments de l'objet source
        Cellule<T> *pparcSource = a.ptete;
        Cellule<T> *pparcDestination = NULL;

        while (pparcSource)
        {
            if (!pparcDestination)
            {
                // Si la liste de destination est vide, crée le premier élément
                ptete = new Cellule<T>(pparcSource->valeur, NULL);
                pparcDestination = ptete;
            }
            else
            {
                // Ajoute un nouvel élément à la liste de destination
                pparcDestination->suivant = new Cellule<T>(pparcSource->valeur, NULL);
                pparcDestination = pparcDestination->suivant;
            }

            pparcSource = pparcSource->suivant;
        }
    }

    return *this;
}

//----------------------------------
//-------GETTERS
//----------------------------------
template<class T>
int ArrayList<T>::getNombreElements() const
{
    int nb = 0;
    Cellule<T> *pparc = ptete;

    while (pparc)
    {
        nb++;
        pparc = pparc->suivant;
    }

    return nb;
}

template<class T>
T &ArrayList<T>::getElement(int ind)
{
    int i = 0;
    Cellule<T> *pparc = ptete;

    while (pparc)
    {
        if (i == ind)
        {
            return pparc->valeur;
        }
        pparc = pparc->suivant;
        i++;
    }

    // Gérer le cas où l'indice est hors limites
    // Vous pouvez jeter une exception ou renvoyer une valeur par défaut, selon vos besoins.
    throw std::out_of_range("Indice hors limites");
}

//----------------------------------
//-------METHODES D'INSTANCES
//----------------------------------
template<class T>
bool ArrayList<T>::estVide()
{
    return ptete == NULL;
}

template<class T>
void ArrayList<T>::insereElement(const T &val)
{
    if (!ptete)
    {
        ptete = new Cellule<T>(val, NULL);
    }
    else
    {
        Cellule<T> *pparc = ptete;
        while (pparc->suivant)
        {
            pparc = pparc->suivant;
        }
        pparc->suivant = new Cellule<T>(val, NULL);
    }
}

template<class T>
T ArrayList<T>::retireElement(int ind)
{
    if (ind < 0 || ind >= getNombreElements())
    {
        // Gérer le cas où l'indice est hors limites
        throw out_of_range("Indice hors limites");
    }

    T val;
    Cellule<T> *pparc = ptete;
    Cellule<T> *pparcPrec = NULL;

    for (int i = 0; i < ind; i++)
    {
        pparcPrec = pparc;
        pparc = pparc->suivant;
    }

    if (pparcPrec)
    {
        // Cas où l'élément à supprimer n'est pas le premier
        pparcPrec->suivant = pparc->suivant;
    }
    else
    {
        // Cas où l'élément à supprimer est le premier
        ptete = pparc->suivant;
    }

    val = pparc->valeur;
    delete pparc;

    return val;
}

template<class T>
void ArrayList<T>::Affiche()
{
    Cellule<T> *pparc = ptete;
    cout << "( ";

    while (pparc)
    {
        cout << pparc->valeur << " , ";
        pparc = pparc->suivant;
    }

    cout << ")\n";
}

// Instanciation des templates pour les types spécifiques utilisés
template class ArrayList<int>;

#include "Couleur.h"
template class ArrayList<Couleur>;

#include "ImageB.h"
template class ArrayList<ImageB>;

#include "ImageNG.h"
template class ArrayList<ImageNG>;

#include "ImageRGB.h"
template class ArrayList<ImageRGB>;
