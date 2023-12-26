#include "PhotoShop.h"
#include "Iterateur.h" // Assurez-vous d'inclure le fichier d'en-tête de la classe Iterateur

int PhotoShop::numCourant = 1; // Initialisation de la variable statique

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
    while (!it.end())
    {
        it->Affiche(); // Utilisez l'opérateur -> pour accéder aux membres de l'objet pointé par le pointeur
        it++;
    }
}

void PhotoShop::dessineImages() const
{
    Iterateur<Image*> it(images);
    while (!it.end())
    {
        it->Dessine(); // Utilisez l'opérateur -> pour accéder aux membres de l'objet pointé par le pointeur
        it++;
    }
}

// Méthode pour réinitialiser la PhotoShop
void PhotoShop::reset()
{
    // Libérer la mémoire associée à la liste
    for (Image* image : images)
    {
        delete image;
    }

    // Vider la liste (libère automatiquement la mémoire)
    images.clear();

    // Réinitialiser numCourant à 1
    numCourant = 1;
}
