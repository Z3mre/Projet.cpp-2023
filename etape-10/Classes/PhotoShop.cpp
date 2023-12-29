#include "PhotoShop.h"

PhotoShop PhotoShop::instance;
int PhotoShop::numCourant=1;
// Constructeur par défaut
PhotoShop::PhotoShop() {}

// Destructeur
PhotoShop::~PhotoShop()
{
    reset();
}

// Méthode pour ajouter une image
void PhotoShop::ajouteImage(Image* pImage)
{
    pImage->setId(numCourant);
    numCourant++;

    images.insereElement(pImage);
}

// Méthodes pour supprimer une image par indice et par id
void PhotoShop::supprimeImageParIndice(int ind)
{
    try
    {
        // Utilisez la méthode retireElement pour retirer l'image du conteneur
        Image* imageToDelete = images.retireElement(ind);

        // Utilisez delete pour libérer la mémoire de l'objet image
        delete imageToDelete;
    }
    catch (const out_of_range& e)
    {
        cout << "Image introuvable" << endl;
    }
}

void PhotoShop::supprimeImageParId(int id)
{
    try
    {
        // Utilisez la méthode retireElement pour retirer l'image du conteneur
        Image* imageToDelete = images.retireElement(id);

        // Utilisez delete pour libérer la mémoire de l'objet image
        delete imageToDelete;
    }
    catch (const out_of_range& e)
    {
        cout << "Image introuvable" << endl;
    }
}

// Méthodes pour récupérer une image par indice et par id
Image* PhotoShop::getImageParIndice(int indice)
{
    try
    {
        return images.getElement(indice);
    }
    catch (const out_of_range& e)
    {
        cout << "Image introuvable" << endl;
        return nullptr;
    }
}

Image* PhotoShop::getImageParId(int id)
{
    try
    {
        return images.getElement(id);
    }
    catch (const out_of_range& e)
    {
        cout << "Image introuvable" << endl;
        return nullptr;
    }
}

// Méthodes pour afficher et dessiner les images
void PhotoShop::afficheImages() const
{
    Iterateur<Image*> it(images);
    for (it.reset() ; !it.end() ; it++)
    {
        Image* i = (Image*) it;
        i->Affiche();

    }
}

void PhotoShop::dessineImages() const
{
    Iterateur<Image*> it(images);
    for (it.reset() ; !it.end() ; it++)
    {
        Image* i = (Image*) it;
        i->Dessine();

    }
}

// Méthode pour réinitialiser la PhotoShop
void PhotoShop::reset()
{
    // Libérer la mémoire associée à la liste
    for (Iterateur<Image*> it(images); !it.end(); ++it)
    {
        delete it;
    }

    // Vider la liste (libère automatiquement la mémoire)
    images.estVide();

    // Réinitialiser numCourant à 1
    numCourant = 1;
}

// METHODE STATIQUE

PhotoShop& PhotoShop::getInstance()
{
    return instance;
}
